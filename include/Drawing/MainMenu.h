#pragma once

#include <Drawing/ToggleButtonGroup.h>
#include <Drawing/ScrollViewer.h>
#include <Drawing/Properties/DockType.h>
#include <Drawing/Buttons/MainMenuButton.h>
#include <Drawing/MainMenuSettings.h>
#include <Drawing/SplitContainer.h>

namespace xit::Drawing
{
    class MainMenu : public SplitContainer
    {
    private:
        ToggleButtonGroup mainMenuToggleButtonGroup;
        ScrollViewer mainMenuContentContainer;

        MainMenuSettings *mainMenuSettings;
        // DockTypeSetting *dockTypeSetting;
        // OrientationSetting *menuOrientationSetting;
        // OrientationDirectionSetting *menuOrientationDirectionSetting;
        OrientationDirection menuOrientationDirection;

        DockType dockType;
        bool isInitialized;
        bool isUpdating;
        int mainMenuItemCount;

        void InstanceRequestComplete(MainMenuSettings *requestedInstance);

        // void MenuOrientationSetting_ValueChanged(const Orientation &newValue);
        // void MenuOrientationDirectionSetting_ValueChanged(const OrientationDirection &newValue);
        // void DockTypeSetting_ValueChanged(const DockType &newValue);
        void UpdateDock();
        void UpdateMenuOrientationDirection();

        void MainMenuToggleButtonGroup_ToggleButtonChecked(Container &sender);
        void MainMenuToggleButtonGroup_GroupClosed(ToggleButtonGroup &sender);

    protected:
        // void OnOrientationChanged() override;

        virtual void OnMenuOpened(EventArgs &e);
        virtual void OnMenuClosed(EventArgs &e);

        MainMenuButton *AddButton(const std::string &name, const std::string &defaultText, const std::string &defaultToolTip, Visual *target);
        virtual void OnSetMainMenuSettings(MainMenuSettings *mainMenuSettings);

    public:
        inline DockType SetDockType() const { return dockType; }
        void SetDockType(DockType value);

        inline const OrientationDirection &GetMenuOrientationDirection() const { return menuOrientationDirection; }
        void SetMenuOrientationDirection(const OrientationDirection &value);

        Event<EventArgs &> MenuOpened;
        Event<EventArgs &> MenuClosed;

        MainMenu();

    public:
        // void ToggleButton(int index);
    };
}
