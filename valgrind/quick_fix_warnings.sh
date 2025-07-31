#!/bin/bash
# Quick fixes for common warning patterns in xit.Drawing

echo "🔧 Applying quick fixes for common warning patterns..."

# Create backup directory
mkdir -p .warning_fixes_backup/$(date +%Y%m%d_%H%M%S)

# Counter for fixes
fixes=0

echo "📝 Fixing unused parameter warnings in virtual functions..."

# Fix unused EventArgs parameters in virtual functions
find . -name "*.h" -o -name "*.hpp" | grep -v lib/ | while read file; do
    if grep -q "virtual.*EventArgs.*{}" "$file"; then
        cp "$file" ".warning_fixes_backup/$(date +%Y%m%d_%H%M%S)/$(basename $file)"
        sed -i 's/virtual void \([A-Za-z]*\)(EventArgs &\([a-z][a-zA-Z]*\)) {}/virtual void \1(EventArgs \&\2) { (void)\2; }/g' "$file"
        echo "  ✅ Fixed unused EventArgs in $file"
        ((fixes++))
    fi
done

echo "🏗️  Fixing simple member initialization patterns..."

# Fix simple constructor patterns: Constructor() { member = value; }
find . -name "*.h" -o -name "*.hpp" -o -name "*.cpp" | grep -v lib/ | while read file; do
    # Look for pattern: Constructor() { singleMember = value; }
    if grep -q -E "[A-Za-z_][A-Za-z0-9_]*\(\)\s*\{\s*[a-zA-Z_][a-zA-Z0-9_]*\s*=\s*[^;]*;\s*\}" "$file"; then
        cp "$file" ".warning_fixes_backup/$(date +%Y%m%d_%H%M%S)/$(basename $file).$(date +%s)" 2>/dev/null || true
        # Simple single-member initialization
        sed -i -E 's/([A-Za-z_][A-Za-z0-9_]*)\(\)\s*\{\s*([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*([^;]*);?\s*\}/\1() : \2(\3) {}/g' "$file"
        echo "  ✅ Fixed constructor initialization in $file"
        ((fixes++))
    fi
done

echo "🎯 Fixing Event initialization patterns..."

# Fix Event member initialization - add Event() to initialization lists
find . -name "*.h" -o -name "*.hpp" | grep -v lib/ | while read file; do
    # Look for constructors that might need Event initialization
    if grep -q "Event<.*>" "$file" && grep -q "should be initialized" "$file" 2>/dev/null || true; then
        # This is more complex, we'll create a targeted fix
        echo "  📍 Found Event initialization issue in $file (manual review needed)"
    fi
done

echo "🔄 Creating member initialization list templates..."

# Create a helper file with common patterns
cat > .member_init_patterns.txt << 'EOF'
Common patterns to fix manually:

1. Event members:
   OLD: EventName() {}
   NEW: EventName() : EventName() {}

2. Multiple members:
   OLD: Constructor() { a = 1; b = 2; }
   NEW: Constructor() : a(1), b(2) {}

3. Base class + members:
   OLD: Derived(const Derived& other) : member(other.member) {}
   NEW: Derived(const Derived& other) : BaseClass(other), member(other.member) {}

4. Unused parameters:
   OLD: virtual void OnSomething(EventArgs &e) {}
   NEW: virtual void OnSomething(EventArgs &e) { (void)e; }
EOF

echo "📋 Summary:"
echo "  - Applied $fixes automatic fixes"
echo "  - Created backups in .warning_fixes_backup/"
echo "  - See .member_init_patterns.txt for manual fix patterns"

echo "🧪 Testing build after fixes..."
if command -v xmake >/dev/null 2>&1; then
    echo "Running quick build test..."
    xmake clean >/dev/null 2>&1
    if xmake 2>&1 | head -20; then
        echo "✅ Build test completed"
    else
        echo "⚠️  Build issues detected - check the output above"
    fi
else
    echo "ℹ️  xmake not found, skipping build test"
fi

echo ""
echo "🎉 Quick fixes completed!"
echo "Next steps:"
echo "  1. Review the build output above"
echo "  2. Check .member_init_patterns.txt for manual fixes"
echo "  3. Run: python3 fix_warnings.py --dry-run for more advanced fixes"
echo "  4. Test with: xmake clean && xmake"
