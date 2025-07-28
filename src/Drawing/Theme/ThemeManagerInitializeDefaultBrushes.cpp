#include <Drawing/Theme/ThemeManager.h>
#include <Drawing/Brushes/ImageBrush.h>
#include <Drawing/Theme/BrushPool.h>

namespace xit::Drawing
{

    void ThemeManager::InitializeDefaultBrushes()
    {
        // Optimized async texture loading
        BrushBase *imageBackgroundBrush = new ImageBrush("Resources/Images/Background/Background1.jpg");

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

        BrushVisualStateGroup *visualStateGroup;

        //******************************************************************************

        //******************************************************************************

        visualStateGroup = new BrushVisualStateGroup("Window");
        visualStateGroup->AddState(new BrushVisualState("Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Normal", imageBackgroundBrush, normalForegroundBrush, BrushPool::GetSolidColorBrush(0xFF4C4C4C)));
        Default.GetBrushVisualStateGroups().push_back(visualStateGroup);

        //******************************************************************************

        //******************************************************************************

        visualStateGroup = new BrushVisualStateGroup("Button");

        visualStateGroup->AddState(new BrushVisualState("Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Normal", normalBackgroundBrush, normalForegroundBrush, normalBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Hovered", hoveredBackgroundBrush, hoveredForegroundBrush, hoveredBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Pressed", pressedBackgroundBrush, pressedForegroundBrush, pressedBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Active", activeBackgroundBrush, activeForegroundBrush, activeBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Focused", focusedBackgroundBrush, focusedForegroundBrush, focusedBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("ActiveHovered", activeHoveredBackgroundBrush, activeHoveredForegroundBrush, activeHoveredBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("MidiLearn", midiLearnBackgroundBrush, midiLearnForegroundBrush, midiLearnBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush));
        Default.GetBrushVisualStateGroups().push_back(visualStateGroup);

        //******************************************************************************

        //******************************************************************************

        visualStateGroup = new BrushVisualStateGroup(*visualStateGroup);
        visualStateGroup->SetName("ComboBoxButton");
        Default.GetBrushVisualStateGroups().push_back(visualStateGroup);

        //******************************************************************************

        //******************************************************************************

        visualStateGroup = new BrushVisualStateGroup(*visualStateGroup);
        visualStateGroup->SetName("ButtonInContainer");
        Default.GetBrushVisualStateGroups().push_back(visualStateGroup);

        //******************************************************************************

        //******************************************************************************

        visualStateGroup = new BrushVisualStateGroup("ComboBox");
        visualStateGroup->AddState(new BrushVisualState("Disabled", BrushPool::GetSolidColorBrush(0x0AFFFFFF), disabledForegroundBrush, BrushPool::GetSolidColorBrush(0x0A4C4C4C)));
        visualStateGroup->AddState(new BrushVisualState("Normal", BrushPool::GetSolidColorBrush(0xD71B2833), normalForegroundBrush, BrushPool::GetSolidColorBrush(0xFF4C4C4C)));
        Default.GetBrushVisualStateGroups().push_back(visualStateGroup);

        //******************************************************************************

        //******************************************************************************

        visualStateGroup = new BrushVisualStateGroup("ContextMenuItem");
        visualStateGroup->AddState(new BrushVisualState("Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Normal", normalBackgroundBrush, normalForegroundBrush, normalBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Hovered", hoveredBackgroundBrush, hoveredForegroundBrush, hoveredBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Pressed", pressedBackgroundBrush, pressedForegroundBrush, pressedBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Active", activeBackgroundBrush, activeForegroundBrush, activeBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Focused", focusedBackgroundBrush, focusedForegroundBrush, focusedBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("ActiveHovered", activeHoveredBackgroundBrush, activeHoveredForegroundBrush, activeHoveredBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("MidiLearn", midiLearnBackgroundBrush, midiLearnForegroundBrush, midiLearnBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush));
        Default.GetBrushVisualStateGroups().push_back(visualStateGroup);

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

        visualStateGroup = new BrushVisualStateGroup("MainMenuButton");
        visualStateGroup->AddState(new BrushVisualState("Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Normal", normalBackgroundBrush, normalForegroundBrush, normalBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Hovered", hoveredBackgroundBrush, hoveredForegroundBrush, hoveredBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Pressed", pressedBackgroundBrush, pressedForegroundBrush, pressedBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Active", activeBackgroundBrush, activeForegroundBrush, activeBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Focused", focusedBackgroundBrush, focusedForegroundBrush, focusedBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("ActiveHovered", activeHoveredBackgroundBrush, activeHoveredForegroundBrush, activeHoveredBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("MidiLearn", midiLearnBackgroundBrush, midiLearnForegroundBrush, midiLearnBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush));
        Default.GetBrushVisualStateGroups().push_back(visualStateGroup);

        //******************************************************************************

        //******************************************************************************

        activeBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF7160E8);
        activeForegroundBrush = BrushPool::GetSolidColorBrush(0xFFFFFFFF);
        activeBorderBrush = BrushPool::GetSolidColorBrush(0xFF7160E8);

        focusedBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF7160E8);
        focusedForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        focusedBorderBrush = BrushPool::GetSolidColorBrush(0xFF7160E8);

        visualStateGroup = new BrushVisualStateGroup("IconButton");
        visualStateGroup->AddState(new BrushVisualState("Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Normal", normalBackgroundBrush, normalForegroundBrush, normalBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Hovered", hoveredBackgroundBrush, hoveredForegroundBrush, hoveredBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Pressed", pressedBackgroundBrush, pressedForegroundBrush, pressedBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Active", activeBackgroundBrush, activeForegroundBrush, activeBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Focused", focusedBackgroundBrush, focusedForegroundBrush, focusedBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("ActiveHovered", activeHoveredBackgroundBrush, activeHoveredForegroundBrush, activeHoveredBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("MidiLearn", midiLearnBackgroundBrush, midiLearnForegroundBrush, midiLearnBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush));
        Default.GetBrushVisualStateGroups().push_back(visualStateGroup);

        //******************************************************************************

        //******************************************************************************

        visualStateGroup = new BrushVisualStateGroup("ToggleButton");
        visualStateGroup->AddState(new BrushVisualState("Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Normal", normalBackgroundBrush, normalForegroundBrush, normalBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Hovered", hoveredBackgroundBrush, hoveredForegroundBrush, hoveredBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Pressed", pressedBackgroundBrush, pressedForegroundBrush, pressedBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Active", activeBackgroundBrush, activeForegroundBrush, activeBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Focused", focusedBackgroundBrush, focusedForegroundBrush, focusedBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("ActiveHovered", activeHoveredBackgroundBrush, activeHoveredForegroundBrush, activeHoveredBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("MidiLearn", midiLearnBackgroundBrush, midiLearnForegroundBrush, midiLearnBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush));
        Default.GetBrushVisualStateGroups().push_back(visualStateGroup);

        //******************************************************************************

        //******************************************************************************

        visualStateGroup = new BrushVisualStateGroup("Switch");
        visualStateGroup->AddState(new BrushVisualState("Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Normal", normalBackgroundBrush, normalForegroundBrush, normalBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Hovered", hoveredBackgroundBrush, hoveredForegroundBrush, hoveredBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Pressed", pressedBackgroundBrush, pressedForegroundBrush, pressedBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Active", activeBackgroundBrush, activeForegroundBrush, activeBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Focused", focusedBackgroundBrush, focusedForegroundBrush, focusedBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("ActiveHovered", activeHoveredBackgroundBrush, activeHoveredForegroundBrush, activeHoveredBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("MidiLearn", midiLearnBackgroundBrush, midiLearnForegroundBrush, midiLearnBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush));
        Default.GetBrushVisualStateGroups().push_back(visualStateGroup);

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

        visualStateGroup = new BrushVisualStateGroup("ListItem");
        visualStateGroup->AddState(new BrushVisualState("Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Normal", normalBackgroundBrush, normalForegroundBrush, normalBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Hovered", hoveredBackgroundBrush, hoveredForegroundBrush, hoveredBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Pressed", pressedBackgroundBrush, pressedForegroundBrush, pressedBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Active", activeBackgroundBrush, activeForegroundBrush, activeBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Focused", focusedBackgroundBrush, focusedForegroundBrush, focusedBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("ActiveHovered", activeHoveredBackgroundBrush, activeHoveredForegroundBrush, activeHoveredBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("MidiLearn", midiLearnBackgroundBrush, midiLearnForegroundBrush, midiLearnBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush));
        Default.GetBrushVisualStateGroups().push_back(visualStateGroup);

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

        visualStateGroup = new BrushVisualStateGroup("HeaderButton");
        visualStateGroup->AddState(new BrushVisualState("Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Normal", normalBackgroundBrush, normalForegroundBrush, normalBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Hovered", hoveredBackgroundBrush, hoveredForegroundBrush, hoveredBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Pressed", pressedBackgroundBrush, pressedForegroundBrush, pressedBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Active", activeBackgroundBrush, activeForegroundBrush, activeBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Focused", focusedBackgroundBrush, focusedForegroundBrush, focusedBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("ActiveHovered", activeHoveredBackgroundBrush, activeHoveredForegroundBrush, activeHoveredBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("MidiLearn", midiLearnBackgroundBrush, midiLearnForegroundBrush, midiLearnBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush));
        Default.GetBrushVisualStateGroups().push_back(visualStateGroup);

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

        visualStateGroup = new BrushVisualStateGroup("TextBox");
        visualStateGroup->AddState(new BrushVisualState("Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Normal", normalBackgroundBrush, normalForegroundBrush, normalBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Hovered", hoveredBackgroundBrush, hoveredForegroundBrush, hoveredBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Focused", focusedBackgroundBrush, focusedForegroundBrush, focusedBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Error", errorBackgroundBrush, errorForegroundBrush, errorBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush));
        Default.GetBrushVisualStateGroups().push_back(visualStateGroup);

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

        visualStateGroup = new BrushVisualStateGroup("Container");
        visualStateGroup->AddState(new BrushVisualState("Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Normal", normalBackgroundBrush, normalForegroundBrush, normalBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("MidiLearn", midiLearnBackgroundBrush, midiLearnForegroundBrush, midiLearnBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush));
        Default.GetBrushVisualStateGroups().push_back(visualStateGroup);

        //******************************************************************************

        //******************************************************************************

        visualStateGroup = new BrushVisualStateGroup("PropertyItem");
        visualStateGroup->AddState(new BrushVisualState("Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Normal", normalBackgroundBrush, normalForegroundBrush, normalBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Hovered", hoveredBackgroundBrush, hoveredForegroundBrush, hoveredBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush));
        Default.GetBrushVisualStateGroups().push_back(visualStateGroup);

        //******************************************************************************

        //******************************************************************************

        SolidColorBrush *cardBackgroundBrush = BrushPool::GetSolidColorBrush(0x602B2B2B);
        SolidColorBrush *cardForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        SolidColorBrush *cardBorderBrush = BrushPool::GetSolidColorBrush(0xFF424242);

        visualStateGroup = new BrushVisualStateGroup("Page");
        visualStateGroup->AddState(new BrushVisualState("Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Normal", cardBackgroundBrush, cardForegroundBrush, cardBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("MidiLearn", midiLearnBackgroundBrush, midiLearnForegroundBrush, midiLearnBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush));
        Default.GetBrushVisualStateGroups().push_back(visualStateGroup);

        //******************************************************************************

        //******************************************************************************

        visualStateGroup = new BrushVisualStateGroup("Card");
        visualStateGroup->AddState(new BrushVisualState("Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Normal", cardBackgroundBrush, cardForegroundBrush, cardBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("MidiLearn", midiLearnBackgroundBrush, midiLearnForegroundBrush, midiLearnBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush));
        Default.GetBrushVisualStateGroups().push_back(visualStateGroup);

        //******************************************************************************

        //******************************************************************************

        visualStateGroup = new BrushVisualStateGroup("List");
        visualStateGroup->AddState(new BrushVisualState("Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Normal", normalBackgroundBrush, normalForegroundBrush, normalBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("MidiLearn", midiLearnBackgroundBrush, midiLearnForegroundBrush, midiLearnBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush));
        Default.GetBrushVisualStateGroups().push_back(visualStateGroup);

        //******************************************************************************

        //******************************************************************************

        visualStateGroup = new BrushVisualStateGroup("GridSplitter");
        visualStateGroup->AddState(new BrushVisualState("Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Normal", normalBackgroundBrush, normalForegroundBrush, normalBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Hovered", hoveredBackgroundBrush, hoveredForegroundBrush, hoveredBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush));
        Default.GetBrushVisualStateGroups().push_back(visualStateGroup);

        //******************************************************************************

        //******************************************************************************

        visualStateGroup = new BrushVisualStateGroup("Header");
        visualStateGroup->AddState(new BrushVisualState("Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Normal", normalBackgroundBrush, normalForegroundBrush, normalBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush));
        Default.GetBrushVisualStateGroups().push_back(visualStateGroup);

        //******************************************************************************

        //******************************************************************************

        SolidColorBrush *mainMenuBackgroundBrush = BrushPool::GetSolidColorBrush(0x102B2B2B);
        SolidColorBrush *mainMenuForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        SolidColorBrush *mainMenuBorderBrush = BrushPool::GetSolidColorBrush(0xFF424242);

        visualStateGroup = new BrushVisualStateGroup("MainMenu");
        visualStateGroup->AddState(new BrushVisualState("Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Normal", mainMenuBackgroundBrush, mainMenuForegroundBrush, mainMenuBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush));
        Default.GetBrushVisualStateGroups().push_back(visualStateGroup);

        //******************************************************************************

        //******************************************************************************

        visualStateGroup = new BrushVisualStateGroup("MainMenuContent");
        visualStateGroup->AddState(new BrushVisualState("Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Normal", normalBackgroundBrush, normalForegroundBrush, normalBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush));
        Default.GetBrushVisualStateGroups().push_back(visualStateGroup);

        //******************************************************************************

        //******************************************************************************

        activeBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF7160E8);

        visualStateGroup = new BrushVisualStateGroup("ProgressBar");
        visualStateGroup->AddState(new BrushVisualState("Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Normal", normalBackgroundBrush, activeBackgroundBrush, normalBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush));
        Default.GetBrushVisualStateGroups().push_back(visualStateGroup);

        //******************************************************************************

        //******************************************************************************

        activeBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF494949);

        normalBackgroundBrush = BrushPool::GetSolidColorBrush(0x00FFFFFF);
        normalForegroundBrush = BrushPool::GetSolidColorBrush(0x70FFFFFF);
        normalBorderBrush = BrushPool::GetSolidColorBrush(0x00000000);

        visualStateGroup = new BrushVisualStateGroup("ScrollBar");
        visualStateGroup->AddState(new BrushVisualState("Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Normal", normalBackgroundBrush, normalForegroundBrush, normalBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Hovered", hoveredBackgroundBrush, hoveredForegroundBrush, hoveredBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("MidiLearn", midiLearnBackgroundBrush, midiLearnForegroundBrush, midiLearnBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush));
        Default.GetBrushVisualStateGroups().push_back(visualStateGroup);

        //******************************************************************************

        //******************************************************************************

        visualStateGroup = new BrushVisualStateGroup("Slider");
        visualStateGroup->AddState(new BrushVisualState("Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Normal", normalBackgroundBrush, normalForegroundBrush, normalBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush));
        Default.GetBrushVisualStateGroups().push_back(visualStateGroup);

        //******************************************************************************

        //******************************************************************************

        visualStateGroup = new BrushVisualStateGroup("StatusBar");
        visualStateGroup->AddState(new BrushVisualState("Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Normal", normalBackgroundBrush, normalForegroundBrush, normalBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush));
        Default.GetBrushVisualStateGroups().push_back(visualStateGroup);

        //******************************************************************************

        //******************************************************************************

        normalBackgroundBrush = BrushPool::GetSolidColorBrush(0xFF161616);
        normalForegroundBrush = BrushPool::GetSolidColorBrush(0xFFF1F1F1);
        normalBorderBrush = BrushPool::GetSolidColorBrush(0xFF3F3F3F);

        visualStateGroup = new BrushVisualStateGroup("ToolTip");
        visualStateGroup->AddState(new BrushVisualState("Normal", normalBackgroundBrush, normalForegroundBrush, normalBorderBrush));
        Default.GetBrushVisualStateGroups().push_back(visualStateGroup);
    }
} // namespace xit::Drawing