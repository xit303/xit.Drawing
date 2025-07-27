# Double Buffered Rendering Implementation

## Overview

This document describes the implementation of double buffered rendering in the Window class to optimize partial region rendering for improved performance.

## Key Features

### 1. Framebuffer Management
- **Front Buffer**: Contains the current displayed frame
- **Back Buffer**: Used for rendering new content
- **Automatic Cleanup**: Framebuffers are properly cleaned up on window destruction and resize

### 2. Partial Region Rendering
- **Region Tracking**: Invalid regions are tracked with Visual* and Rectangle bounds
- **Selective Rendering**: Only invalidated regions are re-rendered when possible
- **Scissor Testing**: Used to limit rendering to specific regions
- **Buffer Copying**: Unchanged regions are copied from front to back buffer

### 3. Performance Optimizations

#### Smart Rendering Strategy
1. **Full Redraw**: When window properties change (size, position, etc.)
2. **Partial Redraw**: When only specific visual regions are invalidated
3. **No-Op**: When no changes occurred, just copy front to back buffer

#### Memory Efficiency
- Uses texture attachments for color and depth buffers
- Properly manages OpenGL resources with automatic cleanup
- Handles window resizing by recreating framebuffers

## Implementation Details

### Header Changes (`Window.h`)
```cpp
// Double buffering for partial region rendering
GLuint frontFramebuffer{0};
GLuint backFramebuffer{0};
GLuint frontColorTexture{0};
GLuint backColorTexture{0};
GLuint frontDepthTexture{0};
GLuint backDepthTexture{0};
bool framebuffersInitialized{false};

// Helper methods
void InitializeFramebuffers();
void CleanupFramebuffers();
void SwapFramebuffers();
void CopyRegionBetweenFramebuffers(const Rectangle& region);
```

### Core Methods

#### `InitializeFramebuffers()`
- Creates front and back framebuffers with color and depth attachments
- Sets up textures with appropriate filtering and clamping
- Validates framebuffer completeness
- Clears both buffers initially

#### `DoRender()` Enhanced Logic
1. **Fallback Safety**: Falls back to traditional rendering if framebuffers aren't ready
2. **Region Processing**: Thread-safe extraction of invalid regions
3. **Rendering Decision**:
   - Full redraw if window invalidated or layout changed
   - Partial redraw if only specific regions invalidated
   - Copy operation if no changes
4. **Buffer Management**: Proper binding and swapping of framebuffers

#### `CleanupFramebuffers()`
- Safely deletes all OpenGL resources
- Called on window destruction and resize events

### Rendering Flow

```
1. Extract invalid regions (thread-safe)
2. Determine rendering strategy
3. Bind back framebuffer
4. Execute rendering strategy:
   a. Full: Clear + Render all
   b. Partial: Copy front to back + Render invalid regions only
   c. No-op: Copy front to back
5. Swap framebuffer identities
6. Copy front framebuffer to default framebuffer for display
7. Swap window buffers
```

## Benefits

### Performance Improvements
- **Reduced GPU Load**: Only invalidated regions are re-rendered
- **Better Frame Rates**: Especially beneficial for complex UIs with localized changes
- **Memory Bandwidth**: Minimizes texture uploads and GPU memory transfers

### Visual Quality
- **Reduced Flicker**: Double buffering eliminates visual artifacts
- **Smoother Animation**: Consistent frame presentation
- **Proper Depth Testing**: Maintains correct Z-ordering

## Usage Considerations

### When Partial Rendering is Used
- Small UI element updates (button state changes, text updates)
- Localized animations
- Mouse hover effects
- Individual control invalidations

### When Full Rendering is Used
- Window resize events
- Layout changes (container size modifications)
- Theme changes
- Initial window display

## Debug Features

The implementation includes debug output (when `DEBUG_WINDOW` is defined) to track:
- Framebuffer initialization and cleanup
- Rendering strategy decisions
- Region processing details
- Buffer swap operations

## Thread Safety

- Invalid regions are protected by `invalidRegionsMutex`
- Region extraction is atomic and thread-safe
- Framebuffer operations are performed on the main thread only

## Future Enhancements

Potential improvements could include:
- Region merging for adjacent invalid areas
- Dirty rectangle optimization
- GPU-based region copying for better performance
- Adaptive rendering strategy based on performance metrics
