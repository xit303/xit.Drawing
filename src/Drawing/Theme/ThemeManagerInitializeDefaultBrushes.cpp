#include <Drawing/Theme/ThemeManager.h>
#include <Drawing/Brushes/ImageBrush.h>
#include <Drawing/Theme/BrushPool.h>
#include <memory>

namespace xit::Drawing
{
    // Helper function to create and add a brush visual state
    template<typename... Args>
    BrushVisualState* CreateBrushState(BrushVisualStateGroup* group, Args&&... args)
    {
        auto state = std::make_unique<BrushVisualState>(std::forward<Args>(args)...);
        BrushVisualState* statePtr = state.get();
        group->AddState(state.release()); // Transfer ownership to the group
        return statePtr;
    }

    // Helper function to create a brush visual state group
    std::unique_ptr<BrushVisualStateGroup> CreateBrushGroup(const std::string& name)
    {
        return std::make_unique<BrushVisualStateGroup>(name);
    }

    // Helper function to create a brush visual state group from copy
    std::unique_ptr<BrushVisualStateGroup> CreateBrushGroupCopy(const BrushVisualStateGroup& other)
    {
        return std::make_unique<BrushVisualStateGroup>(other);
    }

    void ThemeManager::InitializeDefaultBrushes()
    {
        // Optimized async texture loading
        auto imageBackgroundBrushPtr = std::make_unique<ImageBrush>("Resources/Images/Background/Background1.jpg");
        BrushBase *imageBackgroundBrush = imageBackgroundBrushPtr.release(); // Transfer ownership as needed

        // Use BrushPool for shared color brushes
        BrushBase *disabledBackgroundBrush = BrushPool::GetSolidColorBrush(0x3FCCCCCC);
        BrushBase *disabledForegroundBrush = BrushPool::GetSolidColorBrush(0xFF808080);
        BrushBase *disabledBorderBrush = BrushPool::GetSolidColorBrush(0x5FCCCCCC);

        BrushBase *normalBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF7160E8);
        BrushBase *normalForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        BrushBase *normalBorderBrush = BrushPool::GetSolidColorBrush(0x7F7160E8);

