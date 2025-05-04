#include <Drawing/Buttons/MainMenuButton.h>

namespace xit::Drawing
{
    //******************************************************************************
    // Public
    //******************************************************************************

    void MainMenuButton::SetMainMenuSettings(MainMenuSettings *value)
    {
        if (mainMenuSettings != value)
        {
            mainMenuSettings = value;
            CheckMainMenuSettings();
        }
    }

    void MainMenuButton::SetTarget(Visual *value)
    {
        if (target != value)
        {
            target = value;
            UpdateTargetVisibility();
        }
    }

    MainMenuButton::MainMenuButton()
    {
        mainMenuSettings = nullptr;
        target = nullptr;

        SetBrushGroup("MainMenuButton");
        SetLayoutGroup("MainMenuButton");

        SetUniformImageSize(UIDefaults::MenuButtonImageSize);
        SetShowImage(true);

        SetCanActivate(true);
        SetOrientation(Orientation::Vertical);
    }

    //******************************************************************************
    // Protected
    //******************************************************************************

    void MainMenuButton::OnIsActiveChanged(EventArgs &e)
    {
        ButtonBase::OnIsActiveChanged(e);

        UpdateTargetVisibility();
    }

    void MainMenuButton::OnNameChanged(EventArgs &e)
    {
        isActiveSettingName = "Is" + GetName() + "Active";
        isVisibleSettingName = "Is" + GetName() + "Visible";

        ButtonBase::OnNameChanged(e);
    }

    //******************************************************************************
    // Private
    //******************************************************************************

    void MainMenuButton::UpdateImageAndText()
    {
        bool showText = mainMenuSettings->GetShowMainMenuButtonText();
        bool showImage = mainMenuSettings->GetShowMainMenuButtonImage();

        // set once
        SetShowLabel(showText);
        SetShowImage(showImage);

        if (!showImage && showText)
        {
            SetColumnSpacing(0);
            // SetHeight = UIDefaults.MenuButtonHorizontalHeight;
        }
        else if (showImage && !showText)
        {
            SetColumnSpacing(0);
            // SetHeight = UIDefaults.MenuButtonHorizontalHeight;
        }
        else
        {
            // SetHeight = UIDefaults.MenuButtonVerticalHeight;
            SetColumnSpacing(UIDefaults::ButtonSpacing);
        }
    }

    void MainMenuButton::CheckMainMenuSettings()
    {
        if (mainMenuSettings != nullptr && !GetName().empty())
        {
            // BoolSetting *setting = (BoolSetting *)(*mainMenuSettings)[isActiveSettingName];

            // if (!setting)
            // {
            //     setting = new BoolSetting(isActiveSettingName, false);
            //     mainMenuSettings->Add(setting);
            //     // setting.PropertyChanged += (s, e) => Update();
            // }

            // SetIsActiveSetting(setting);

            // setting = (BoolSetting *)(*mainMenuSettings)[isVisibleSettingName];
            // if (!setting)
            // {
            //     setting = new BoolSetting(isVisibleSettingName, true);
            //     mainMenuSettings->Add(setting);
            // }

            // setting->ValueChanged.Add(&MainMenuButton::IsVisibleSetting_ValueChanged, this);
            // VisibilityToggleButton.IsActiveSetting = setting;

            // mainMenuSettings->ShowMainMenuButtonText.ValueChanged.Add(&MainMenuButton::ShowContentValueChanged, this);
            // mainMenuSettings->ShowMainMenuButtonImage.ValueChanged.Add(&MainMenuButton::ShowContentValueChanged, this);

            UpdateImageAndText();
            // Update();
        }
    }

    // void MainMenuButton::IsVisibleSetting_ValueChanged(bool newValue)
    // {
    //     SetVisibility(newValue ? Visibility::Visible : Visibility::Collapsed);
    // }
    // void MainMenuButton::ShowContentValueChanged(bool newValue)
    // {
    //     UpdateImageAndText();
    // }

    void MainMenuButton::UpdateTargetVisibility()
    {
        if (target != nullptr)
        {
            target->SetIsVisible(GetIsActive());
        }
    }

}
