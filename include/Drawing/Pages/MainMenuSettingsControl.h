#pragma once

#include <Drawing/Expander.h>
#include <Drawing/Switch.h>
#include <Drawing/GroupBox.h>
#include <Drawing/ToggleButtonGroup.h>
#include <Drawing/Buttons/ToggleButton.h>
#include <Drawing/Buttons/MainMenuButton.h>
// #include "../../Settings/MainMenuSettings.h"
// #include "../Controller.h"

namespace xit::Drawing::Pages
{
    class MainMenuSettingsControl : public Expander
    {
    private:
        GroupBox buttonAppearanceGroupBox;
        // PropertyGrid buttonAppearancePropertyGrid;
        //Switch KeepMenuOrderFixed;
        // Switch* ShowMainMenuButtonText;
        // Switch* ShowMainMenuButtonImage;

        GroupBox dockTypeGroupBox;
        ToggleButtonGroup dockTypeToggleButtonGroup;
        ToggleButton dockTop;
        ToggleButton dockTopLeftCorner;
        ToggleButton dockTopRightCorner;

        ToggleButton dockLeft;
        ToggleButton dockRight;

        ToggleButton dockBottom;
        ToggleButton dockBottomLeftCorner;
        ToggleButton dockBottomRightCorner;

        GroupBox menuOrientationGroupBox;
        ToggleButtonGroup menuOrientationToggleButtonGroup;
        ToggleButton menuOrientationHorizontal;
        ToggleButton menuOrientationVertical;

        GroupBox menuOrientationDirectionGroupBox;
        ToggleButtonGroup menuOrientationDirectionToggleButtonGroup;
        ToggleButton menuOrientationDirectionNormal;
        ToggleButton menuOrientationDirectionInverted;

        MainMenuSettings* mainMenuSettings;
        // DockTypeSetting* dockTypeSetting;
        // Settings::OrientationSetting* menuOrientationSetting;
        // Settings::OrientationDirectionSetting* menuOrientationDirectionSetting;

        //List<Switch*> switchesWaitingForSettings;

        GroupBox buttonVisibilitygroupBox;
        Label usageLabel;

