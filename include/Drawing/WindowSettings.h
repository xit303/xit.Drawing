#pragma once

#include <string>

#include "Drawing/Rectangle.h"
#include "Drawing/Properties/WindowState.h"

namespace xit::Drawing
{
	class WindowSettings
	{
    private:        
		int left;
		int top;
		int width;
		int height;

        WindowState windowState;

    public:
        inline int GetLeft() const { return left; }
        inline int GetTop() const { return top; }
        inline int GetWidth() const { return width; }
        inline int GetHeight() const { return height; }
        
        inline WindowState GetWindowState() const { return windowState; }
        void SetWindowState(WindowState value) { windowState = value; }

        void SetLocation(int left, int top) { this->left = left; this->top = top; }
        void SetSize(int width, int height) { this->width = width; this->height = height; }
        

		WindowSettings();
        WindowSettings(const std::string& name, int width, int height, WindowState windowState);
		void Save();
		void CheckWorkingArea(const Rectangle& dpiScaledWorkingArea);
		bool Load(const std::string& path);
	};
}
