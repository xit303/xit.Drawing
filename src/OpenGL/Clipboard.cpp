#include <OpenGL/Clipboard.h>
#include <Input/InputHandler.h>
#include <Drawing/ToolTip.h>

namespace xit::Drawing
{
    GLFWwindow *Clipboard::window = nullptr;

    std::string Clipboard::GetText()
    {
        if (window == nullptr)
            return "";

        const char *clipboardString = glfwGetClipboardString(window);
        if (clipboardString == nullptr)
            return "";

        return std::string(clipboardString);
    }

    bool Clipboard::SetText(const std::string &text)
    {
        if (window == nullptr)
            return false;

        glfwSetClipboardString(window, text.c_str());

        Point location = InputHandler::GetLastMousePosition();

        ToolTip::Show("Text copied to clipboard", location.X, location.Y, 3000);
        return true;
    }
}
