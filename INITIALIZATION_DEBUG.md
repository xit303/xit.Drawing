# Window Initialization Debug

This feature provides detailed timing information about every initialization step in the Window constructor and Initialize() method, including inheritance chain calls.

## How to Enable

Define the `DEBUG_INITIALIZATION` flag during compilation by adding `-DDEBUG_INITIALIZATION` to your compiler flags or including it in your build configuration.

## What It Measures

The initialization debug functionality tracks these detailed steps:

### Constructor Phase:
1. **App::Settings() calls**: Time to retrieve application scale settings
2. **SetBrushGroup()**: Time to set the window's brush group for theming
3. **SetName()**: Time to set the window's name for debugging
4. **glfwInit()**: GLFW library initialization time
5. **GLFW window hints**: Time to set OpenGL context hints
6. **Dispatcher::SetMainThreadId()**: Time to register main thread for dispatch

### Initialize() Method Phase:
1. **GLFW window creation**: Native window creation time
2. **OpenGL context setup**: Context creation and GLAD initialization
3. **Window list registration**: Time to register window in global list
4. **GLFW callback setup**: Time to register all event callbacks
5. **Scene2D setup**: Scene initialization and sizing
6. **App::Closing event registration**: Event handler registration
7. **DPI scale detection**: Time to query window content scale
8. **SetDPIScale()**: Time to apply DPI scaling to window and content
9. **Framebuffer initialization**: Double buffering setup time
10. **OnInitializeComponent()**: Virtual method call for derived class initialization

### Show() Method Phase:
1. **OpenGLExtensions::Initialize2D()**: OpenGL extensions initialization

## Sample Output

When enabled, you'll see detailed output like:

```
>>> INITIALIZATION: App::Settings() calls took 1250μs <<<
>>> INITIALIZATION: SetBrushGroup() took 45μs <<<
>>> INITIALIZATION: SetName() took 12μs <<<
>>> INITIALIZATION: glfwInit() took 8500μs <<<
>>> INITIALIZATION: GLFW window hints took 8μs <<<
>>> INITIALIZATION: Dispatcher::SetMainThreadId() took 15μs <<<

>>> INITIALIZATION: OpenGL context setup took 884μs <<<
>>> INITIALIZATION: Window list registration took 5μs <<<
>>> INITIALIZATION: GLFW callback setup took 25μs <<<
>>> INITIALIZATION: Scene2D setup took 120μs <<<
>>> INITIALIZATION: App::Closing event registration took 8μs <<<
>>> INITIALIZATION: DPI scale detection took 45μs <<<
>>> INITIALIZATION: SetDPIScale() took 1250μs <<<
>>> INITIALIZATION: Framebuffer initialization took 634μs <<<
>>> INITIALIZATION: OnInitializeComponent() took 2340μs <<<

================================================
>>> INITIALIZATION SUMMARY <<<
Total Initialize() time: 15420μs (15.42ms)
Total from construction: 25980μs (25.98ms)
================================================

>>> INITIALIZATION: OpenGLExtensions::Initialize2D() took 450μs <<<
```

## Inheritance Chain Considerations

The Window class inherits from:
- **InputContent**: Handles input events and content management
- **WindowStyleProperty**: Manages window styling properties
- **WindowStateProperty**: Manages window state (minimized, maximized, etc.)

The timing measurements include:
- Virtual method calls that may invoke base class implementations
- Property setters that might trigger inheritance chain calls
- Event registration that involves multiple inheritance layers

## Key Metrics Explained

### Constructor Metrics:
- **App::Settings() calls**: Can be slow if configuration files are being read
- **glfwInit()**: One-time GLFW library initialization (only slow on first call)
- **SetBrushGroup()/SetName()**: Usually fast unless complex theming is involved

### Initialize() Metrics:
- **OpenGL context setup**: Graphics driver initialization time
- **GLFW callback setup**: Should be very fast (just function pointer assignments)
- **Scene2D setup**: Scene graph initialization
- **SetDPIScale()**: Can be slow if it triggers content layout updates
- **OnInitializeComponent()**: Derived class initialization - timing depends on implementation

### Show() Metrics:
- **OpenGLExtensions::Initialize2D()**: OpenGL shader and extension setup

## Performance Analysis

Use this debug output to identify:
- Which initialization steps are unexpectedly slow
- Whether inheritance chain calls are adding overhead
- If virtual method calls are performant
- Where graphics driver initialization occurs
- Content layout and theming overhead

## Typical Timing Ranges

On modern systems:
- **Fast operations** (< 50μs): Property setters, callback registration, simple initializations
- **Medium operations** (50-500μs): Scene setup, DPI detection, framebuffer creation
- **Slow operations** (> 500μs): Graphics driver init, content layout, file I/O operations

Significantly longer times may indicate:
- Complex inheritance chain overhead
- Expensive virtual method implementations
- Graphics driver issues
- File system access during initialization
- Network or database operations in derived classes

## Usage with Other Debug Flags

This debug output complements:
- `DEBUG_WINDOW`: High-level window construction timing
- `DEBUG_WINDOW2`: Detailed rendering and frame timing

Use together for complete performance analysis of window lifecycle.
