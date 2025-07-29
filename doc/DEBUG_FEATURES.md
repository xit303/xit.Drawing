# Debug Features for Double Buffered Rendering

## Overview

Comprehensive debug instrumentation has been added to the double buffered rendering system to help analyze performance and troubleshoot issues. All debug output is controlled by the `DEBUG_WINDOW` preprocessor define.

## Debug Output Categories

### 1. Frame-Level Performance Monitoring

#### FPS Reporting
- Reports average FPS every 5 seconds
- Shows average frame time in milliseconds
- Example output:
```
>>> PERFORMANCE REPORT: 58.3 FPS (avg frame time: 17.2ms) <<<
```

#### Frame Gap Detection
- Logs when frames take longer than the 16ms target
- Helps identify performance bottlenecks
- Example output:
```
Frame gap: 23ms (target: 16ms)
```

### 2. Render Method Timing

#### Total Render Time
Each `DoRender()` call is wrapped with timing:
```
=== Window::DoRender START ===
DoRender: TOTAL RENDER TIME: 2847μs (2.847ms)
=== Window::DoRender END ===
```

#### Phase-by-Phase Breakdown
- **Region Extraction**: Time to extract invalid regions from queue
- **Rendering Phase**: Time for actual drawing operations
- **Framebuffer Swap**: Time to swap buffer identities
- **Present**: Time to copy to screen and swap buffers

### 3. Rendering Strategy Analysis

#### Strategy Selection
Shows which rendering path was chosen:
```
DoRender: Rendering strategy - hasInvalidRegions=true needsFullRedraw=false
DoRender: Performing PARTIAL REDRAW with 3 regions
```

#### Full Redraw Reasons
When full redraw is triggered, shows the specific reasons:
```
DoRender: Full redraw reasons - invalidated=true needWidth=false needHeight=false needLeft=false needTop=false
```

### 4. Partial Rendering Details

#### Buffer Copy Performance
```
DoRender: Buffer copy (1920x1080) took 234μs
```

#### Per-Region Processing
For each invalid region:
```
DoRender: Processing region 0 - bounds(100,50,200,30) visual=Button1
DoRender: Scissor region set to (100,1000,200,30)
DoRender: Region render completed in 156μs
```

#### Region Warnings
```
DoRender: WARNING - Null visual for region 2
```

### 5. Region Invalidation Tracking

#### Region Addition
```
InvalidateRegion: Adding region for visual 'Button1' bounds(100,50,200,30)
InvalidateRegion: Total invalid regions now: 2
```

### 6. Framebuffer Management

#### Initialization Timing
```
InitializeFramebuffers: Starting framebuffer initialization
InitializeFramebuffers: Creating framebuffers with size 1920x1080
InitializeFramebuffers: Front framebuffer setup complete
InitializeFramebuffers: Back framebuffer setup complete
Window::InitializeFramebuffers - Framebuffers initialized with size 1920x1080 in 1247μs
InitializeFramebuffers: Estimated GPU memory usage: 31.64 MB
```

#### Swap Operations
```
Window::SwapFramebuffers - Framebuffers swapped in 127ns
SwapFramebuffers: Front 1 -> 2, Back 2 -> 1
```

#### Error Detection
```
InitializeFramebuffers: ERROR - Front framebuffer is not complete! Status: 36054
```

### 7. Fallback Rendering
```
DoRender: Framebuffers not initialized, using fallback rendering
DoRender: Fallback rendering completed in 3421μs
```

## Performance Analysis Use Cases

### 1. Identifying Rendering Bottlenecks
- Compare times between full redraw, partial redraw, and no-change scenarios
- Monitor individual region render times to find expensive visuals
- Track buffer copy performance vs. region count

### 2. Memory Usage Monitoring
- GPU memory estimates for framebuffers
- Track framebuffer recreations during window resize

### 3. Frame Rate Analysis
- Monitor sustained FPS over time
- Identify frame drops and their causes
- Validate 60 FPS target achievement

### 4. Debugging Rendering Issues
- Verify correct region bounds and scissor rectangles
- Track visual names for problematic regions
- Monitor framebuffer swap operations

## Example Debug Session Output

```
InvalidateRegion: Adding region for visual 'Button1' bounds(10,20,100,30)
InvalidateRegion: Total invalid regions now: 1

=== Window::DoRender START ===
DoRender: Region extraction took 23μs
DoRender: Found 1 invalid regions
DoRender: Rendering strategy - hasInvalidRegions=true needsFullRedraw=false
DoRender: Performing PARTIAL REDRAW with 1 regions
DoRender: Buffer copy (800x600) took 156μs
DoRender: Processing region 0 - bounds(10,20,100,30) visual=Button1
DoRender: Scissor region set to (10,550,100,30)
DoRender: Region render completed in 89μs
DoRender: Partial redraw completed in 267μs
DoRender: Total rendering phase took 290μs
DoRender: Framebuffer swap took 45ns
DoRender: Present to screen took 112μs
DoRender: TOTAL RENDER TIME: 547μs (0.547ms)
=== Window::DoRender END ===

>>> PERFORMANCE REPORT: 59.7 FPS (avg frame time: 16.8ms) <<<
```

## Enabling Debug Output

Debug output is enabled by defining `DEBUG_WINDOW` during compilation. In the current build system, this is already enabled in Debug builds.

## Performance Impact

The debug instrumentation adds minimal overhead:
- Time measurements use high-resolution clocks
- Debug output only occurs when `DEBUG_WINDOW` is defined
- String operations are compile-time eliminated in release builds
- Typical debug overhead: < 10μs per frame
