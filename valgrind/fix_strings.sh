#!/bin/bash

# Script to fix string initialization issues found by Valgrind
# Specifically targets the patterns seen in AccountDataView.cpp

echo "🔧 String Initialization Fix Script"
echo "==================================="

# Function to fix a single file
fix_file() {
    local file="$1"
    local backup_file="${file}.backup.$(date +%s)"
    
    if [[ ! -f "$file" ]]; then
        echo "❌ File not found: $file"
        return 1
    fi
    
    echo "📁 Processing: $file"
    
    # Create backup
    cp "$file" "$backup_file"
    echo "💾 Backup created: $backup_file"
    
    # Apply fixes using sed
    local fixes_applied=0
    
    # Fix 1: Initialize char* pointers to nullptr
    if sed -i.tmp 's/^\(\s*\)\(char\s*\*\s*\w\+\)\s*;/\1\2 = nullptr;/g' "$file"; then
        if ! cmp -s "$file" "$file.tmp"; then
            fixes_applied=$((fixes_applied + 1))
            echo "  ✅ Fixed char* declarations"
        fi
        rm -f "$file.tmp"
    fi
    
    # Fix 2: Initialize const char* pointers to nullptr  
    if sed -i.tmp 's/^\(\s*\)\(const\s\+char\s*\*\s*\w\+\)\s*;/\1\2 = nullptr;/g' "$file"; then
        if ! cmp -s "$file" "$file.tmp"; then
            fixes_applied=$((fixes_applied + 1))
            echo "  ✅ Fixed const char* declarations"
        fi
        rm -f "$file.tmp"
    fi
    
    # Fix 3: Add null checks before string construction
    # This is more complex and requires Python script for accurate parsing
    
    if [[ $fixes_applied -gt 0 ]]; then
        echo "  🎉 Applied $fixes_applied fixes to $file"
        return 0
    else
        echo "  ℹ️  No fixes needed for $file"
        # Remove backup if no changes
        rm -f "$backup_file"
        return 1
    fi
}

# Function to create a more sophisticated Python fix for string constructors
create_string_constructor_fix() {
    cat > "fix_string_constructors.py" << 'EOF'
#!/usr/bin/env python3
import re
import sys

def fix_string_constructors(content):
    """Fix string constructor calls with potentially null char* pointers."""
    lines = content.splitlines()
    modified_lines = []
    changes_made = 0
    
    for i, line in enumerate(lines):
        # Look for std::string constructor patterns
        string_ctor_pattern = r'(\s*)(std::string\s+\w+\s*\(\s*(\w+)\s*\))\s*;'
        match = re.match(string_ctor_pattern, line)
        
        if match:
            indent = match.group(1)
            full_statement = match.group(2)
            char_ptr_var = match.group(3)
            
            # Check if the variable might be a char* by looking backwards
            is_char_ptr = False
            for j in range(max(0, i-10), i):
                if re.search(rf'\b{char_ptr_var}\b.*\*', lines[j]):
                    is_char_ptr = True
                    break
            
            if is_char_ptr:
                # Replace with null-safe version
                safe_version = f'{indent}std::string {full_statement.split()[1].split("(")[0]}({char_ptr_var} ? {char_ptr_var} : "");'
                modified_lines.append(safe_version)
                changes_made += 1
                print(f"  ✅ Line {i+1}: Added null check for {char_ptr_var}")
            else:
                modified_lines.append(line)
        else:
            modified_lines.append(line)
    
    return '\n'.join(modified_lines), changes_made

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 fix_string_constructors.py <file>")
        sys.exit(1)
    
    filename = sys.argv[1]
    
    try:
        with open(filename, 'r') as f:
            content = f.read()
        
        fixed_content, changes = fix_string_constructors(content)
        
        if changes > 0:
            with open(filename, 'w') as f:
                f.write(fixed_content)
            print(f"🎉 Applied {changes} string constructor fixes to {filename}")
        else:
            print(f"ℹ️  No string constructor fixes needed for {filename}")
            
    except Exception as e:
        print(f"❌ Error processing {filename}: {e}")
        sys.exit(1)
EOF
    chmod +x "fix_string_constructors.py"
    echo "📄 Created fix_string_constructors.py"
}

# Main script logic
main() {
    local target_dir="${1:-$(pwd)}"
    
    if [[ ! -d "$target_dir" ]]; then
        echo "❌ Directory not found: $target_dir"
        echo "Usage: $0 [directory]"
        exit 1
    fi
    
    echo "🎯 Target directory: $target_dir"
    
    # Find all C++ files
    local cpp_files
    readarray -t cpp_files < <(find "$target_dir" -name "*.cpp" -o -name "*.cc" -o -name "*.cxx" -type f)
    
    if [[ ${#cpp_files[@]} -eq 0 ]]; then
        echo "❌ No C++ files found in $target_dir"
        exit 1
    fi
    
    echo "📂 Found ${#cpp_files[@]} C++ files"
    
    # Create the Python helper script
    create_string_constructor_fix
    
    local total_fixes=0
    local files_modified=0
    
    # Process each file
    for file in "${cpp_files[@]}"; do
        if fix_file "$file"; then
            files_modified=$((files_modified + 1))
        fi
        
        # Also run the Python script for string constructor fixes
        if python3 "fix_string_constructors.py" "$file"; then
            echo "  🐍 Applied Python string constructor fixes"
        fi
    done
    
    echo ""
    echo "📊 Summary:"
    echo "  Files processed: ${#cpp_files[@]}"
    echo "  Files modified: $files_modified"
    
    # Cleanup
    rm -f "fix_string_constructors.py"
    
    if [[ $files_modified -gt 0 ]]; then
        echo ""
        echo "🔨 Next steps:"
        echo "1. Review the changes made"
        echo "2. Compile your project to ensure no syntax errors"
        echo "3. Run Valgrind again to verify fixes"
        echo "4. If satisfied, you can remove the .backup files"
        echo ""
        echo "To restore backups if needed:"
        echo "  find $target_dir -name '*.backup.*' -exec sh -c 'mv \"\$1\" \"\${1%%.backup.*}\"' _ {} \;"
    fi
}

# Run the script
main "$@"
