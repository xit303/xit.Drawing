#include <map>
#include <Exceptions.h>
#include <Application/App.h>

#include <Clipboard.h>
#include <Input/InputHandler.h>

#include <Drawing/ToolTip.h>
#include <Drawing/Window.h>
#include <Drawing/DebugUtils.h>
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
        activeInstance->DoRender();
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

        char keyChar = key;
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
            keyChar = 'a' + ((int)c - (int)CKey::A);
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

    Window::Window()
    {
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

        contentScaleX = App::Settings().GetAppScaleX();
        contentScaleY = App::Settings().GetAppScaleY();

        // Initialize background buffer variables
        backgroundFramebuffer = 0;
        backgroundTexture = 0;
        backgroundDepthBuffer = 0;
        useBackgroundBuffer = true;
        backgroundBufferInitialized = false;

        SetBrushGroup("Window");
        SetName("Window");

        if (!glfwInit())
        {
            ERROR("Failed to initialize GLFW");
            return;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        Dispatcher::SetMainThreadId();

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

        // CRITICAL FIX: Also update content when window is invalidated (even if window size/position unchanged)
        // This handles cases where content invalidates and window needs to update its content layout
        bool needContentUpdate = needClientUpdate || GetInvalidated();

#ifdef DEBUG_WINDOW
        std::cout << "Window::OnUpdate called. needClientUpdate=" << needClientUpdate
                  << " needContentUpdate=" << needContentUpdate
                  << " invalidated=" << GetInvalidated()
                  << " bounds=(" << bounds.GetLeft() << "," << bounds.GetTop()
                  << "," << bounds.GetWidth() << "," << bounds.GetHeight() << ")" << std::endl;
#endif

        InputContent::OnUpdate(bounds);

        if (needContentUpdate)
        {
#ifdef DEBUG_WINDOW
            std::cout << "Window::OnUpdate - Updating client bounds and content" << std::endl;
#endif
            // TODO create Method GetClientBounds(Visual& v); see Window, SplitContainer, ScrollViewer, ContainerBase

            const Thickness &padding = GetPadding();
            const Thickness &borderThickness = GetBorderThickness();

            clientBounds.SetLocation(padding.GetLeft() + borderThickness.GetLeft(), padding.GetTop() + borderThickness.GetTop());
            clientBounds.SetWidth(GetActualWidth() - padding.GetWidth() - borderThickness.GetWidth());
            clientBounds.SetHeight(GetActualHeight() - padding.GetHeight() - borderThickness.GetHeight());

            if (content)
            {
#ifdef DEBUG_WINDOW
                std::cout << "Window::OnUpdate - Updating content with clientBounds=("
                          << clientBounds.GetLeft() << "," << clientBounds.GetTop()
                          << "," << clientBounds.GetWidth() << "," << clientBounds.GetHeight() << ")" << std::endl;
#endif
                content->Update(clientBounds);
                ToolTip::DoUpdate(clientBounds);
            }
            else
            {
#ifdef DEBUG_WINDOW
                std::cout << "Window::OnUpdate - WARNING: No content to update!" << std::endl;
#endif
            }

            // Mark the entire window as dirty on client update
            if (useBackgroundBuffer)
            {
                Rectangle windowBounds(0, 0, scene.GetWidth(), scene.GetHeight());
                AddDirtyRegion(windowBounds);
            }
        }
        else
        {
#ifdef DEBUG_WINDOW
            std::cout << "Window::OnUpdate - No client update needed" << std::endl;
#endif
        }
    }

    void Window::OnInvalidated(EventArgs &e)
    {
        if (useBackgroundBuffer && backgroundBufferInitialized)
        {
            // Add the visual's bounds as a dirty region
            Rectangle dirtyRegion(GetLeft(), GetTop(), GetActualWidth(), GetActualHeight());
            AddDirtyRegion(dirtyRegion);
        }

        // Call base implementation
        InputContent::OnInvalidated(e);

        mainLoopSemaphore.release();
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
        this->windowSettings = windowSettings;

        window = glfwCreateWindow(windowSettings.GetWidth(), windowSettings.GetHeight(), title.c_str(), NULL, NULL);
        if (window == NULL)
        {
            ERRORT("Failed to create GLFW window");
            return false;
        }

        glfwSetWindowPos(window, windowSettings.GetLeft(), windowSettings.GetTop());

        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            ERRORT("Failed to initialize GLAD");
            return false;
        }

        windowList.emplace(std::make_pair(window, this));

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

        scene.Resize(windowSettings.GetWidth(), windowSettings.GetHeight());
        Scene2D::MakeCurrent(&scene);

        // SetBrushGroup("Window");

        // glfwSetWindowSizeLimits(window,
        //                         (MinWidth > 0 ? MinWidth : GLFW_DONT_CARE),
        //                         (MinHeight > 0 ? MinHeight : GLFW_DONT_CARE),
        //                         (MaxWidth != -1 ? MaxWidth : GLFW_DONT_CARE),
        //                         (MaxHeight != -1 ? MaxHeight : GLFW_DONT_CARE));

        App::Closing.Add(&Window::App_Closing, this);

        float scaleX = 1;
        float scaleY = 1;
        glfwGetWindowContentScale(window, &scaleX, &scaleY);

        // SetDPIScale override for Window calls Invalidate() to take the semaphore
        SetDPIScale(scaleX, scaleY);

        // Initialize background buffer after OpenGL context is ready
        InitializeBackgroundBuffer();

        OnInitializeComponent();

        return true;
    }
    void Window::Show()
    {
        if (activeInstance != nullptr)
        {
            lastActiveInstance = activeInstance;
        }

        activeInstance = this;
        OpenGLExtensions::Initialize2D(scene);

        while (!glfwWindowShouldClose(window) && !isDestroyed)
        {
            using namespace std::literals;
            if (mainLoopSemaphore.try_acquire_for(1ms))
            {
                DoRender();
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
            DestroyBackgroundBuffer();
            glfwDestroyWindow(window);
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
        scene.Resize(width, height);

        // Resize background buffer when window size changes
        if (backgroundBufferInitialized)
        {
            ResizeBackgroundBuffer(width, height);
        }
    }
    void Window::SetDPIScale(float scaleX, float scaleY)
    {
        InputContent::SetDPIScale(scaleX, scaleY);

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

            // CRITICAL FIX: Invalidate the window when content changes
            Invalidate();

#ifdef DEBUG_WINDOW
            std::cout << "Window::SetContent - Content changed, window invalidated" << std::endl;
#endif
        }
    }

    void Window::OnContentInvalidated(Visual *childVisual)
    {
        if (useBackgroundBuffer && backgroundBufferInitialized && childVisual)
        {
            // Calculate the child's absolute bounds within the window
            Rectangle childBounds(
                childVisual->GetLeft(),
                childVisual->GetTop(),
                childVisual->GetActualWidth(),
                childVisual->GetActualHeight());

            AddDirtyRegion(childBounds);
        }
    }

    void Window::OnChildInvalidated(LayoutManager *childLayout)
    {
#ifdef DEBUG_WINDOW
        std::cout << "Window::OnChildInvalidated called for child: "
                  << (childLayout ? childLayout->GetName() : "null") << std::endl;
#endif

        if (useBackgroundBuffer && backgroundBufferInitialized && childLayout)
        {
            // Calculate the child's absolute bounds within the window
            Rectangle childBounds(
                childLayout->GetLeft(),
                childLayout->GetTop(),
                childLayout->GetActualWidth(),
                childLayout->GetActualHeight());

            AddDirtyRegion(childBounds);
        }

#ifdef DEBUG_WINDOW
        std::cout << "Window invalidating self due to child invalidation" << std::endl;
#endif

        // CRITICAL FIX: When child content is invalidated, the window must also invalidate
        // so it knows to update and render the changes
        Invalidate();

        // Don't call parent since Window is the top-level container
    }

    void Window::DoRender()
    {
        Scene2D::MakeCurrent(&scene);
        // scene.SetFrameTime();

        // int invalidationCount = scene.InvalidationCount;

#ifdef DEBUG_WINDOW
        if (GetInvalidated() || GetNeedWidthRecalculation() || GetNeedHeightRecalculation() ||
            GetNeedLeftRecalculation() || GetNeedTopRecalculation())
        {
            std::cout << "Window::DoRender - About to update. Window invalidated=" << GetInvalidated()
                      << " needWidth=" << GetNeedWidthRecalculation()
                      << " needHeight=" << GetNeedHeightRecalculation() << std::endl;
        }
#endif

        if (Update(scene.SceneRect))
        {
#ifdef DEBUG_WINDOW
            std::cout << "Window::DoRender - Update returned true, proceeding with render" << std::endl;
#endif

            if (useBackgroundBuffer && backgroundBufferInitialized && !dirtyRegions.empty())
            {
                // Partial redraw: only render dirty regions
                for (const auto &dirtyRegion : dirtyRegions)
                {
                    // Set scissor test to limit rendering to dirty region
                    glEnable(GL_SCISSOR_TEST);
                    glScissor(dirtyRegion.GetLeft(),
                              scene.GetHeight() - dirtyRegion.GetBottom(),
                              dirtyRegion.GetWidth(),
                              dirtyRegion.GetHeight());

                    // Copy unchanged parts from background buffer
                    CopyFromBackgroundBuffer(dirtyRegion);

                    // Render only the dirty region
                    Render();

                    // Copy the newly rendered region to background buffer
                    CopyToBackgroundBuffer(dirtyRegion);

                    glDisable(GL_SCISSOR_TEST);
                }
                ClearDirtyRegions();
            }
            else
            {
                // Full redraw
                OpenGLExtensions::ClearScene2D();
                static_assert(static_cast<int>(WindowState::Normal) == 0, "WindowState::Normal must be 0");

                Render();

                // Copy entire frame to background buffer
                if (useBackgroundBuffer && backgroundBufferInitialized)
                {
                    Rectangle fullRect(0, 0, scene.GetWidth(), scene.GetHeight());
                    CopyToBackgroundBuffer(fullRect);
                }
            }

            glfwSwapBuffers(window);
        }
        else
        {
#ifdef DEBUG_WINDOW
            std::cout << "Window::DoRender - Update returned false, skipping render" << std::endl;
#endif
        }
    }

    //******************************************************************************
    // Background Buffer Implementation
    //******************************************************************************

    void Window::InitializeBackgroundBuffer()
    {
        if (!useBackgroundBuffer || backgroundBufferInitialized)
            return;

        int width = scene.GetWidth();
        int height = scene.GetHeight();

        if (width <= 0 || height <= 0)
            return;

        // Generate framebuffer
        glGenFramebuffers(1, &backgroundFramebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, backgroundFramebuffer);

        // Generate texture for color attachment
        glGenTextures(1, &backgroundTexture);
        glBindTexture(GL_TEXTURE_2D, backgroundTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, backgroundTexture, 0);

        // Generate depth buffer
        glGenRenderbuffers(1, &backgroundDepthBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, backgroundDepthBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, backgroundDepthBuffer);

        // Check framebuffer completeness
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            ERROR("Background framebuffer not complete!");
            DestroyBackgroundBuffer();
            return;
        }

        // Bind default framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        backgroundBufferInitialized = true;
    }

    void Window::ResizeBackgroundBuffer(int width, int height)
    {
        if (!backgroundBufferInitialized || width <= 0 || height <= 0)
            return;

        // Resize texture
        glBindTexture(GL_TEXTURE_2D, backgroundTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        // Resize depth buffer
        glBindRenderbuffer(GL_RENDERBUFFER, backgroundDepthBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);

        // Clear dirty regions and force full redraw
        ClearDirtyRegions();
        Invalidate();
    }

    void Window::DestroyBackgroundBuffer()
    {
        if (!backgroundBufferInitialized)
            return;

        if (backgroundFramebuffer != 0)
        {
            glDeleteFramebuffers(1, &backgroundFramebuffer);
            backgroundFramebuffer = 0;
        }

        if (backgroundTexture != 0)
        {
            glDeleteTextures(1, &backgroundTexture);
            backgroundTexture = 0;
        }

        if (backgroundDepthBuffer != 0)
        {
            glDeleteRenderbuffers(1, &backgroundDepthBuffer);
            backgroundDepthBuffer = 0;
        }

        backgroundBufferInitialized = false;
        ClearDirtyRegions();
    }

    void Window::AddDirtyRegion(const Rectangle &region)
    {
        if (!useBackgroundBuffer)
            return;

        // Check if region intersects with window bounds
        Rectangle windowBounds(0, 0, scene.GetWidth(), scene.GetHeight());
        Rectangle regionCopy = region; // Create a non-const copy
        if (!regionCopy.IntersectsWith(windowBounds))
            return;

        // Clip the region to window bounds
        Rectangle clippedRegion = *Rectangle::Intersect(regionCopy, windowBounds);

        // Merge overlapping regions to optimize rendering
        bool merged = false;
        for (auto it = dirtyRegions.begin(); it != dirtyRegions.end(); ++it)
        {
            if (it->IntersectsWith(clippedRegion))
            {
                // Merge the regions by creating a union
                int left = std::min(it->GetLeft(), clippedRegion.GetLeft());
                int top = std::min(it->GetTop(), clippedRegion.GetTop());
                int right = std::max(it->GetRight(), clippedRegion.GetRight());
                int bottom = std::max(it->GetBottom(), clippedRegion.GetBottom());

                it->Set(left, top, right - left, bottom - top);
                merged = true;
                break;
            }
        }

        if (!merged)
        {
            dirtyRegions.push_back(clippedRegion);
        }

        // Optimization: if dirty regions cover too much of the screen,
        // fall back to full redraw
        OptimizeDirtyRegions();
    }

    void Window::OptimizeDirtyRegions()
    {
        if (dirtyRegions.empty())
            return;

        int totalDirtyArea = 0;
        int windowArea = scene.GetWidth() * scene.GetHeight();

        for (const auto &region : dirtyRegions)
        {
            totalDirtyArea += region.GetWidth() * region.GetHeight();
        }

        // If more than 75% of the window is dirty, just do a full redraw
        if (totalDirtyArea > windowArea * 0.75f)
        {
            ClearDirtyRegions();
            Rectangle fullWindow(0, 0, scene.GetWidth(), scene.GetHeight());
            dirtyRegions.push_back(fullWindow);
        }
    }

    void Window::ClearDirtyRegions()
    {
        dirtyRegions.clear();
    }

    void Window::CopyFromBackgroundBuffer(const Rectangle &region)
    {
        if (!backgroundBufferInitialized)
            return;

        // Bind the background framebuffer as read buffer
        glBindFramebuffer(GL_READ_FRAMEBUFFER, backgroundFramebuffer);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

        // Copy the region from background buffer to default framebuffer
        glBlitFramebuffer(
            region.GetLeft(), scene.GetHeight() - region.GetBottom(),
            region.GetRight(), scene.GetHeight() - region.GetTop(),
            region.GetLeft(), scene.GetHeight() - region.GetBottom(),
            region.GetRight(), scene.GetHeight() - region.GetTop(),
            GL_COLOR_BUFFER_BIT, GL_NEAREST);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Window::CopyToBackgroundBuffer(const Rectangle &region)
    {
        if (!backgroundBufferInitialized)
            return;

        // Bind the default framebuffer as read buffer and background as draw buffer
        glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, backgroundFramebuffer);

        // Copy the region from default framebuffer to background buffer
        glBlitFramebuffer(
            region.GetLeft(), scene.GetHeight() - region.GetBottom(),
            region.GetRight(), scene.GetHeight() - region.GetTop(),
            region.GetLeft(), scene.GetHeight() - region.GetBottom(),
            region.GetRight(), scene.GetHeight() - region.GetTop(),
            GL_COLOR_BUFFER_BIT, GL_NEAREST);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    bool Window::HasDirtyRegions() const
    {
        return !dirtyRegions.empty();
    }

    void Window::SetBackgroundBufferEnabled(bool enabled)
    {
        if (useBackgroundBuffer != enabled)
        {
            useBackgroundBuffer = enabled;

            if (enabled && !backgroundBufferInitialized)
            {
                InitializeBackgroundBuffer();
            }
            else if (!enabled && backgroundBufferInitialized)
            {
                DestroyBackgroundBuffer();
            }
        }
    }

    bool Window::IsBackgroundBufferEnabled() const
    {
        return useBackgroundBuffer;
    }

    void Window::InvalidateRegion(const Rectangle &region)
    {
        AddDirtyRegion(region);
        Invalidate(); // Trigger a render
    }
}