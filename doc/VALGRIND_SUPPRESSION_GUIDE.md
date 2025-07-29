# Valgrind Suppression Files - Complete Guide

## What are Suppression Files?

Suppression files tell Valgrind to ignore specific types of errors that are:
1. **False positives** (not real bugs)
2. **Third-party library issues** you can't fix
3. **Known acceptable behavior** (like intentional memory pools)

## How to Use Suppression Files

### 1. Basic Usage
```bash
# Run Valgrind with your suppression file
valgrind --suppressions=valgrind-suppressions.supp \
         --leak-check=full \
         --show-leak-kinds=all \
         ./your_program
```

### 2. Multiple Suppression Files
```bash
# You can use multiple suppression files
valgrind --suppressions=nvidia-suppressions.supp \
         --suppressions=qt-suppressions.supp \
         --suppressions=my-suppressions.supp \
         ./your_program
```

### 3. Generate Suppressions Automatically
```bash
# Let Valgrind help you create suppressions
valgrind --gen-suppressions=all \
         --leak-check=full \
         ./your_program

# This will output suppression blocks you can copy-paste
```

## Suppression File Format

### Basic Structure
```
{
   suppression_name
   Tool:ErrorType
   frame_specifications
}
```

### Error Types
- `Memcheck:Leak` - Memory leaks
- `Memcheck:Cond` - Conditional jumps on uninitialized values
- `Memcheck:Value4` - 4-byte uninitialized value usage
- `Memcheck:Value8` - 8-byte uninitialized value usage
- `Memcheck:Free` - Invalid free/delete operations

### Frame Specifications
```
fun:function_name         # Exact function name
obj:*/library.so*         # Library pattern matching
...                       # Match any number of frames
src:source_file.cpp       # Source file matching
```

## Creating Your Own Suppressions

### 1. From Valgrind Output
When Valgrind shows an error like:
```
==12345== Conditional jump or move depends on uninitialised value(s)
==12345==    at 0x4E7D4A2: some_function
==12345==    by 0x514C1F4: library_call
==12345==    by 0x51CBAFF: main
```

Create a suppression:
```
{
   my-uninitialized-suppression
   Memcheck:Cond
   fun:some_function
   fun:library_call
   fun:main
}
```

### 2. Pattern Matching
```
{
   all-nvidia-issues
   Memcheck:*              # Any error type
   ...                     # Any call stack depth
   obj:*/nvidia*           # Any nvidia library
}
```

### 3. Specific to Your Project
```
{
   acceptable-memory-pool
   Memcheck:Leak
   match-leak-kinds: definite
   fun:malloc
   fun:MyMemoryPool::allocate
   ...
   fun:main
}
```

## Testing Your Suppressions

### 1. Count Errors Before/After
```bash
# Before suppressions
valgrind --leak-check=full ./program 2>&1 | grep "ERROR SUMMARY"

# After suppressions  
valgrind --suppressions=my.supp --leak-check=full ./program 2>&1 | grep "ERROR SUMMARY"
```

### 2. Validate Suppression File
```bash
# Check if your suppression file is valid
valgrind --suppressions=my.supp --error-limit=no /bin/true
```

## Common Suppression Patterns

### OpenGL/Graphics Drivers
```
{
   opengl-driver-leaks
   Memcheck:Leak
   ...
   obj:*/libGL.so*
}
```

### X11/GUI Libraries
```
{
   x11-font-leaks
   Memcheck:Leak
   ...
   obj:*/libX11.so*
}
```

### C++ Standard Library (older versions)
```
{
   std-locale-leaks
   Memcheck:Leak
   ...
   fun:*locale*
}
```

## Best Practices

1. **Be Specific**: Don't suppress too broadly
2. **Document**: Add comments explaining why you're suppressing
3. **Review Regularly**: Suppressions may become obsolete with updates
4. **Version Control**: Include suppression files in your repository
5. **Team Sharing**: Use the same suppressions across your team

## Example Usage for Your Project

```bash
# Navigate to your project
cd /home/xor/workspace_pc/NewLibrary/xit.Drawing

# Build your project first
xmake

# Run with suppressions
valgrind --suppressions=valgrind-suppressions.supp \
         --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         ./.bin/Debug/PassMaga

# Or create a script:
echo '#!/bin/bash
valgrind --suppressions=valgrind-suppressions.supp \
         --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         "$@"' > run_valgrind.sh
chmod +x run_valgrind.sh

# Then use:
./run_valgrind.sh ./.bin/Debug/PassMaga
```

This approach will significantly reduce the noise in your Valgrind output, letting you focus on real bugs in your code!