        BrushBase *hoveredBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF4b39cf);
        BrushBase *hoveredForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        BrushBase *hoveredBorderBrush = BrushPool::GetSolidColorBrush(0xFF9E9E9E);

        BrushBase *pressedBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF343434);
        BrushBase *pressedForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        BrushBase *pressedBorderBrush = BrushPool::GetSolidColorBrush(0xFF877EC3);

        BrushBase *activeBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF494949);
        BrushBase *activeForegroundBrush = BrushPool::GetSolidColorBrush(0xFFFFFFFF);
        BrushBase *activeBorderBrush = BrushPool::GetSolidColorBrush(0xFF7160E8);

        BrushBase *focusedBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF7160E8);
        BrushBase *focusedForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        BrushBase *focusedBorderBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);

        BrushBase *activeHoveredBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF494949);
        BrushBase *activeHoveredForegroundBrush = BrushPool::GetSolidColorBrush(0xFFFFFFFF);
        BrushBase *activeHoveredBorderBrush = BrushPool::GetSolidColorBrush(0xFF8E8E8E);

        BrushBase *midiLearnBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF2B2B2B);
        BrushBase *midiLearnForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        BrushBase *midiLearnBorderBrush = BrushPool::GetSolidColorBrush(0x00424242);

        BrushBase *errorBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF2B2B2B);
        BrushBase *errorForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        BrushBase *errorBorderBrush = BrushPool::GetSolidColorBrush(0xFFFF0000);

        BrushBase *highlightBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF2B2B2B);
        BrushBase *highlightForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        BrushBase *highlightBorderBrush = BrushPool::GetSolidColorBrush(0xFFFFFF00);

        //******************************************************************************

        //******************************************************************************

        auto windowGroup = CreateBrushGroup("Window");
        CreateBrushState(windowGroup.get(), "Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush);
        CreateBrushState(windowGroup.get(), "Normal", imageBackgroundBrush, normalForegroundBrush, BrushPool::GetSolidColorBrush(0xFF4C4C4C));
        Default.GetBrushVisualStateGroups().push_back(windowGroup.release());

        //******************************************************************************

        //******************************************************************************

        auto labelGroup = CreateBrushGroup("Label");
        CreateBrushState(labelGroup.get(), "Normal", BrushPool::GetSolidColorBrush(0x00000000), normalForegroundBrush, BrushPool::GetSolidColorBrush(0x00000000));
        Default.GetBrushVisualStateGroups().push_back(labelGroup.release());

        //******************************************************************************

        //******************************************************************************

        auto buttonGroup = CreateBrushGroup("Button");

        CreateBrushState(buttonGroup.get(), "Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush);
        CreateBrushState(buttonGroup.get(), "Normal", normalBackgroundBrush, normalForegroundBrush, normalBorderBrush);
        CreateBrushState(buttonGroup.get(), "Hovered", hoveredBackgroundBrush, hoveredForegroundBrush, hoveredBorderBrush);
        CreateBrushState(buttonGroup.get(), "Pressed", pressedBackgroundBrush, pressedForegroundBrush, pressedBorderBrush);
        CreateBrushState(buttonGroup.get(), "Active", activeBackgroundBrush, activeForegroundBrush, activeBorderBrush);
        CreateBrushState(buttonGroup.get(), "Focused", focusedBackgroundBrush, focusedForegroundBrush, focusedBorderBrush);
        CreateBrushState(buttonGroup.get(), "ActiveHovered", activeHoveredBackgroundBrush, activeHoveredForegroundBrush, activeHoveredBorderBrush);
        CreateBrushState(buttonGroup.get(), "MidiLearn", midiLearnBackgroundBrush, midiLearnForegroundBrush, midiLearnBorderBrush);
        CreateBrushState(buttonGroup.get(), "Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush);
        
        // Store pointer for copying before transferring ownership
        BrushVisualStateGroup* buttonGroupPtr = buttonGroup.get();
        Default.GetBrushVisualStateGroups().push_back(buttonGroup.release());

        //******************************************************************************

        //******************************************************************************

        auto comboBoxButtonGroup = CreateBrushGroupCopy(*buttonGroupPtr);
        comboBoxButtonGroup->SetName("ComboBoxButton");
        Default.GetBrushVisualStateGroups().push_back(comboBoxButtonGroup.release());

        //******************************************************************************

        //******************************************************************************

        auto buttonInContainerGroup = CreateBrushGroupCopy(*buttonGroupPtr);
        buttonInContainerGroup->SetName("ButtonInContainer");
        Default.GetBrushVisualStateGroups().push_back(buttonInContainerGroup.release());

        //******************************************************************************

        //******************************************************************************

        auto comboBoxGroup = CreateBrushGroup("ComboBox");
        CreateBrushState(comboBoxGroup.get(), "Disabled", BrushPool::GetSolidColorBrush(0x0AFFFFFF), disabledForegroundBrush, BrushPool::GetSolidColorBrush(0x0A4C4C4C));
        CreateBrushState(comboBoxGroup.get(), "Normal", BrushPool::GetSolidColorBrush(0xD71B2833), normalForegroundBrush, BrushPool::GetSolidColorBrush(0xFF4C4C4C));
        Default.GetBrushVisualStateGroups().push_back(comboBoxGroup.release());

        //******************************************************************************

        //******************************************************************************

        auto contextMenuItemGroup = CreateBrushGroup("ContextMenuItem");
        CreateBrushState(contextMenuItemGroup.get(), "Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush);
        CreateBrushState(contextMenuItemGroup.get(), "Normal", normalBackgroundBrush, normalForegroundBrush, normalBorderBrush);
        CreateBrushState(contextMenuItemGroup.get(), "Hovered", hoveredBackgroundBrush, hoveredForegroundBrush, hoveredBorderBrush);
        CreateBrushState(contextMenuItemGroup.get(), "Pressed", pressedBackgroundBrush, pressedForegroundBrush, pressedBorderBrush);
        CreateBrushState(contextMenuItemGroup.get(), "Active", activeBackgroundBrush, activeForegroundBrush, activeBorderBrush);
        CreateBrushState(contextMenuItemGroup.get(), "Focused", focusedBackgroundBrush, focusedForegroundBrush, focusedBorderBrush);
        CreateBrushState(contextMenuItemGroup.get(), "ActiveHovered", activeHoveredBackgroundBrush, activeHoveredForegroundBrush, activeHoveredBorderBrush);
        CreateBrushState(contextMenuItemGroup.get(), "MidiLearn", midiLearnBackgroundBrush, midiLearnForegroundBrush, midiLearnBorderBrush);
        CreateBrushState(contextMenuItemGroup.get(), "Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush);
        Default.GetBrushVisualStateGroups().push_back(contextMenuItemGroup.release());

        //******************************************************************************

        //******************************************************************************

        // Update brush pointers to use pool for next visual state groups
        disabledBackgroundBrush = BrushPool::GetSolidColorBrush(0x3FCCCCCC);
        disabledForegroundBrush = BrushPool::GetSolidColorBrush(0xFF808080);
        disabledBorderBrush = BrushPool::GetSolidColorBrush(0x5FCCCCCC);

        normalBackgroundBrush = BrushPool::GetSolidColorBrush(0x7F2B2B2B);
        normalForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        normalBorderBrush = BrushPool::GetSolidColorBrush(0xFF424242);

        hoveredBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF333333);
        hoveredForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        hoveredBorderBrush = BrushPool::GetSolidColorBrush(0xFF9E9E9E);

        pressedBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF343434);
        pressedForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        pressedBorderBrush = BrushPool::GetSolidColorBrush(0xFF877EC3);

        activeBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF494949);
        activeForegroundBrush = BrushPool::GetSolidColorBrush(0xFFFFFFFF);
        activeBorderBrush = BrushPool::GetSolidColorBrush(0xFF7160E8);

        focusedBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF494949);
        focusedForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        focusedBorderBrush = BrushPool::GetSolidColorBrush(0xFF7160E8);

        activeHoveredBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF494949);
        activeHoveredForegroundBrush = BrushPool::GetSolidColorBrush(0xFFFFFFFF);
        activeHoveredBorderBrush = BrushPool::GetSolidColorBrush(0xFF8E8E8E);

        midiLearnBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF2B2B2B);
        midiLearnForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        midiLearnBorderBrush = BrushPool::GetSolidColorBrush(0x00424242);

        errorBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF2B2B2B);
        errorForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        errorBorderBrush = BrushPool::GetSolidColorBrush(0xFFFF0000);

        auto mainMenuButtonGroup = CreateBrushGroup("MainMenuButton");
        CreateBrushState(mainMenuButtonGroup.get(), "Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush);
        CreateBrushState(mainMenuButtonGroup.get(), "Normal", normalBackgroundBrush, normalForegroundBrush, normalBorderBrush);
        CreateBrushState(mainMenuButtonGroup.get(), "Hovered", hoveredBackgroundBrush, hoveredForegroundBrush, hoveredBorderBrush);
        CreateBrushState(mainMenuButtonGroup.get(), "Pressed", pressedBackgroundBrush, pressedForegroundBrush, pressedBorderBrush);
        CreateBrushState(mainMenuButtonGroup.get(), "Active", activeBackgroundBrush, activeForegroundBrush, activeBorderBrush);
        CreateBrushState(mainMenuButtonGroup.get(), "Focused", focusedBackgroundBrush, focusedForegroundBrush, focusedBorderBrush);
        CreateBrushState(mainMenuButtonGroup.get(), "ActiveHovered", activeHoveredBackgroundBrush, activeHoveredForegroundBrush, activeHoveredBorderBrush);
        CreateBrushState(mainMenuButtonGroup.get(), "MidiLearn", midiLearnBackgroundBrush, midiLearnForegroundBrush, midiLearnBorderBrush);
        CreateBrushState(mainMenuButtonGroup.get(), "Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush);
        Default.GetBrushVisualStateGroups().push_back(mainMenuButtonGroup.release());

        //******************************************************************************

        //******************************************************************************

        activeBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF7160E8);
        activeForegroundBrush = BrushPool::GetSolidColorBrush(0xFFFFFFFF);
        activeBorderBrush = BrushPool::GetSolidColorBrush(0xFF7160E8);

        focusedBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF7160E8);
        focusedForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        focusedBorderBrush = BrushPool::GetSolidColorBrush(0xFF7160E8);

        auto iconButtonGroup = CreateBrushGroup("IconButton");
        CreateBrushState(iconButtonGroup.get(), "Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush);
        CreateBrushState(iconButtonGroup.get(), "Normal", normalBackgroundBrush, normalForegroundBrush, normalBorderBrush);
        CreateBrushState(iconButtonGroup.get(), "Hovered", hoveredBackgroundBrush, hoveredForegroundBrush, hoveredBorderBrush);
        CreateBrushState(iconButtonGroup.get(), "Pressed", pressedBackgroundBrush, pressedForegroundBrush, pressedBorderBrush);
        CreateBrushState(iconButtonGroup.get(), "Active", activeBackgroundBrush, activeForegroundBrush, activeBorderBrush);
        CreateBrushState(iconButtonGroup.get(), "Focused", focusedBackgroundBrush, focusedForegroundBrush, focusedBorderBrush);
        CreateBrushState(iconButtonGroup.get(), "ActiveHovered", activeHoveredBackgroundBrush, activeHoveredForegroundBrush, activeHoveredBorderBrush);
        CreateBrushState(iconButtonGroup.get(), "MidiLearn", midiLearnBackgroundBrush, midiLearnForegroundBrush, midiLearnBorderBrush);
        CreateBrushState(iconButtonGroup.get(), "Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush);
        Default.GetBrushVisualStateGroups().push_back(iconButtonGroup.release());

        //******************************************************************************

        //******************************************************************************

        auto toggleButtonGroup = CreateBrushGroup("ToggleButton");
        CreateBrushState(toggleButtonGroup.get(), "Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush);
        CreateBrushState(toggleButtonGroup.get(), "Normal", normalBackgroundBrush, normalForegroundBrush, normalBorderBrush);
        CreateBrushState(toggleButtonGroup.get(), "Hovered", hoveredBackgroundBrush, hoveredForegroundBrush, hoveredBorderBrush);
        CreateBrushState(toggleButtonGroup.get(), "Pressed", pressedBackgroundBrush, pressedForegroundBrush, pressedBorderBrush);
        CreateBrushState(toggleButtonGroup.get(), "Active", activeBackgroundBrush, activeForegroundBrush, activeBorderBrush);
        CreateBrushState(toggleButtonGroup.get(), "Focused", focusedBackgroundBrush, focusedForegroundBrush, focusedBorderBrush);
        CreateBrushState(toggleButtonGroup.get(), "ActiveHovered", activeHoveredBackgroundBrush, activeHoveredForegroundBrush, activeHoveredBorderBrush);
        CreateBrushState(toggleButtonGroup.get(), "MidiLearn", midiLearnBackgroundBrush, midiLearnForegroundBrush, midiLearnBorderBrush);
        CreateBrushState(toggleButtonGroup.get(), "Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush);
        Default.GetBrushVisualStateGroups().push_back(toggleButtonGroup.release());

        //******************************************************************************

        //******************************************************************************

        auto switchGroup = CreateBrushGroup("Switch");
        CreateBrushState(switchGroup.get(), "Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush);
        CreateBrushState(switchGroup.get(), "Normal", normalBackgroundBrush, normalForegroundBrush, normalBorderBrush);
        CreateBrushState(switchGroup.get(), "Hovered", hoveredBackgroundBrush, hoveredForegroundBrush, hoveredBorderBrush);
        CreateBrushState(switchGroup.get(), "Pressed", pressedBackgroundBrush, pressedForegroundBrush, pressedBorderBrush);
        CreateBrushState(switchGroup.get(), "Active", activeBackgroundBrush, activeForegroundBrush, activeBorderBrush);
        CreateBrushState(switchGroup.get(), "Focused", focusedBackgroundBrush, focusedForegroundBrush, focusedBorderBrush);
        CreateBrushState(switchGroup.get(), "ActiveHovered", activeHoveredBackgroundBrush, activeHoveredForegroundBrush, activeHoveredBorderBrush);
        CreateBrushState(switchGroup.get(), "MidiLearn", midiLearnBackgroundBrush, midiLearnForegroundBrush, midiLearnBorderBrush);
        CreateBrushState(switchGroup.get(), "Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush);
        Default.GetBrushVisualStateGroups().push_back(switchGroup.release());

        //******************************************************************************

        //******************************************************************************

        disabledBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF2B2B2B);
        disabledForegroundBrush = BrushPool::GetSolidColorBrush(0xFF808080);
        disabledBorderBrush = BrushPool::GetSolidColorBrush(0x5FCCCCCC);

        normalBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF2B2B2B);
        normalForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        normalBorderBrush = BrushPool::GetSolidColorBrush(0xFF424242);

        hoveredBackgroundBrush = BrushPool::GetSolidColorBrush(0x4AFFFFFF);
        hoveredForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        hoveredBorderBrush = BrushPool::GetSolidColorBrush(0xFF9E9E9E);

        pressedBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF343434);
        pressedForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        pressedBorderBrush = BrushPool::GetSolidColorBrush(0xFF877EC3);

        activeBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF7160E8);
        activeForegroundBrush = BrushPool::GetSolidColorBrush(0xFFFFFFFF);
        activeBorderBrush = BrushPool::GetSolidColorBrush(0xFF7160E8);

        focusedBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF7160E8);
        focusedForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        focusedBorderBrush = BrushPool::GetSolidColorBrush(0xFF7160E8);

        activeHoveredBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF7160E8);
        activeHoveredForegroundBrush = BrushPool::GetSolidColorBrush(0xFFFFFFFF);
        activeHoveredBorderBrush = BrushPool::GetSolidColorBrush(0xFF8E8E8E);

        midiLearnBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF2B2B2B);
        midiLearnForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        midiLearnBorderBrush = BrushPool::GetSolidColorBrush(0x00424242);

        errorBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF2B2B2B);
        errorForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        errorBorderBrush = BrushPool::GetSolidColorBrush(0xFFFF0000);

        auto listItemGroup = CreateBrushGroup("ListItem");
        CreateBrushState(listItemGroup.get(), "Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush);
        CreateBrushState(listItemGroup.get(), "Normal", normalBackgroundBrush, normalForegroundBrush, normalBorderBrush);
        CreateBrushState(listItemGroup.get(), "Hovered", hoveredBackgroundBrush, hoveredForegroundBrush, hoveredBorderBrush);
        CreateBrushState(listItemGroup.get(), "Pressed", pressedBackgroundBrush, pressedForegroundBrush, pressedBorderBrush);
        CreateBrushState(listItemGroup.get(), "Active", activeBackgroundBrush, activeForegroundBrush, activeBorderBrush);
        CreateBrushState(listItemGroup.get(), "Focused", focusedBackgroundBrush, focusedForegroundBrush, focusedBorderBrush);
        CreateBrushState(listItemGroup.get(), "ActiveHovered", activeHoveredBackgroundBrush, activeHoveredForegroundBrush, activeHoveredBorderBrush);
        CreateBrushState(listItemGroup.get(), "MidiLearn", midiLearnBackgroundBrush, midiLearnForegroundBrush, midiLearnBorderBrush);
        CreateBrushState(listItemGroup.get(), "Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush);
        Default.GetBrushVisualStateGroups().push_back(listItemGroup.release());

        //******************************************************************************

        //******************************************************************************

        disabledBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF2B2B2B);
        disabledForegroundBrush = BrushPool::GetSolidColorBrush(0xFF808080);
        disabledBorderBrush = BrushPool::GetSolidColorBrush(0x5FCCCCCC);

        normalBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF2B2B2B);
        normalForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        normalBorderBrush = BrushPool::GetSolidColorBrush(0xFF424242);

        hoveredBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF3B3B3B);
        hoveredForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        hoveredBorderBrush = BrushPool::GetSolidColorBrush(0xFF9E9E9E);

        pressedBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF343434);
        pressedForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        pressedBorderBrush = BrushPool::GetSolidColorBrush(0xFF877EC3);

        activeBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF2B2B2B);
        activeForegroundBrush = BrushPool::GetSolidColorBrush(0xFFFFFFFF);
        activeBorderBrush = BrushPool::GetSolidColorBrush(0xFF7160E8);

        focusedBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF2B2B2B);
        focusedForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        focusedBorderBrush = BrushPool::GetSolidColorBrush(0xFF7160E8);

        activeHoveredBackgroundBrush = BrushPool::GetSolidColorBrush(0x1AFFFFFF);
        activeHoveredForegroundBrush = BrushPool::GetSolidColorBrush(0xFFFFFFFF);
        activeHoveredBorderBrush = BrushPool::GetSolidColorBrush(0xFF7160E8);

        midiLearnBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF2B2B2B);
        midiLearnForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        midiLearnBorderBrush = BrushPool::GetSolidColorBrush(0x00424242);

        errorBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF2B2B2B);
        errorForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        errorBorderBrush = BrushPool::GetSolidColorBrush(0xFFFF0000);

        auto headerButtonGroup = CreateBrushGroup("HeaderButton");
        CreateBrushState(headerButtonGroup.get(), "Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush);
        CreateBrushState(headerButtonGroup.get(), "Normal", normalBackgroundBrush, normalForegroundBrush, normalBorderBrush);
        CreateBrushState(headerButtonGroup.get(), "Hovered", hoveredBackgroundBrush, hoveredForegroundBrush, hoveredBorderBrush);
        CreateBrushState(headerButtonGroup.get(), "Pressed", pressedBackgroundBrush, pressedForegroundBrush, pressedBorderBrush);
        CreateBrushState(headerButtonGroup.get(), "Active", activeBackgroundBrush, activeForegroundBrush, activeBorderBrush);
        CreateBrushState(headerButtonGroup.get(), "Focused", focusedBackgroundBrush, focusedForegroundBrush, focusedBorderBrush);
        CreateBrushState(headerButtonGroup.get(), "ActiveHovered", activeHoveredBackgroundBrush, activeHoveredForegroundBrush, activeHoveredBorderBrush);
        CreateBrushState(headerButtonGroup.get(), "MidiLearn", midiLearnBackgroundBrush, midiLearnForegroundBrush, midiLearnBorderBrush);
        CreateBrushState(headerButtonGroup.get(), "Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush);
        Default.GetBrushVisualStateGroups().push_back(headerButtonGroup.release());

        //******************************************************************************

        //******************************************************************************

        disabledBackgroundBrush = BrushPool::GetSolidColorBrush(0x7F2B2B2B);
        disabledForegroundBrush = BrushPool::GetSolidColorBrush(0xFF808080);
        disabledBorderBrush = BrushPool::GetSolidColorBrush(0x5FCCCCCC);

        normalBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF2B2B2B);
        normalForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        normalBorderBrush = BrushPool::GetSolidColorBrush(0xFF444444); // 0xFF424242

        hoveredBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF2B2B2B);
        hoveredForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        hoveredBorderBrush = BrushPool::GetSolidColorBrush(0xFF9E9E9E);

        pressedBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF343434);
        pressedForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        pressedBorderBrush = BrushPool::GetSolidColorBrush(0x00424242);

        activeBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF2B2B2B);
        activeForegroundBrush = BrushPool::GetSolidColorBrush(0xFFFFFFFF);
        activeBorderBrush = BrushPool::GetSolidColorBrush(0xFF7160E8);

        focusedBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF2B2B2B);
        focusedForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        focusedBorderBrush = BrushPool::GetSolidColorBrush(0xFF7160E8);

        activeHoveredBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF2B2B2B);
        activeHoveredForegroundBrush = BrushPool::GetSolidColorBrush(0xFFFFFFFF);
        activeHoveredBorderBrush = BrushPool::GetSolidColorBrush(0xFF8E8E8E);

        midiLearnBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF2B2B2B);
        midiLearnForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        midiLearnBorderBrush = BrushPool::GetSolidColorBrush(0x00424242);

        errorBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF2B2B2B);
        errorForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        errorBorderBrush = BrushPool::GetSolidColorBrush(0xFFFF0000);

        auto textBoxGroup = CreateBrushGroup("TextBox");
        CreateBrushState(textBoxGroup.get(), "Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush);
        CreateBrushState(textBoxGroup.get(), "Normal", normalBackgroundBrush, normalForegroundBrush, normalBorderBrush);
        CreateBrushState(textBoxGroup.get(), "Hovered", hoveredBackgroundBrush, hoveredForegroundBrush, hoveredBorderBrush);
        CreateBrushState(textBoxGroup.get(), "Focused", focusedBackgroundBrush, focusedForegroundBrush, focusedBorderBrush);
        CreateBrushState(textBoxGroup.get(), "Error", errorBackgroundBrush, errorForegroundBrush, errorBorderBrush);
        CreateBrushState(textBoxGroup.get(), "Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush);
        Default.GetBrushVisualStateGroups().push_back(textBoxGroup.release());

        //******************************************************************************

        //******************************************************************************

        disabledBackgroundBrush = BrushPool::GetSolidColorBrush(0x3FCCCCCC);
        disabledForegroundBrush = BrushPool::GetSolidColorBrush(0xFF808080);
        disabledBorderBrush = BrushPool::GetSolidColorBrush(0x5FCCCCCC);

        normalBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF161616);
        normalForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        normalBorderBrush = BrushPool::GetSolidColorBrush(0xFF3F3F3F);

        hoveredBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF2B2B2B);
        hoveredForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        hoveredBorderBrush = BrushPool::GetSolidColorBrush(0xFF9E9E9E);

        pressedBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF343434);
        pressedForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        pressedBorderBrush = BrushPool::GetSolidColorBrush(0x00424242);

        activeBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF494949);
        activeForegroundBrush = BrushPool::GetSolidColorBrush(0xFFFFFFFF);
        activeBorderBrush = BrushPool::GetSolidColorBrush(0xFF494949);

        focusedBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF2B2B2B);
        focusedForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        focusedBorderBrush = BrushPool::GetSolidColorBrush(0x00424242);

        activeHoveredBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF494949);
        activeHoveredForegroundBrush = BrushPool::GetSolidColorBrush(0xFFFFFFFF);
        activeHoveredBorderBrush = BrushPool::GetSolidColorBrush(0xFF9E9E9E);

        midiLearnBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF2B2B2B);
        midiLearnForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        midiLearnBorderBrush = BrushPool::GetSolidColorBrush(0x00424242);

        errorBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF2B2B2B);
        errorForegroundBrush = BrushPool::GetSolidColorBrush(0xFFFF0000);
        errorBorderBrush = BrushPool::GetSolidColorBrush(0xFFFF0000);

        auto containerGroup = CreateBrushGroup("Container");
        CreateBrushState(containerGroup.get(), "Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush);
        CreateBrushState(containerGroup.get(), "Normal", normalBackgroundBrush, normalForegroundBrush, normalBorderBrush);
        CreateBrushState(containerGroup.get(), "MidiLearn", midiLearnBackgroundBrush, midiLearnForegroundBrush, midiLearnBorderBrush);
        CreateBrushState(containerGroup.get(), "Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush);
        Default.GetBrushVisualStateGroups().push_back(containerGroup.release());

        //******************************************************************************

        //******************************************************************************

        auto propertyItemGroup = CreateBrushGroup("PropertyItem");
        CreateBrushState(propertyItemGroup.get(), "Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush);
        CreateBrushState(propertyItemGroup.get(), "Normal", normalBackgroundBrush, normalForegroundBrush, normalBorderBrush);
        CreateBrushState(propertyItemGroup.get(), "Hovered", hoveredBackgroundBrush, hoveredForegroundBrush, hoveredBorderBrush);
        CreateBrushState(propertyItemGroup.get(), "Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush);
        Default.GetBrushVisualStateGroups().push_back(propertyItemGroup.release());

        //******************************************************************************

        //******************************************************************************

        SolidColorBrush *cardBackgroundBrush = BrushPool::GetSolidColorBrush(0x602B2B2B);
        SolidColorBrush *cardForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        SolidColorBrush *cardBorderBrush = BrushPool::GetSolidColorBrush(0xFF424242);

        auto pageGroup = CreateBrushGroup("Page");
        CreateBrushState(pageGroup.get(), "Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush);
        CreateBrushState(pageGroup.get(), "Normal", cardBackgroundBrush, cardForegroundBrush, cardBorderBrush);
        CreateBrushState(pageGroup.get(), "MidiLearn", midiLearnBackgroundBrush, midiLearnForegroundBrush, midiLearnBorderBrush);
        CreateBrushState(pageGroup.get(), "Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush);
        Default.GetBrushVisualStateGroups().push_back(pageGroup.release());

        //******************************************************************************

        //******************************************************************************

        auto cardGroup = CreateBrushGroup("Card");
        CreateBrushState(cardGroup.get(), "Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush);
        CreateBrushState(cardGroup.get(), "Normal", cardBackgroundBrush, cardForegroundBrush, cardBorderBrush);
        CreateBrushState(cardGroup.get(), "MidiLearn", midiLearnBackgroundBrush, midiLearnForegroundBrush, midiLearnBorderBrush);
        CreateBrushState(cardGroup.get(), "Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush);
        Default.GetBrushVisualStateGroups().push_back(cardGroup.release());

        //******************************************************************************

        //******************************************************************************

        auto listGroup = CreateBrushGroup("List");
        CreateBrushState(listGroup.get(), "Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush);
        CreateBrushState(listGroup.get(), "Normal", normalBackgroundBrush, normalForegroundBrush, normalBorderBrush);
        CreateBrushState(listGroup.get(), "MidiLearn", midiLearnBackgroundBrush, midiLearnForegroundBrush, midiLearnBorderBrush);
        CreateBrushState(listGroup.get(), "Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush);
        Default.GetBrushVisualStateGroups().push_back(listGroup.release());

        //******************************************************************************

        //******************************************************************************

        auto gridSplitterGroup = CreateBrushGroup("GridSplitter");
        CreateBrushState(gridSplitterGroup.get(), "Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush);
        CreateBrushState(gridSplitterGroup.get(), "Normal", normalBackgroundBrush, normalForegroundBrush, normalBorderBrush);
        CreateBrushState(gridSplitterGroup.get(), "Hovered", hoveredBackgroundBrush, hoveredForegroundBrush, hoveredBorderBrush);
        CreateBrushState(gridSplitterGroup.get(), "Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush);
        Default.GetBrushVisualStateGroups().push_back(gridSplitterGroup.release());

        //******************************************************************************

        //******************************************************************************

        auto headerGroup = CreateBrushGroup("Header");
        CreateBrushState(headerGroup.get(), "Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush);
        CreateBrushState(headerGroup.get(), "Normal", normalBackgroundBrush, normalForegroundBrush, normalBorderBrush);
        CreateBrushState(headerGroup.get(), "Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush);
        Default.GetBrushVisualStateGroups().push_back(headerGroup.release());

        //******************************************************************************

        //******************************************************************************

        SolidColorBrush *mainMenuBackgroundBrush = BrushPool::GetSolidColorBrush(0x102B2B2B);
        SolidColorBrush *mainMenuForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        SolidColorBrush *mainMenuBorderBrush = BrushPool::GetSolidColorBrush(0xFF424242);

        auto mainMenuGroup = CreateBrushGroup("MainMenu");
        CreateBrushState(mainMenuGroup.get(), "Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush);
        CreateBrushState(mainMenuGroup.get(), "Normal", mainMenuBackgroundBrush, mainMenuForegroundBrush, mainMenuBorderBrush);
        CreateBrushState(mainMenuGroup.get(), "Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush);
        Default.GetBrushVisualStateGroups().push_back(mainMenuGroup.release());

        //******************************************************************************

        //******************************************************************************

        auto mainMenuContentGroup = CreateBrushGroup("MainMenuContent");
        CreateBrushState(mainMenuContentGroup.get(), "Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush);
        CreateBrushState(mainMenuContentGroup.get(), "Normal", normalBackgroundBrush, normalForegroundBrush, normalBorderBrush);
        CreateBrushState(mainMenuContentGroup.get(), "Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush);
        Default.GetBrushVisualStateGroups().push_back(mainMenuContentGroup.release());

        //******************************************************************************

        //******************************************************************************

        activeBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF7160E8);

        auto progressBarGroup = CreateBrushGroup("ProgressBar");
        CreateBrushState(progressBarGroup.get(), "Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush);
        CreateBrushState(progressBarGroup.get(), "Normal", normalBackgroundBrush, activeBackgroundBrush, normalBorderBrush);
        CreateBrushState(progressBarGroup.get(), "Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush);
        Default.GetBrushVisualStateGroups().push_back(progressBarGroup.release());

        //******************************************************************************

        //******************************************************************************

        activeBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF494949);

        normalBackgroundBrush = BrushPool::GetSolidColorBrush(0x00FFFFFF);
        normalForegroundBrush = BrushPool::GetSolidColorBrush(0x70FFFFFF);
        normalBorderBrush = BrushPool::GetSolidColorBrush(0x00000000);

        auto scrollBarGroup = CreateBrushGroup("ScrollBar");
        CreateBrushState(scrollBarGroup.get(), "Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush);
        CreateBrushState(scrollBarGroup.get(), "Normal", normalBackgroundBrush, normalForegroundBrush, normalBorderBrush);
        CreateBrushState(scrollBarGroup.get(), "Hovered", hoveredBackgroundBrush, hoveredForegroundBrush, hoveredBorderBrush);
        CreateBrushState(scrollBarGroup.get(), "MidiLearn", midiLearnBackgroundBrush, midiLearnForegroundBrush, midiLearnBorderBrush);
        CreateBrushState(scrollBarGroup.get(), "Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush);
        Default.GetBrushVisualStateGroups().push_back(scrollBarGroup.release());

        //******************************************************************************

        //******************************************************************************

        auto sliderGroup = CreateBrushGroup("Slider");
        CreateBrushState(sliderGroup.get(), "Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush);
        CreateBrushState(sliderGroup.get(), "Normal", normalBackgroundBrush, normalForegroundBrush, normalBorderBrush);
        CreateBrushState(sliderGroup.get(), "Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush);
        Default.GetBrushVisualStateGroups().push_back(sliderGroup.release());

        //******************************************************************************

        //******************************************************************************

        auto statusBarGroup = CreateBrushGroup("StatusBar");
        CreateBrushState(statusBarGroup.get(), "Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush);
        CreateBrushState(statusBarGroup.get(), "Normal", normalBackgroundBrush, normalForegroundBrush, normalBorderBrush);
        CreateBrushState(statusBarGroup.get(), "Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush);
        Default.GetBrushVisualStateGroups().push_back(statusBarGroup.release());

        //******************************************************************************

        //******************************************************************************

        normalBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF161616);
        normalForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        normalBorderBrush = BrushPool::GetSolidColorBrush(0xFF3F3F3F);

        auto toolTipGroup = CreateBrushGroup("ToolTip");
        CreateBrushState(toolTipGroup.get(), "Normal", normalBackgroundBrush, normalForegroundBrush, normalBorderBrush);
        Default.GetBrushVisualStateGroups().push_back(toolTipGroup.release());
    }
} // namespace xit::Drawing