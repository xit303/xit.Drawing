#include <map>
#include <chrono>
#include <Exceptions.h>
#include <Application/App.h>

#include <Clipboard.h>
#include <Input/InputHandler.h>

#include <Drawing/ToolTip.h>
#include <Drawing/Window.h>
#include <Drawing/DebugUtils.h>
#include <Drawing/Theme/BrushPool.h>
// #include <Drawing/Container.h>
#include <Threading/Dispatcher.h>

using namespace xit;

#define ERROR(x)            \
    {                       \
        fprintf(stderr, x); \
        fflush(stderr);     \
    }
#define ERRORT(x)           \
    {                       \
        fprintf(stderr, x); \
        fflush(stderr);     \
        glfwTerminate();    \
    }

static Window *lastActiveInstance = nullptr;
static Window *activeInstance = nullptr;

static Point mousePosition;
// static char mouseButtons[GLFW_MOUSE_BUTTON_LAST + 1];

static std::map<GLFWwindow *, Window *> windowList;

static void WindowPositionCallback(GLFWwindow *window, int left, int top)
{
    if (activeInstance == nullptr)
    {
        throw NullReferenceException("activeInstance");
    }
    else
    {
        activeInstance->SetWindowPos(left, top);
    }
}
static void FramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    if (activeInstance == nullptr)
    {
        throw NullReferenceException("activeInstance");
    }
    else
    {
        activeInstance->SetWindowSize(width, height);
    }
}

/*! @brief The function signature for keyboard key callbacks.
 *
 *  This is the function signature for keyboard key callback functions.
 *
 *  @param[in] window The window that received the event.
 *  @param[in] key The [keyboard key](@ref keys) that was pressed or released.
 *  @param[in] scancode The system-specific scancode of the key.
 *  @param[in] action `GLFW_PRESS`, `GLFW_RELEASE` or `GLFW_REPEAT`.
 *  @param[in] mods Bit field describing which [modifier keys](@ref mods) were
 *  held down.
 *
 *  @sa glfwSetKeyCallback
 *
 *  @ingroup input
 */
static void KeyboardCallback(GLFWwindow *window, int key, int scancode, int action, int modifierKeys)
{
    if (activeInstance == nullptr)
    {
        throw NullReferenceException("activeInstance");
    }
    else
    {
        xit::Clipboard::Clipboard::SetWindow(window);

        char keyChar = static_cast<char>(key);
        CKey c = (CKey)key;

        if (c == CKey::KpEnter)
            c = CKey::Enter;

        int modifiers = (int)InputHandler::GetModifiers();

        if (action == GLFW_PRESS)
        {
            if (c == CKey::LeftControl || c == CKey::RightControl)
                modifiers |= (int)ModifierKeys::Control;
            else if (c == CKey::LeftShift || c == CKey::RightShift)
                modifiers |= (int)ModifierKeys::Shift;
            else if (c == CKey::LeftAlt || c == CKey::RightAlt)
                modifiers |= (int)ModifierKeys::Alt;
            else if (c == CKey::LeftSuper || c == CKey::RightSuper)
                modifiers |= (int)ModifierKeys::Super;
        }
        else if (action == GLFW_RELEASE)
        {
            if (c == CKey::LeftControl || c == CKey::RightControl)
                modifiers &= ~(int)ModifierKeys::Control;
            else if (c == CKey::LeftShift || c == CKey::RightShift)
                modifiers &= ~(int)ModifierKeys::Shift;
            else if (c == CKey::LeftAlt || c == CKey::RightAlt)
                modifiers &= ~(int)ModifierKeys::Alt;
            else if (c == CKey::LeftSuper || c == CKey::RightSuper)
                modifiers &= ~(int)ModifierKeys::Super;
        }

        InputHandler::SetModifiers((ModifierKeys)modifiers);

        if (!InputHandler::IsShift() && c >= CKey::A && c <= CKey::Z)
        {
            keyChar = static_cast<char>('a' + ((int)c - (int)CKey::A));
        }
        KeyEventArgs e(c, keyChar, modifierKeys);

        if (action == GLFW_PRESS || action == GLFW_REPEAT)
        {
            activeInstance->ExecuteKeyDown(e);
        }
        else if (action == GLFW_RELEASE)
        {
            activeInstance->ExecuteKeyUp(e);
        }
    }
}

/*! @brief
 *
 *  This is the function signature for mouse button callback functions.
 *
 *  @param[in] window The window that received the event.
 *  @param[in] button The [mouse button](@ref buttons) that was pressed or
 *  released.
 *  @param[in] action One of `GLFW_PRESS` or `GLFW_RELEASE`.
 *  @param[in] mods Bit field describing which [modifier keys](@ref mods) were
 *  held down.
 *
 *  @sa glfwSetMouseButtonCallback
 *
 *  @ingroup input
 */
static void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
    if (activeInstance == nullptr)
    {
        throw NullReferenceException("activeInstance");
    }
    else
    {
        MouseButton mouseButton = (MouseButton)(button + 1);

        if (action == GLFW_PRESS)
        {
            MouseEventArgs e(mouseButton, mousePosition);
            activeInstance->ExecuteInputPressed(e);
        }
        else if (action == GLFW_RELEASE)
        {
            MouseEventArgs e(mouseButton, mousePosition);
            activeInstance->ExecuteInputReleased(e);
        }
        else
        {
            MouseEventArgs e(mouseButton, mousePosition);
            activeInstance->ExecuteInputReleased(e);
        }
    }
}
static void CursorPositionCallback(GLFWwindow *window, double x, double y)
{
    if (activeInstance == nullptr)
    {
        throw NullReferenceException("activeInstance");
    }
    else
    {
        mousePosition.X = (int)x;
        mousePosition.Y = (int)y;
        MouseEventArgs e(mousePosition);
        activeInstance->ExecuteInputMove(e);
    }
}
/*! @brief The function signature for cursor enter/leave callbacks.
 *
 *  This is the function signature for cursor enter/leave callback functions.
 *
 *  @param[in] window The window that received the event.
 *  @param[in] entered `GL_TRUE` if the cursor entered the window's client
 *  area, or `GL_FALSE` if it left it.
 *
 *  @sa glfwSetCursorEnterCallback
 *
 *  @ingroup input
 */
static void CursorEnterCallback(GLFWwindow *window, int entered)
{
    if (activeInstance == nullptr)
    {
        throw NullReferenceException("activeInstance");
    }
    else
    {
        if (entered)
        {
            EventArgs e;
            activeInstance->ExecuteInputEnter(e);
        }
        else
        {
            MouseEventArgs me(mousePosition);
            activeInstance->ExecuteInputLeave(me);
        }
    }
}
/*! @brief The function signature for scroll callbacks.
 *
 *  This is the function signature for scroll callback functions.
 *
 *  @param[in] window The window that received the event.
 *  @param[in] xoffset The scroll offset along the x-axis.
 *  @param[in] yoffset The scroll offset along the y-axis.
 *
 *  @sa glfwSetScrollCallback
 *
 *  @ingroup input
 */
static void CursorScrollCallback(GLFWwindow *window, double xOffset, double yOffset)
{
    if (activeInstance == nullptr)
    {
        throw NullReferenceException("activeInstance");
    }
    else
    {
        MouseEventArgs e((int)yOffset, mousePosition);
        activeInstance->ExecuteInputScroll(e);
    }
}

static void WindowContentScaleCallback(GLFWwindow *glFwWindow, float scaleX, float scaleY)
{
    Window *window = windowList[glFwWindow];
    if (window)
        window->SetDPIScale(scaleX, scaleY);
}

