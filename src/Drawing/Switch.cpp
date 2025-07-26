#include <Drawing/Switch.h>

namespace xit::Drawing
{
    void Switch::SetVisualState(const std::string& value)
    {
        Container::SetVisualState(value);
        trackBorder.SetVisualState(value);
        //thumbBorder.SetVisualState(value);
        thumbBorder.SetBackground(trackBorder.GetForeground());
        //label.SetVisualState(value);
    }

    Switch::Switch()
    {
        SetHandleMouse(true);
        SetHandleKeyboard(true);
        SetCanActivate(true);
        SetCanDeactivate(true);
        SetCanFocus(true);
        SetClipToBounds(true);
        SetInheritForeground(true);

        SetColumns("*,Auto");
        SetRows("Auto,Auto");

        SetColumnSpacing(UIDefaults::ColumnSpacing);

        SetBackground(new SolidColorBrush(0x00000000));//(Color::Transparent));
        SetLayoutGroup("Switch");
        SetName("Switch");

        // label is the text of the switch
        // we place it at the bottom to be close to the description
        label.SetGrid(0, 0);
        label.SetName("SwitchLabel");
        AddChild(&label);

        // description is the part of the switch that describes the funtion of the switch
        // this should be aligned to the top to be close to the label above
        description.SetGrid(0, 1);
        description.SetFontSize(UIDefaults::SmallFontSize);
        description.SetName("SwitchDescription");
        AddChild(&description);

        trackBorder.SetGrid(1, 0, 1, 2);
        trackBorder.SetHandleMouse(false);
        trackBorder.SetPadding(2);
        trackBorder.SetHandleKeyboard(false);
        trackBorder.SetWidth(UIDefaults::DefaultItemHeight);
        trackBorder.SetHeight(UIDefaults::DefaultItemHeight >> 1);
        trackBorder.SetCornerRadius((double)(UIDefaults::DefaultItemHeight >> 3));
        trackBorder.SetBorderThickness(UIDefaults::DefaultBorderThickness);
        trackBorder.SetBrushGroup("Switch");
        trackBorder.SetName("SwitchTrackBorder");
        AddChild(&trackBorder);

        thumbBorder.SetGrid(1, 0, 1, 2);
        thumbBorder.SetHandleMouse(false);
        thumbBorder.SetHandleKeyboard(false);
        thumbBorder.SetWidth(UIDefaults::DefaultItemHeight >> 1);
        thumbBorder.SetCornerRadius((double)(UIDefaults::DefaultItemHeight >> 3));
        thumbBorder.SetBackground(trackBorder.GetForeground());
        thumbBorder.SetName("SwitchThumbBorder");
        trackBorder.SetContent(&thumbBorder);
    }

    Switch::Switch(const std::string& name, const std::string& defaultText)
        : Switch()
    {
        SetName(name);
        //SetDefaultText(defaultText);
    }

    Switch::Switch(const std::string& name, const std::string& defaultText, int column, int row)
        : Switch(name, defaultText)
    {
        SetGrid(column, row);
    }

    //******************************************************************************
    // Protected overrides
    //******************************************************************************

    void Switch::OnIsActiveChanged(EventArgs& e)
    {
        Container::OnIsActiveChanged(e);

        thumbBorder.SetHorizontalAlignment(GetIsActive() ? HorizontalAlignment::Right : HorizontalAlignment::Left);

        // TODO MidiCommander::SetCommandValue(this, IsActive ? 127 : 0);
    }

    void Switch::OnNameChanged(EventArgs& e)
    {
        Container::OnNameChanged(e);

        // if (!GetName().empty())
        // {
        //     SetTextSource(GetName());
        // }
    }

    //******************************************************************************
    // Public
    //******************************************************************************

    // void Switch::SetCommand(Command* command)
    // {

    // }

    // int Switch::GetCommandValue()
    // {
    //     return IsActive;
    // }

    // void Switch::SetCommandValue(int value)
    // {
    //     ////Syncronizer.Invoke(() =>
    //     //{
    //     //    Command* command = dynamic_cast<Command*>(value);

    //     //    if (value == nullptr || command)
    //     //    {
    //     //        if (command)
    //     //        {
    //     //            command->SetName(Name);
    //     //        }

    //     //        MidiCommander::SetCommandValue(this, IsActive ? 127 : 0);

    //     //        //midiMenuItem.IsMidiLearn = false;
    //     //    }
    //     //    else
    //     //    {
    //     //        if (Enabled)
    //     //        {
    //     //            bool isActive = false;

    //     //            bool* boolean = static_cast<bool*>(value);

    //     //            if (boolean)
    //     //            {
    //     //                isActive = *boolean;
    //     //            }
    //     //            else
    //     //            {
    //     //                int* integer = static_cast<int*>(value);

    //     //                if (integer)
    //     //                {
    //     //                    isActive = *integer != 0;
    //     //                }
    //     //            }

    //     //            SetIsActive(isActive);
    //     //        }
    //     //    }

    //     //    //midiMenuItem.SetMidiDeleteMenuItem();
    //     //}//);
    // }

}
