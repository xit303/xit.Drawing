#!/bin/bash

# Detailed diagnostic - shows exactly what Valgrind is finding
# This will help us understand why nuclear script shows nothing

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${RED}🔍 DETAILED VALGRIND DIAGNOSTIC${NC}"
echo "==============================="

PROGRAM="$1"
if [[ -z "$PROGRAM" ]]; then
    echo -e "${RED}❌ Usage: $0 <program> [args...]${NC}"
    exit 1
fi

shift
ARGS="$@"

echo -e "${BLUE}Running basic Valgrind to see what's actually happening...${NC}"
echo ""

# Run with no suppressions to see everything
valgrind \
    --tool=memcheck \
    --leak-check=full \
    --show-leak-kinds=all \
    --track-origins=yes \
    --num-callers=6 \
    "$PROGRAM" $ARGS > diagnostic_output.tmp 2>&1

echo -e "${YELLOW}📊 DETAILED ANALYSIS:${NC}"

# Extract the error summary
ERROR_SUMMARY=$(grep "ERROR SUMMARY:" diagnostic_output.tmp || echo "No error summary found")
echo "Error Summary: $ERROR_SUMMARY"

# Count all types of issues
echo ""
echo "Issue Breakdown:"
UNINIT_COUNT=$(grep -c "Conditional jump or move depends on uninitialised value" diagnostic_output.tmp || echo "0")
INVALID_READ=$(grep -c "Invalid read" diagnostic_output.tmp || echo "0")
INVALID_WRITE=$(grep -c "Invalid write" diagnostic_output.tmp || echo "0")
DEFINITE_LEAKS=$(grep -c "definitely lost" diagnostic_output.tmp || echo "0")
INDIRECT_LEAKS=$(grep -c "indirectly lost" diagnostic_output.tmp || echo "0")
POSSIBLE_LEAKS=$(grep -c "possibly lost" diagnostic_output.tmp || echo "0")
REACHABLE_LEAKS=$(grep -c "still reachable" diagnostic_output.tmp || echo "0")

echo "  - Uninitialized values: $UNINIT_COUNT"
echo "  - Invalid reads: $INVALID_READ"
echo "  - Invalid writes: $INVALID_WRITE"
echo "  - Definite leaks: $DEFINITE_LEAKS"
echo "  - Indirect leaks: $INDIRECT_LEAKS"
echo "  - Possible leaks: $POSSIBLE_LEAKS"
echo "  - Still reachable: $REACHABLE_LEAKS"

# Show actual uninitialized value errors if any
if [[ "$UNINIT_COUNT" -gt 0 ]]; then
    echo ""
    echo -e "${RED}🚨 UNINITIALIZED VALUE ERRORS:${NC}"
    grep -A 5 "Conditional jump or move depends on uninitialised value" diagnostic_output.tmp | head -20
fi

# Show actual definite leaks if any
if [[ "$DEFINITE_LEAKS" -gt 0 ]]; then
    echo ""
    echo -e "${RED}💧 DEFINITE MEMORY LEAKS:${NC}"
    grep -A 3 "definitely lost" diagnostic_output.tmp | head -15
fi

# Check if these are in your code or libraries
echo ""
echo -e "${BLUE}🎯 ERROR LOCATION ANALYSIS:${NC}"
YOUR_CODE_ERRORS=$(grep -E "(PassMaga|AccountDataView|AccountTemplate)" diagnostic_output.tmp | wc -l)
LIBRARY_ERRORS=$(grep -E "(obj:.*lib|fun:_)" diagnostic_output.tmp | wc -l)

echo "  - Errors in YOUR code: $YOUR_CODE_ERRORS"
echo "  - Errors in libraries: $LIBRARY_ERRORS"

if [[ "$YOUR_CODE_ERRORS" -gt 0 ]]; then
    echo ""
    echo -e "${YELLOW}📋 YOUR CODE ERRORS:${NC}"
    grep -E "(PassMaga|AccountDataView|AccountTemplate)" diagnostic_output.tmp | head -10
fi

echo ""
echo -e "${BLUE}💡 CONCLUSION:${NC}"
if [[ "$UNINIT_COUNT" == "0" && "$DEFINITE_LEAKS" == "0" ]]; then
    echo -e "${GREEN}✅ No critical issues in your code!${NC}"
elif [[ "$YOUR_CODE_ERRORS" == "0" ]]; then
    echo -e "${GREEN}✅ All issues are in external libraries - your code is clean!${NC}"
else
    echo -e "${YELLOW}⚠️  Some issues may need attention in your code${NC}"
fi

# Cleanup
rm -f diagnostic_output.tmp
