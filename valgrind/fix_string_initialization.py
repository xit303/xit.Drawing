#!/usr/bin/env python3
"""
Script to fix uninitialized string pointer issues in C++ code.
Fixes patterns where char* pointers are used without initialization before being passed to std::string constructors.
"""

import os
import re
import sys
import argparse
from pathlib import Path

class StringInitializationFixer:
    def __init__(self):
        # Patterns to detect uninitialized char* declarations
        self.char_ptr_patterns = [
            # char* varname;
            re.compile(r'^\s*(char\s*\*\s*(\w+)\s*;)\s*$', re.MULTILINE),
            # char *varname;
            re.compile(r'^\s*(char\s+\*\s*(\w+)\s*;)\s*$', re.MULTILINE),
            # const char* varname;
            re.compile(r'^\s*(const\s+char\s*\*\s*(\w+)\s*;)\s*$', re.MULTILINE),
            # const char *varname;
            re.compile(r'^\s*(const\s+char\s+\*\s*(\w+)\s*;)\s*$', re.MULTILINE),
        ]
        
        # Patterns to detect usage in string constructors
        self.string_usage_patterns = [
            # std::string var(charptr)
            re.compile(r'std::string\s+\w+\s*\(\s*(\w+)\s*\)', re.MULTILINE),
            # std::string var = charptr
            re.compile(r'std::string\s+\w+\s*=\s*(\w+)', re.MULTILINE),
            # string.assign(charptr)
            re.compile(r'\w+\.assign\s*\(\s*(\w+)\s*\)', re.MULTILINE),
            # string = charptr
            re.compile(r'\w+\s*=\s*(\w+)', re.MULTILINE),
        ]
        
        self.fixes_applied = []
        
    def find_uninitialized_char_ptrs(self, content, filename):
        """Find uninitialized char* declarations and their usage."""
        uninitialized_vars = set()
        
        # Find all uninitialized char* declarations
        for pattern in self.char_ptr_patterns:
            matches = pattern.finditer(content)
            for match in matches:
                var_name = match.group(2)
                # Check if it's not already initialized
                full_decl = match.group(1)
                if '=' not in full_decl and 'nullptr' not in full_decl:
                    uninitialized_vars.add(var_name)
                    
        return uninitialized_vars
    
    def fix_char_ptr_declarations(self, content, filename):
        """Fix uninitialized char* declarations by adding = nullptr."""
        modified = False
        lines = content.splitlines(True)
        
        for i, line in enumerate(lines):
            for pattern in self.char_ptr_patterns:
                match = pattern.match(line.strip())
                if match:
                    var_name = match.group(2)
                    full_decl = match.group(1)
                    
                    # Skip if already initialized
                    if '=' in full_decl or 'nullptr' in full_decl:
                        continue
                        
                    # Add nullptr initialization
                    if 'const' in full_decl:
                        new_decl = full_decl.replace(';', ' = nullptr;')
                    else:
                        new_decl = full_decl.replace(';', ' = nullptr;')
                    
                    # Replace the line
                    old_line = line
                    new_line = line.replace(full_decl, new_decl)
                    lines[i] = new_line
                    
                    if old_line != new_line:
                        modified = True
                        self.fixes_applied.append({
                            'file': filename,
                            'line': i + 1,
                            'type': 'char_ptr_init',
                            'old': old_line.strip(),
                            'new': new_line.strip()
                        })
        
        return ''.join(lines) if modified else content, modified
    
    def add_null_checks_for_string_usage(self, content, filename):
        """Add null checks before string constructor usage."""
        modified = False
        lines = content.splitlines(True)
        uninitialized_vars = self.find_uninitialized_char_ptrs(''.join(lines), filename)
        
        i = 0
        while i < len(lines):
            line = lines[i]
            
            # Check for std::string constructor with potential uninitialized char*
            string_ctor_match = re.search(r'std::string\s+(\w+)\s*\(\s*(\w+)\s*\)', line)
            if string_ctor_match:
                var_name = string_ctor_match.group(1)
                char_ptr = string_ctor_match.group(2)
                
                if char_ptr in uninitialized_vars:
                    # Add null check
                    indent = len(line) - len(line.lstrip())
                    indent_str = ' ' * indent
                    
                    null_check_lines = [
                        f"{indent_str}if ({char_ptr} != nullptr) {{\n",
                        f"{indent_str}    {line.strip()}\n",
                        f"{indent_str}}} else {{\n",
                        f"{indent_str}    std::string {var_name}; // Empty string for null pointer\n",
                        f"{indent_str}}}\n"
                    ]
                    
                    # Replace current line with null check
                    lines[i:i+1] = null_check_lines
                    i += len(null_check_lines)
                    modified = True
                    
                    self.fixes_applied.append({
                        'file': filename,
                        'line': i - len(null_check_lines) + 1,
                        'type': 'null_check_added',
                        'old': line.strip(),
                        'new': f"Added null check for {char_ptr}"
                    })
                    continue
            
            i += 1
        
        return ''.join(lines) if modified else content, modified
    
    def fix_member_initialization_lists(self, content, filename):
        """Fix member initialization lists for char* members."""
        # Pattern to find constructors
        ctor_pattern = re.compile(r'(\w+::\w+\([^)]*\))\s*(:.*?)?\s*\{', re.DOTALL)
        
        modified = False
        new_content = content
        
        matches = list(ctor_pattern.finditer(content))
        
        for match in reversed(matches):  # Process in reverse to maintain positions
            ctor_signature = match.group(1)
            init_list = match.group(2) if match.group(2) else None
            
            # Look for char* members in the class
            # This is a simplified approach - in practice you'd need to parse the class definition
            class_name = ctor_signature.split('::')[0]
            
            # If no initialization list exists and we have char* members, add one
            if not init_list:
                # This is a basic implementation - you might need to customize based on your class structure
                new_ctor = f"{ctor_signature} : /* Add char* member initializations here */"
                new_content = new_content.replace(match.group(0), new_ctor + " {")
                modified = True
        
        return new_content, modified
    
    def process_file(self, filepath):
        """Process a single C++ file."""
        try:
            with open(filepath, 'r', encoding='utf-8') as f:
                content = f.read()
        except Exception as e:
            print(f"Error reading {filepath}: {e}")
            return False
        
        original_content = content
        file_modified = False
        
        # Apply fixes
        content, mod1 = self.fix_char_ptr_declarations(content, str(filepath))
        content, mod2 = self.add_null_checks_for_string_usage(content, str(filepath))
        
        file_modified = mod1 or mod2
        
        if file_modified:
            try:
                with open(filepath, 'w', encoding='utf-8') as f:
                    f.write(content)
                print(f"✅ Fixed: {filepath}")
                return True
            except Exception as e:
                print(f"❌ Error writing {filepath}: {e}")
                return False
        
        return False
    
    def find_cpp_files(self, directory):
        """Find all C++ source files in directory."""
        cpp_extensions = {'.cpp', '.cxx', '.cc', '.c++', '.C'}
        cpp_files = []
        
        for root, dirs, files in os.walk(directory):
            for file in files:
                if any(file.endswith(ext) for ext in cpp_extensions):
                    cpp_files.append(os.path.join(root, file))
        
        return cpp_files
    
    def run(self, target_path, dry_run=False):
        """Run the fixer on the target path."""
        if os.path.isfile(target_path):
            files_to_process = [target_path]
        elif os.path.isdir(target_path):
            files_to_process = self.find_cpp_files(target_path)
        else:
            print(f"❌ Target path does not exist: {target_path}")
            return False
        
        if not files_to_process:
            print("No C++ files found to process.")
            return False
        
        print(f"Found {len(files_to_process)} C++ files to process...")
        
        if dry_run:
            print("🔍 DRY RUN MODE - No files will be modified")
        
        files_modified = 0
        
        for filepath in files_to_process:
            if dry_run:
                print(f"Would process: {filepath}")
            else:
                if self.process_file(filepath):
                    files_modified += 1
        
        # Print summary
        print(f"\n📊 Summary:")
        print(f"Files processed: {len(files_to_process)}")
        print(f"Files modified: {files_modified}")
        print(f"Total fixes applied: {len(self.fixes_applied)}")
        
        if self.fixes_applied:
            print(f"\n🔧 Fixes applied:")
            for fix in self.fixes_applied:
                print(f"  {fix['file']}:{fix['line']} ({fix['type']})")
                print(f"    - {fix['old']}")
                print(f"    + {fix['new']}")
        
        return files_modified > 0

def main():
    parser = argparse.ArgumentParser(description="Fix uninitialized string pointer issues in C++ code")
    parser.add_argument("target", help="Target file or directory to process")
    parser.add_argument("--dry-run", action="store_true", help="Show what would be changed without modifying files")
    parser.add_argument("--verbose", "-v", action="store_true", help="Verbose output")
    
    args = parser.parse_args()
    
    fixer = StringInitializationFixer()
    success = fixer.run(args.target, dry_run=args.dry_run)
    
    if success:
        print("✅ String initialization fixes completed successfully!")
        return 0
    else:
        print("❌ No fixes were applied.")
        return 1

if __name__ == "__main__":
    sys.exit(main())
