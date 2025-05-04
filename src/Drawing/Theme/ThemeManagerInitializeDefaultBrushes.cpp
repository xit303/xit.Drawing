#include <Drawing/Theme/ThemeManager.h>
#include <Drawing/Brushes/ImageBrush.h>

namespace xit::Drawing
{

    void ThemeManager::InitializeDefaultBrushes()
    {
        BrushBase *imageBackgroundBrush = new ImageBrush("Resources/Images/Background/Background1.jpg");

        BrushBase *disabledBackgroundBrush = new SolidColorBrush(0x3FCCCCCC);
        BrushBase *disabledForegroundBrush = new SolidColorBrush(0xFF808080);
        BrushBase *disabledBorderBrush = new SolidColorBrush(0x5FCCCCCC);

        BrushBase *normalBackgroundBrush = new SolidColorBrush(0xFF7160E8);
        BrushBase *normalForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        BrushBase *normalBorderBrush = new SolidColorBrush(0x7F7160E8);

        BrushBase *hoveredBackgroundBrush = new SolidColorBrush(0xFF4b39cf);
        BrushBase *hoveredForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        BrushBase *hoveredBorderBrush = new SolidColorBrush(0xFF9E9E9E);

        BrushBase *pressedBackgroundBrush = new SolidColorBrush(0xFF343434);
        BrushBase *pressedForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        BrushBase *pressedBorderBrush = new SolidColorBrush(0xFF877EC3);

        BrushBase *activeBackgroundBrush = new SolidColorBrush(0xFF494949);
        BrushBase *activeForegroundBrush = new SolidColorBrush(0xFFFFFFFF);
        BrushBase *activeBorderBrush = new SolidColorBrush(0xFF7160E8);

        BrushBase *focusedBackgroundBrush = new SolidColorBrush(0xFF7160E8);
        BrushBase *focusedForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        BrushBase *focusedBorderBrush = new SolidColorBrush(0xFFF1F1F1);

        BrushBase *activeHoveredBackgroundBrush = new SolidColorBrush(0xFF494949);
        BrushBase *activeHoveredForegroundBrush = new SolidColorBrush(0xFFFFFFFF);
        BrushBase *activeHoveredBorderBrush = new SolidColorBrush(0xFF8E8E8E);

        BrushBase *midiLearnBackgroundBrush = new SolidColorBrush(0xFF2B2B2B);
        BrushBase *midiLearnForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        BrushBase *midiLearnBorderBrush = new SolidColorBrush(0x00424242);

        BrushBase *errorBackgroundBrush = new SolidColorBrush(0xFF2B2B2B);
        BrushBase *errorForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        BrushBase *errorBorderBrush = new SolidColorBrush(0xFFFF0000);

        BrushBase *highlightBackgroundBrush = new SolidColorBrush(0xFF2B2B2B);
        BrushBase *highlightForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        BrushBase *highlightBorderBrush = new SolidColorBrush(0xFFFFFF00);

        BrushVisualStateGroup *visualStateGroup;

        //******************************************************************************

        //******************************************************************************

        visualStateGroup = new BrushVisualStateGroup("Window");
        visualStateGroup->AddState(new BrushVisualState("Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Normal", imageBackgroundBrush, normalForegroundBrush, new SolidColorBrush(0xFF4C4C4C)));
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
        visualStateGroup->AddState(new BrushVisualState("Disabled", new SolidColorBrush(0x0AFFFFFF), disabledForegroundBrush, new SolidColorBrush(0x0A4C4C4C)));
        visualStateGroup->AddState(new BrushVisualState("Normal", new SolidColorBrush(0xD71B2833), normalForegroundBrush, new SolidColorBrush(0xFF4C4C4C)));
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

        disabledBackgroundBrush = new SolidColorBrush(0x3FCCCCCC);
        disabledForegroundBrush = new SolidColorBrush(0xFF808080);
        disabledBorderBrush = new SolidColorBrush(0x5FCCCCCC);

        normalBackgroundBrush = new SolidColorBrush(0x7F2B2B2B);
        normalForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        normalBorderBrush = new SolidColorBrush(0xFF424242);

        hoveredBackgroundBrush = new SolidColorBrush(0xFF333333);
        hoveredForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        hoveredBorderBrush = new SolidColorBrush(0xFF9E9E9E);

        pressedBackgroundBrush = new SolidColorBrush(0xFF343434);
        pressedForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        pressedBorderBrush = new SolidColorBrush(0xFF877EC3);

        activeBackgroundBrush = new SolidColorBrush(0xFF494949);
        activeForegroundBrush = new SolidColorBrush(0xFFFFFFFF);
        activeBorderBrush = new SolidColorBrush(0xFF7160E8);

        focusedBackgroundBrush = new SolidColorBrush(0xFF494949);
        focusedForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        focusedBorderBrush = new SolidColorBrush(0xFF7160E8);

        activeHoveredBackgroundBrush = new SolidColorBrush(0xFF494949);
        activeHoveredForegroundBrush = new SolidColorBrush(0xFFFFFFFF);
        activeHoveredBorderBrush = new SolidColorBrush(0xFF8E8E8E);

        midiLearnBackgroundBrush = new SolidColorBrush(0xFF2B2B2B);
        midiLearnForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        midiLearnBorderBrush = new SolidColorBrush(0x00424242);

        errorBackgroundBrush = new SolidColorBrush(0xFF2B2B2B);
        errorForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        errorBorderBrush = new SolidColorBrush(0xFFFF0000);

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

        activeBackgroundBrush = new SolidColorBrush(0xFF7160E8);
        activeForegroundBrush = new SolidColorBrush(0xFFFFFFFF);
        activeBorderBrush = new SolidColorBrush(0xFF7160E8);

        focusedBackgroundBrush = new SolidColorBrush(0xFF7160E8);
        focusedForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        focusedBorderBrush = new SolidColorBrush(0xFF7160E8);

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

        disabledBackgroundBrush = new SolidColorBrush(0xFF2B2B2B);
        disabledForegroundBrush = new SolidColorBrush(0xFF808080);
        disabledBorderBrush = new SolidColorBrush(0x5FCCCCCC);

        normalBackgroundBrush = new SolidColorBrush(0xFF2B2B2B);
        normalForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        normalBorderBrush = new SolidColorBrush(0xFF424242);

        hoveredBackgroundBrush = new SolidColorBrush(0x4AFFFFFF);
        hoveredForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        hoveredBorderBrush = new SolidColorBrush(0xFF9E9E9E);

        pressedBackgroundBrush = new SolidColorBrush(0xFF343434);
        pressedForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        pressedBorderBrush = new SolidColorBrush(0xFF877EC3);

        activeBackgroundBrush = new SolidColorBrush(0xFF7160E8);
        activeForegroundBrush = new SolidColorBrush(0xFFFFFFFF);
        activeBorderBrush = new SolidColorBrush(0xFF7160E8);

        focusedBackgroundBrush = new SolidColorBrush(0xFF7160E8);
        focusedForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        focusedBorderBrush = new SolidColorBrush(0xFF7160E8);

        activeHoveredBackgroundBrush = new SolidColorBrush(0xFF7160E8);
        activeHoveredForegroundBrush = new SolidColorBrush(0xFFFFFFFF);
        activeHoveredBorderBrush = new SolidColorBrush(0xFF8E8E8E);

        midiLearnBackgroundBrush = new SolidColorBrush(0xFF2B2B2B);
        midiLearnForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        midiLearnBorderBrush = new SolidColorBrush(0x00424242);

        errorBackgroundBrush = new SolidColorBrush(0xFF2B2B2B);
        errorForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        errorBorderBrush = new SolidColorBrush(0xFFFF0000);

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

        disabledBackgroundBrush = new SolidColorBrush(0xFF2B2B2B);
        disabledForegroundBrush = new SolidColorBrush(0xFF808080);
        disabledBorderBrush = new SolidColorBrush(0x5FCCCCCC);

        normalBackgroundBrush = new SolidColorBrush(0xFF2B2B2B);
        normalForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        normalBorderBrush = new SolidColorBrush(0xFF424242);

        hoveredBackgroundBrush = new SolidColorBrush(0xFF3B3B3B);
        hoveredForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        hoveredBorderBrush = new SolidColorBrush(0xFF9E9E9E);

        pressedBackgroundBrush = new SolidColorBrush(0xFF343434);
        pressedForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        pressedBorderBrush = new SolidColorBrush(0xFF877EC3);

        activeBackgroundBrush = new SolidColorBrush(0xFF2B2B2B);
        activeForegroundBrush = new SolidColorBrush(0xFFFFFFFF);
        activeBorderBrush = new SolidColorBrush(0xFF7160E8);

        focusedBackgroundBrush = new SolidColorBrush(0xFF2B2B2B);
        focusedForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        focusedBorderBrush = new SolidColorBrush(0xFF7160E8);

        activeHoveredBackgroundBrush = new SolidColorBrush(0x1AFFFFFF);
        activeHoveredForegroundBrush = new SolidColorBrush(0xFFFFFFFF);
        activeHoveredBorderBrush = new SolidColorBrush(0xFF7160E8);

        midiLearnBackgroundBrush = new SolidColorBrush(0xFF2B2B2B);
        midiLearnForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        midiLearnBorderBrush = new SolidColorBrush(0x00424242);

        errorBackgroundBrush = new SolidColorBrush(0xFF2B2B2B);
        errorForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        errorBorderBrush = new SolidColorBrush(0xFFFF0000);

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

        disabledBackgroundBrush = new SolidColorBrush(0x7F2B2B2B);
        disabledForegroundBrush = new SolidColorBrush(0xFF808080);
        disabledBorderBrush = new SolidColorBrush(0x5FCCCCCC);

        normalBackgroundBrush = new SolidColorBrush(0xFF2B2B2B);
        normalForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        normalBorderBrush = new SolidColorBrush(0xFF444444); // 0xFF424242

        hoveredBackgroundBrush = new SolidColorBrush(0xFF2B2B2B);
        hoveredForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        hoveredBorderBrush = new SolidColorBrush(0xFF9E9E9E);

        pressedBackgroundBrush = new SolidColorBrush(0xFF343434);
        pressedForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        pressedBorderBrush = new SolidColorBrush(0x00424242);

        activeBackgroundBrush = new SolidColorBrush(0xFF2B2B2B);
        activeForegroundBrush = new SolidColorBrush(0xFFFFFFFF);
        activeBorderBrush = new SolidColorBrush(0xFF7160E8);

        focusedBackgroundBrush = new SolidColorBrush(0xFF2B2B2B);
        focusedForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        focusedBorderBrush = new SolidColorBrush(0xFF7160E8);

        activeHoveredBackgroundBrush = new SolidColorBrush(0xFF2B2B2B);
        activeHoveredForegroundBrush = new SolidColorBrush(0xFFFFFFFF);
        activeHoveredBorderBrush = new SolidColorBrush(0xFF8E8E8E);

        midiLearnBackgroundBrush = new SolidColorBrush(0xFF2B2B2B);
        midiLearnForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        midiLearnBorderBrush = new SolidColorBrush(0x00424242);

        errorBackgroundBrush = new SolidColorBrush(0xFF2B2B2B);
        errorForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        errorBorderBrush = new SolidColorBrush(0xFFFF0000);

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

        disabledBackgroundBrush = new SolidColorBrush(0x3FCCCCCC);
        disabledForegroundBrush = new SolidColorBrush(0xFF808080);
        disabledBorderBrush = new SolidColorBrush(0x5FCCCCCC);

        normalBackgroundBrush = new SolidColorBrush(0xFF161616);
        normalForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        normalBorderBrush = new SolidColorBrush(0xFF3F3F3F);

        hoveredBackgroundBrush = new SolidColorBrush(0xFF2B2B2B);
        hoveredForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        hoveredBorderBrush = new SolidColorBrush(0xFF9E9E9E);

        pressedBackgroundBrush = new SolidColorBrush(0xFF343434);
        pressedForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        pressedBorderBrush = new SolidColorBrush(0x00424242);

        activeBackgroundBrush = new SolidColorBrush(0xFF494949);
        activeForegroundBrush = new SolidColorBrush(0xFFFFFFFF);
        activeBorderBrush = new SolidColorBrush(0xFF494949);

        focusedBackgroundBrush = new SolidColorBrush(0xFF2B2B2B);
        focusedForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        focusedBorderBrush = new SolidColorBrush(0x00424242);

        activeHoveredBackgroundBrush = new SolidColorBrush(0xFF494949);
        activeHoveredForegroundBrush = new SolidColorBrush(0xFFFFFFFF);
        activeHoveredBorderBrush = new SolidColorBrush(0xFF9E9E9E);

        midiLearnBackgroundBrush = new SolidColorBrush(0xFF2B2B2B);
        midiLearnForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        midiLearnBorderBrush = new SolidColorBrush(0x00424242);

        errorBackgroundBrush = new SolidColorBrush(0xFF2B2B2B);
        errorForegroundBrush = new SolidColorBrush(0xFFFF0000);
        errorBorderBrush = new SolidColorBrush(0xFFFF0000);

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

        SolidColorBrush *cardBackgroundBrush = new SolidColorBrush(0x602B2B2B);
        SolidColorBrush *cardForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        SolidColorBrush *cardBorderBrush = new SolidColorBrush(0xFF424242);

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

        SolidColorBrush *mainMenuBackgroundBrush = new SolidColorBrush(0x102B2B2B);
        SolidColorBrush *mainMenuForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        SolidColorBrush *mainMenuBorderBrush = new SolidColorBrush(0xFF424242);

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

        activeBackgroundBrush = new SolidColorBrush(0xFF7160E8);

        visualStateGroup = new BrushVisualStateGroup("ProgressBar");
        visualStateGroup->AddState(new BrushVisualState("Disabled", disabledBackgroundBrush, disabledForegroundBrush, disabledBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Normal", normalBackgroundBrush, activeBackgroundBrush, normalBorderBrush));
        visualStateGroup->AddState(new BrushVisualState("Highlight", highlightBackgroundBrush, highlightForegroundBrush, highlightBorderBrush));
        Default.GetBrushVisualStateGroups().push_back(visualStateGroup);

        //******************************************************************************

        //******************************************************************************

        activeBackgroundBrush = new SolidColorBrush(0xFF494949);

        normalBackgroundBrush = new SolidColorBrush(0x00FFFFFF);
        normalForegroundBrush = new SolidColorBrush(0x70FFFFFF);
        normalBorderBrush = new SolidColorBrush(0x00000000);

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

        normalBackgroundBrush = new SolidColorBrush(0xFF161616);
        normalForegroundBrush = new SolidColorBrush(0xFFF1F1F1);
        normalBorderBrush = new SolidColorBrush(0xFF3F3F3F);

        visualStateGroup = new BrushVisualStateGroup("ToolTip");
        visualStateGroup->AddState(new BrushVisualState("Normal", normalBackgroundBrush, normalForegroundBrush, normalBorderBrush));
        Default.GetBrushVisualStateGroups().push_back(visualStateGroup);
    }
} // namespace xit::Drawing