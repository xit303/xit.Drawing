#include <map>
#include <Exceptions.h>
#include <Application/App.h>

#include <Clipboard.h>
#include <OpenGL/OpenGLExtensions.h>
#include <Input/InputHandler.h>

#include <Drawing/ToolTip.h>
#include <Drawing/Window.h>
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
        EventArgs e;
        if (entered)
        {
            activeInstance->ExecuteInputEnter(e);
        }
        else
        {
            activeInstance->ExecuteInputLeave(e);
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

        SetBrushGroup("Window");

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

    void Window::OnSceneInvalidated(EventArgs &e)
    {
        mainLoopSemaphore.release();
    }
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
        bool needClientUpdate = needLeftRecalculation || needTopRecalculation || needWidthRecalculation || needHeightRecalculation;

        InputContent::OnUpdate(bounds);

        if (needClientUpdate)
        {
            // TODO create Method GetClientBounds(Visual& v); see Window, SplitContainer, ScrollViewer, ContainerBase

            const Thickness &padding = GetPadding();
            const Thickness &borderThickness = GetBorderThickness();

            clientBounds.SetLocation(padding.GetLeft() + borderThickness.GetLeft(), padding.GetTop() + borderThickness.GetTop());
            clientBounds.SetWidth(GetActualWidth() - padding.GetWidth() - borderThickness.GetWidth());
            clientBounds.SetHeight(GetActualHeight() - padding.GetHeight() - borderThickness.GetHeight());

            if (content)
            {
                content->Update(clientBounds);
                ToolTip::DoUpdate(clientBounds);
            }
        }
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
    void Window::ExecuteInputLeave(EventArgs &e)
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
        if (!InputHandler::CheckInputPressed(e) && content && InputHandler::IsHit(*dynamic_cast<IFocus*>(content), e.Position))
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
        if (!InputHandler::CheckInputReleased(e) && content && InputHandler::IsHit(*dynamic_cast<IFocus*>(content), e.Position))
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
        if (!InputHandler::CheckInputScroll(e) && content && InputHandler::IsHit(*dynamic_cast<IFocus*>(content), e.Position))
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
        if (!InputHandler::CheckInputMove(e) && content && InputHandler::IsHit(*dynamic_cast<IFocus*>(content), e.Position))
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
        scene.Invalidated.Add(&Window::OnSceneInvalidated, this);
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
        }
    }

    void Window::DoRender()
    {
        Scene2D::MakeCurrent(&scene);
        // scene.SetFrameTime();

        // int invalidationCount = scene.InvalidationCount;

        if (Update(scene.SceneRect))
        {
            OpenGLExtensions::ClearScene2D();
            static_assert(static_cast<int>(WindowState::Normal) == 0, "WindowState::Normal must be 0");

            Render();

            scene.SetInvalidationDone();

            glfwSwapBuffers(window);
        }
    }
}
