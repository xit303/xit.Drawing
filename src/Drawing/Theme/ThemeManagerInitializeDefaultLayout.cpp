#include <Drawing/Theme/ThemeManager.h>

namespace xit::Drawing
{
    LayoutVisualState *ThemeManager::CloneLayoutForState(LayoutVisualStateGroup *layoutVisualStateGroup, LayoutVisualState *layoutVisualState, const std::string &newStateName)
    {
        LayoutVisualState *newState = new LayoutVisualState(newStateName, *layoutVisualState);
        layoutVisualStateGroup->AddState(newState);
        return newState;
    }

    void ThemeManager::CloneLayoutForAllStates(LayoutVisualStateGroup *layoutVisualStateGroup, LayoutVisualState *layoutVisualState)
    {
        for (int i = 1; i < VisualStatesCount; i++)
        {
            CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, VisualStates[i]);
        }
    }

    void ThemeManager::InitializeDefaultLayout()
    {
        LayoutVisualStateGroup *layoutVisualStateGroup;
        LayoutVisualState *layoutVisualState;

        //******************************************************************************
        // Button
        //******************************************************************************

        layoutVisualState = new LayoutVisualState("Disabled");
        layoutVisualState->SetElevation(0);
        layoutVisualState->SetBorderThickness(UIDefaults::DefaultBorderThickness);
        layoutVisualState->SetCornerRadius(UIDefaults::CornerRadius);
        layoutVisualState->SetMinWidth(UIDefaults::ButtonMinWidth);
        layoutVisualState->SetHeight(UIDefaults::ButtonHeight);
        layoutVisualState->SetPadding(UIDefaults::ButtonPaddingLeftRight, 0, UIDefaults::ButtonPaddingLeftRight, 0);
        layoutVisualState->SetHorizontalContentAlignment(HorizontalAlignment::Center);
        layoutVisualState->SetVerticalContentAlignment(VerticalAlignment::Center);
        layoutVisualState->SetFontSize(UIDefaults::ButtonFontSize);

        layoutVisualStateGroup = new LayoutVisualStateGroup("Button");
        layoutVisualStateGroup->AddState(layoutVisualState);

        CloneLayoutForAllStates(layoutVisualStateGroup, layoutVisualState);
        Default.AddLayoutVisualStateGroup(layoutVisualStateGroup);

        //******************************************************************************
        // ButtonInContainer
        //******************************************************************************

        layoutVisualState = new LayoutVisualState("Disabled");
        layoutVisualState->SetElevation(0);
        layoutVisualState->SetBorderThickness(UIDefaults::DefaultBorderThickness, 0, 0, 0);
        layoutVisualState->SetMargin(0);
        layoutVisualState->SetWidth(UIDefaults::ToggleButtonHeight);
        layoutVisualState->SetHorizontalAlignment(HorizontalAlignment::Right);
        layoutVisualState->SetHorizontalContentAlignment(HorizontalAlignment::Center);
        layoutVisualState->SetVerticalContentAlignment(VerticalAlignment::Center);
        layoutVisualStateGroup = new LayoutVisualStateGroup("ButtonInContainer");
        layoutVisualStateGroup->AddState(layoutVisualState);

        CloneLayoutForAllStates(layoutVisualStateGroup, layoutVisualState);
        Default.AddLayoutVisualStateGroup(layoutVisualStateGroup);

        //******************************************************************************
        // Card
        //******************************************************************************

        layoutVisualState = new LayoutVisualState("Disabled");
        layoutVisualState->SetElevation(1);
        layoutVisualState->SetBorderThickness(UIDefaults::DefaultBorderThickness);
        layoutVisualState->SetHorizontalContentAlignment(HorizontalAlignment::Stretch);
        layoutVisualState->SetVerticalContentAlignment(VerticalAlignment::Top);

        layoutVisualStateGroup = new LayoutVisualStateGroup("Card");
        layoutVisualStateGroup->AddState(layoutVisualState);

        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "Normal");
        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "MidiLearn");
        Default.AddLayoutVisualStateGroup(layoutVisualStateGroup);

        //******************************************************************************
        // HSVColorPicker
        //******************************************************************************

        layoutVisualState = new LayoutVisualState("Disabled");
        layoutVisualState->SetElevation(1);
        layoutVisualState->SetBorderThickness(UIDefaults::DefaultBorderThickness);
        layoutVisualState->SetVerticalAlignment(VerticalAlignment::Top);
        layoutVisualState->SetMaxHeight(300);

        layoutVisualStateGroup = new LayoutVisualStateGroup("HSVColorPicker");
        layoutVisualStateGroup->AddState(layoutVisualState);

        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "Normal");
        Default.AddLayoutVisualStateGroup(layoutVisualStateGroup);

        //******************************************************************************
        // ComboBox
        //******************************************************************************

        layoutVisualState = new LayoutVisualState("Disabled");
        layoutVisualState->SetElevation(0);
        layoutVisualState->SetMinWidth(UIDefaults::ButtonMinWidth);
        layoutVisualState->SetMaxHeight(UIDefaults::TextBoxHeight);
        layoutVisualState->SetBorderThickness(UIDefaults::DefaultBorderThickness);

        layoutVisualStateGroup = new LayoutVisualStateGroup("ComboBox");
        layoutVisualStateGroup->AddState(layoutVisualState);

        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "Normal");
        Default.AddLayoutVisualStateGroup(layoutVisualStateGroup);

        //******************************************************************************
        // ComboBoxButton
        //******************************************************************************

        layoutVisualState = new LayoutVisualState("Disabled");
        layoutVisualState->SetElevation(0);
        layoutVisualState->SetCornerRadius(UIDefaults::CornerRadius);
        layoutVisualState->SetFontSize(UIDefaults::ButtonFontSize);
        layoutVisualState->SetHorizontalContentAlignment(HorizontalAlignment::Center);
        layoutVisualState->SetVerticalContentAlignment(VerticalAlignment::Center);

        layoutVisualStateGroup = new LayoutVisualStateGroup("ComboBoxButton");
        layoutVisualStateGroup->AddState(layoutVisualState);

        CloneLayoutForAllStates(layoutVisualStateGroup, layoutVisualState);
        Default.AddLayoutVisualStateGroup(layoutVisualStateGroup);

        //******************************************************************************
        // Container
        //******************************************************************************

        layoutVisualState = new LayoutVisualState("Disabled");
        layoutVisualState->SetElevation(0);
        layoutVisualState->SetBorderThickness(UIDefaults::DefaultBorderThickness);
        layoutVisualState->SetPadding(UIDefaults::SmallContainerPaddingTop);
        layoutVisualState->SetHorizontalContentAlignment(HorizontalAlignment::Stretch);
        layoutVisualState->SetVerticalContentAlignment(VerticalAlignment::Stretch);

        layoutVisualStateGroup = new LayoutVisualStateGroup("Container");
        layoutVisualStateGroup->AddState(layoutVisualState);

        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "Normal");
        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "MidiLearn");
        Default.AddLayoutVisualStateGroup(layoutVisualStateGroup);

        //******************************************************************************
        // ContextMenuItem
        //******************************************************************************

        layoutVisualState = new LayoutVisualState("Disabled");
        layoutVisualState->SetHeight(UIDefaults::TextBoxHeight);
        layoutVisualState->SetPadding(UIDefaults::TextBoxPaddingLeft, 0, UIDefaults::TextBoxPaddingRight, 0);
        layoutVisualState->SetVerticalContentAlignment(VerticalAlignment::Center);

        layoutVisualStateGroup = new LayoutVisualStateGroup("ContextMenuItem");
        layoutVisualStateGroup->AddState(layoutVisualState);

        CloneLayoutForAllStates(layoutVisualStateGroup, layoutVisualState);
        Default.AddLayoutVisualStateGroup(layoutVisualStateGroup);

        //******************************************************************************
        // FloatingActionButton
        //******************************************************************************

        layoutVisualState = new LayoutVisualState("Disabled");
        layoutVisualState->SetElevation(0);
        layoutVisualState->SetBorderThickness(0);
        layoutVisualState->SetWidth(UIDefaults::FloatingActionButtonSize);
        layoutVisualState->SetHeight(UIDefaults::FloatingActionButtonSize);
        layoutVisualState->SetHorizontalContentAlignment(HorizontalAlignment::Center);
        layoutVisualState->SetVerticalContentAlignment(VerticalAlignment::Center);

        layoutVisualStateGroup = new LayoutVisualStateGroup("FloatingActionButton");
        layoutVisualStateGroup->AddState(layoutVisualState);

        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "Normal");
        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "Pressed");
        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "Hovered");
        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "Focused");
        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "MidiLearn");
        Default.AddLayoutVisualStateGroup(layoutVisualStateGroup);

        //******************************************************************************
        // Header
        //******************************************************************************

        layoutVisualState = new LayoutVisualState("Disabled");
        layoutVisualState->SetElevation(0);
        layoutVisualState->SetBorderThickness(0, 0, 0, 5);
        layoutVisualState->SetHeight(UIDefaults::TextBoxHeight);
        layoutVisualState->SetPadding(UIDefaults::TextBoxPaddingLeft, 0, UIDefaults::TextBoxPaddingRight, 0);
        layoutVisualState->SetFontSize(UIDefaults::HeaderFontSize);

        layoutVisualStateGroup = new LayoutVisualStateGroup("Header");
        layoutVisualStateGroup->AddState(layoutVisualState);

        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "Normal");
        Default.AddLayoutVisualStateGroup(layoutVisualStateGroup);

        //******************************************************************************
        // HeaderButton
        //******************************************************************************

        layoutVisualState = new LayoutVisualState("Disabled");
        layoutVisualState->SetElevation(0);
        layoutVisualState->SetBorderThickness(0, 0, 0, 5);
        layoutVisualState->SetHeight(UIDefaults::ButtonHeight * 2);
        layoutVisualState->SetPadding(UIDefaults::ButtonPaddingLeftRight, 0, UIDefaults::ButtonPaddingLeftRight, 0);
        layoutVisualState->SetHorizontalContentAlignment(HorizontalAlignment::Stretch);
        layoutVisualState->SetVerticalContentAlignment(VerticalAlignment::Center);

        layoutVisualStateGroup = new LayoutVisualStateGroup("HeaderButton");
        layoutVisualStateGroup->AddState(layoutVisualState);

        CloneLayoutForAllStates(layoutVisualStateGroup, layoutVisualState);
        Default.AddLayoutVisualStateGroup(layoutVisualStateGroup);

        //******************************************************************************
        // Expander
        //******************************************************************************

        layoutVisualState = new LayoutVisualState("Disabled");
        layoutVisualState->SetElevation(0);
        layoutVisualState->SetBorderThickness(1);
        layoutVisualState->SetPadding(UIDefaults::ButtonPaddingLeftRight);
        layoutVisualState->SetVerticalAlignment(VerticalAlignment::Top);
        layoutVisualState->SetVerticalContentAlignment(VerticalAlignment::Top);

        layoutVisualStateGroup = new LayoutVisualStateGroup("Expander");
        layoutVisualStateGroup->AddState(layoutVisualState);

        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "Normal");
        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "Active");
        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "ActiveHovered");
        Default.AddLayoutVisualStateGroup(layoutVisualStateGroup);

        //******************************************************************************
        // HeaderText
        //******************************************************************************

        layoutVisualState = new LayoutVisualState("Disabled");
        layoutVisualState->SetElevation(0);
        layoutVisualState->SetBorderThickness(0);
        layoutVisualState->SetFontSize(UIDefaults::HeaderFontSize);
        layoutVisualState->SetVerticalAlignment(VerticalAlignment::Center);

        layoutVisualStateGroup = new LayoutVisualStateGroup("HeaderText");
        layoutVisualStateGroup->AddState(layoutVisualState);

        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "Normal");
        Default.AddLayoutVisualStateGroup(layoutVisualStateGroup);

        //******************************************************************************
        // HScrollBar
        //******************************************************************************

        layoutVisualState = new LayoutVisualState("Disabled");
        layoutVisualState->SetWidth(-1);
        layoutVisualState->SetHeight(UIDefaults::ProgressBarMinHeight);
        layoutVisualState->SetHorizontalAlignment(HorizontalAlignment::Stretch);
        layoutVisualState->SetVerticalAlignment(VerticalAlignment::Bottom);
        layoutVisualState->SetBorderThickness(UIDefaults::DefaultBorderThickness);

        layoutVisualStateGroup = new LayoutVisualStateGroup("HScrollBar");
        layoutVisualStateGroup->AddState(layoutVisualState);

        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "Normal");
        Default.AddLayoutVisualStateGroup(layoutVisualStateGroup);

        //******************************************************************************
        // IconButton
        //******************************************************************************

        layoutVisualState = new LayoutVisualState("Disabled");
        layoutVisualState->SetElevation(0);
        layoutVisualState->SetBorderThickness(UIDefaults::DefaultBorderThickness);
        layoutVisualState->SetWidth(UIDefaults::ToggleButtonHeight);
        layoutVisualState->SetHeight(UIDefaults::ToggleButtonHeight);
        layoutVisualState->SetPadding(
            UIDefaults::ToggleButtonPaddingLeftRight,
            UIDefaults::ToggleButtonPaddingTopBottom,
            UIDefaults::ToggleButtonPaddingLeftRight,
            UIDefaults::ToggleButtonPaddingTopBottom);
        layoutVisualState->SetHorizontalContentAlignment(HorizontalAlignment::Stretch);
        layoutVisualState->SetVerticalContentAlignment(VerticalAlignment::Stretch);
        layoutVisualStateGroup = new LayoutVisualStateGroup("IconButton");
        layoutVisualStateGroup->AddState(layoutVisualState);

        CloneLayoutForAllStates(layoutVisualStateGroup, layoutVisualState);
        Default.AddLayoutVisualStateGroup(layoutVisualStateGroup);

        //******************************************************************************
        // LabelCentered
        //******************************************************************************

        layoutVisualState = new LayoutVisualState("Disabled");
        layoutVisualState->SetHorizontalAlignment(HorizontalAlignment::Center);
        layoutVisualState->SetVerticalAlignment(VerticalAlignment::Center);

        layoutVisualStateGroup = new LayoutVisualStateGroup("LabelCentered");
        layoutVisualStateGroup->AddState(layoutVisualState);

        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "Normal");
        Default.AddLayoutVisualStateGroup(layoutVisualStateGroup);

        //******************************************************************************
        // List
        //******************************************************************************

        layoutVisualState = new LayoutVisualState("Disabled");
        layoutVisualState->SetBorderThickness(UIDefaults::DefaultBorderThickness);
        layoutVisualState->SetPadding(UIDefaults::MinimumColumnSpacing);
        // TODO added this to the ListView
        layoutVisualState->SetVerticalAlignment(VerticalAlignment::Stretch);
        layoutVisualStateGroup = new LayoutVisualStateGroup("List");
        layoutVisualStateGroup->AddState(layoutVisualState);

        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "Normal");
        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "Hovered");
        Default.AddLayoutVisualStateGroup(layoutVisualStateGroup);

        //******************************************************************************
        // ListItem
        //******************************************************************************

        layoutVisualState = new LayoutVisualState("Disabled");
        layoutVisualState->SetHeight(UIDefaults::TextBoxHeight);
        layoutVisualState->SetPadding(UIDefaults::TextBoxPaddingLeft, 0, UIDefaults::TextBoxPaddingRight, 0);
        layoutVisualState->SetBorderThickness(1);
        layoutVisualState->SetHorizontalContentAlignment(HorizontalAlignment::Center);
        layoutVisualState->SetVerticalContentAlignment(VerticalAlignment::Center);

        layoutVisualStateGroup = new LayoutVisualStateGroup("ListItem");
        layoutVisualStateGroup->AddState(layoutVisualState);

        CloneLayoutForAllStates(layoutVisualStateGroup, layoutVisualState);
        Default.AddLayoutVisualStateGroup(layoutVisualStateGroup);

        //******************************************************************************
        // ImageListItem
        //******************************************************************************

        layoutVisualState = new LayoutVisualState("Disabled");
        layoutVisualState->SetHeight(UIDefaults::TextBoxHeight * 4);
        layoutVisualState->SetPadding(UIDefaults::TextBoxPaddingLeft, 0, UIDefaults::TextBoxPaddingRight, 0);
        layoutVisualState->SetBorderThickness(1);
        layoutVisualState->SetHorizontalContentAlignment(HorizontalAlignment::Center);
        layoutVisualState->SetVerticalContentAlignment(VerticalAlignment::Center);

        layoutVisualStateGroup = new LayoutVisualStateGroup("ImageListItem");
        layoutVisualStateGroup->AddState(layoutVisualState);

        CloneLayoutForAllStates(layoutVisualStateGroup, layoutVisualState);
        Default.AddLayoutVisualStateGroup(layoutVisualStateGroup);

        //******************************************************************************
        // MainMenu
        //******************************************************************************

        layoutVisualState = new LayoutVisualState("Disabled");
        layoutVisualState->SetElevation(8);
        layoutVisualState->SetBorderThickness(0, 0, 0, UIDefaults::DefaultBorderThickness);
        layoutVisualState->SetHorizontalContentAlignment(HorizontalAlignment::Center);

        layoutVisualStateGroup = new LayoutVisualStateGroup("MainMenu");
        layoutVisualStateGroup->AddState(layoutVisualState);

        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "Normal");
        Default.AddLayoutVisualStateGroup(layoutVisualStateGroup);

        //******************************************************************************
        // MainMenuButton
        //******************************************************************************

        layoutVisualState = new LayoutVisualState("Disabled");
        layoutVisualState->SetElevation(0);
        layoutVisualState->SetMinWidth(UIDefaults::MenuButtonMinWidth);
        layoutVisualState->SetMinHeight(UIDefaults::DefaultItemHeight);
        layoutVisualState->SetMaxWidth(UIDefaults::MenuButtonMinWidth);
        layoutVisualState->SetMaxHeight(UIDefaults::MenuButtonVerticalHeight);
        layoutVisualState->SetPadding(16, 9, 16, 9);
        layoutVisualState->SetBorderThickness(0, 0, 0, 5);
        layoutVisualState->SetHorizontalContentAlignment(HorizontalAlignment::Center);
        layoutVisualState->SetVerticalContentAlignment(VerticalAlignment::Center);
        layoutVisualState->SetFontSize(UIDefaults::ButtonFontSize);

        layoutVisualStateGroup = new LayoutVisualStateGroup("MainMenuButton");
        layoutVisualStateGroup->AddState(layoutVisualState);

        CloneLayoutForAllStates(layoutVisualStateGroup, layoutVisualState);
        Default.AddLayoutVisualStateGroup(layoutVisualStateGroup);

        //******************************************************************************
        // Page
        //******************************************************************************

        layoutVisualState = new LayoutVisualState("Disabled");
        layoutVisualState->SetElevation(1);
        layoutVisualState->SetBorderThickness(UIDefaults::DefaultBorderThickness);
        layoutVisualState->SetPadding(UIDefaults::ContainerPadding);

        layoutVisualStateGroup = new LayoutVisualStateGroup("Page");
        layoutVisualStateGroup->AddState(layoutVisualState);

        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "Normal");
        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "MidiLearn");
        Default.AddLayoutVisualStateGroup(layoutVisualStateGroup);

        //******************************************************************************
        // LoginPage
        //******************************************************************************

        layoutVisualState = new LayoutVisualState("Disabled");
        layoutVisualState->SetElevation(1);
        layoutVisualState->SetBorderThickness(UIDefaults::DefaultBorderThickness);
        layoutVisualState->SetPadding(UIDefaults::ContainerPadding);
        layoutVisualState->SetMaxWidth(800);
        layoutVisualState->SetHorizontalAlignment(HorizontalAlignment::Center);
        layoutVisualState->SetVerticalAlignment(VerticalAlignment::Center);

        layoutVisualStateGroup = new LayoutVisualStateGroup("LoginPage");
        layoutVisualStateGroup->AddState(layoutVisualState);

        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "Normal");
        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "MidiLearn");
        Default.AddLayoutVisualStateGroup(layoutVisualStateGroup);

        //******************************************************************************
        // ProgressBar
        //******************************************************************************

        layoutVisualState = new LayoutVisualState("Disabled");
        layoutVisualState->SetHeight(UIDefaults::ProgressBarMinHeight);
        layoutVisualState->SetBorderThickness(UIDefaults::DefaultBorderThickness);

        layoutVisualStateGroup = new LayoutVisualStateGroup("ProgressBar");
        layoutVisualStateGroup->AddState(layoutVisualState);

        CloneLayoutForAllStates(layoutVisualStateGroup, layoutVisualState);
        Default.AddLayoutVisualStateGroup(layoutVisualStateGroup);

        //******************************************************************************
        // TextBox
        //******************************************************************************

        layoutVisualState = new LayoutVisualState("Disabled");
        layoutVisualState->SetMaxHeight(UIDefaults::TextBoxHeight);
        layoutVisualState->SetBorderThickness(UIDefaults::DefaultBorderThickness);
        layoutVisualState->SetVerticalContentAlignment(VerticalAlignment::Center);

        layoutVisualStateGroup = new LayoutVisualStateGroup("TextBox");
        layoutVisualStateGroup->AddState(layoutVisualState);

        // TODO this could be a reason why the layout changes. The TextBox only has these states. What happens if a different state is used?
        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "Normal");
        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "Hovered");
        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "Focused");
        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "Error");

        Default.AddLayoutVisualStateGroup(layoutVisualStateGroup);

        //******************************************************************************
        // MultiLineTextBox
        //******************************************************************************

        layoutVisualState = new LayoutVisualState("Disabled");
        layoutVisualState->SetBorderThickness(1);
        layoutVisualState->SetPadding(UIDefaults::TextBoxPaddingLeft, 0, UIDefaults::TextBoxPaddingRight, 0);
        layoutVisualState->SetVerticalContentAlignment(VerticalAlignment::Top);

        layoutVisualStateGroup = new LayoutVisualStateGroup("MultiLineTextBox");
        layoutVisualStateGroup->AddState(layoutVisualState);

        // TODO this could be a reason why the layout changes. The TextBox only has these states. What happens if a different state is used?
        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "Normal");
        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "Hovered");
        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "Focused");
        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "Error");

        Default.AddLayoutVisualStateGroup(layoutVisualStateGroup);

        //******************************************************************************
        // CenteredTextBox
        //******************************************************************************

        layoutVisualState = new LayoutVisualState("Disabled");
        layoutVisualState->SetHeight(UIDefaults::TextBoxHeight);
        layoutVisualState->SetBorderThickness(UIDefaults::DefaultBorderThickness);
        layoutVisualState->SetPadding(UIDefaults::TextBoxPaddingLeft, 0, UIDefaults::TextBoxPaddingRight, 0);
        layoutVisualState->SetHorizontalContentAlignment(HorizontalAlignment::Center);

        layoutVisualStateGroup = new LayoutVisualStateGroup("CenteredTextBox");
        layoutVisualStateGroup->AddState(layoutVisualState);

        // TODO this could be a reason why the layout changes. The TextBox only has these states. What happens if a different state is used?
        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "Normal");
        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "Hovered");
        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "Focused");
        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "Error");

        Default.AddLayoutVisualStateGroup(layoutVisualStateGroup);

        //******************************************************************************
        // ToggleButton
        //******************************************************************************

        layoutVisualState = new LayoutVisualState("Disabled");
        layoutVisualState->SetElevation(0);
        layoutVisualState->SetBorderThickness(UIDefaults::DefaultBorderThickness);
        layoutVisualState->SetMaxWidth(UIDefaults::ToggleButtonHeight);
        layoutVisualState->SetMaxHeight(UIDefaults::ToggleButtonHeight);
        layoutVisualState->SetPadding(
            UIDefaults::ToggleButtonPaddingLeftRight,
            UIDefaults::ToggleButtonPaddingTopBottom,
            UIDefaults::ToggleButtonPaddingLeftRight,
            UIDefaults::ToggleButtonPaddingTopBottom);

        layoutVisualStateGroup = new LayoutVisualStateGroup("ToggleButton");
        layoutVisualStateGroup->AddState(layoutVisualState);

        CloneLayoutForAllStates(layoutVisualStateGroup, layoutVisualState);
        Default.AddLayoutVisualStateGroup(layoutVisualStateGroup);

        //******************************************************************************
        // SearchBar
        //******************************************************************************

        layoutVisualState = new LayoutVisualState("Disabled");
        layoutVisualState->SetMaxHeight(UIDefaults::TextBoxHeight);
        layoutVisualState->SetVerticalContentAlignment(VerticalAlignment::Center);

        layoutVisualStateGroup = new LayoutVisualStateGroup("SearchBar");
        layoutVisualStateGroup->AddState(layoutVisualState);

        // TODO this could be a reason why the layout changes. The TextBox only has these states. What happens if a different state is used?
        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "Normal");
        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "Hovered");
        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "Focused");
        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "Error");

        Default.AddLayoutVisualStateGroup(layoutVisualStateGroup);

        //******************************************************************************
        // Switch
        //******************************************************************************

        layoutVisualState = new LayoutVisualState("Disabled");
        layoutVisualState->SetMinHeight(UIDefaults::ToggleButtonHeight);
        layoutVisualState->SetMaxHeight(UIDefaults::ToggleButtonHeight << 1);
        layoutVisualState->SetVerticalAlignment(VerticalAlignment::Top);
        layoutVisualState->SetVerticalContentAlignment(VerticalAlignment::Center);
        layoutVisualState->SetPadding(UIDefaults::TextBoxPaddingLeft);
        layoutVisualStateGroup = new LayoutVisualStateGroup("Switch");
        layoutVisualStateGroup->AddState(layoutVisualState);

        CloneLayoutForAllStates(layoutVisualStateGroup, layoutVisualState);
        Default.AddLayoutVisualStateGroup(layoutVisualStateGroup);

        //******************************************************************************
        // SwitchCentered
        //******************************************************************************

        layoutVisualState = new LayoutVisualState("Disabled");
        layoutVisualState->SetHeight(UIDefaults::ToggleButtonHeight);
        layoutVisualState->SetHorizontalAlignment(HorizontalAlignment::Center);

        layoutVisualStateGroup = new LayoutVisualStateGroup("SwitchCentered");
        layoutVisualStateGroup->AddState(layoutVisualState);

        CloneLayoutForAllStates(layoutVisualStateGroup, layoutVisualState);
        Default.AddLayoutVisualStateGroup(layoutVisualStateGroup);

        //******************************************************************************
        // VScrollBar
        //******************************************************************************

        layoutVisualState = new LayoutVisualState("Disabled");
        layoutVisualState->SetWidth(UIDefaults::ProgressBarMinHeight);
        layoutVisualState->SetHeight(-1);
        layoutVisualState->SetHorizontalAlignment(HorizontalAlignment::Right);
        // layoutVisualState->SetBorderThickness(UIDefaults::DefaultBorderThickness);

        layoutVisualStateGroup = new LayoutVisualStateGroup("VScrollBar");
        layoutVisualStateGroup->AddState(layoutVisualState);

        CloneLayoutForState(layoutVisualStateGroup, layoutVisualState, "Normal");
        Default.AddLayoutVisualStateGroup(layoutVisualStateGroup);

        //******************************************************************************
        // ToolTip
        //******************************************************************************

        layoutVisualState = new LayoutVisualState("Normal");

        layoutVisualState->SetHorizontalAlignment(HorizontalAlignment::Left);
        layoutVisualState->SetVerticalAlignment(VerticalAlignment::Top);
        layoutVisualState->SetHorizontalContentAlignment(HorizontalAlignment::Left);
        layoutVisualState->SetVerticalContentAlignment(VerticalAlignment::Top);
        layoutVisualState->SetPadding(UIDefaults::ContainerPadding);
        layoutVisualState->SetCornerRadius(UIDefaults::BigCornerRadius);
        layoutVisualState->SetBorderThickness(UIDefaults::DefaultBorderThickness);

        layoutVisualStateGroup = new LayoutVisualStateGroup("ToolTip");
        layoutVisualStateGroup->AddState(layoutVisualState);

        Default.AddLayoutVisualStateGroup(layoutVisualStateGroup);
    }

} // namespace xit::Drawing