    public:
        MainMenuSettingsControl()
        {
            // dockTypeSetting = nullptr;
            mainMenuSettings = nullptr;
            // menuOrientationSetting = nullptr;
            // menuOrientationDirectionSetting = nullptr;

            SetName("MainMenuSettingsControl");
            SetText("Main menu settings");

            //******************************************************************************
            // #region Button Appearance
            //******************************************************************************

            // buttonAppearanceGroupBox.SetTextSource("MainMenuButtonAppearance");
            buttonAppearanceGroupBox.SetText("Change button appearance");
            AddChild(&buttonAppearanceGroupBox);
            
            // buttonAppearanceGroupBox.AddChild(&buttonAppearancePropertyGrid);

            // ShowMainMenuButtonText = buttonAppearancePropertyGrid.AddSwitch("MainMenuSettingsShowMainMenuButtonTextSetting");
            // ShowMainMenuButtonImage = buttonAppearancePropertyGrid.AddSwitch("MainMenuSettingsShowMainMenuButtonImageSetting");

            //AddChild(KeepMenuOrderFixed = new Switch
            //(
            //    "KeepMenuOrderFixed),
            //    "Keep menu order fixed",
            //));

            //KeepMenuOrderFixed.CheckedAction = () => mainMenuSettings.KeepMenuOrderFixed = true;
            //KeepMenuOrderFixed.UncheckedAction = () => mainMenuSettings.KeepMenuOrderFixed = false;

            //******************************************************************************
            // #region Dock Type
            //******************************************************************************
            
            // dockTypeGroupBox.SetTextSource("MainMenuSettingsMainMenuDockType");
            dockTypeGroupBox.SetText("Change where the main menu should be docked");
            AddChild(&dockTypeGroupBox);
            
            dockTypeToggleButtonGroup.SetUseOrientation(false);
            dockTypeToggleButtonGroup.SetMustSelectOne(true);
            dockTypeToggleButtonGroup.SetColumns("Auto,Auto,Auto");
            dockTypeToggleButtonGroup.SetRows("Auto,Auto,Auto");
            dockTypeToggleButtonGroup.SetColumnSpacing(UIDefaults::MinimumColumnSpacing);
            dockTypeToggleButtonGroup.SetRowSpacing(UIDefaults::MinimumRowSpacing);
            dockTypeGroupBox.AddChild(&dockTypeToggleButtonGroup);

            //******************************************************************************
            // #region Top
            //******************************************************************************
            
            dockTopLeftCorner.SetImageSource("Resources/Images/Buttons/DockTopLeftCorner.png");
            // dockTopLeftCorner.SetToolTipSource("MainMenuSettingsDockTopLeftCorner");
            dockTopLeftCorner.SetToolTip("Dock main menu in the top left corner");
            dockTopLeftCorner.SetGrid(0, 0);
            dockTopLeftCorner.IsActiveChanged.Add(&MainMenuSettingsControl::DockType_ActiveChanged, this);
            dockTypeToggleButtonGroup.AddChild(&dockTopLeftCorner);
            
            dockTop.SetImageSource("Resources/Images/Buttons/DockTop.png");
            // dockTop.SetToolTipSource("MainMenuSettingsDockTop");
            dockTop.SetToolTip("Dock main menu centered at top");
            dockTop.SetGrid(1, 0);
            dockTop.IsActiveChanged.Add(&MainMenuSettingsControl::DockType_ActiveChanged, this);
            dockTypeToggleButtonGroup.AddChild(&dockTop);

            dockTopRightCorner.SetImageSource("Resources/Images/Buttons/DockTopRightCorner.png");
            // dockTopRightCorner.SetToolTipSource("MainMenuSettingsDockTopRightCorner");
            dockTopRightCorner.SetToolTip("Dock main menu in the top right corner");
            dockTopRightCorner.SetGrid(2, 0);
            dockTopRightCorner.IsActiveChanged.Add(&MainMenuSettingsControl::DockType_ActiveChanged, this);
            dockTypeToggleButtonGroup.AddChild(&dockTopRightCorner);
            
            //******************************************************************************
            // #region Left / Right
            //******************************************************************************

            dockLeft.SetImageSource("Resources/Images/Buttons/DockLeft.png");
            // dockLeft.SetToolTipSource("MainMenuSettingsDockLeft");
            dockLeft.SetToolTip("Dock main menu left centered");
            dockLeft.SetGrid(0, 1);
            dockLeft.IsActiveChanged.Add(&MainMenuSettingsControl::DockType_ActiveChanged, this);
            dockTypeToggleButtonGroup.AddChild(&dockLeft);
            
            dockRight.SetImageSource("Resources/Images/Buttons/DockRight.png");
            // dockRight.SetToolTipSource("MainMenuSettingsDockRight");
            dockRight.SetToolTip("Dock main menu right centered");
            dockRight.SetGrid(2, 1);
            dockRight.IsActiveChanged.Add(&MainMenuSettingsControl::DockType_ActiveChanged, this);
            dockTypeToggleButtonGroup.AddChild(&dockRight);

            //******************************************************************************
            // #region Bottom
            //******************************************************************************

            dockBottomLeftCorner.SetImageSource("Resources/Images/Buttons/DockBottomLeftCorner.png");
            //dockBottomLeftCorner.SetToolTipSource("MainMenuSettingsDockBottomLeftCorner");
            dockBottomLeftCorner.SetToolTip("Dock main menu in the bottom left corner");
            dockBottomLeftCorner.SetGrid(0, 2);
            dockBottomLeftCorner.IsActiveChanged.Add(&MainMenuSettingsControl::DockType_ActiveChanged, this);
            dockTypeToggleButtonGroup.AddChild(&dockBottomLeftCorner);
            
            dockBottom.SetImageSource("Resources/Images/Buttons/DockBottom.png");
            // dockBottom.SetToolTipSource("MainMenuSettingsDockBottom");
            dockBottom.SetToolTip("Dock main menu centered at bottom");
            dockBottom.SetGrid(1, 2);
            dockBottom.IsActiveChanged.Add(&MainMenuSettingsControl::DockType_ActiveChanged, this);
            dockTypeToggleButtonGroup.AddChild(&dockBottom);
            
            dockBottomRightCorner.SetImageSource("Resources/Images/Buttons/DockBottomRightCorner.png");
            // dockBottomRightCorner.SetToolTipSource("MainMenuSettingsDockBottomRightCorner");
            dockBottomRightCorner.SetToolTip("Dock main menu in the bottom right corner");
            dockBottomRightCorner.SetGrid(2, 2);
            dockBottomRightCorner.IsActiveChanged.Add(&MainMenuSettingsControl::DockType_ActiveChanged, this);
            dockTypeToggleButtonGroup.AddChild(&dockBottomRightCorner);

            //******************************************************************************
            // #region Menu orientation
            //******************************************************************************
            
            // menuOrientationGroupBox.SetTextSource("MainMenuSettingsMainMenuOrientation");
            menuOrientationGroupBox.SetText("Change orientation (horizontal, vertical) of the main menu (only available in corners)");
            AddChild(&menuOrientationGroupBox);
            
            menuOrientationToggleButtonGroup.SetMustSelectOne(true);
            menuOrientationToggleButtonGroup.SetColumns("Auto,Auto");
            menuOrientationToggleButtonGroup.SetColumnSpacing(UIDefaults::MinimumColumnSpacing);
            menuOrientationGroupBox.AddChild(&menuOrientationToggleButtonGroup);

            menuOrientationHorizontal.SetImageSource("Resources/Images/Buttons/MenuOrientationHorizontal.png");
            // menuOrientationHorizontal.SetToolTipSource("MainMenuSettingsMenuOrientationHorizontal");
            menuOrientationHorizontal.SetToolTip("Set horizontal menu item direcion"); // TODO Better ToolTip
            menuOrientationHorizontal.SetColumn(0);
            menuOrientationHorizontal.IsActiveChanged.Add(&MainMenuSettingsControl::MenuOrientation_ActiveChanged, this);
            menuOrientationToggleButtonGroup.AddChild(&menuOrientationHorizontal);

            menuOrientationVertical.SetImageSource("Resources/Images/Buttons/MenuOrientationVertical.png");
            // menuOrientationVertical.SetToolTipSource("MainMenuSettingsMenuOrientationVertical");
            menuOrientationVertical.SetToolTip("Set vertical menu item direction"); // TODO Better ToolTip
            menuOrientationVertical.SetColumn(1);
            menuOrientationVertical.IsActiveChanged.Add(&MainMenuSettingsControl::MenuOrientation_ActiveChanged, this);
            menuOrientationToggleButtonGroup.AddChild(&menuOrientationVertical);
            
            //******************************************************************************
            // #region Menu orienation direction
            //******************************************************************************
            
            // menuOrientationDirectionGroupBox.SetTextSource("MainMenuSettingsMainMenuOrientationDirection");
            menuOrientationDirectionGroupBox.SetText("Change button order (direction) of the main menu");
            AddChild(&menuOrientationDirectionGroupBox);
            
            menuOrientationDirectionToggleButtonGroup.SetMustSelectOne(true);
            menuOrientationDirectionToggleButtonGroup.SetColumns("Auto,Auto");
            menuOrientationDirectionToggleButtonGroup.SetColumnSpacing(UIDefaults::MinimumColumnSpacing);
            menuOrientationDirectionGroupBox.AddChild(&menuOrientationDirectionToggleButtonGroup);

            menuOrientationDirectionNormal.SetImageSource("Resources/Images/Buttons/MenuOrientationDirectionNormal.png");
            // menuOrientationDirectionNormal.SetToolTipSource("MainMenuSettingsMenuOrientationDirectionNormal");
            menuOrientationDirectionNormal.SetToolTip("Normal direction (Left to right or top to bottom)");
            menuOrientationDirectionNormal.SetColumn(0);
            menuOrientationDirectionNormal.IsActiveChanged.Add(&MainMenuSettingsControl::MenuOrientationDirection_ActiveChanged, this);
            menuOrientationDirectionToggleButtonGroup.AddChild(&menuOrientationDirectionNormal);
            
            menuOrientationDirectionInverted.SetImageSource("Resources/Images/Buttons/MenuOrientationDirectionInverted.png");
            // menuOrientationDirectionInverted.SetToolTipSource("MainMenuSettingsMenuOrientationDirectionInverted");
            menuOrientationDirectionInverted.SetToolTip("Inverted direction (right to left or bottom to top)");
            menuOrientationDirectionInverted.SetColumn(1);
            menuOrientationDirectionInverted.IsActiveChanged.Add(&MainMenuSettingsControl::MenuOrientationDirection_ActiveChanged, this);
            menuOrientationDirectionToggleButtonGroup.AddChild(&menuOrientationDirectionInverted);

            //******************************************************************************
            // #region Button visibility
            //******************************************************************************

            // buttonVisibilitygroupBox.SetTextSource("MainMenuSettingsMainMenuButtonVisibility");
            buttonVisibilitygroupBox.SetText("Change button visibility");
            buttonVisibilitygroupBox.SetVisibility(Visibility::Collapsed);
            AddChild(&buttonVisibilitygroupBox);

            usageLabel.SetText(
                "Press any of the buttons below to show or hide the menu button in the main menu.\n" \
                "This will also remove the menu from the settings for a better overview.\n" \
                "If \"Keep menu order fixed\" is disabled, the order of the buttons and the settings menu can be changed\n" \
                "by activating/deactivating all buttons and deactivate/activate them in the order you want :)\n" \
                "Otherwise each of the buttons below correspond to the main menu position");
            buttonVisibilitygroupBox.AddChild(&usageLabel);
            
            // TODO get button list from main page and add them dynamically
            //Controller::RequestControl("UsersButton", &MainMenuSettingsControl::ControlAvailable, this, false);
            //Controller::RequestControl("TrainingSettingsButton", &MainMenuSettingsControl::ControlAvailable, this, false);
            //Controller::RequestControl("GameSettingsButton", &MainMenuSettingsControl::ControlAvailable, this, false);
            //Controller::RequestControl("KeyboardSettingsButton", &MainMenuSettingsControl::ControlAvailable, this, false);
            //Controller::RequestControl("AudioSettingsButton", &MainMenuSettingsControl::ControlAvailable, this, false);
            //Controller::RequestControl("MidiSettingsButton", &MainMenuSettingsControl::ControlAvailable, this, false);
            //Controller::RequestControl("LanguageSettingsButton", &MainMenuSettingsControl::ControlAvailable, this, false);
            //Controller::RequestControl("CommunityButton", &MainMenuSettingsControl::ControlAvailable, this, false);
            //Controller::RequestControl("ModifyUIButton", &MainMenuSettingsControl::ControlAvailable, this, false);

            // InstanceHandler<MainMenuSettings>::RequestInstance(&MainMenuSettingsControl::InstanceRequestComplete, this);
        }

