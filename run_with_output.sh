#!/bin/bash

# Script to run testWindow with output redirection
# Usage: ./run_with_output.sh [output_file]

OUTPUT_FILE="${1:-debug_output.txt}"
PROGRAM="./testWindow/.bin/Debug/testWindow"

echo "Running $PROGRAM..."
echo "Output will be saved to: $OUTPUT_FILE"
echo "=========================================="

cd testWindow
if [ -f ".bin/Debug/testWindow" ]; then
    ./.bin/Debug/testWindow > "../$OUTPUT_FILE" 2>&1
    echo "Program finished. Output saved to $OUTPUT_FILE"
else
    echo "Error: testWindow executable not found. Please build first with 'xmake testWindow'"
    exit 1
fi
