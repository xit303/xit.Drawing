# UI Layout and Rendering Issues - Troubleshooting Guide

## Quick Fixes for Common Problems

### 1. Content Not Updating
If your UI content is not updating when data changes:

```cpp
// Quick fix - force invalidation
myVisual->ForceInvalidate();

// Or use the debug utilities
#include <Drawing/DebugUtils.h>
xit::Drawing::Debug::LayoutDiagnostics::SetDebugEnabled(true);
xit::Drawing::Debug::LayoutDiagnostics::ForceInvalidateTree(myRootVisual);
```

### 2. Content Not Appearing At All
If visuals are not showing up:

```cpp
// Check common issues
auto issues = xit::Drawing::Debug::LayoutDiagnostics::CheckCommonIssues(myVisual);
for (const auto& issue : issues) {
    std::cout << "Issue: " << issue << std::endl;
}

// Print the visual tree to see what's actually there
xit::Drawing::Debug::LayoutDiagnostics::PrintVisualTree(myRootVisual);
```

### 3. Debug Layout Problems
To understand what's happening with layout:

```cpp
// Print detailed layout information
xit::Drawing::Debug::LayoutDiagnostics::PrintLayoutInfo(myVisual);
xit::Drawing::Debug::LayoutDiagnostics::PrintInvalidationStatus(myVisual);
```

## Common Root Causes

### 1. Visibility Issues
- Check if `GetIsVisible()` returns true
- Check if `GetVisibility() != Visibility::Collapsed`
- Parent containers might be hiding children

### 2. Size Issues
- Zero width/height visuals won't appear
- Check if container has proper size allocation
- Verify Measure/Arrange cycle is working

### 3. Position Issues  
- Visuals positioned outside parent bounds
- Incorrect margin/padding calculations
- Layout alignment problems

### 4. Invalidation Chain Broken
- Parent not notified of child changes
- Scene invalidation not triggered
- Recursive update prevention blocking updates

## Systematic Debugging Approach

1. **Enable Debug Mode**
   ```cpp
   xit::Drawing::Debug::LayoutDiagnostics::SetDebugEnabled(true);
   ```

2. **Check Visual Tree**
   ```cpp
   xit::Drawing::Debug::LayoutDiagnostics::PrintVisualTree(rootVisual);
   ```

3. **Inspect Problem Visual**
   ```cpp
   xit::Drawing::Debug::LayoutDiagnostics::PrintLayoutInfo(problemVisual);
   xit::Drawing::Debug::LayoutDiagnostics::PrintInvalidationStatus(problemVisual);
   ```

4. **Force Update if Needed**
   ```cpp
   xit::Drawing::Debug::LayoutDiagnostics::ForceInvalidateTree(rootVisual);
   ```

## Fixes Applied to Your Codebase

1. **Improved Invalidation Chain**: Enhanced Visual::NotifyParentOfInvalidation() with fallbacks
2. **Added Debug Logging**: DEBUG builds now show invalidation and update activity  
3. **Fixed Thread Safety**: Made recursive update prevention thread-local
4. **Added RAII Safety**: Ensures update flags are always reset properly
5. **Added ForceInvalidate()**: Nuclear option when normal invalidation fails
6. **Added Debug Utilities**: Comprehensive debugging and diagnostic tools

## Performance Notes

- The debug logging only runs in DEBUG builds
- ForceInvalidate() should be used sparingly as it bypasses optimizations
- Consider disabling debug output in production builds

## When All Else Fails

If you're still having issues:

1. Create a minimal test case with just the problematic visual
2. Use the debug utilities to trace the issue step by step
3. Check if the issue is in layout (positioning/sizing) or rendering
4. Verify the update/render loop is being called properly