/*! @brief The function pointer type for window maximize callbacks.
 *
 *  This is the function pointer type for window maximize callbacks.  A window
 *  maximize callback function has the following signature:
 *  @code
 *  void function_name(GLFWwindow* window, int maximized)
 *  @endcode
 *
 *  @param[in] window The window that was maximized or restored.
 *  @param[in] maximized `GLFW_TRUE` if the window was maximized, or
 *  `GLFW_FALSE` if it was restored.
 *
 *  @sa @ref window_maximize
 *  @sa glfwSetWindowMaximizeCallback
 *
 *  @since Added in version 3.3.
 *
 *  @ingroup window
 */
static void WindowMaximizeCallback(GLFWwindow *window, int maximized)
{
    if (activeInstance == nullptr)
    {
        throw NullReferenceException("activeInstance");
    }
    else
    {
        activeInstance->SetWindowState(maximized ? WindowState::Maximized : WindowState::Normal);
    }
}

/*! @brief The function pointer type for window iconify callbacks.
 *
 *  This is the function pointer type for window iconify callbacks.  A window
 *  iconify callback function has the following signature:
 *  @code
 *  void function_name(GLFWwindow* window, int iconified)
 *  @endcode
 *
 *  @param[in] window The window that was iconified or restored.
 *  @param[in] iconified `GLFW_TRUE` if the window was iconified, or
 *  `GLFW_FALSE` if it was restored.
 *
 *  @sa @ref window_iconify
 *  @sa @ref glfwSetWindowIconifyCallback
 *
 *  @since Added in version 3.0.
 *
 *  @ingroup window
 */
static void WindowIconifyCallback(GLFWwindow *window, int iconified)
{
    if (activeInstance == nullptr)
    {
        throw NullReferenceException("activeInstance");
    }
    else
    {
        if (iconified)
            activeInstance->SetWindowState(WindowState::Minimized);
        else
            activeInstance->SetWindowState(WindowState::Normal);
    }
}

static void WindowCloseCallback(GLFWwindow *window)
{
    // App::Close();
}

namespace xit::Drawing
{
    void Window::SetTitle(const std::string &value)
    {
        if (title != value)
        {
            title = value;
            glfwSetWindowTitle(window, title.c_str());
        }
    }

    void Window::InvalidateRegion(Visual *visual, Rectangle bounds)
    {
#ifdef DEBUG_WINDOW2
        std::cout << "InvalidateRegion: Adding region for visual '"
                  << (visual ? visual->GetName() : "null") << "' bounds("
                  << bounds.GetLeft() << "," << bounds.GetTop()
                  << "," << bounds.GetWidth() << "," << bounds.GetHeight() << ")" << std::endl;
#endif
        {
            std::lock_guard<std::mutex> lock(invalidRegionsMutex);
            invalidRegions.push_back({visual, bounds});
#ifdef DEBUG_WINDOW2
            std::cout << "InvalidateRegion: Total invalid regions now: " << invalidRegions.size() << std::endl;
#endif
        }
        ScheduleRedraw();
    }

    Window::Window()
    {
#ifdef DEBUG_WINDOW
        // Record construction start time for debugging
        constructionStartTime = std::chrono::steady_clock::now();
        std::cout << "\n>>> WINDOW CONSTRUCTION TIMING: Constructor started at "
                  << std::chrono::duration_cast<std::chrono::microseconds>(
                         constructionStartTime.time_since_epoch())
                         .count()
                  << "μs <<<" << std::endl;
#endif

        window = nullptr;
        content = nullptr;

        topmost = false;
        isClosing = false;
        canFocus = false;
        isFocused = false;
        isInputPressed = false;
        handleMouse = false;
        isMouseOver = false;
        isDestroyed = false;

#ifdef DEBUG_INITIALIZATION
        auto appSettingsStart = std::chrono::steady_clock::now();
#endif
        contentScaleX = App::Settings().GetAppScaleX();
        contentScaleY = App::Settings().GetAppScaleY();
#ifdef DEBUG_INITIALIZATION
        auto appSettingsEnd = std::chrono::steady_clock::now();
        auto appSettingsDuration = std::chrono::duration_cast<std::chrono::microseconds>(
            appSettingsEnd - appSettingsStart);
        std::cout << ">>> INITIALIZATION: App::Settings() calls took "
                  << appSettingsDuration.count() << "μs <<<" << std::endl;
#endif

        backgroundTexture = 0;

        // Initialize double buffering members
        frontFramebuffer = 0;
        backFramebuffer = 0;
        frontColorTexture = 0;
        backColorTexture = 0;
        frontDepthTexture = 0;
        backDepthTexture = 0;
        framebuffersInitialized = false;

        // Initialize timing debug variables
        firstFrameCompleted = false;

#ifdef DEBUG_INITIALIZATION
        std::cout << ">>> INITIALIZATION: BrushPool has " << BrushPool::GetPoolSize()
                  << " unique colors before SetBrushGroup() <<<" << std::endl;
        auto setBrushGroupStart = std::chrono::steady_clock::now();
        std::cout << ">>> DEBUG: About to call SetBrushGroup('Window') <<<" << std::endl;
#endif
        SetBrushGroup("Window");
#ifdef DEBUG_INITIALIZATION
        std::cout << ">>> DEBUG: SetBrushGroup('Window') completed <<<" << std::endl;
        auto setBrushGroupEnd = std::chrono::steady_clock::now();
        auto setBrushGroupDuration = std::chrono::duration_cast<std::chrono::microseconds>(
            setBrushGroupEnd - setBrushGroupStart);
        std::cout << ">>> INITIALIZATION: SetBrushGroup() took "
                  << setBrushGroupDuration.count() << "μs <<<" << std::endl;
        std::cout << ">>> INITIALIZATION: BrushPool now has " << BrushPool::GetPoolSize()
                  << " unique colors after SetBrushGroup() <<<" << std::endl;
#endif

#ifdef DEBUG_INITIALIZATION
        auto setNameStart = std::chrono::steady_clock::now();
#endif
        SetName("Window");
#ifdef DEBUG_INITIALIZATION
        auto setNameEnd = std::chrono::steady_clock::now();
        auto setNameDuration = std::chrono::duration_cast<std::chrono::microseconds>(
            setNameEnd - setNameStart);
        std::cout << ">>> INITIALIZATION: SetName() took "
                  << setNameDuration.count() << "μs <<<" << std::endl;
#endif

#ifdef DEBUG_INITIALIZATION
        auto glfwInitStart = std::chrono::steady_clock::now();
#endif
        if (!glfwInit())
        {
            ERROR("Failed to initialize GLFW");
            return;
        }
#ifdef DEBUG_INITIALIZATION
        auto glfwInitEnd = std::chrono::steady_clock::now();
        auto glfwInitDuration = std::chrono::duration_cast<std::chrono::microseconds>(
            glfwInitEnd - glfwInitStart);
        std::cout << ">>> INITIALIZATION: glfwInit() took "
                  << glfwInitDuration.count() << "μs <<<" << std::endl;
#endif

#ifdef DEBUG_INITIALIZATION
        auto glfwHintsStart = std::chrono::steady_clock::now();
#endif
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef DEBUG_INITIALIZATION
        auto glfwHintsEnd = std::chrono::steady_clock::now();
        auto glfwHintsDuration = std::chrono::duration_cast<std::chrono::microseconds>(
            glfwHintsEnd - glfwHintsStart);
        std::cout << ">>> INITIALIZATION: GLFW window hints took "
                  << glfwHintsDuration.count() << "μs <<<" << std::endl;
#endif

#ifdef DEBUG_INITIALIZATION
        auto dispatcherStart = std::chrono::steady_clock::now();
#endif
        Dispatcher::SetMainThreadId();
#ifdef DEBUG_INITIALIZATION
        auto dispatcherEnd = std::chrono::steady_clock::now();
        auto dispatcherDuration = std::chrono::duration_cast<std::chrono::microseconds>(
            dispatcherEnd - dispatcherStart);
        std::cout << ">>> INITIALIZATION: Dispatcher::SetMainThreadId() took "
                  << dispatcherDuration.count() << "μs <<<" << std::endl;
#endif

#ifdef OSX
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // OSX
    }

