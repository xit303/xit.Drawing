# Window Construction Timing Debug

This feature provides detailed timing information about the window construction and first frame rendering process.

## How to Enable

Ensure that the `DEBUG_WINDOW` flag is defined during compilation. This is typically done by adding `-DDEBUG_WINDOW` to your compiler flags or including it in your build configuration.

## What It Measures

The timing debug functionality tracks the following milestones:

1. **Constructor Start**: The moment the Window constructor begins execution
2. **Initialize() Start**: When the Initialize() method is called
3. **Window Creation**: Time taken for GLFW window creation
4. **OpenGL Context Setup**: Time to initialize OpenGL context and GLAD
5. **Framebuffer Initialization**: Time to setup double buffering framebuffers
6. **Initialize() Complete**: Total time spent in initialization
7. **Show() Start**: When the Show() method begins
8. **First Frame Complete**: When the first rendered frame is completed and presented

## Sample Output

When enabled, you'll see output similar to:

```
>>> WINDOW CONSTRUCTION TIMING: Constructor started at 12345678μs <<<

>>> WINDOW CONSTRUCTION TIMING: Initialize() started after 1250μs from construction <<<

>>> WINDOW CONSTRUCTION TIMING: GLFW window creation took 15400μs <<<

>>> WINDOW CONSTRUCTION TIMING: OpenGL context setup took 8750μs <<<

>>> WINDOW CONSTRUCTION TIMING: Framebuffer initialization took 2300μs <<<

>>> WINDOW CONSTRUCTION TIMING: Initialize() completed in 28500μs (total from construction: 29750μs) <<<

>>> WINDOW CONSTRUCTION TIMING: Show() started 35200μs after construction <<<

========================================
>>> FIRST FRAME COMPLETED! <<<
Total time from construction to first frame: 52340μs (52.34ms)
Time from Show() to first frame: 17140μs (17.14ms)
========================================
```

## Key Metrics Explained

- **Total Construction Time**: Complete time from constructor start to first rendered frame
- **Initialization Time**: Time spent setting up the window, OpenGL context, and framebuffers
- **Show() to First Frame**: Time from calling Show() until the first frame is rendered and displayed

## Breakdown of Times

- **GLFW Window Creation**: Time to create the native window
- **OpenGL Context Setup**: Time to make context current and initialize GLAD
- **Framebuffer Initialization**: Time to setup double buffering textures and framebuffers
- **Show() to First Frame**: Includes main loop startup, content layout, and first render

## Performance Considerations

Typical timing ranges on modern systems:
- **Total construction time**: 20-100ms depending on system and content complexity
- **Window creation**: 5-30ms
- **OpenGL setup**: 2-15ms
- **Framebuffer init**: 1-10ms
- **First frame**: 5-20ms

Significantly longer times may indicate:
- Slow graphics drivers
- Complex content initialization
- Resource loading issues
- System performance problems

## Usage in Testing

This timing information is valuable for:
- Performance profiling
- Regression testing
- Identifying bottlenecks in window startup
- Comparing performance across different systems
- Optimizing application startup time
