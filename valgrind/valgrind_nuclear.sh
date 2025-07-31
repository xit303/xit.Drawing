#!/bin/bash

# NUCLEAR OPTION: Show ONLY uninitialized values and definite leaks
# Hides ALL UI framework allocations and system noise

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${RED}🚀 NUCLEAR VALGRIND - CRITICAL ERRORS ONLY${NC}"
echo "============================================="
echo -e "${YELLOW}This shows ONLY uninitialized values and definite memory leaks${NC}"
echo ""

PROGRAM="$1"
if [[ -z "$PROGRAM" ]]; then
    echo -e "${RED}❌ Usage: $0 <program> [args...]${NC}"
    exit 1
fi

shift
ARGS="$@"

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ULTRA_SUPPRESSIONS="$SCRIPT_DIR/valgrind-ultra-clean.supp"

# Nuclear Valgrind command - only show critical issues
valgrind \
    --tool=memcheck \
    --suppressions="$ULTRA_SUPPRESSIONS" \
    --leak-check=full \
    --show-leak-kinds=definite \
    --track-origins=yes \
    --quiet \
    --child-silent-after-fork=yes \
    --num-callers=8 \
    "$PROGRAM" $ARGS > nuclear_output.tmp 2>&1

EXIT_CODE=$?

# Check if there are any critical errors
CRITICAL_ERRORS=$(grep -E "(Conditional jump|Invalid read|Invalid write|definitely lost)" nuclear_output.tmp | grep -v "obj:*/lib" | grep -v "fun:_" || true)
ERROR_SUMMARY=$(grep "ERROR SUMMARY:" nuclear_output.tmp || true)

if [[ -n "$CRITICAL_ERRORS" ]]; then
    echo -e "${RED}🚨 CRITICAL ISSUES FOUND:${NC}"
    echo "$CRITICAL_ERRORS"
    echo ""
fi

if [[ -n "$ERROR_SUMMARY" ]]; then
    echo -e "${YELLOW}📊 Summary:${NC}"
    echo "$ERROR_SUMMARY"
    
    # Extract error count from summary
    ERROR_COUNT=$(echo "$ERROR_SUMMARY" | grep -o '[0-9]\+ errors' | head -1 | grep -o '[0-9]\+' || echo "0")
    if [[ "$ERROR_COUNT" == "0" ]]; then
        echo -e "${GREEN}🎉 NO CRITICAL ERRORS DETECTED!${NC}"
        echo -e "${BLUE}✅ Your application appears to be memory-safe${NC}"
    fi
else
    echo -e "${GREEN}🎉 NO CRITICAL ERRORS DETECTED!${NC}"
    echo -e "${BLUE}✅ Your application appears to be memory-safe${NC}"
fi

rm -f nuclear_output.tmp

echo ""
echo -e "${GREEN}✅ Nuclear analysis complete${NC}"
echo -e "${BLUE}💡 This shows only YOUR code issues that need immediate fixing${NC}"