    //******************************************************************************
    // Private
    //******************************************************************************

    void Window::App_Closing(EventArgs &e)
    {
        Close();
    }

    void Window::ScheduleRedraw()
    {
        if (!redrawScheduled.exchange(true))
        {
#ifdef DEBUG_WINDOW2
            std::cout << "Window::ScheduleRedraw - Scheduling redraw" << std::endl;
#endif
#ifdef DEBUG_VISUAL_STATES
            std::cout << "[DEBUG] Window::ScheduleRedraw() - Scheduling redraw" << std::endl;
#endif

            // Signal the main loop that a redraw is needed
            mainLoopSemaphore.release();
        }
        else
        {
#ifdef DEBUG_WINDOW2
            std::cout << "Window::ScheduleRedraw - Redraw already scheduled" << std::endl;
#endif
#ifdef DEBUG_VISUAL_STATES
            std::cout << "[DEBUG] Window::ScheduleRedraw() - Redraw already scheduled" << std::endl;
#endif
        }
    }

    //******************************************************************************
    // Protected overrides
    //******************************************************************************

    void Window::OnWindowStateChanged(EventArgs &e)
    {
        if (GetWindowState() != WindowState::Minimized)
            Invalidate();
    }

    void Window::OnUpdate(const Rectangle &bounds)
    {
        bool needClientUpdate = GetNeedLeftRecalculation() || GetNeedTopRecalculation() || GetNeedWidthRecalculation() || GetNeedHeightRecalculation();

        // Also update content when window is invalidated (even if window size/position unchanged)
        // This handles cases where content invalidates and window needs to update its content layout
        bool needContentUpdate = needClientUpdate || GetInvalidated();

#ifdef DEBUG_WINDOW2
        std::cout << "Window::OnUpdate called. needClientUpdate=" << needClientUpdate
                  << " needContentUpdate=" << needContentUpdate
                  << " invalidated=" << GetInvalidated()
                  << " bounds=(" << bounds.GetLeft() << "," << bounds.GetTop()
                  << "," << bounds.GetWidth() << "," << bounds.GetHeight() << ")" << std::endl;
#endif

        InputContent::OnUpdate(bounds);

        if (needContentUpdate)
        {
#ifdef DEBUG_WINDOW2
            std::cout << "Window::OnUpdate - Updating client bounds and content" << std::endl;
#endif
            // Use optimized BoxModel method for client bounds calculation
            clientBounds = GetClientRectangle(0, 0, GetActualWidth(), GetActualHeight());

            if (content)
            {
#ifdef DEBUG_WINDOW2
                std::cout << "Window::OnUpdate - Updating content with clientBounds=("
                          << clientBounds.GetLeft() << "," << clientBounds.GetTop()
                          << "," << clientBounds.GetWidth() << "," << clientBounds.GetHeight() << ")" << std::endl;
#endif
                content->Update(clientBounds);
                ToolTip::DoUpdate(clientBounds);
            }
            else
            {
#ifdef DEBUG_WINDOW2
                std::cout << "Window::OnUpdate - WARNING: No content to update!" << std::endl;
#endif
            }
        }
        else
        {
#ifdef DEBUG_WINDOW2
            std::cout << "Window::OnUpdate - No client update needed" << std::endl;
#endif
        }
    }

    void Window::OnInvalidated(EventArgs &e)
    {
        // Call base implementation
        InputContent::OnInvalidated(e);
    }
    void Window::OnRender()
    {
        InputContent::OnRender();
        if (content)
        {
            content->Render();
            ToolTip::DoRender();
        }
    }

    //******************************************************************************
    // Protected
    //******************************************************************************

    bool Window::OnClosing(bool canceled)
    {
        SaveState();

        return canceled;
    }

    //******************************************************************************
    // Public overrides
    //******************************************************************************

    void Window::ExecuteInputEnter(EventArgs &e)
    {
        if (content)
        {
            InputContent *inputContent = dynamic_cast<InputContent *>(content);
            if (inputContent)
                inputContent->ExecuteInputEnter(e);
        }
        else
        {
            InputContent::ExecuteInputEnter(e);
        }
    }
    void Window::ExecuteInputLeave(MouseEventArgs &e)
    {
        if (content)
        {
            InputContent *inputContent = dynamic_cast<InputContent *>(content);
            if (inputContent)
                inputContent->ExecuteInputLeave(e);
        }
        else
        {
            InputContent::ExecuteInputLeave(e);
        }
    }

    void Window::ExecuteInputPressed(MouseEventArgs &e)
    {
        if (!InputHandler::CheckInputPressed(e) && content && InputHandler::IsHit(*dynamic_cast<IFocus *>(content), e.Position))
        {
            InputContent *inputContent = dynamic_cast<InputContent *>(content);
            if (inputContent)
                inputContent->ExecuteInputPressed(e);
        }
        if (!e.Handled)
        {
            InputContent::ExecuteInputPressed(e);
        }
    }
    void Window::ExecuteInputReleased(MouseEventArgs &e)
    {
        if (!InputHandler::CheckInputReleased(e) && content && InputHandler::IsHit(*dynamic_cast<IFocus *>(content), e.Position))
        {
            InputContent *inputContent = dynamic_cast<InputContent *>(content);
            if (inputContent)
                inputContent->ExecuteInputReleased(e);
        }
        else
        {
            InputContent::ExecuteInputReleased(e);
        }
        if (!e.Handled)
        {
            InputContent::ExecuteInputReleased(e);
        }
    }

    void Window::ExecuteInputScroll(MouseEventArgs &e)
    {
        if (!InputHandler::CheckInputScroll(e) && content && InputHandler::IsHit(*dynamic_cast<IFocus *>(content), e.Position))
        {
            InputContent *inputContent = dynamic_cast<InputContent *>(content);
            if (inputContent)
                inputContent->ExecuteInputScroll(e);
        }
        if (!e.Handled)
        {
            InputContent::ExecuteInputScroll(e);
        }
    }
    void Window::ExecuteInputMove(MouseEventArgs &e)
    {
        if (!InputHandler::CheckInputMove(e) && content && InputHandler::IsHit(*dynamic_cast<IFocus *>(content), e.Position))
        {
            InputContent *inputContent = dynamic_cast<InputContent *>(content);
            if (inputContent)
                inputContent->ExecuteInputMove(e);
        }
        if (!e.Handled)
        {
            InputContent::ExecuteInputMove(e);
        }
    }

    void Window::ExecuteKeyDown(KeyEventArgs &e)
    {
        if (!InputHandler::CheckKeyDown(e) && content)
        {
            InputContent *inputContent = dynamic_cast<InputContent *>(content);
            if (inputContent)
                inputContent->ExecuteKeyDown(e);
        }

        if (!e.Handled)
        {
            SetIsFocused(true);
            InputContent::ExecuteKeyDown(e);
        }
    }
    void Window::ExecuteKeyUp(KeyEventArgs &e)
    {
        if (!InputHandler::CheckKeyUp(e) && content)
        {
            InputContent *inputContent = dynamic_cast<InputContent *>(content);
            if (inputContent)
                inputContent->ExecuteKeyUp(e);
        }
        if (!e.Handled)
        {
            SetIsFocused(true);
            InputContent::ExecuteKeyUp(e);
        }
    }

