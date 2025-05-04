#pragma once

#include <IO/IO.h>
#include <Drawing/Properties/Orientation.h>
#include <Drawing/Properties/OrientationDirection.h>
#include <Drawing/Properties/DockType.h>

namespace xit::Drawing
{
    class MainMenuSettings
    {
    private:
        bool keepMenuOrderFixed = true;
        int mainMenuHeight = 70;
        bool isPercentageScaling = true;
        bool showMainMenuButtonText = true;
        bool showMainMenuImage = true;

        DockType menuDockType = DockType::Top;
        Orientation menuOrientation = Orientation::Vertical;
        OrientationDirection menuOrientationDirection = OrientationDirection::Normal;

    public:
        __always_inline bool GetKeepMenuOrderFixed() const { return keepMenuOrderFixed; }
        void SetKeepMenuOrderFixed(const bool &value) { keepMenuOrderFixed = value; }

        __always_inline int GetMainMenuHeight() const { return mainMenuHeight; }
        void SetMainMenuHeight(const int &value) { mainMenuHeight = value; }

        __always_inline bool GetIsPercentageScaling() const { return isPercentageScaling; }
        void SetIsPercentageScaling(const bool &value) { isPercentageScaling = value; }

        __always_inline bool GetShowMainMenuButtonText() const { return showMainMenuButtonText; }
        void SetShowMainMenuButtonText(const bool &value) { showMainMenuButtonText = value; }

        __always_inline bool GetShowMainMenuButtonImage() const { return showMainMenuImage; }
        void SetShowMainMenuButtonImage(const bool &value) { showMainMenuImage = value; }

        __always_inline DockType GetMenuDockType() const { return menuDockType; }
        void SetMenuDockType(const DockType &value) { menuDockType = value; }

        __always_inline Orientation GetMenuOrientation() const { return menuOrientation; }
        void SetMenuOrientation(const Orientation &value) { menuOrientation = value; }

        __always_inline OrientationDirection GetMenuOrientationDirection() const { return menuOrientationDirection; }
        void SetMenuOrientationDirection(const OrientationDirection &value) { menuOrientationDirection = value; }

        MainMenuSettings() {}
        MainMenuSettings(const std::string &fileName) {}

        bool Save();
        bool Load(const std::string &path);
    };
}