    private:
        // void InstanceRequestComplete(MainMenuSettings* requestedInstance)
        // {
        //     mainMenuSettings = requestedInstance;
        //     ShowMainMenuButtonText->SetIsActiveSetting(&requestedInstance->ShowMainMenuButtonText);
        //     ShowMainMenuButtonImage->SetIsActiveSetting(&requestedInstance->ShowMainMenuButtonImage);
        //     buttonAppearancePropertyGrid.SetResetSetting(ShowMainMenuButtonText, &requestedInstance->ShowMainMenuButtonText);
        //     buttonAppearancePropertyGrid.SetResetSetting(ShowMainMenuButtonImage, &requestedInstance->ShowMainMenuButtonImage);

        //     menuOrientationSetting = &requestedInstance->MenuOrientation;
        //     menuOrientationSetting->ValueChanged.Add(&MainMenuSettingsControl::MenuOrientationSetting_ValueChanged, this);
        //     MenuOrientationSetting_ValueChanged(menuOrientationSetting->Value());

        //     menuOrientationDirectionSetting = &requestedInstance->MenuOrientationDirection;
        //     menuOrientationDirectionSetting->ValueChanged.Add(&MainMenuSettingsControl::MenuOrientationDirectionSetting_ValueChanged, this);
        //     MenuOrientationDirectionSetting_ValueChanged(menuOrientationDirectionSetting->Value());