    int Window::MeasureWidth(int availableSize)
    {
        // Ensure availableSize is non-negative
        if (availableSize <= 0)
        {
            return 0; // No available width
        }

        // a window always returns all the available size minus the border and padding
        int desiredWidth = std::max(0, availableSize - GetPadding().GetWidth() - GetBorderThickness().GetWidth());
        desiredSize.SetWidth(desiredWidth);
        return desiredWidth;
    }

    int Window::MeasureHeight(int availableSize)
    {
        // Ensure availableSize is non-negative
        if (availableSize <= 0)
        {
            return 0; // No available width
        }

        // a window always returns all the available size minus the border and padding
        int desiredHeight = std::max(0, availableSize - GetPadding().GetHeight() - GetBorderThickness().GetHeight());
        desiredSize.SetHeight(desiredHeight);
        return desiredHeight;
    }

    //******************************************************************************
    // Public
    //******************************************************************************

    bool Window::Initialize(const WindowSettings &windowSettings, const std::string &title)
    {
        // Record initialization start time for debugging
        initializeStartTime = std::chrono::steady_clock::now();

#ifdef DEBUG_WINDOW
        auto constructionDuration = std::chrono::duration_cast<std::chrono::microseconds>(
            initializeStartTime - constructionStartTime);
        std::cout << "\n>>> WINDOW CONSTRUCTION TIMING: Initialize() started after "
                  << constructionDuration.count() << "μs from construction <<<" << std::endl;
#endif

        this->windowSettings = windowSettings;

#ifdef DEBUG_WINDOW
        auto windowCreateStart = std::chrono::steady_clock::now();
#endif
        window = glfwCreateWindow(windowSettings.GetWidth(), windowSettings.GetHeight(), title.c_str(), NULL, NULL);
        if (window == NULL)
        {
            ERRORT("Failed to create GLFW window");
            return false;
        }
#ifdef DEBUG_WINDOW
        auto windowCreateEnd = std::chrono::steady_clock::now();
        auto windowCreateDuration = std::chrono::duration_cast<std::chrono::microseconds>(
            windowCreateEnd - windowCreateStart);
        std::cout << ">>> WINDOW CONSTRUCTION TIMING: GLFW window creation took "
                  << windowCreateDuration.count() << "μs <<<" << std::endl;
#endif

        glfwSetWindowPos(window, windowSettings.GetLeft(), windowSettings.GetTop());

#if defined(DEBUG_INITIALIZATION) || defined(DEBUG_WINDOW)
        auto contextSetupStart = std::chrono::steady_clock::now();
#endif
        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            ERRORT("Failed to initialize GLAD");
            return false;
        }
#if defined(DEBUG_INITIALIZATION) || defined(DEBUG_WINDOW)
        auto contextSetupEnd = std::chrono::steady_clock::now();
        auto contextSetupDuration = std::chrono::duration_cast<std::chrono::microseconds>(
            contextSetupEnd - contextSetupStart);
#endif
#ifdef DEBUG_INITIALIZATION
        std::cout << ">>> INITIALIZATION: OpenGL context setup took "
                  << contextSetupDuration.count() << "μs <<<" << std::endl;
#endif
#ifdef DEBUG_WINDOW
        std::cout << ">>> WINDOW CONSTRUCTION TIMING: OpenGL context setup took "
                  << contextSetupDuration.count() << "μs <<<" << std::endl;
#endif

#ifdef DEBUG_INITIALIZATION
        auto windowListStart = std::chrono::steady_clock::now();
#endif
        windowList.emplace(std::make_pair(window, this));
#ifdef DEBUG_INITIALIZATION
        auto windowListEnd = std::chrono::steady_clock::now();
        auto windowListDuration = std::chrono::duration_cast<std::chrono::microseconds>(
            windowListEnd - windowListStart);
        std::cout << ">>> INITIALIZATION: Window list registration took "
                  << windowListDuration.count() << "μs <<<" << std::endl;
#endif

#ifdef DEBUG_INITIALIZATION
        auto callbacksStart = std::chrono::steady_clock::now();
#endif
        glfwSetWindowPosCallback(window, WindowPositionCallback);
        glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
        glfwSetKeyCallback(window, KeyboardCallback);
        glfwSetMouseButtonCallback(window, MouseButtonCallback);
        glfwSetCursorPosCallback(window, CursorPositionCallback);
        glfwSetCursorEnterCallback(window, CursorEnterCallback);
        glfwSetScrollCallback(window, CursorScrollCallback);
        glfwSetWindowContentScaleCallback(window, WindowContentScaleCallback);
        glfwSetWindowMaximizeCallback(window, WindowMaximizeCallback);
        glfwSetWindowIconifyCallback(window, WindowIconifyCallback);
        glfwSetWindowCloseCallback(window, WindowCloseCallback);
#ifdef DEBUG_INITIALIZATION
        auto callbacksEnd = std::chrono::steady_clock::now();
        auto callbacksDuration = std::chrono::duration_cast<std::chrono::microseconds>(
            callbacksEnd - callbacksStart);
        std::cout << ">>> INITIALIZATION: GLFW callback setup took "
                  << callbacksDuration.count() << "μs <<<" << std::endl;
#endif

#ifdef DEBUG_INITIALIZATION
        auto sceneSetupStart = std::chrono::steady_clock::now();
#endif
        scene.Resize(windowSettings.GetWidth(), windowSettings.GetHeight());
        Scene2D::MakeCurrent(&scene);
#ifdef DEBUG_INITIALIZATION
        auto sceneSetupEnd = std::chrono::steady_clock::now();
        auto sceneSetupDuration = std::chrono::duration_cast<std::chrono::microseconds>(
            sceneSetupEnd - sceneSetupStart);
        std::cout << ">>> INITIALIZATION: Scene2D setup took "
                  << sceneSetupDuration.count() << "μs <<<" << std::endl;
#endif

        // SetBrushGroup("Window");

        // glfwSetWindowSizeLimits(window,
        //                         (MinWidth > 0 ? MinWidth : GLFW_DONT_CARE),
        //                         (MinHeight > 0 ? MinHeight : GLFW_DONT_CARE),
        //                         (MaxWidth != -1 ? MaxWidth : GLFW_DONT_CARE),
        //                         (MaxHeight != -1 ? MaxHeight : GLFW_DONT_CARE));

#ifdef DEBUG_INITIALIZATION
        auto appClosingStart = std::chrono::steady_clock::now();
#endif
        App::Closing.Add(&Window::App_Closing, this);
#ifdef DEBUG_INITIALIZATION
        auto appClosingEnd = std::chrono::steady_clock::now();
        auto appClosingDuration = std::chrono::duration_cast<std::chrono::microseconds>(
            appClosingEnd - appClosingStart);
        std::cout << ">>> INITIALIZATION: App::Closing event registration took "
                  << appClosingDuration.count() << "μs <<<" << std::endl;
#endif

#ifdef DEBUG_INITIALIZATION
        auto dpiDetectionStart = std::chrono::steady_clock::now();
#endif
        float scaleX = 1;
        float scaleY = 1;
        glfwGetWindowContentScale(window, &scaleX, &scaleY);
#ifdef DEBUG_INITIALIZATION
        auto dpiDetectionEnd = std::chrono::steady_clock::now();
        auto dpiDetectionDuration = std::chrono::duration_cast<std::chrono::microseconds>(
            dpiDetectionEnd - dpiDetectionStart);
        std::cout << ">>> INITIALIZATION: DPI scale detection took "
                  << dpiDetectionDuration.count() << "μs <<<" << std::endl;
#endif

