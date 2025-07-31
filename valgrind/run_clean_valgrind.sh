#!/bin/bash

# Clean Valgrind Runner - Focus on YOUR code issues only
# Suppresses noise from libraries and system components

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}🔍 Running Clean Valgrind Analysis${NC}"
echo "========================================"

# Default values
PROGRAM=""
ARGS=""
SUPPRESSIONS_FILE=""
LEAK_CHECK="full"
SHOW_REACHABLE="no"
TRACK_ORIGINS="yes"
VERBOSE="no"

# Find suppression file
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ULTRA_SUPPRESSIONS="$SCRIPT_DIR/valgrind-ultra-clean.supp"
NORMAL_SUPPRESSIONS="$SCRIPT_DIR/valgrind-suppressions.supp"

if [[ -f "$ULTRA_SUPPRESSIONS" ]]; then
    SUPPRESSIONS_FILE="$ULTRA_SUPPRESSIONS"
    echo -e "${GREEN}🚀 Using ULTRA-CLEAN suppressions (hides UI framework noise)${NC}"
elif [[ -f "$NORMAL_SUPPRESSIONS" ]]; then
    SUPPRESSIONS_FILE="$NORMAL_SUPPRESSIONS"
elif [[ -f "valgrind-suppressions.supp" ]]; then
    SUPPRESSIONS_FILE="valgrind-suppressions.supp"
else
    echo -e "${YELLOW}⚠️  Warning: No suppression file found${NC}"
fi

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        --program)
            PROGRAM="$2"
            shift 2
            ;;
        --args)
            ARGS="$2"
            shift 2
            ;;
        --suppressions)
            SUPPRESSIONS_FILE="$2"
            shift 2
            ;;
        --show-reachable)
            SHOW_REACHABLE="yes"
            shift
            ;;
        --full-analysis)
            # Use normal suppressions instead of ultra-clean
            SUPPRESSIONS_FILE="$NORMAL_SUPPRESSIONS"
            echo -e "${YELLOW}📊 Using FULL analysis mode (shows more details)${NC}"
            shift
            ;;
        --no-track-origins)
            TRACK_ORIGINS="no"
            shift
            ;;
        --verbose)
            VERBOSE="yes"
            shift
            ;;
        --help|-h)
            echo "Usage: $0 [options] --program <executable>"
            echo ""
            echo "Options:"
            echo "  --program <exe>          Program to analyze"
            echo "  --args <args>           Program arguments"
            echo "  --suppressions <file>   Custom suppression file"
            echo "  --show-reachable        Show 'still reachable' memory"
            echo "  --full-analysis         Use normal suppressions (more verbose)"
            echo "  --no-track-origins      Disable origin tracking (faster)"
            echo "  --verbose               Show valgrind verbose output"
            echo "  --help                  Show this help"
            echo ""
            echo "Examples:"
            echo "  $0 --program ./myapp"
            echo "  $0 --program ./myapp --args \"arg1 arg2\""
            echo "  $0 --program ./myapp --show-reachable"
            exit 0
            ;;
        *)
            if [[ -z "$PROGRAM" ]]; then
                PROGRAM="$1"
            else
                ARGS="$ARGS $1"
            fi
            shift
            ;;
    esac
done

# Check if program is provided
if [[ -z "$PROGRAM" ]]; then
    echo -e "${RED}❌ Error: No program specified${NC}"
    echo "Usage: $0 --program <executable>"
    echo "Use --help for more options"
    exit 1
fi

# Check if program exists
if [[ ! -f "$PROGRAM" ]]; then
    echo -e "${RED}❌ Error: Program not found: $PROGRAM${NC}"
    exit 1
fi

# Build Valgrind command
VALGRIND_CMD="valgrind"

# Add suppressions if available
if [[ -n "$SUPPRESSIONS_FILE" ]]; then
    VALGRIND_CMD="$VALGRIND_CMD --suppressions=$SUPPRESSIONS_FILE"
    echo -e "${GREEN}📄 Using suppressions: $SUPPRESSIONS_FILE${NC}"
fi

