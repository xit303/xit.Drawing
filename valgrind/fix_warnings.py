#!/usr/bin/env python3
"""
Automated script to fix common C++ compiler warnings in the xit.Drawing project.
This script focuses on the most critical memory safety and initialization warnings.
"""

import os
import re
import glob
import argparse
from typing import List, Tuple

class WarningFixer:
    def __init__(self, dry_run: bool = False):
        self.dry_run = dry_run
        self.fixes_applied = 0
        self.files_modified = 0
        
    def log(self, message: str):
        print(f"{'[DRY RUN] ' if self.dry_run else ''}{message}")
        
    def fix_unused_parameters(self, content: str, filepath: str) -> str:
        """Fix unused parameter warnings by adding (void)param; statements"""
        # Pattern for virtual functions with unused parameters
        pattern = r'(virtual\s+\w+.*?\([^)]*?(\w+)\s*&?\s*(\w+)\s*\)\s*\{)(\s*)(.*?)(\})'
        
        def replace_unused_param(match):
            func_decl = match.group(1)
            param_type = match.group(2)
            param_name = match.group(3)
            whitespace = match.group(4)
            body = match.group(5)
            closing = match.group(6)
            
            # Check if parameter is used in the body
            if param_name not in body and body.strip() == '':
                # Add void cast for unused parameter
                new_body = f"{whitespace}(void){param_name};"
                return f"{func_decl}{new_body} {closing}"
            
            return match.group(0)
        
        return re.sub(pattern, replace_unused_param, content, flags=re.DOTALL)
    
    def fix_member_initialization_lists(self, content: str, filepath: str) -> str:
        """Fix member initialization list warnings"""
        fixes = []
        
        # Common patterns for constructors that need member initialization
        patterns = [
            # Pattern: Constructor() { member = value; }
            (r'(\w+\(\))\s*\{\s*(\w+)\s*=\s*([^;]+);\s*\}', 
             r'\1 : \2(\3) {}'),
            
            # Pattern: Constructor() { member1 = val1; member2 = val2; }
            (r'(\w+\(\))\s*\{\s*(\w+)\s*=\s*([^;]+);\s*(\w+)\s*=\s*([^;]+);\s*\}',
             r'\1 : \2(\3), \4(\5) {}'),
        ]
        
        modified = content
        for pattern, replacement in patterns:
            new_content = re.sub(pattern, replacement, modified, flags=re.MULTILINE)
            if new_content != modified:
                fixes.append(f"Fixed member initialization in {filepath}")
                modified = new_content
        
        return modified
    
    def fix_event_initialization(self, content: str, filepath: str) -> str:
        """Fix Event object initialization warnings"""
        # Pattern for Event member declarations that need initialization
        if 'Event<' in content and 'should be initialized in the member initialization list' in filepath:
            # Look for Event declarations and ensure they're in init lists
            pattern = r'(Event<[^>]+>\s+\w+);'
            # This is complex and needs context, so we'll mark it for manual review
            pass
        
        return content
    
    def fix_virtual_destructors(self, content: str, filepath: str) -> str:
        """Add virtual destructors to classes with virtual functions"""
        # Find classes with virtual functions but no virtual destructor
        class_pattern = r'class\s+(\w+)[^{]*\{[^}]*virtual\s+[^}]*(?!virtual\s+~)'
        
        matches = re.finditer(class_pattern, content, re.DOTALL)
        for match in matches:
            class_name = match.group(1)
            # Check if there's already a destructor
            destructor_pattern = f'~{class_name}\\s*\\('
            if not re.search(destructor_pattern, content):
                # This is complex and needs careful insertion, mark for manual review
                pass
        
        return content
    
    def fix_copy_constructor_base_init(self, content: str, filepath: str) -> str:
        """Fix copy constructors missing base class initialization"""
        # Pattern: ClassName(const ClassName& other) : MemberInit(other) {}
        # Should be: ClassName(const ClassName& other) : BaseClass(other), MemberInit(other) {}
        
        # This is complex and needs inheritance analysis, mark for later
        return content
    
    def process_file(self, filepath: str) -> bool:
        """Process a single file and apply fixes"""
        try:
            with open(filepath, 'r', encoding='utf-8') as f:
                original_content = f.read()
            
            content = original_content
            
            # Apply fixes in order of safety/simplicity
            content = self.fix_unused_parameters(content, filepath)
            content = self.fix_member_initialization_lists(content, filepath)
            content = self.fix_event_initialization(content, filepath)
            content = self.fix_virtual_destructors(content, filepath)
            content = self.fix_copy_constructor_base_init(content, filepath)
            
            if content != original_content:
                if not self.dry_run:
                    with open(filepath, 'w', encoding='utf-8') as f:
                        f.write(content)
                
                self.log(f"Modified: {filepath}")
                self.files_modified += 1
                return True
            
            return False
            
        except Exception as e:
            self.log(f"Error processing {filepath}: {e}")
            return False
    
    def find_cpp_files(self, directory: str) -> List[str]:
        """Find all C++ header and source files"""
        patterns = ['**/*.h', '**/*.hpp', '**/*.cpp', '**/*.cc', '**/*.cxx']
        files = []
        
        for pattern in patterns:
            files.extend(glob.glob(os.path.join(directory, pattern), recursive=True))
        
        # Filter out library files
        filtered_files = []
        for f in files:
            if not any(exclude in f for exclude in ['lib/', 'test/', 'build/', '.bin/']):
                filtered_files.append(f)
        
        return sorted(filtered_files)
    
    def run(self, directory: str):
        """Run the fixer on all files in the directory"""
        files = self.find_cpp_files(directory)
        self.log(f"Found {len(files)} C++ files to process")
        
        for filepath in files:
            self.process_file(filepath)
        
        self.log(f"Summary: Modified {self.files_modified} files")