        // SetDPIScale override for Window calls Invalidate() to take the semaphore
#ifdef DEBUG_INITIALIZATION
        auto setDPIScaleStart = std::chrono::steady_clock::now();
#endif
        SetDPIScale(scaleX, scaleY);
#ifdef DEBUG_INITIALIZATION
        auto setDPIScaleEnd = std::chrono::steady_clock::now();
        auto setDPIScaleDuration = std::chrono::duration_cast<std::chrono::microseconds>(
            setDPIScaleEnd - setDPIScaleStart);
        std::cout << ">>> INITIALIZATION: SetDPIScale() took "
                  << setDPIScaleDuration.count() << "μs <<<" << std::endl;
#endif

        // Initialize framebuffers for double buffering
#if defined(DEBUG_INITIALIZATION) || defined(DEBUG_WINDOW)
        auto framebufferInitStart = std::chrono::steady_clock::now();
#endif
        InitializeFramebuffers();
#if defined(DEBUG_INITIALIZATION) || defined(DEBUG_WINDOW)
        auto framebufferInitEnd = std::chrono::steady_clock::now();
        auto framebufferDuration = std::chrono::duration_cast<std::chrono::microseconds>(
            framebufferInitEnd - framebufferInitStart);
#endif
#ifdef DEBUG_INITIALIZATION
        std::cout << ">>> INITIALIZATION: Framebuffer initialization took "
                  << framebufferDuration.count() << "μs <<<" << std::endl;
#endif
#ifdef DEBUG_WINDOW
        std::cout << ">>> WINDOW CONSTRUCTION TIMING: Framebuffer initialization took "
                  << framebufferDuration.count() << "μs <<<" << std::endl;
#endif

#ifdef DEBUG_INITIALIZATION
        auto onInitializeComponentStart = std::chrono::steady_clock::now();
#endif
        OnInitializeComponent();
#ifdef DEBUG_INITIALIZATION
        auto onInitializeComponentEnd = std::chrono::steady_clock::now();
        auto onInitializeComponentDuration = std::chrono::duration_cast<std::chrono::microseconds>(
            onInitializeComponentEnd - onInitializeComponentStart);
        std::cout << ">>> INITIALIZATION: OnInitializeComponent() took "
                  << onInitializeComponentDuration.count() << "μs <<<" << std::endl;
#endif

#ifdef DEBUG_WINDOW
        auto initializeEndTime = std::chrono::steady_clock::now();
        auto initializeDuration = std::chrono::duration_cast<std::chrono::microseconds>(
            initializeEndTime - initializeStartTime);
        auto totalFromConstruction = std::chrono::duration_cast<std::chrono::microseconds>(
            initializeEndTime - constructionStartTime);
        std::cout << "\n>>> WINDOW CONSTRUCTION TIMING: Initialize() completed in "
                  << initializeDuration.count() << "μs (total from construction: "
                  << totalFromConstruction.count() << "μs) <<<" << std::endl;
#endif

#ifdef DEBUG_INITIALIZATION
        auto initializeEndTimeInit = std::chrono::steady_clock::now();
        auto initializeDurationInit = std::chrono::duration_cast<std::chrono::microseconds>(
            initializeEndTimeInit - initializeStartTime);
        auto totalFromConstructionInit = std::chrono::duration_cast<std::chrono::microseconds>(
            initializeEndTimeInit - constructionStartTime);

        std::cout << "\n================================================" << std::endl;
        std::cout << ">>> INITIALIZATION SUMMARY <<<" << std::endl;
        std::cout << "Total Initialize() time: " << initializeDurationInit.count() << "μs ("
                  << (initializeDurationInit.count() / 1000.0) << "ms)" << std::endl;
        std::cout << "Total from construction: " << totalFromConstructionInit.count() << "μs ("
                  << (totalFromConstructionInit.count() / 1000.0) << "ms)" << std::endl;
        std::cout << "================================================\n"
                  << std::endl;
#endif

        return true;
    }
    void Window::Show()
    {
        // Record show start time for debugging
        showStartTime = std::chrono::steady_clock::now();

#ifdef DEBUG_WINDOW
        auto showDelay = std::chrono::duration_cast<std::chrono::microseconds>(
            showStartTime - constructionStartTime);
        std::cout << "\n>>> WINDOW CONSTRUCTION TIMING: Show() started "
                  << showDelay.count() << "μs after construction <<<" << std::endl;
#endif

        if (activeInstance != nullptr)
        {
            lastActiveInstance = activeInstance;
        }

        activeInstance = this;

#ifdef DEBUG_INITIALIZATION
        auto openGLExtensionsStart = std::chrono::steady_clock::now();
#endif
        OpenGLExtensions::Initialize2D(scene);
#ifdef DEBUG_INITIALIZATION
        auto openGLExtensionsEnd = std::chrono::steady_clock::now();
        auto openGLExtensionsDuration = std::chrono::duration_cast<std::chrono::microseconds>(
            openGLExtensionsEnd - openGLExtensionsStart);
        std::cout << ">>> INITIALIZATION: OpenGLExtensions::Initialize2D() took "
                  << openGLExtensionsDuration.count() << "μs <<<" << std::endl;
#endif

        while (!glfwWindowShouldClose(window) && !isDestroyed)
        {
            using namespace std::literals;

            // Add frame rate limiting to prevent excessive rendering during resize
            static auto lastRenderTime = std::chrono::steady_clock::now();
            auto currentTime = std::chrono::steady_clock::now();
            auto timeSinceLastRender = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastRenderTime);

            // Limit to ~60 FPS (16ms between frames) to reduce resize flicker
            bool canRender = timeSinceLastRender.count() >= 16;

#ifdef DEBUG_WINDOW
            static int frameCount = 0;
            static auto lastFpsReport = currentTime;
            frameCount++;

            auto timeSinceLastFpsReport = std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastFpsReport);
            if (timeSinceLastFpsReport.count() >= 5) // Report FPS every 5 seconds
            {
                double fps = frameCount / 5.0;
                std::cout << "\n>>> PERFORMANCE REPORT: " << fps << " FPS (avg frame time: "
                          << (5000.0 / frameCount) << "ms) <<<\n"
                          << std::endl;
                frameCount = 0;
                lastFpsReport = currentTime;
            }
