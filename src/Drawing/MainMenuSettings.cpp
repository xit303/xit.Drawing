
#include <Drawing/MainMenuSettings.h>
#include <Application/App.h>
#include <ArduinoJson.h>

namespace xit::Drawing
{
    bool MainMenuSettings::Save()
    {
        JsonDocument doc;
        doc["KeepMenuOrderFixed"] = keepMenuOrderFixed;
        doc["MainMenuHeight"] = mainMenuHeight;
        doc["IsPercentageScaling"] = isPercentageScaling;
        doc["ShowMainMenuButtonText"] = showMainMenuButtonText;
        doc["ShowMainMenuImage"] = showMainMenuImage;
        doc["MenuDockType"] = (int)menuDockType;
        doc["MenuOrientation"] = (int)menuOrientation;
        doc["MenuOrientationDirection"] = (int)menuOrientationDirection;

        std::string fileName = xit::Application::App::UserPath() + "MainMenuSettings.json";
        File file(fileName, std::ios::out);
        file.Write(doc.as<std::string>());

        return true;
    }

    bool MainMenuSettings::Load(const std::string &path)
    {
        std::string fileName = path + "MainMenuSettings.json";
        std::string data = File::ReadAllText(fileName);

        // nothing saved so far so we did not load anything
        if (data.empty())
            return false;

        JsonDocument doc;
        deserializeJson(doc, data);

        keepMenuOrderFixed = doc["KeepMenuOrderFixed"].as<bool>();
        mainMenuHeight = doc["MainMenuHeight"].as<int>();
        isPercentageScaling = doc["IsPercentageScaling"].as<bool>();
        showMainMenuButtonText = doc["ShowMainMenuButtonText"].as<bool>();
        showMainMenuImage = doc["ShowMainMenuImage"].as<bool>();
        menuDockType = (DockType)doc["MenuDockType"].as<int>();
        menuOrientation = (Orientation)doc["MenuOrientation"].as<int>();
        menuOrientationDirection = (OrientationDirection)doc["MenuOrientationDirection"].as<int>();

        return true;
    }
}