        //     dockTypeSetting = &requestedInstance->MenuDockType;
        //     dockTypeSetting->ValueChanged.Add(&MainMenuSettingsControl::DockTypeSetting_ValueChanged, this);
        //     DockTypeSetting_ValueChanged(dockTypeSetting->Value());
        //     //KeepMenuOrderFixed.IsActiveSetting = value.LoadSetting("mainMenuSettings.KeepMenuOrderFixed), true);

        //     bool switchesAvailable = false;

        //     std::string visible = "Visible";
        //     size_t visibleLength = strlen(visible);

        //     for (SettingBase* settingBase : mainMenuSettings->Values)
        //     {
        //         std::string settingName = settingBase->Name;

        //         if (String::EndsWith(settingName, visible))
        //         {
        //             if (String::Contains(settingName, "Settings"))
        //                 continue;

        //             size_t len = strlen(settingName);

        //             std::string tmp = String::Remove(settingName, 0, 2);
        //             std::string buttonName = String::Remove(tmp, len - visibleLength - 1, visibleLength);
        //             delete tmp;

        //             Switch* visibilitySwitch = new Switch();
        //             visibilitySwitch->SetTextSource(buttonName);
        //             visibilitySwitch->SetIsActiveSetting((BoolSetting*)settingBase);

        //             buttonVisibilitygroupBox.AddChild(visibilitySwitch);
        //             switchesAvailable = true;
        //         }
        //     }
        //     if (switchesAvailable)
        //         buttonVisibilitygroupBox.SetVisibility(Visibility::Visible);
        // }

