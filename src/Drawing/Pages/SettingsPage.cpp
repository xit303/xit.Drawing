#include <Drawing/Pages/SettingsPage.h>

namespace xit::Drawing::Pages
{
    SettingsPage::SettingsPage()
    {
        // SetRows("Auto");
        SetRowSpacing(UIDefaults::RowSpacing);

#ifdef DEBUG
        debugSettingsExpander.SetName("debugSettingsExpander");
        debugSettingsExpander.SetText("Debug settings");

        AddChild(&debugSettingsExpander);

        //******************************************************************************
        // #region LoggerComboBox
        //******************************************************************************

        for (int i = 0; i < (int)LogLevel::None + 1; i++)
        {
            std::string name = Logger::GetLogLevelName((LogLevel)i);
            logLevelNames.push_back(name);
        }

        loggerComboBox.SetItems(&logLevelNames);
        loggerComboBox.SetColumn(1);
        // loggerComboBox.SetMargin(5, 0, 0, 0);

        // set loglevel before adding the event handler to prevent useless triggering
        loggerComboBox.SetSelectedValue(Logger::GetLogLevelName(Logger::GetLogLevel()));
        loggerComboBox.SelectionChanged.Add(&SettingsPage::LoggerComboBox_SelectionChanged, this);

        loggerContainer.SetInheritForeground(true);
        loggerContainer.SetBrushGroup("Container");
        loggerContainer.SetColumns("Auto,*");
        loggerContainer.SetRows("Auto");
        loggerContainer.SetColumnSpacing(UIDefaults::ColumnSpacing);
        debugSettingsExpander.AddChild(&loggerContainer);

        // logLevelLabel.SetTextSource("LogLevelLabel");
        logLevelLabel.SetText("Log level:");
        loggerContainer.AddChild(&logLevelLabel);
        loggerContainer.AddChild(&loggerComboBox);

        // debugSettingsExpander.AddChild(&debugSettingsPropertyGrid);

        // ShowGridLinesSwitch = debugSettingsPropertyGrid.AddSwitch("DebugSettingsShowGridLinesSetting");
        ShowGridLinesSwitch->IsActiveChanged.Add([](IsActiveProperty &sender, EventArgs &e) -> void
                                                 {
                                                     // foreach (Grid grid in Grid.AllGrids)
                                                     //{
                                                     //     grid.ShowGridLines = ShowGridLinesSwitch.IsActive;
                                                     // };
                                                 });
#endif

        //******************************************************************************
        // #region MainMenuSettingsExpander
        //******************************************************************************

        int row = 0;
        // SetRows("Auto,Auto");
        SetRows("Auto");

        mainMenuSettingsControl.SetRow(row++);
        AddChild(&mainMenuSettingsControl);

        // InputOverlayExpander.SetName("InputOverlayExpander");
        // InputOverlayExpander.SetText("Change Input overlay settings");
        // InputOverlayExpander.SetRow(row++);

        // AddChild(&InputOverlayExpander);

        // propertyGrid.SetInheritForeground(true);
        // ShowInputOverlaySwitch = propertyGrid.AddSwitch("EnableInputOverlay");
        // OverlayTime = propertyGrid.AddNumericTextBox("OverlayTime", 100, 10000, 1000);
        // InputOverlayExpander.AddChild(&propertyGrid);

        // InstanceHandler<InputOverlaySettings>::RequestInstance(&SettingsPage::InstanceRequestComplete, this);
    }

    // void SettingsPage::InstanceRequestComplete(InputOverlaySettings* requestedInstance)
    // {
    //     ShowInputOverlaySwitch->SetIsActiveSetting((BoolSetting*)requestedInstance->GetSetting<bool>("EnableInputOverlay"));
    //     propertyGrid.SetResetSetting(ShowInputOverlaySwitch, ShowInputOverlaySwitch->IsActiveSetting());

    //     OverlayTime->SetValueSetting((FloatSetting*)requestedInstance->GetSetting<double>("OverlayTime"));
    //     propertyGrid.SetResetSetting(OverlayTime, OverlayTime->ValueSetting());
    // }

#ifdef DEBUG
    void SettingsPage::LoggerComboBox_SelectionChanged(const std::string &selectedValue)
    {
        Logger::SetLogLevel((LogLevel)loggerComboBox.GetSelectedIndex());
    }
#endif

    //******************************************************************************

    //******************************************************************************

    void SettingsPage::AddChild2(Container &container, const std::string &headerTextSource)
    {
        if (container == nullptr)
        {
            return;
        }

        size_t count = GetChildCount();
        for (size_t i = 0; i < count; i++)
        {
            Expander *existingExpander = dynamic_cast<Expander *>(GetChildAt(i));

            if (existingExpander)
            {
                if (existingExpander->ContainsChild(&container))
                {
                    return;
                }
            }
        }

        Expander *expander = new Expander();
        // expander->SetTextSource(headerTextSource);
        expander->AddChild(&container);
        AddChild(expander);

        container.SetVisibility(Visibility::Visible);
        expander->SetIsExpanded(false);
    }

    void SettingsPage::RemoveChild2(Container &container)
    {
        if (container == nullptr)
        {
            return;
        }

        size_t count = GetChildCount();
        for (size_t i = 0; i < count; i++)
        {
            Expander *existingExpander = dynamic_cast<Expander *>(GetChildAt(i));

            if (existingExpander)
            {
                if (existingExpander->ContainsChild(&container))
                {
                    existingExpander->RemoveChild(&container);
                    RemoveChild(existingExpander);
                    break;
                }
            }
        }

        container.SetVisibility(Visibility::Collapsed);
    }
}
