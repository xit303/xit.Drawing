#include <Drawing/Theme/ThemeManager.h>
#include <memory>

namespace xit::Drawing
{
    // Helper function to create and add a layout visual state
    template<typename... Args>
    LayoutVisualState* CreateLayoutState(LayoutVisualStateGroup* group, Args&&... args)
    {
        auto state = std::make_unique<LayoutVisualState>(std::forward<Args>(args)...);
        LayoutVisualState* statePtr = state.get();
        group->AddState(state.release()); // Transfer ownership to the group
        return statePtr;
    }

    // Helper function to create a layout visual state group
    std::unique_ptr<LayoutVisualStateGroup> CreateLayoutGroup(const std::string& name)
    {
        return std::make_unique<LayoutVisualStateGroup>(name);
    }

    LayoutVisualState *ThemeManager::CloneLayoutForState(LayoutVisualStateGroup *layoutVisualStateGroup, LayoutVisualState *layoutVisualState, const std::string &newStateName)
    {
        return CreateLayoutState(layoutVisualStateGroup, newStateName, *layoutVisualState);
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
        LayoutVisualState *layoutVisualState;

        //******************************************************************************
        // Button
        //******************************************************************************

        auto layoutVisualStateGroup = CreateLayoutGroup("Button");
        layoutVisualState = CreateLayoutState(layoutVisualStateGroup.get(), "Disabled");
        layoutVisualState->SetElevation(0);
        layoutVisualState->SetBorderThickness(UIDefaults::DefaultBorderThickness);
        layoutVisualState->SetCornerRadius(UIDefaults::CornerRadius);
        layoutVisualState->SetMinWidth(UIDefaults::ButtonMinWidth);
        layoutVisualState->SetHeight(UIDefaults::ButtonHeight);
        layoutVisualState->SetPadding(UIDefaults::ButtonPaddingLeftRight, 0, UIDefaults::ButtonPaddingLeftRight, 0);
        layoutVisualState->SetHorizontalContentAlignment(HorizontalAlignment::Center);
        layoutVisualState->SetVerticalContentAlignment(VerticalAlignment::Center);
        layoutVisualState->SetFontSize(UIDefaults::ButtonFontSize);

        CloneLayoutForAllStates(layoutVisualStateGroup.get(), layoutVisualState);
        Default.AddLayoutVisualStateGroup(layoutVisualStateGroup.release());

        //******************************************************************************
        // ButtonInContainer
        //******************************************************************************

        auto buttonInContainerGroup = CreateLayoutGroup("ButtonInContainer");
        layoutVisualState = CreateLayoutState(buttonInContainerGroup.get(), "Disabled");
        layoutVisualState->SetElevation(0);
        layoutVisualState->SetBorderThickness(UIDefaults::DefaultBorderThickness, 0, 0, 0);
        layoutVisualState->SetMargin(0);
        layoutVisualState->SetWidth(UIDefaults::ToggleButtonHeight);
        layoutVisualState->SetHorizontalAlignment(HorizontalAlignment::Right);
        layoutVisualState->SetHorizontalContentAlignment(HorizontalAlignment::Center);
        layoutVisualState->SetVerticalContentAlignment(VerticalAlignment::Center);

        CloneLayoutForAllStates(buttonInContainerGroup.get(), layoutVisualState);
        Default.AddLayoutVisualStateGroup(buttonInContainerGroup.release());

        //******************************************************************************
        // Card
        //******************************************************************************

        auto cardGroup = CreateLayoutGroup("Card");
        layoutVisualState = CreateLayoutState(cardGroup.get(), "Disabled");
        layoutVisualState->SetElevation(1);
        layoutVisualState->SetBorderThickness(UIDefaults::DefaultBorderThickness);
        layoutVisualState->SetHorizontalContentAlignment(HorizontalAlignment::Stretch);
        layoutVisualState->SetVerticalContentAlignment(VerticalAlignment::Top);

        CloneLayoutForState(cardGroup.get(), layoutVisualState, "Normal");
        CloneLayoutForState(cardGroup.get(), layoutVisualState, "MidiLearn");
        Default.AddLayoutVisualStateGroup(cardGroup.release());

        //******************************************************************************
        // HSVColorPicker
        //******************************************************************************

        auto hsvColorPickerGroup = CreateLayoutGroup("HSVColorPicker");
        layoutVisualState = CreateLayoutState(hsvColorPickerGroup.get(), "Disabled");
        layoutVisualState->SetElevation(1);
        layoutVisualState->SetBorderThickness(UIDefaults::DefaultBorderThickness);
        layoutVisualState->SetVerticalAlignment(VerticalAlignment::Top);
        layoutVisualState->SetMaxHeight(300);

        CloneLayoutForState(hsvColorPickerGroup.get(), layoutVisualState, "Normal");
        Default.AddLayoutVisualStateGroup(hsvColorPickerGroup.release());

        //******************************************************************************
        // ComboBox
        //******************************************************************************

        auto comboBoxGroup = CreateLayoutGroup("ComboBox");
        layoutVisualState = CreateLayoutState(comboBoxGroup.get(), "Disabled");
        layoutVisualState->SetElevation(0);
        layoutVisualState->SetMinWidth(UIDefaults::ButtonMinWidth);
        layoutVisualState->SetMaxHeight(UIDefaults::TextBoxHeight);
        layoutVisualState->SetBorderThickness(UIDefaults::DefaultBorderThickness);

        CloneLayoutForState(comboBoxGroup.get(), layoutVisualState, "Normal");
        Default.AddLayoutVisualStateGroup(comboBoxGroup.release());

        //******************************************************************************
        // ComboBoxButton
        //******************************************************************************

        auto comboBoxButtonGroup = CreateLayoutGroup("ComboBoxButton");
        layoutVisualState = CreateLayoutState(comboBoxButtonGroup.get(), "Disabled");
        layoutVisualState->SetElevation(0);
        layoutVisualState->SetCornerRadius(UIDefaults::CornerRadius);
        layoutVisualState->SetFontSize(UIDefaults::ButtonFontSize);
        layoutVisualState->SetHorizontalContentAlignment(HorizontalAlignment::Center);
        layoutVisualState->SetVerticalContentAlignment(VerticalAlignment::Center);

        CloneLayoutForAllStates(comboBoxButtonGroup.get(), layoutVisualState);
        Default.AddLayoutVisualStateGroup(comboBoxButtonGroup.release());

        //******************************************************************************
        // Container
        //******************************************************************************

        auto containerGroup = CreateLayoutGroup("Container");
        layoutVisualState = CreateLayoutState(containerGroup.get(), "Disabled");
        layoutVisualState->SetElevation(0);
        layoutVisualState->SetBorderThickness(UIDefaults::DefaultBorderThickness);
        layoutVisualState->SetPadding(UIDefaults::SmallContainerPaddingTop);
        layoutVisualState->SetHorizontalContentAlignment(HorizontalAlignment::Stretch);
        layoutVisualState->SetVerticalContentAlignment(VerticalAlignment::Stretch);

        CloneLayoutForState(containerGroup.get(), layoutVisualState, "Normal");
        CloneLayoutForState(containerGroup.get(), layoutVisualState, "MidiLearn");
        Default.AddLayoutVisualStateGroup(containerGroup.release());

        //******************************************************************************
        // ContextMenuItem
        //******************************************************************************

        auto contextMenuItemGroup = CreateLayoutGroup("ContextMenuItem");
        layoutVisualState = CreateLayoutState(contextMenuItemGroup.get(), "Disabled");
        layoutVisualState->SetHeight(UIDefaults::TextBoxHeight);
        layoutVisualState->SetPadding(UIDefaults::TextBoxPaddingLeft, 0, UIDefaults::TextBoxPaddingRight, 0);
        layoutVisualState->SetVerticalContentAlignment(VerticalAlignment::Center);

        CloneLayoutForAllStates(contextMenuItemGroup.get(), layoutVisualState);
        Default.AddLayoutVisualStateGroup(contextMenuItemGroup.release());

        //******************************************************************************
        // FloatingActionButton
        //******************************************************************************

        auto floatingActionButtonGroup = CreateLayoutGroup("FloatingActionButton");
        layoutVisualState = CreateLayoutState(floatingActionButtonGroup.get(), "Disabled");
        layoutVisualState->SetElevation(0);
        layoutVisualState->SetBorderThickness(0);
        layoutVisualState->SetWidth(UIDefaults::FloatingActionButtonSize);
        layoutVisualState->SetHeight(UIDefaults::FloatingActionButtonSize);
        layoutVisualState->SetHorizontalContentAlignment(HorizontalAlignment::Center);
        layoutVisualState->SetVerticalContentAlignment(VerticalAlignment::Center);

        CloneLayoutForState(floatingActionButtonGroup.get(), layoutVisualState, "Normal");
        CloneLayoutForState(floatingActionButtonGroup.get(), layoutVisualState, "Pressed");
        CloneLayoutForState(floatingActionButtonGroup.get(), layoutVisualState, "Hovered");
        CloneLayoutForState(floatingActionButtonGroup.get(), layoutVisualState, "Focused");
        CloneLayoutForState(floatingActionButtonGroup.get(), layoutVisualState, "MidiLearn");
        Default.AddLayoutVisualStateGroup(floatingActionButtonGroup.release());

        //******************************************************************************
        // Header
        //******************************************************************************

        auto headerGroup = CreateLayoutGroup("Header");
        layoutVisualState = CreateLayoutState(headerGroup.get(), "Disabled");
        layoutVisualState->SetElevation(0);
        layoutVisualState->SetBorderThickness(0, 0, 0, 5);
        layoutVisualState->SetHeight(UIDefaults::TextBoxHeight);
        layoutVisualState->SetPadding(UIDefaults::TextBoxPaddingLeft, 0, UIDefaults::TextBoxPaddingRight, 0);
        layoutVisualState->SetFontSize(UIDefaults::HeaderFontSize);

        CloneLayoutForState(headerGroup.get(), layoutVisualState, "Normal");
        Default.AddLayoutVisualStateGroup(headerGroup.release());

        //******************************************************************************
        // HeaderButton
        //******************************************************************************

        auto headerButtonGroup = CreateLayoutGroup("HeaderButton");
        layoutVisualState = CreateLayoutState(headerButtonGroup.get(), "Disabled");
        layoutVisualState->SetElevation(0);
        layoutVisualState->SetBorderThickness(0, 0, 0, 5);
        layoutVisualState->SetHeight(UIDefaults::ButtonHeight * 2);
        layoutVisualState->SetPadding(UIDefaults::ButtonPaddingLeftRight, 0, UIDefaults::ButtonPaddingLeftRight, 0);
        layoutVisualState->SetHorizontalContentAlignment(HorizontalAlignment::Stretch);
        layoutVisualState->SetVerticalContentAlignment(VerticalAlignment::Center);

        CloneLayoutForAllStates(headerButtonGroup.get(), layoutVisualState);
        Default.AddLayoutVisualStateGroup(headerButtonGroup.release());

        //******************************************************************************
        // Expander
        //******************************************************************************

        auto expanderGroup = CreateLayoutGroup("Expander");
        layoutVisualState = CreateLayoutState(expanderGroup.get(), "Disabled");
        layoutVisualState->SetElevation(0);
        layoutVisualState->SetBorderThickness(1);
        layoutVisualState->SetPadding(UIDefaults::ButtonPaddingLeftRight);
        layoutVisualState->SetVerticalAlignment(VerticalAlignment::Top);
        layoutVisualState->SetVerticalContentAlignment(VerticalAlignment::Top);

        CloneLayoutForState(expanderGroup.get(), layoutVisualState, "Normal");
        CloneLayoutForState(expanderGroup.get(), layoutVisualState, "Active");
        CloneLayoutForState(expanderGroup.get(), layoutVisualState, "ActiveHovered");
        Default.AddLayoutVisualStateGroup(expanderGroup.release());

        //******************************************************************************
        // HeaderText
        //******************************************************************************

        auto headerTextGroup = CreateLayoutGroup("HeaderText");
        layoutVisualState = CreateLayoutState(headerTextGroup.get(), "Disabled");
        layoutVisualState->SetElevation(0);
        layoutVisualState->SetBorderThickness(0);
        layoutVisualState->SetFontSize(UIDefaults::HeaderFontSize);
        layoutVisualState->SetVerticalAlignment(VerticalAlignment::Center);

        CloneLayoutForState(headerTextGroup.get(), layoutVisualState, "Normal");
        Default.AddLayoutVisualStateGroup(headerTextGroup.release());

        //******************************************************************************
        // HScrollBar
        //******************************************************************************

        auto hScrollBarGroup = CreateLayoutGroup("HScrollBar");
        layoutVisualState = CreateLayoutState(hScrollBarGroup.get(), "Disabled");
        layoutVisualState->SetWidth(-1);
        layoutVisualState->SetHeight(UIDefaults::ProgressBarMinHeight);
        layoutVisualState->SetHorizontalAlignment(HorizontalAlignment::Stretch);
        layoutVisualState->SetVerticalAlignment(VerticalAlignment::Bottom);
        layoutVisualState->SetBorderThickness(UIDefaults::DefaultBorderThickness);

        CloneLayoutForState(hScrollBarGroup.get(), layoutVisualState, "Normal");
        Default.AddLayoutVisualStateGroup(hScrollBarGroup.release());

        //******************************************************************************
        // IconButton
        //******************************************************************************

        auto iconButtonGroup = CreateLayoutGroup("IconButton");
        layoutVisualState = CreateLayoutState(iconButtonGroup.get(), "Disabled");
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

        CloneLayoutForAllStates(iconButtonGroup.get(), layoutVisualState);
        Default.AddLayoutVisualStateGroup(iconButtonGroup.release());

        //******************************************************************************
        // LabelCentered
        //******************************************************************************

        auto labelCenteredGroup = CreateLayoutGroup("LabelCentered");
        layoutVisualState = CreateLayoutState(labelCenteredGroup.get(), "Disabled");
        layoutVisualState->SetHorizontalAlignment(HorizontalAlignment::Center);
        layoutVisualState->SetVerticalAlignment(VerticalAlignment::Center);

        CloneLayoutForState(labelCenteredGroup.get(), layoutVisualState, "Normal");
        Default.AddLayoutVisualStateGroup(labelCenteredGroup.release());

        //******************************************************************************
        // List
        //******************************************************************************

        auto listGroup = CreateLayoutGroup("List");
        layoutVisualState = CreateLayoutState(listGroup.get(), "Disabled");
        layoutVisualState->SetBorderThickness(UIDefaults::DefaultBorderThickness);
        layoutVisualState->SetPadding(UIDefaults::MinimumColumnSpacing);
        // TODO added this to the ListView
        layoutVisualState->SetVerticalAlignment(VerticalAlignment::Stretch);

        CloneLayoutForState(listGroup.get(), layoutVisualState, "Normal");
        CloneLayoutForState(listGroup.get(), layoutVisualState, "Hovered");
        Default.AddLayoutVisualStateGroup(listGroup.release());

        //******************************************************************************
        // ListItem
        //******************************************************************************

        auto listItemGroup = CreateLayoutGroup("ListItem");
        layoutVisualState = CreateLayoutState(listItemGroup.get(), "Disabled");
        layoutVisualState->SetHeight(UIDefaults::TextBoxHeight);
        layoutVisualState->SetPadding(UIDefaults::TextBoxPaddingLeft, 0, UIDefaults::TextBoxPaddingRight, 0);
        layoutVisualState->SetBorderThickness(1);
        layoutVisualState->SetHorizontalContentAlignment(HorizontalAlignment::Center);
        layoutVisualState->SetVerticalContentAlignment(VerticalAlignment::Center);

        CloneLayoutForAllStates(listItemGroup.get(), layoutVisualState);
        Default.AddLayoutVisualStateGroup(listItemGroup.release());

        //******************************************************************************
        // ImageListItem
        //******************************************************************************

        auto imageListItemGroup = CreateLayoutGroup("ImageListItem");
        layoutVisualState = CreateLayoutState(imageListItemGroup.get(), "Disabled");
        layoutVisualState->SetHeight(UIDefaults::TextBoxHeight * 4);
        layoutVisualState->SetPadding(UIDefaults::TextBoxPaddingLeft, 0, UIDefaults::TextBoxPaddingRight, 0);
        layoutVisualState->SetBorderThickness(1);
        layoutVisualState->SetHorizontalContentAlignment(HorizontalAlignment::Center);
        layoutVisualState->SetVerticalContentAlignment(VerticalAlignment::Center);

        CloneLayoutForAllStates(imageListItemGroup.get(), layoutVisualState);
        Default.AddLayoutVisualStateGroup(imageListItemGroup.release());

        //******************************************************************************
        // MainMenu
        //******************************************************************************

        auto mainMenuGroup = CreateLayoutGroup("MainMenu");
        layoutVisualState = CreateLayoutState(mainMenuGroup.get(), "Disabled");
        layoutVisualState->SetElevation(8);
        layoutVisualState->SetBorderThickness(0, 0, 0, UIDefaults::DefaultBorderThickness);
        layoutVisualState->SetHorizontalContentAlignment(HorizontalAlignment::Center);

        CloneLayoutForState(mainMenuGroup.get(), layoutVisualState, "Normal");
        Default.AddLayoutVisualStateGroup(mainMenuGroup.release());

        //******************************************************************************
        // MainMenuButton
        //******************************************************************************

        auto mainMenuButtonGroup = CreateLayoutGroup("MainMenuButton");
        layoutVisualState = CreateLayoutState(mainMenuButtonGroup.get(), "Disabled");
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

        CloneLayoutForAllStates(mainMenuButtonGroup.get(), layoutVisualState);
        Default.AddLayoutVisualStateGroup(mainMenuButtonGroup.release());

        //******************************************************************************
        // Page
        //******************************************************************************

        auto pageGroup = CreateLayoutGroup("Page");
        layoutVisualState = CreateLayoutState(pageGroup.get(), "Disabled");
        layoutVisualState->SetElevation(1);
        layoutVisualState->SetBorderThickness(UIDefaults::DefaultBorderThickness);
        layoutVisualState->SetPadding(UIDefaults::ContainerPadding);

        CloneLayoutForState(pageGroup.get(), layoutVisualState, "Normal");
        CloneLayoutForState(pageGroup.get(), layoutVisualState, "MidiLearn");
        Default.AddLayoutVisualStateGroup(pageGroup.release());

        //******************************************************************************
        // LoginPage
        //******************************************************************************

        auto loginPageGroup = CreateLayoutGroup("LoginPage");
        layoutVisualState = CreateLayoutState(loginPageGroup.get(), "Disabled");
        layoutVisualState->SetElevation(1);
        layoutVisualState->SetBorderThickness(UIDefaults::DefaultBorderThickness);
        layoutVisualState->SetPadding(UIDefaults::ContainerPadding);
        layoutVisualState->SetMaxWidth(800);
        layoutVisualState->SetHorizontalAlignment(HorizontalAlignment::Center);
        layoutVisualState->SetVerticalAlignment(VerticalAlignment::Center);

        CloneLayoutForState(loginPageGroup.get(), layoutVisualState, "Normal");
        CloneLayoutForState(loginPageGroup.get(), layoutVisualState, "MidiLearn");
        Default.AddLayoutVisualStateGroup(loginPageGroup.release());

        //******************************************************************************
        // ProgressBar
        //******************************************************************************

        auto progressBarGroup = CreateLayoutGroup("ProgressBar");
        layoutVisualState = CreateLayoutState(progressBarGroup.get(), "Disabled");
        layoutVisualState->SetHeight(UIDefaults::ProgressBarMinHeight);
        layoutVisualState->SetBorderThickness(UIDefaults::DefaultBorderThickness);

        CloneLayoutForAllStates(progressBarGroup.get(), layoutVisualState);
        Default.AddLayoutVisualStateGroup(progressBarGroup.release());

        //******************************************************************************
        // TextBox
        //******************************************************************************

        auto textBoxGroup = CreateLayoutGroup("TextBox");
        layoutVisualState = CreateLayoutState(textBoxGroup.get(), "Disabled");
        layoutVisualState->SetMaxHeight(UIDefaults::TextBoxHeight);
        layoutVisualState->SetBorderThickness(UIDefaults::DefaultBorderThickness);
        layoutVisualState->SetVerticalContentAlignment(VerticalAlignment::Center);

        // TODO this could be a reason why the layout changes. The TextBox only has these states. What happens if a different state is used?
        CloneLayoutForState(textBoxGroup.get(), layoutVisualState, "Normal");
        CloneLayoutForState(textBoxGroup.get(), layoutVisualState, "Hovered");
        CloneLayoutForState(textBoxGroup.get(), layoutVisualState, "Focused");
        CloneLayoutForState(textBoxGroup.get(), layoutVisualState, "Error");

        Default.AddLayoutVisualStateGroup(textBoxGroup.release());

        //******************************************************************************
        // MultiLineTextBox
        //******************************************************************************

        auto multiLineTextBoxGroup = CreateLayoutGroup("MultiLineTextBox");
        layoutVisualState = CreateLayoutState(multiLineTextBoxGroup.get(), "Disabled");
        layoutVisualState->SetBorderThickness(1);
        layoutVisualState->SetPadding(UIDefaults::TextBoxPaddingLeft, 0, UIDefaults::TextBoxPaddingRight, 0);
        layoutVisualState->SetVerticalContentAlignment(VerticalAlignment::Top);

        // TODO this could be a reason why the layout changes. The TextBox only has these states. What happens if a different state is used?
        CloneLayoutForState(multiLineTextBoxGroup.get(), layoutVisualState, "Normal");
        CloneLayoutForState(multiLineTextBoxGroup.get(), layoutVisualState, "Hovered");
        CloneLayoutForState(multiLineTextBoxGroup.get(), layoutVisualState, "Focused");
        CloneLayoutForState(multiLineTextBoxGroup.get(), layoutVisualState, "Error");

        Default.AddLayoutVisualStateGroup(multiLineTextBoxGroup.release());

        //******************************************************************************
        // CenteredTextBox
        //******************************************************************************

        auto centeredTextBoxGroup = CreateLayoutGroup("CenteredTextBox");
        layoutVisualState = CreateLayoutState(centeredTextBoxGroup.get(), "Disabled");
        layoutVisualState->SetHeight(UIDefaults::TextBoxHeight);
        layoutVisualState->SetBorderThickness(UIDefaults::DefaultBorderThickness);
        layoutVisualState->SetPadding(UIDefaults::TextBoxPaddingLeft, 0, UIDefaults::TextBoxPaddingRight, 0);
        layoutVisualState->SetHorizontalContentAlignment(HorizontalAlignment::Center);

        // TODO this could be a reason why the layout changes. The TextBox only has these states. What happens if a different state is used?
        CloneLayoutForState(centeredTextBoxGroup.get(), layoutVisualState, "Normal");
        CloneLayoutForState(centeredTextBoxGroup.get(), layoutVisualState, "Hovered");
        CloneLayoutForState(centeredTextBoxGroup.get(), layoutVisualState, "Focused");
        CloneLayoutForState(centeredTextBoxGroup.get(), layoutVisualState, "Error");

        Default.AddLayoutVisualStateGroup(centeredTextBoxGroup.release());

        //******************************************************************************
        // ToggleButton
        //******************************************************************************

        auto toggleButtonGroup = CreateLayoutGroup("ToggleButton");
        layoutVisualState = CreateLayoutState(toggleButtonGroup.get(), "Disabled");
        layoutVisualState->SetElevation(0);
        layoutVisualState->SetBorderThickness(UIDefaults::DefaultBorderThickness);
        layoutVisualState->SetMaxWidth(UIDefaults::ToggleButtonHeight);
        layoutVisualState->SetMaxHeight(UIDefaults::ToggleButtonHeight);
        layoutVisualState->SetPadding(
            UIDefaults::ToggleButtonPaddingLeftRight,
            UIDefaults::ToggleButtonPaddingTopBottom,
            UIDefaults::ToggleButtonPaddingLeftRight,
            UIDefaults::ToggleButtonPaddingTopBottom);

        CloneLayoutForAllStates(toggleButtonGroup.get(), layoutVisualState);
        Default.AddLayoutVisualStateGroup(toggleButtonGroup.release());

        //******************************************************************************
        // SearchBar
        //******************************************************************************

        auto searchBarGroup = CreateLayoutGroup("SearchBar");
        layoutVisualState = CreateLayoutState(searchBarGroup.get(), "Disabled");
        layoutVisualState->SetMaxHeight(UIDefaults::TextBoxHeight);
        layoutVisualState->SetVerticalContentAlignment(VerticalAlignment::Center);

        // TODO this could be a reason why the layout changes. The TextBox only has these states. What happens if a different state is used?
        CloneLayoutForState(searchBarGroup.get(), layoutVisualState, "Normal");
        CloneLayoutForState(searchBarGroup.get(), layoutVisualState, "Hovered");
        CloneLayoutForState(searchBarGroup.get(), layoutVisualState, "Focused");
        CloneLayoutForState(searchBarGroup.get(), layoutVisualState, "Error");

        Default.AddLayoutVisualStateGroup(searchBarGroup.release());

        //******************************************************************************
        // Switch
        //******************************************************************************

        auto switchGroup = CreateLayoutGroup("Switch");
        layoutVisualState = CreateLayoutState(switchGroup.get(), "Disabled");
        layoutVisualState->SetMinHeight(UIDefaults::ToggleButtonHeight);
        layoutVisualState->SetMaxHeight(UIDefaults::ToggleButtonHeight << 1);
        layoutVisualState->SetVerticalAlignment(VerticalAlignment::Top);
        layoutVisualState->SetVerticalContentAlignment(VerticalAlignment::Center);
        layoutVisualState->SetPadding(UIDefaults::TextBoxPaddingLeft);

        CloneLayoutForAllStates(switchGroup.get(), layoutVisualState);
        Default.AddLayoutVisualStateGroup(switchGroup.release());

        //******************************************************************************
        // SwitchCentered
        //******************************************************************************

        auto switchCenteredGroup = CreateLayoutGroup("SwitchCentered");
        layoutVisualState = CreateLayoutState(switchCenteredGroup.get(), "Disabled");
        layoutVisualState->SetHeight(UIDefaults::ToggleButtonHeight);
        layoutVisualState->SetHorizontalAlignment(HorizontalAlignment::Center);

        CloneLayoutForAllStates(switchCenteredGroup.get(), layoutVisualState);
        Default.AddLayoutVisualStateGroup(switchCenteredGroup.release());

        //******************************************************************************
        // VScrollBar
        //******************************************************************************

        auto vScrollBarGroup = CreateLayoutGroup("VScrollBar");
        layoutVisualState = CreateLayoutState(vScrollBarGroup.get(), "Disabled");
        layoutVisualState->SetWidth(UIDefaults::ProgressBarMinHeight);
        layoutVisualState->SetHeight(-1);
        layoutVisualState->SetHorizontalAlignment(HorizontalAlignment::Right);
        // layoutVisualState->SetBorderThickness(UIDefaults::DefaultBorderThickness);

        CloneLayoutForState(vScrollBarGroup.get(), layoutVisualState, "Normal");
        Default.AddLayoutVisualStateGroup(vScrollBarGroup.release());

        //******************************************************************************
        // ToolTip
        //******************************************************************************

        auto toolTipGroup = CreateLayoutGroup("ToolTip");
        layoutVisualState = CreateLayoutState(toolTipGroup.get(), "Normal");

        layoutVisualState->SetHorizontalAlignment(HorizontalAlignment::Left);
        layoutVisualState->SetVerticalAlignment(VerticalAlignment::Top);
        layoutVisualState->SetHorizontalContentAlignment(HorizontalAlignment::Left);
        layoutVisualState->SetVerticalContentAlignment(VerticalAlignment::Top);
        layoutVisualState->SetPadding(UIDefaults::ContainerPadding);
        layoutVisualState->SetCornerRadius(UIDefaults::BigCornerRadius);
        layoutVisualState->SetBorderThickness(UIDefaults::DefaultBorderThickness);

        Default.AddLayoutVisualStateGroup(toolTipGroup.release());
    }

} // namespace xit::Drawing