#endif

            if (canRender && mainLoopSemaphore.try_acquire_for(std::chrono::milliseconds(1)))
            {
#ifdef DEBUG_WINDOW2
                if (timeSinceLastRender.count() > 20) // Log if frame took longer than expected
                {
                    std::cout << "Frame gap: " << timeSinceLastRender.count() << "ms (target: 16ms)" << std::endl;
                }
#endif
                DoRender();
                lastRenderTime = currentTime;
            }

            Dispatcher::Run();
            glfwPollEvents();
        }

        if (lastActiveInstance != nullptr)
        {
            activeInstance = lastActiveInstance;
        }

        Close();
    }
    void Window::Close()
    {
        isClosing = true;

        bool canceled = OnClosing(false);

        if (!glfwWindowShouldClose(window))
        {
            if (!canceled)
                glfwSetWindowShouldClose(window, true);
            else
                isClosing = false;

            // no need to terminate here because stopping the
            // event loop will call close again and end in else part below
        }
        else if (!isDestroyed)
        {
            isDestroyed = true;
            CleanupFramebuffers();
            glfwDestroyWindow(window);

            BrushPool::Clear();
        }
    }

    void Window::SaveState()
    {
        windowSettings.SetWindowState(GetWindowState());
        windowSettings.Save();
    }

    void Window::SetWindowPos(int left, int top)
    {
        windowSettings.SetLocation(left, top);
    }

    void Window::SetWindowSize(int width, int height)
    {
        windowSettings.SetSize(width, height);

        // Update scene dimensions immediately for proper viewport
        scene.Resize(width, height);

        // Reinitialize framebuffers with new size
        if (framebuffersInitialized)
        {
            CleanupFramebuffers();
            InitializeFramebuffers();
        }

        Update(scene.SceneRect);
        // Trigger a redraw
        Invalidate();
    }

    void Window::SetDPIScale(float scaleX, float scaleY)
    {
        InputContent::SetDPIScale(scaleX, scaleY);
        // TODO should we add this? -> Scene2D::SetDPIScale(scaleX, scaleY);

        contentScaleX = App::Settings().GetAppScaleX() * scaleX;
        contentScaleY = App::Settings().GetAppScaleY() * scaleY;

        if (content)
            content->SetDPIScale(scaleX, scaleY);

        ToolTip::SetDPI(scaleX, scaleY);

        Invalidate();
    }

    void Window::SetContent(Visual *value)
    {
        if (content != value)
        {
            Visual *oldContent = content;
            if (content != nullptr)
            {
                content->SetParent(nullptr);
            }
            content = value;

            if (content != nullptr)
            {
                content->SetDPIScale(contentScaleX, contentScaleY);
                content->SetParent(this);
                if (content->GetInheritForeground())
                {
                    content->SetForeground(GetForeground());
                }
            }

            OnContentChanged(oldContent, content);

            // Invalidate the window when content changes
            Invalidate();

#ifdef DEBUG_WINDOW2
            std::cout << "Window::SetContent - Content changed, window invalidated" << std::endl;
#endif
        }
    }

    void Window::DoRender()
    {
#ifdef DEBUG_WINDOW2
        auto renderStartTime = std::chrono::high_resolution_clock::now();
        std::cout << "\n=== Window::DoRender START ===" << std::endl;
#endif

        // Reset the scheduled flag
        redrawScheduled = false;

        // TODO i do not want to call update every time, but only when needed
        // find possible spots to trigger update
        Update(scene.SceneRect);

        Scene2D::MakeCurrent(&scene);

        if (!framebuffersInitialized)
        {
#ifdef DEBUG_WINDOW2
            std::cout << "DoRender: Framebuffers not initialized, using fallback rendering" << std::endl;
#endif
            // Fallback to traditional rendering if framebuffers aren't ready
            if (content)
            {
                OpenGLExtensions::ClearScene2D();
                Render();
                glfwSwapBuffers(window);

                // Check if this is the first completed frame (fallback path)
                if (!firstFrameCompleted)
                {
                    firstFrameCompleted = true;
                    firstFrameCompleteTime = std::chrono::steady_clock::now();

#ifdef DEBUG_WINDOW
                    auto totalConstructionTime = std::chrono::duration_cast<std::chrono::microseconds>(
                        firstFrameCompleteTime - constructionStartTime);
                    auto showToFirstFrame = std::chrono::duration_cast<std::chrono::microseconds>(
                        firstFrameCompleteTime - showStartTime);

                    std::cout << "\n========================================" << std::endl;
                    std::cout << ">>> FIRST FRAME COMPLETED! (FALLBACK) <<<" << std::endl;
                    std::cout << "Total time from construction to first frame: "
                              << totalConstructionTime.count() << "μs ("
                              << (totalConstructionTime.count() / 1000.0) << "ms)" << std::endl;
                    std::cout << "Time from Show() to first frame: "
                              << showToFirstFrame.count() << "μs ("
                              << (showToFirstFrame.count() / 1000.0) << "ms)" << std::endl;
                    std::cout << "========================================\n"
                              << std::endl;
#endif
                }
            }
#ifdef DEBUG_WINDOW2
            auto renderEndTime = std::chrono::high_resolution_clock::now();
            auto renderDuration = std::chrono::duration_cast<std::chrono::microseconds>(renderEndTime - renderStartTime);
            std::cout << "DoRender: Fallback rendering completed in " << renderDuration.count() << "μs" << std::endl;
            std::cout << "=== Window::DoRender END ===\n"
                      << std::endl;
#endif
            return;
        }

#ifdef DEBUG_WINDOW2
        if (GetInvalidated() || GetNeedWidthRecalculation() || GetNeedHeightRecalculation() ||
            GetNeedLeftRecalculation() || GetNeedTopRecalculation())
        {
            std::cout << "Window::DoRender - About to update. Window invalidated=" << GetInvalidated()
                      << " needWidth=" << GetNeedWidthRecalculation()
                      << " needHeight=" << GetNeedHeightRecalculation() << std::endl;
        }
#endif

        if (content)
        {
#ifdef DEBUG_WINDOW2
            auto regionExtractionStart = std::chrono::high_resolution_clock::now();
#endif

            // Storage for regions to process thread-safely
            std::vector<std::pair<Visual *, Rectangle>> regionsToProcess;

            {
                std::lock_guard<std::mutex> lock(invalidRegionsMutex);
                if (!invalidRegions.empty())
                {
                    regionsToProcess = std::move(invalidRegions);
                    invalidRegions.clear();
                }
            }

#ifdef DEBUG_WINDOW2
            auto regionExtractionEnd = std::chrono::high_resolution_clock::now();
            auto regionExtractionDuration = std::chrono::duration_cast<std::chrono::microseconds>(regionExtractionEnd - regionExtractionStart);
            std::cout << "DoRender: Region extraction took " << regionExtractionDuration.count() << "μs" << std::endl;
            std::cout << "DoRender: Found " << regionsToProcess.size() << " invalid regions" << std::endl;
#endif

            // Bind back framebuffer for rendering
            glBindFramebuffer(GL_FRAMEBUFFER, backFramebuffer);
            glViewport(0, 0, scene.GetWidth(), scene.GetHeight());

            bool hasInvalidRegions = !regionsToProcess.empty();
            bool needsFullRedraw = GetInvalidated() || GetNeedWidthRecalculation() ||
                                   GetNeedHeightRecalculation() || GetNeedLeftRecalculation() ||
                                   GetNeedTopRecalculation();

#ifdef DEBUG_WINDOW2
            std::cout << "DoRender: Rendering strategy - hasInvalidRegions=" << hasInvalidRegions
                      << " needsFullRedraw=" << needsFullRedraw << std::endl;
            if (needsFullRedraw)
            {
                std::cout << "DoRender: Full redraw reasons - invalidated=" << GetInvalidated()
                          << " needWidth=" << GetNeedWidthRecalculation()
                          << " needHeight=" << GetNeedHeightRecalculation()
                          << " needLeft=" << GetNeedLeftRecalculation()
                          << " needTop=" << GetNeedTopRecalculation() << std::endl;
            }
            auto renderingStart = std::chrono::high_resolution_clock::now();
#endif

            if (needsFullRedraw)
            {
#ifdef DEBUG_WINDOW2
                std::cout << "DoRender: Performing FULL REDRAW" << std::endl;
                auto fullRedrawStart = std::chrono::high_resolution_clock::now();
#endif
                // Full redraw - clear and render everything
                OpenGLExtensions::ClearScene2D();
                Render();
#ifdef DEBUG_WINDOW2
                auto fullRedrawEnd = std::chrono::high_resolution_clock::now();
                auto fullRedrawDuration = std::chrono::duration_cast<std::chrono::microseconds>(fullRedrawEnd - fullRedrawStart);
                std::cout << "DoRender: Full redraw completed in " << fullRedrawDuration.count() << "μs" << std::endl;
#endif
            }
            else if (hasInvalidRegions)
            {
#ifdef DEBUG_WINDOW2
                std::cout << "DoRender: Performing PARTIAL REDRAW with " << regionsToProcess.size() << " regions" << std::endl;
                auto partialRedrawStart = std::chrono::high_resolution_clock::now();
#endif
                // Partial redraw - copy unchanged regions from front buffer and render only invalid regions

                // First, copy the entire front buffer to back buffer
#ifdef DEBUG_WINDOW2
                auto copyStart = std::chrono::high_resolution_clock::now();
#endif
                glBindFramebuffer(GL_READ_FRAMEBUFFER, frontFramebuffer);
                glBindFramebuffer(GL_DRAW_FRAMEBUFFER, backFramebuffer);
                glBlitFramebuffer(0, 0, scene.GetWidth(), scene.GetHeight(),
                                  0, 0, scene.GetWidth(), scene.GetHeight(),
                                  GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_NEAREST);
#ifdef DEBUG_WINDOW2
                auto copyEnd = std::chrono::high_resolution_clock::now();
                auto copyDuration = std::chrono::duration_cast<std::chrono::microseconds>(copyEnd - copyStart);
                std::cout << "DoRender: Buffer copy (" << scene.GetWidth() << "x" << scene.GetHeight()
                          << ") took " << copyDuration.count() << "μs" << std::endl;
#endif

                // Now render only the invalidated regions
                glBindFramebuffer(GL_FRAMEBUFFER, backFramebuffer);

#ifdef DEBUG_WINDOW2
                int regionIndex = 0;
#endif
                for (const auto &region : regionsToProcess)
                {
                    Visual *visual = region.first;
                    Rectangle bounds = region.second;

#ifdef DEBUG_WINDOW2
                    std::cout << "DoRender: Processing region " << regionIndex++ << " - bounds("
                              << bounds.GetLeft() << "," << bounds.GetTop()
                              << "," << bounds.GetWidth() << "," << bounds.GetHeight() << ")"
                              << " visual=" << (visual ? visual->GetName() : "null") << std::endl;
                    auto regionRenderStart = std::chrono::high_resolution_clock::now();
#endif

                    if (visual)
                    {
                        // Set scissor test to limit rendering to the invalid region
                        glEnable(GL_SCISSOR_TEST);

                        // Convert coordinates (OpenGL uses bottom-left origin)
                        int scissorY = scene.GetHeight() - bounds.GetTop() - bounds.GetHeight();
                        glScissor(bounds.GetLeft(), scissorY, bounds.GetWidth(), bounds.GetHeight());

#ifdef DEBUG_WINDOW2
                        std::cout << "DoRender: Scissor region set to ("
                                  << bounds.GetLeft() << "," << scissorY
                                  << "," << bounds.GetWidth() << "," << bounds.GetHeight() << ")" << std::endl;
#endif

                        // Clear only this region
                        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
                        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                        // Render the visual
                        visual->Render();

                        glDisable(GL_SCISSOR_TEST);

#ifdef DEBUG_WINDOW2
                        auto regionRenderEnd = std::chrono::high_resolution_clock::now();
                        auto regionRenderDuration = std::chrono::duration_cast<std::chrono::microseconds>(regionRenderEnd - regionRenderStart);
                        std::cout << "DoRender: Region render completed in " << regionRenderDuration.count() << "μs" << std::endl;
#endif
                    }
#ifdef DEBUG_WINDOW2
                    else
                    {
                        std::cout << "DoRender: WARNING - Null visual for region " << (regionIndex - 1) << std::endl;
                    }
#endif
                }
#ifdef DEBUG_WINDOW2
                auto partialRedrawEnd = std::chrono::high_resolution_clock::now();
                auto partialRedrawDuration = std::chrono::duration_cast<std::chrono::microseconds>(partialRedrawEnd - partialRedrawStart);
                std::cout << "DoRender: Partial redraw completed in " << partialRedrawDuration.count() << "μs" << std::endl;
#endif
            }
            else
            {
#ifdef DEBUG_WINDOW2
                std::cout << "DoRender: Performing BUFFER COPY (no changes)" << std::endl;
                auto noCopyStart = std::chrono::high_resolution_clock::now();
#endif
                // No changes - just copy front buffer to back buffer
                glBindFramebuffer(GL_READ_FRAMEBUFFER, frontFramebuffer);
                glBindFramebuffer(GL_DRAW_FRAMEBUFFER, backFramebuffer);
                glBlitFramebuffer(0, 0, scene.GetWidth(), scene.GetHeight(),
                                  0, 0, scene.GetWidth(), scene.GetHeight(),
                                  GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_NEAREST);
#ifdef DEBUG_WINDOW2
                auto noCopyEnd = std::chrono::high_resolution_clock::now();
                auto noCopyDuration = std::chrono::duration_cast<std::chrono::microseconds>(noCopyEnd - noCopyStart);
                std::cout << "DoRender: No-change buffer copy completed in " << noCopyDuration.count() << "μs" << std::endl;
#endif
            }

#ifdef DEBUG_WINDOW2
            auto renderingEnd = std::chrono::high_resolution_clock::now();
            auto renderingDuration = std::chrono::duration_cast<std::chrono::microseconds>(renderingEnd - renderingStart);
            std::cout << "DoRender: Total rendering phase took " << renderingDuration.count() << "μs" << std::endl;

            auto swapStart = std::chrono::high_resolution_clock::now();
#endif

            // Swap the framebuffers
            SwapFramebuffers();

#ifdef DEBUG_WINDOW2
            auto swapEnd = std::chrono::high_resolution_clock::now();
            auto swapDuration = std::chrono::duration_cast<std::chrono::microseconds>(swapEnd - swapStart);
            std::cout << "DoRender: Framebuffer swap took " << swapDuration.count() << "μs" << std::endl;

            auto presentStart = std::chrono::high_resolution_clock::now();
#endif

            // Copy the front framebuffer content to the default framebuffer for display
            glBindFramebuffer(GL_READ_FRAMEBUFFER, frontFramebuffer);
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
            glBlitFramebuffer(0, 0, scene.GetWidth(), scene.GetHeight(),
                              0, 0, scene.GetWidth(), scene.GetHeight(),
                              GL_COLOR_BUFFER_BIT, GL_NEAREST);

            glfwSwapBuffers(window);

#ifdef DEBUG_WINDOW2
            auto presentEnd = std::chrono::high_resolution_clock::now();
            auto presentDuration = std::chrono::duration_cast<std::chrono::microseconds>(presentEnd - presentStart);
            std::cout << "DoRender: Present to screen took " << presentDuration.count() << "μs" << std::endl;
#endif

            // Check if this is the first completed frame
            if (!firstFrameCompleted)
            {
                firstFrameCompleted = true;
                firstFrameCompleteTime = std::chrono::steady_clock::now();

#ifdef DEBUG_WINDOW
                auto totalConstructionTime = std::chrono::duration_cast<std::chrono::microseconds>(
                    firstFrameCompleteTime - constructionStartTime);
                auto showToFirstFrame = std::chrono::duration_cast<std::chrono::microseconds>(
                    firstFrameCompleteTime - showStartTime);

                std::cout << "\n========================================" << std::endl;
                std::cout << ">>> FIRST FRAME COMPLETED! <<<" << std::endl;
                std::cout << "Total time from construction to first frame: "
                          << totalConstructionTime.count() << "μs ("
                          << (totalConstructionTime.count() / 1000.0) << "ms)" << std::endl;
                std::cout << "Time from Show() to first frame: "
                          << showToFirstFrame.count() << "μs ("
                          << (showToFirstFrame.count() / 1000.0) << "ms)" << std::endl;
                std::cout << "========================================\n"
                          << std::endl;
#endif
            }
        }

#ifdef DEBUG_WINDOW2
        auto renderEndTime = std::chrono::high_resolution_clock::now();
        auto totalRenderDuration = std::chrono::duration_cast<std::chrono::microseconds>(renderEndTime - renderStartTime);
        std::cout << "DoRender: TOTAL RENDER TIME: " << totalRenderDuration.count() << "μs ("
                  << (totalRenderDuration.count() / 1000.0) << "ms)" << std::endl;
        std::cout << "=== Window::DoRender END ===\n"
                  << std::endl;
#endif
    }

    //******************************************************************************
    // Double Buffering Implementation
    //******************************************************************************

    void Window::InitializeFramebuffers()
    {
#ifdef DEBUG_WINDOW2
        auto initStart = std::chrono::high_resolution_clock::now();
        std::cout << "InitializeFramebuffers: Starting framebuffer initialization" << std::endl;
#endif

        if (framebuffersInitialized)
        {
#ifdef DEBUG_WINDOW2
            std::cout << "InitializeFramebuffers: Cleaning up existing framebuffers first" << std::endl;
#endif
            CleanupFramebuffers();
        }

        int width = scene.GetWidth();
        int height = scene.GetHeight();

#ifdef DEBUG_WINDOW2
        std::cout << "InitializeFramebuffers: Creating framebuffers with size " << width << "x" << height << std::endl;
#endif

        if (width <= 0 || height <= 0)
        {
#ifdef DEBUG_WINDOW2
            std::cout << "InitializeFramebuffers: ERROR - Invalid dimensions, aborting" << std::endl;
#endif
            return; // Invalid dimensions
        }

        // Generate framebuffers
        glGenFramebuffers(1, &frontFramebuffer);
        glGenFramebuffers(1, &backFramebuffer);

        // Generate textures for color attachments
        glGenTextures(1, &frontColorTexture);
        glGenTextures(1, &backColorTexture);
        glGenTextures(1, &frontDepthTexture);
        glGenTextures(1, &backDepthTexture);

        // Setup front framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, frontFramebuffer);

        // Front color texture
        glBindTexture(GL_TEXTURE_2D, frontColorTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frontColorTexture, 0);

        // Front depth texture
        glBindTexture(GL_TEXTURE_2D, frontDepthTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, frontDepthTexture, 0);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
#ifdef DEBUG_WINDOW2
            std::cout << "InitializeFramebuffers: ERROR - Front framebuffer is not complete! Status: "
                      << glCheckFramebufferStatus(GL_FRAMEBUFFER) << std::endl;
#endif
            ERROR("Front framebuffer is not complete!");
            CleanupFramebuffers();
            return;
        }

