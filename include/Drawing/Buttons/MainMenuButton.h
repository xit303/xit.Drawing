#pragma once

#include <Drawing/Buttons/ButtonBase.h>
#include <Drawing/MainMenuSettings.h>

namespace xit::Drawing
{
    class MainMenuButton : public ButtonBase
    {
    private:
        std::string isActiveSettingName;
        std::string isVisibleSettingName;
        MainMenuSettings *mainMenuSettings;

        Visual *target;

        void UpdateImageAndText();
        void CheckMainMenuSettings();
        // void IsVisibleSetting_ValueChanged(bool newValue);
        // void ShowContentValueChanged(bool newValue);
        void UpdateTargetVisibility();

    protected:
        virtual void OnIsActiveChanged(EventArgs &e) override;
        virtual void OnNameChanged(EventArgs &e) override;

    public:
        __always_inline const std::string &IsActiveSettingName() const { return isActiveSettingName; }
        __always_inline const std::string &IsVisibleSettingName() const { return isVisibleSettingName; }

        __always_inline MainMenuSettings *GetMainMenuSettings() { return mainMenuSettings; }
        void SetMainMenuSettings(MainMenuSettings *value);

        __always_inline Visual *GetTarget() { return target; }
        void SetTarget(Visual *value);

        MainMenuButton();
    };
}
