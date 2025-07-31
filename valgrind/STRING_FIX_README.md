# String Initialization Fix Scripts

This directory contains two scripts to fix the uninitialized string pointer issues found by Valgrind:

## 🔧 Scripts Available

### 1. `fix_strings.sh` (Recommended)
**Quick and automatic bash script**

```bash
# Run in your PassMaga project directory
cd /path/to/your/PassMaga/project
/home/xor/workspace_pc/NewLibrary/xit.Drawing/fix_strings.sh .
```

**What it does:**
- Finds all `.cpp`, `.cc`, `.cxx` files
- Fixes `char* varname;` → `char* varname = nullptr;`
- Fixes `const char* varname;` → `const char* varname = nullptr;`
- Adds null checks for string constructors
- Creates backups of all modified files
- Shows summary of changes

### 2. `fix_string_initialization.py` (Advanced)
**More sophisticated Python script with detailed analysis**

```bash
# For single file
python3 fix_string_initialization.py /path/to/AccountDataView.cpp

# For entire directory  
python3 fix_string_initialization.py /path/to/your/PassMaga/src --dry-run

# Apply fixes
python3 fix_string_initialization.py /path/to/your/PassMaga/src
```

**What it does:**
- Comprehensive C++ parsing
- Detects uninitialized char* variables
- Adds nullptr initialization
- Wraps string constructors with null checks
- Detailed reporting of all changes
- Dry-run mode for preview

## 📋 Common Patterns Fixed

### Before (Causes Valgrind Errors):
```cpp
char* someString;
// ... later in code ...
std::string result(someString);  // ❌ Uninitialized pointer passed to strlen()
```

### After (Fixed):
```cpp
char* someString = nullptr;
// ... later in code ...
std::string result(someString ? someString : "");  // ✅ Safe
```

## 🎯 For Your AccountDataView Issues

Based on the Valgrind output, you have issues at these lines in `AccountDataView.cpp`:
- Lines: 27, 36, 61, 71, 81, 92, 105, 116, 127, 136

Run this command in your PassMaga project:
```bash
cd /path/to/your/PassMaga/project
/home/xor/workspace_pc/NewLibrary/xit.Drawing/fix_strings.sh .
```

## 🔄 After Running the Script

1. **Compile your project** to check for syntax errors
2. **Run Valgrind again** to verify the fixes worked
3. **Review the changes** (backups are created automatically)
4. **Remove backups** if you're satisfied:
   ```bash
   find . -name "*.backup.*" -delete
   ```

## 🆘 If Something Goes Wrong

Restore from backup:
```bash
find . -name "*.backup.*" -exec sh -c 'mv "$1" "${1%%.backup.*}"' _ {} \;
```

## Example Usage

```bash
# Navigate to your PassMaga project
cd /home/xor/workspace_pc/PassMaga

# Run the fix script
/home/xor/workspace_pc/NewLibrary/xit.Drawing/fix_strings.sh .

# Compile to verify
xmake

# Test with Valgrind
valgrind --leak-check=full ./your_executable
```

The script will show you exactly what it fixed and create backups of all modified files for safety!