# Core options for clean output
VALGRIND_CMD="$VALGRIND_CMD --tool=memcheck"
VALGRIND_CMD="$VALGRIND_CMD --leak-check=$LEAK_CHECK"
VALGRIND_CMD="$VALGRIND_CMD --show-leak-kinds=definite,indirect"

# Only show reachable if requested
if [[ "$SHOW_REACHABLE" == "yes" ]]; then
    VALGRIND_CMD="$VALGRIND_CMD --show-leak-kinds=definite,indirect,possible,reachable"
    echo -e "${YELLOW}📊 Including 'still reachable' memory${NC}"
fi

# Track origins for better debugging (but slower)
if [[ "$TRACK_ORIGINS" == "yes" ]]; then
    VALGRIND_CMD="$VALGRIND_CMD --track-origins=yes"
fi

# Reduce noise
VALGRIND_CMD="$VALGRIND_CMD --child-silent-after-fork=yes"
VALGRIND_CMD="$VALGRIND_CMD --error-exitcode=1"

# Verbose mode
if [[ "$VERBOSE" == "no" ]]; then
    VALGRIND_CMD="$VALGRIND_CMD --quiet"
    VALGRIND_CMD="$VALGRIND_CMD --num-callers=10"
else
    VALGRIND_CMD="$VALGRIND_CMD --verbose"
    VALGRIND_CMD="$VALGRIND_CMD --num-callers=20"
fi

# Final command
FULL_CMD="$VALGRIND_CMD $PROGRAM $ARGS"

echo -e "${BLUE}🚀 Program: $PROGRAM${NC}"
if [[ -n "$ARGS" ]]; then
    echo -e "${BLUE}📝 Arguments: $ARGS${NC}"
fi
echo ""

# Run the analysis
echo -e "${GREEN}Running analysis...${NC}"
echo "Command: $FULL_CMD"
echo ""

# Create output file with timestamp
OUTPUT_FILE="valgrind_clean_$(date +%Y%m%d_%H%M%S).txt"

# Run Valgrind and capture output
if $FULL_CMD 2>&1 | tee "$OUTPUT_FILE"; then
    echo ""
    echo -e "${GREEN}✅ Analysis completed successfully${NC}"
    echo -e "${BLUE}📄 Full output saved to: $OUTPUT_FILE${NC}"
    
    # Quick summary
    ERROR_COUNT=$(grep -c "ERROR SUMMARY:" "$OUTPUT_FILE" 2>/dev/null || echo "0")
    if [[ $ERROR_COUNT -gt 0 ]]; then
        echo ""
        echo -e "${YELLOW}📊 Quick Summary:${NC}"
        grep "ERROR SUMMARY:" "$OUTPUT_FILE" | tail -1
        
        # Check for specific issues
        UNINIT_COUNT=$(grep -c "Conditional jump or move depends on uninitialised value" "$OUTPUT_FILE" 2>/dev/null || echo "0")
        LEAK_COUNT=$(grep -c "definitely lost\|indirectly lost" "$OUTPUT_FILE" 2>/dev/null || echo "0")
        
        if [[ $UNINIT_COUNT -gt 0 ]]; then
            echo -e "${RED}⚠️  Uninitialized value errors: $UNINIT_COUNT${NC}"
        fi
        
        if [[ $LEAK_COUNT -gt 0 ]]; then
            echo -e "${YELLOW}💧 Memory leaks detected: $LEAK_COUNT${NC}"
        fi
        
        echo ""
        echo -e "${BLUE}💡 To analyze further:${NC}"
        echo "  python3 $(dirname "$0")/analyze_valgrind.py $OUTPUT_FILE"
    fi
    
    exit 0
else
    echo ""
    echo -e "${RED}❌ Analysis completed with errors${NC}"
    echo -e "${BLUE}📄 Full output saved to: $OUTPUT_FILE${NC}"
    
    # Show summary even on failure
    if [[ -f "$OUTPUT_FILE" ]]; then
        echo ""
        echo -e "${YELLOW}📊 Error Summary:${NC}"
        grep "ERROR SUMMARY:" "$OUTPUT_FILE" | tail -1 || echo "No summary found"
    fi
    
    exit 1
fi