        //void ControlAvailable(ICommand* control)
        //{
        //    MainMenuButton* button = dynamic_cast<MainMenuButton*>(control);
        //    if (!button)
        //    {
        //        Logger::Log(LogLevel::Error, "MainMenuSettingsControl.ControlAvailable", "The requested control must be a MainMenuButton. dynamic_cast<MainMenuButton*>(control) failed.");
        //    }
        //    else
        //        AddMainMenuVisibilityControl(*button);
        //}

        //void AddMainMenuVisibilityControl(MainMenuButton& mainMenuButton)
        //{
        //    if (mainMenuButton != nullptr) // TODO this should be removed in final
        //    {
        //        if (!buttonVisibilitygroupBox.IsVisible)
        //        {
        //            buttonVisibilitygroupBox.SetVisibility(Visibility::Visible);
        //        }

        //        Switch* visibilitySwitch = new Switch();
        //        visibilitySwitch->SetTextSource(mainMenuButton.TextSource);
        //        // TODO visibilitySwitch->SetTag((void*)mainMenuButton.IsVisibleSettingName());
        //        
        //        switchesWaitingForSettings.Add(visibilitySwitch);

        //        buttonVisibilitygroupBox.AddChild(visibilitySwitch);
        //    }
        //}

        void DockTypeSetting_ValueChanged(DockType newValue)
        {
            switch (newValue)
            {
            case DockType::TopLeftCorner:
                dockTopLeftCorner.SetIsActive(true);
                menuOrientationHorizontal.SetEnabled(true);
                menuOrientationVertical.SetEnabled(true);
                break;

            case DockType::Top:
                dockTop.SetIsActive(true);
                menuOrientationHorizontal.SetEnabled(false);
                menuOrientationVertical.SetEnabled(false);
                break;

            case DockType::Left:
                dockLeft.SetIsActive(true);
                menuOrientationHorizontal.SetEnabled(false);
                menuOrientationVertical.SetEnabled(false);
                break;

            case DockType::TopRightCorner:
                dockTopRightCorner.SetIsActive(true);
                menuOrientationHorizontal.SetEnabled(true);
                menuOrientationVertical.SetEnabled(true);
                break;

            case DockType::Right:
                dockRight.SetIsActive(true);
                menuOrientationHorizontal.SetEnabled(false);
                menuOrientationVertical.SetEnabled(false);
                break;

            case DockType::Bottom:
                dockBottom.SetIsActive(true);
                menuOrientationHorizontal.SetEnabled(false);
                menuOrientationVertical.SetEnabled(false);
                break;

            case DockType::BottomLeftCorner:
                dockBottomLeftCorner.SetIsActive(true);
                menuOrientationHorizontal.SetEnabled(true);
                menuOrientationVertical.SetEnabled(true);
                break;

            case DockType::BottomRightCorner:
                dockBottomRightCorner.SetIsActive(true);
                menuOrientationHorizontal.SetEnabled(true);
                menuOrientationVertical.SetEnabled(true);
                break;

            default:
                // we do not handle None and Fill for menu docking
                break;
            }
        }

