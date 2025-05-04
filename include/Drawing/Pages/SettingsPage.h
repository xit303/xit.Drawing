#pragma once

// #include "../../Settings/InputOverlaySettings.h"

#include "Page.h"
#include "../ComboBox.h"
#include <Drawing/Expander.h>
// #include "../PropertyGrid.h"
#include <Drawing/Switch.h>
#include <Drawing/NumericTextBox.h>
#include <Drawing/Pages/MainMenuSettingsControl.h>

namespace xit::Drawing::Pages
{
    class SettingsPage : public Page
    {
    private:
        Expander MainMenuSettingsExpander;
        MainMenuSettingsControl mainMenuSettingsControl;
        // int startIndex;

        // ExpanderSettingsControl ExpanderSettingsControl;

        std::list<std::string> logLevelNames;

        Expander debugSettingsExpander;
        Expander InputOverlayExpander;
        // PropertyGrid propertyGrid;

        // Switch* ShowInputOverlaySwitch;
        // NumericTextBox* OverlayTime;

#ifdef DEBUG
        Container loggerContainer;
        ComboBox loggerComboBox;
        Label logLevelLabel;

        // PropertyGrid debugSettingsPropertyGrid;
        Switch *ShowGridLinesSwitch;
#endif

        // void InstanceRequestComplete(InputOverlaySettings* requestedInstance);
#ifdef DEBUG
        void LoggerComboBox_SelectionChanged(const std::string &selectedValue);
#endif

    public:
        SettingsPage();

        void AddChild2(Container &container, const std::string &headerTextSource);
        void RemoveChild2(Container &container);
    };
}
