#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace xit::Drawing
{
    class Clipboard
    {
    private:
        // Private static member to hold the GLFW window pointer
        static GLFWwindow *window;

    public:
        static void SetWindow(GLFWwindow *window)
        {
            Clipboard::window = window;
        }

        // Gets the text from the clipboard. Returns an empty string on failure.
        static std::string GetText();

        // Sets the clipboard data to the given text. Returns true on success, false on failure.
        static bool SetText(const std::string &text);
    };
}