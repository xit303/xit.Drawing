#!/bin/bash

# Script to find potentially problematic static STL containers in C++ code
# Usage: ./find_static_containers.sh /path/to/library

if [ $# -ne 1 ]; then
    echo "Usage: $0 <library_directory>"
    echo "Example: $0 /home/xor/workspace_pc/NewLibrary/xit.Drawing"
    exit 1
fi

LIBRARY_DIR="$1"

if [ ! -d "$LIBRARY_DIR" ]; then
    echo "Error: Directory $LIBRARY_DIR does not exist"
    exit 1
fi

echo "Searching for potentially problematic static STL containers in: $LIBRARY_DIR"
echo "=================================================================="

echo ""
echo "1. Static STL containers with strings (excluding functions, references, and Meyer's singletons):"
grep -rn "static.*std::.*<.*std::.*string" "$LIBRARY_DIR" --include="*.cpp" --include="*.h" 2>/dev/null | grep -v "(" | grep -v "static.*&.*(" | grep -v "static.*&" | grep ";" | grep -v "Get.*Map\|Get.*List\|Get.*Vector"

echo ""
echo "2. Static STL containers with function objects (excluding functions, references, and Meyer's singletons):"
grep -rn "static.*std::.*<.*std::function" "$LIBRARY_DIR" --include="*.cpp" --include="*.h" 2>/dev/null | grep -v "(" | grep -v "static.*&.*(" | grep -v "static.*&" | grep ";" | grep -v "Get.*Map\|Get.*List\|Get.*Vector"

echo ""
echo "3. General static STL containers (excluding functions, references, and Meyer's singletons):"
grep -rn "static.*std::\(list\|vector\|queue\|deque\|map\|set\)" "$LIBRARY_DIR" --include="*.cpp" --include="*.h" 2>/dev/null | grep -v "(" | grep -v "static.*&.*(" | grep -v "static.*&" | grep ";" | grep -v "Get.*Map\|Get.*List\|Get.*Vector"

echo ""
echo "4. Static member variable declarations (excluding functions, references, and Meyer's singletons):"
grep -rn "static.*std::" "$LIBRARY_DIR" --include="*.cpp" --include="*.h" 2>/dev/null | grep -E "(list|vector|queue|deque|map|set)" | grep -v "(" | grep -v "static.*&.*(" | grep -v "static.*&" | grep ";" | grep -v "Get.*Map\|Get.*List\|Get.*Vector"

echo ""
echo "=================================================================="
echo "PROBLEMATIC static member variable declarations found above."
echo "These should be converted to use Meyer's singleton pattern or dynamic allocation"
echo "to avoid static destruction order issues."
echo ""
echo "SAFE patterns (ignored by this script):"
echo "  - static ReturnType& GetContainer() { static Container c; return c; }  // Meyer's singleton"
echo "  - static void Function(std::vector<T>& param);                         // Function parameters"  
echo "  - static std::vector<T> Function();                                   // Function return types"
echo "  - Static locals inside Get*Map/Get*List/Get*Vector functions          // Meyer's singleton internals"