#ifdef DEBUG_WINDOW2
        std::cout << "InitializeFramebuffers: Front framebuffer setup complete" << std::endl;
#endif

        // Setup back framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, backFramebuffer);

        // Back color texture
        glBindTexture(GL_TEXTURE_2D, backColorTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, backColorTexture, 0);

        // Back depth texture
        glBindTexture(GL_TEXTURE_2D, backDepthTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, backDepthTexture, 0);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
#ifdef DEBUG_WINDOW2
            std::cout << "InitializeFramebuffers: ERROR - Back framebuffer is not complete! Status: "
                      << glCheckFramebufferStatus(GL_FRAMEBUFFER) << std::endl;
#endif
            ERROR("Back framebuffer is not complete!");
            CleanupFramebuffers();
            return;
        }

#ifdef DEBUG_WINDOW2
        std::cout << "InitializeFramebuffers: Back framebuffer setup complete" << std::endl;
#endif

        // Clear both framebuffers initially
        glBindFramebuffer(GL_FRAMEBUFFER, frontFramebuffer);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindFramebuffer(GL_FRAMEBUFFER, backFramebuffer);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Restore default framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        framebuffersInitialized = true;

#ifdef DEBUG_WINDOW2
        auto initEnd = std::chrono::high_resolution_clock::now();
        auto initDuration = std::chrono::duration_cast<std::chrono::microseconds>(initEnd - initStart);
        std::cout << "Window::InitializeFramebuffers - Framebuffers initialized with size "
                  << width << "x" << height << " in " << initDuration.count() << "μs" << std::endl;

        // Report texture memory usage
        size_t totalMemory = width * height * 4 * 4; // 4 textures (2 color + 2 depth), 4 bytes per pixel for color
        totalMemory += width * height * 4 * 2;       // depth textures use 4 bytes per pixel
        std::cout << "InitializeFramebuffers: Estimated GPU memory usage: "
                  << (totalMemory / 1024.0 / 1024.0) << " MB" << std::endl;
