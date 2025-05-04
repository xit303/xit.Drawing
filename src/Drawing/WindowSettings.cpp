#include "Drawing/WindowSettings.h"

#include "Application/App.h"
#include "IO/IO.h"

#include <ArduinoJson.h>

namespace xit::Drawing
{
	WindowSettings::WindowSettings()
		: left(10), top(10), width(800), height(600), windowState(WindowState::Normal)
	{
	}
    WindowSettings::WindowSettings(const std::string& name, int width, int height, WindowState windowState)
        : left(10), top(10), width(width), height(height), windowState(windowState)
    {
    }

	void WindowSettings::Save()
	{
        JsonDocument doc;
        doc["Left"] = left;
        doc["Top"] = top;
        doc["Width"] = width;
        doc["Height"] = height;
        doc["WindowState"] = (int)windowState;

		std::string fileName = xit::Application::App::UserPath() + "WindowSettings.json";
        File file(fileName, std::ios::out);
        file.Write(doc.as<std::string>());
	}

	bool WindowSettings::Load(const std::string& path)
	{
        std::string fileName = path + "/WindowSettings.json";
        std::string data = File::ReadAllText(fileName);

        // nothing saved so far so we did not load anything
        if (data.empty())
            return false;

        JsonDocument doc;
        deserializeJson(doc, data);

        left = doc["Left"];
        top = doc["Top"];
        width = doc["Width"];
        height = doc["Height"];
        windowState = (WindowState)(int)doc["WindowState"];

		return true;
	}

    void WindowSettings::CheckWorkingArea(const Rectangle& dpiScaledWorkingArea)
    {
        // in first stage check if window left location is completely outside
        if (left >= dpiScaledWorkingArea.GetRight())
        {
            // check if we have to update window width
            if (width > dpiScaledWorkingArea.GetWidth())
            {
                width = dpiScaledWorkingArea.GetWidth();
            }

            // center window horizontally
            left = (dpiScaledWorkingArea.GetWidth() - width) >> 1;
        }
        // in second stage check if we are only slightly outside of our window on the right side (might be wanted by user)
        else if (left + 100 > dpiScaledWorkingArea.GetRight())
        {
            left = dpiScaledWorkingArea.GetRight() - 100;
        }

        // in third stage we check if we are outside of our window on the left side
        if (left < dpiScaledWorkingArea.GetLeft())
        {
            left = dpiScaledWorkingArea.GetLeft();
        }

        if (left + width > dpiScaledWorkingArea.GetRight())
        {
            width = dpiScaledWorkingArea.GetRight() - left;
        }

        // do the same for top setting

        if (top >= dpiScaledWorkingArea.GetBottom())
        {
            if (height > dpiScaledWorkingArea.GetHeight())
            {
                height = dpiScaledWorkingArea.GetHeight();
            }

            top = (dpiScaledWorkingArea.GetHeight() - height) >> 1;
        }
        else if (top + 100 > dpiScaledWorkingArea.GetBottom())
        {
            top = dpiScaledWorkingArea.GetBottom() - 100;
        }

        if (top < dpiScaledWorkingArea.GetTop())
        {
            top = dpiScaledWorkingArea.GetTop();
        }

        if (top + height > dpiScaledWorkingArea.GetBottom())
        {
            height = dpiScaledWorkingArea.GetBottom() - top;
        }
    }
}
