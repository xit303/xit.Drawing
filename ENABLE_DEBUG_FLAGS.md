# Enabling DEBUG_INITIALIZATION

To enable the detailed initialization timing debug output, you have several options:

## Option 1: Add to xmakefile.json (Recommended)

Edit your `xmakefile.json` file and add `"DEBUG_INITIALIZATION"` to the defines array:

```json
"defines": [
    "DEBUG",
    "USE_AI_SUGGESTED_FIX", 
    "DEBUG_WINDOW",
    "DEBUG_INITIALIZATION"
],
```

## Option 2: Compiler Flag

Add the flag directly to your compiler command:
```bash
g++ -DDEBUG_INITIALIZATION [other flags] ...
```

## Option 3: CMake Integration

If using CMake, add:
```cmake
add_definitions(-DDEBUG_INITIALIZATION)
```

## Debug Flag Hierarchy

You can use these debug flags independently or together:

- `DEBUG_WINDOW`: High-level window construction timing (already enabled)
- `DEBUG_INITIALIZATION`: Detailed initialization step timing (new)
- `DEBUG_WINDOW2`: Detailed rendering and frame timing

## Recommended Usage

For complete timing analysis during development:
```json
"defines": [
    "DEBUG",
    "DEBUG_WINDOW",
    "DEBUG_INITIALIZATION"
]
```

For production builds, remove all debug flags:
```json
"defines": [
    "USE_AI_SUGGESTED_FIX"
]
```

## Performance Impact

- `DEBUG_INITIALIZATION` adds minimal overhead (microsecond-level timing calls)
- Only affects initialization phase, not runtime performance
- Safe to leave enabled during development
- Should be disabled for release builds