        void MenuOrientationSetting_ValueChanged(Orientation newValue)
        {
            switch (newValue)
            {
            case Orientation::Vertical:
                menuOrientationHorizontal.SetIsActive(true);
                break;

            case Orientation::Horizontal:
                menuOrientationVertical.SetIsActive(true);
                break;
            }
        }

        void MenuOrientationDirectionSetting_ValueChanged(OrientationDirection newValue)
        {
            switch (newValue)
            {
            case OrientationDirection::Normal:
                menuOrientationDirectionNormal.SetIsActive(true);
                break;

            case OrientationDirection::Inverted:
                menuOrientationDirectionInverted.SetIsActive(true);
                break;
            }
        }

        void DockType_ActiveChanged(IsActiveProperty& sender, EventArgs& e)
        {
            // if (dockTypeSetting == nullptr)
            // {
            //     return;
            // }

            // ToggleButton* button = (ToggleButton*)&sender;

            // if (button->GetIsActive())
            // {
            //     if (button == &dockTopLeftCorner)
            //     {
            //         dockTypeSetting->SetValue(DockType::TopLeftCorner);
            //     }
            //     else if (button == &dockTop)
            //     {
            //         dockTypeSetting->SetValue(DockType::Top);
            //     }
            //     else if (button == &dockTopRightCorner)
            //     {
            //         dockTypeSetting->SetValue(DockType::TopRightCorner);
            //     }
            //     if (button == &dockLeft)
            //     {
            //         dockTypeSetting->SetValue(DockType::Left);
            //     }
            //     else if (button == &dockRight)
            //     {
            //         dockTypeSetting->SetValue(DockType::Right);
            //     }
            //     else if (button == &dockBottomLeftCorner)
            //     {
            //         dockTypeSetting->SetValue(DockType::BottomLeftCorner);
            //     }
            //     else if (button == &dockBottom)
            //     {
            //         dockTypeSetting->SetValue(DockType::Bottom);
            //     }
            //     else if (button == &dockBottomRightCorner)
            //     {
            //         dockTypeSetting->SetValue(DockType::BottomRightCorner);
            //     }
            // }
        }

        void MenuOrientation_ActiveChanged(IsActiveProperty& sender, EventArgs& e)
        {
            // if (menuOrientationSetting == nullptr)
            // {
            //     return;
            // }

            // ToggleButton* button = (ToggleButton*)&sender;

            // if (button->GetIsActive())
            // {
            //     menuOrientationSetting->SetValue
            //     (
            //         button == menuOrientationHorizontal 
            //             ? Orientation::Vertical 
            //             : Orientation::Horizontal
            //     );
            // }
        }

        void MenuOrientationDirection_ActiveChanged(IsActiveProperty& sender, EventArgs& e)
        {
            // if (menuOrientationSetting == nullptr)
            // {
            //     return;
            // }

            // ToggleButton* button = (ToggleButton*)&sender;
            // if (button->GetIsActive())
            // {
            //     menuOrientationDirectionSetting->SetValue
            //     (
            //         button == menuOrientationDirectionNormal
            //             ? OrientationDirection::Normal
            //             : OrientationDirection::Inverted
            //     );
            // }
        }
    };
}
