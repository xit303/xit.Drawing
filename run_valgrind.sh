#!/bin/bash
# Valgrind runner script with suppressions
# Usage: ./run_valgrind.sh [program] [args...]

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
SUPPRESSIONS="$SCRIPT_DIR/valgrind-suppressions.supp"

if [ ! -f "$SUPPRESSIONS" ]; then
    echo "Error: Suppression file not found: $SUPPRESSIONS"
    exit 1
fi

if [ $# -eq 0 ]; then
    echo "Usage: $0 <program> [arguments...]"
    echo "Example: $0 ./.bin/Debug/PassMaga"
    exit 1
fi

echo "Running Valgrind with suppressions..."
echo "Suppression file: $SUPPRESSIONS"
echo "Program: $1"
echo "Arguments: ${@:2}"
echo "----------------------------------------"

exec valgrind \
    --suppressions="$SUPPRESSIONS" \
    --leak-check=full \
    --show-leak-kinds=all \
    --track-origins=yes \
    --verbose \
    --error-exitcode=1 \
    "$@"