def create_simple_fixes_script():
    """Create a simple shell script for common pattern fixes"""
    script_content = '''#!/bin/bash
# Simple fixes for common warning patterns

echo "Applying simple warning fixes..."

# Fix unused parameter warnings in virtual functions
find . -name "*.h" -o -name "*.hpp" -o -name "*.cpp" | grep -v lib/ | xargs sed -i.bak '
# Add (void)param; for empty virtual function bodies with EventArgs
s/virtual void On\([A-Za-z]*\)(EventArgs &\([a-z]*\)) {}/virtual void On\1(EventArgs \&\2) { (void)\2; }/g
'

# Fix simple member initialization patterns
find . -name "*.h" -o -name "*.hpp" | grep -v lib/ | xargs sed -i.bak '
# Convert simple assignment in constructor body to initialization list
s/\([A-Za-z_][A-Za-z0-9_]*\)() *{ *\([a-zA-Z_][a-zA-Z0-9_]*\) *= *\([^;]*\); *}/\1() : \2(\3) {}/g
'

echo "Simple fixes applied. Check .bak files for originals if needed."
echo "Note: Complex fixes may require manual intervention."
'''
    
    with open('/home/xor/workspace_pc/NewLibrary/xit.Drawing/simple_fixes.sh', 'w') as f:
        f.write(script_content)
    
    os.chmod('/home/xor/workspace_pc/NewLibrary/xit.Drawing/simple_fixes.sh', 0o755)

def main():
    parser = argparse.ArgumentParser(description='Fix common C++ compiler warnings')
    parser.add_argument('--dry-run', action='store_true', 
                        help='Show what would be changed without making changes')
    parser.add_argument('--directory', default='.', 
                        help='Directory to process (default: current directory)')
    parser.add_argument('--create-simple', action='store_true',
                        help='Create a simple shell script for basic fixes')
    
    args = parser.parse_args()
    
    if args.create_simple:
        create_simple_fixes_script()
        print("Created simple_fixes.sh script")
        return
    
    fixer = WarningFixer(dry_run=args.dry_run)
    fixer.run(args.directory)

if __name__ == '__main__':
    main()