#endif
    }

    void Window::CleanupFramebuffers()
    {
        if (!framebuffersInitialized)
        {
            return;
        }

        if (frontFramebuffer != 0)
        {
            glDeleteFramebuffers(1, &frontFramebuffer);
            frontFramebuffer = 0;
        }

        if (backFramebuffer != 0)
        {
            glDeleteFramebuffers(1, &backFramebuffer);
            backFramebuffer = 0;
        }

        if (frontColorTexture != 0)
        {
            glDeleteTextures(1, &frontColorTexture);
            frontColorTexture = 0;
        }

        if (backColorTexture != 0)
        {
            glDeleteTextures(1, &backColorTexture);
            backColorTexture = 0;
        }

        if (frontDepthTexture != 0)
        {
            glDeleteTextures(1, &frontDepthTexture);
            frontDepthTexture = 0;
        }

        if (backDepthTexture != 0)
        {
            glDeleteTextures(1, &backDepthTexture);
            backDepthTexture = 0;
        }

        framebuffersInitialized = false;

#ifdef DEBUG_WINDOW2
        std::cout << "Window::CleanupFramebuffers - Framebuffers cleaned up" << std::endl;
#endif
    }

    void Window::SwapFramebuffers()
    {
#ifdef DEBUG_WINDOW2
        auto swapStart = std::chrono::high_resolution_clock::now();
        GLuint oldFront = frontFramebuffer;
        GLuint oldBack = backFramebuffer;
#endif

        // Swap the framebuffer IDs and texture IDs
        std::swap(frontFramebuffer, backFramebuffer);
        std::swap(frontColorTexture, backColorTexture);
        std::swap(frontDepthTexture, backDepthTexture);

#ifdef DEBUG_WINDOW2
        auto swapEnd = std::chrono::high_resolution_clock::now();
        auto swapDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(swapEnd - swapStart);
        std::cout << "Window::SwapFramebuffers - Framebuffers swapped in " << swapDuration.count() << "ns" << std::endl;
        std::cout << "SwapFramebuffers: Front " << oldFront << " -> " << frontFramebuffer
                  << ", Back " << oldBack << " -> " << backFramebuffer << std::endl;
#endif
    }

    void Window::CopyRegionBetweenFramebuffers(const Rectangle &region)
    {
        // Convert region coordinates for OpenGL (bottom-left origin)
        int sourceY = scene.GetHeight() - region.GetTop() - region.GetHeight();
        int destY = sourceY;

        glBindFramebuffer(GL_READ_FRAMEBUFFER, frontFramebuffer);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, backFramebuffer);

        glBlitFramebuffer(
            region.GetLeft(), sourceY,
            region.GetLeft() + region.GetWidth(), sourceY + region.GetHeight(),
            region.GetLeft(), destY,
            region.GetLeft() + region.GetWidth(), destY + region.GetHeight(),
            GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT,
            GL_NEAREST);

#ifdef DEBUG_WINDOW2
        std::cout << "Window::CopyRegionBetweenFramebuffers - Copied region ("
                  << region.GetLeft() << "," << region.GetTop()
                  << "," << region.GetWidth() << "," << region.GetHeight() << ")" << std::endl;
#endif
    }
}