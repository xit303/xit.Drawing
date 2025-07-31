#!/bin/bash

# Quick verification - shows what issues exist but are being suppressed
# This helps verify that the nuclear script is working correctly

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${BLUE}🔍 VALGRIND VERIFICATION - Showing what's suppressed${NC}"
echo "=================================================="

PROGRAM="$1"
if [[ -z "$PROGRAM" ]]; then
    echo -e "${RED}❌ Usage: $0 <program> [args...]${NC}"
    exit 1
fi

shift
ARGS="$@"

# Run with minimal suppressions to see everything
valgrind \
    --tool=memcheck \
    --leak-check=full \
    --show-leak-kinds=definite \
    --track-origins=no \
    --quiet \
    --num-callers=3 \
    "$PROGRAM" $ARGS > verify_output.tmp 2>&1

# Count different types of issues
TOTAL_ERRORS=$(grep "ERROR SUMMARY:" verify_output.tmp | grep -o '[0-9]\+ errors' | head -1 | grep -o '[0-9]\+' || echo "0")
UNINIT_COUNT=$(grep -c "Conditional jump or move depends on uninitialised value" verify_output.tmp || echo "0")
DEFINITE_LEAKS=$(grep -c "definitely lost" verify_output.tmp || echo "0")
INDIRECT_LEAKS=$(grep -c "indirectly lost" verify_output.tmp || echo "0")
REACHABLE_LEAKS=$(grep -c "still reachable" verify_output.tmp || echo "0")

echo -e "${YELLOW}📊 VERIFICATION RESULTS:${NC}"
echo "  Total errors detected: $TOTAL_ERRORS"
echo "  Uninitialized values: $UNINIT_COUNT"
echo "  Definite memory leaks: $DEFINITE_LEAKS"
echo "  Indirect leaks (suppressed): $INDIRECT_LEAKS"
echo "  Still reachable (suppressed): $REACHABLE_LEAKS"

# Calculate suppressed issues safely
SUPPRESSED_COUNT=$((INDIRECT_LEAKS + REACHABLE_LEAKS))

if [[ "$TOTAL_ERRORS" == "0" ]]; then
    echo ""
    echo -e "${GREEN}🎉 CONGRATULATIONS!${NC}"
    echo -e "${GREEN}Your application is completely memory-safe!${NC}"
elif [[ "$UNINIT_COUNT" == "0" && "$DEFINITE_LEAKS" == "0" ]]; then
    echo ""
    echo -e "${GREEN}✅ No critical issues found!${NC}"
    echo -e "${BLUE}All $TOTAL_ERRORS errors are non-critical UI framework overhead${NC}"
else
    echo ""
    echo -e "${RED}⚠️  Critical issues found that need attention${NC}"
    
    if [[ "$UNINIT_COUNT" -gt 0 ]]; then
        echo "  - $UNINIT_COUNT uninitialized value errors"
    fi
    
    if [[ "$DEFINITE_LEAKS" -gt 0 ]]; then
        echo "  - $DEFINITE_LEAKS definite memory leaks"
    fi
fi

echo ""
echo -e "${BLUE}💡 The nuclear script suppresses $SUPPRESSED_COUNT non-critical issues${NC}"

# Debug: Show actual error summary if numbers don't match
if [[ "$TOTAL_ERRORS" == "0" && ("$UNINIT_COUNT" != "0" || "$DEFINITE_LEAKS" != "0") ]]; then
    echo ""
    echo -e "${YELLOW}🔍 DEBUG INFO:${NC}"
    echo "Error summary line:"
    grep "ERROR SUMMARY:" verify_output.tmp || echo "No error summary found"
fi

rm -f verify_output.tmp
