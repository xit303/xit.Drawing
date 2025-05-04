#include <Drawing/ComboBox.h>

namespace xit::Drawing
{
    ComboBox::ComboBox()
    {
        isEditable = false;
        isSelectionChanging = false;
        storedSelectedValue = nullptr;
        items = nullptr;

        SetBrushGroup("ComboBox");
        SetLayoutGroup("ComboBox");

        SetCanFocus(true);
        SetHandleMouse(true);

        SetRows("*,Auto");

        ComboBoxButton.SetBrushGroup("ComboBoxButton");
        ComboBoxButton.SetLayoutGroup("ComboBoxButton");
        ComboBoxButton.SetCanActivate(true);
        ComboBoxButton.IsActiveChanged.Add(&ComboBox::ComboBoxButton_ActiveChanged, this);
        ComboBoxButton.InputScroll.Add(&ComboBox::ComboBoxButton_InputScroll, this);
        AddChild(&ComboBoxButton);

        textBox.SetHeight(-1);
        textBox.SetBorderThickness(0);
        //textBox.SetMargin(ComboBoxButton.BorderThickness)
        textBox.SetVisibility(Visibility::Hidden);
        textBox.KeyDown.Add(&ComboBox::TextBox_KeyDown, this);
        textBox.TextChanged.Add(&ComboBox::TextBox_TextChanged, this);
        textBox.InputScroll.Add(&ComboBox::ComboBoxButton_InputScroll, this);
        AddChild(&textBox);

        expandButton.SetBrushGroup("IconButton");
        expandButton.SetLayoutGroup("ButtonInContainer");
        expandButton.SetUniformImageSize(UIDefaults::ButtonImageHeight);
        expandButton.SetShowImage(true);
        expandButton.SetShowLabel(false);
        expandButton.SetImageSource("Resources/Images/Buttons/ExpanderClosed.png");
        expandButton.SetCanActivate(true);
        expandButton.SetVisibility(Visibility::Collapsed);
        expandButton.IsActiveChanged.Add(&ComboBox::ComboBoxButton_ActiveChanged, this);
        AddChild(&expandButton);

        //popup.SetMaxHeight(UIDefaults::TextBoxHeight * 10);
        //popup.SetVisibility(Visibility::Collapsed);
        //popup.SetGrid(0, 1, 2, 1);
        //popup.Closed += Popup_Closed;
        //popup.InputReleased += Popup_MouseUp;
        //AddChild(popup);

        listView.ChildAdded.Add(&ComboBox::ListView_ChildrenChanged, this);
        listView.ChildRemoved.Add(&ComboBox::ListView_ChildrenChanged, this);
        listView.SelectionChanged.Add(&ComboBox::ListView_SelectionChanged, this);
        //popup.AddChild(listView);
    }

    //******************************************************************************
    // Private
    //******************************************************************************

    void ComboBox::ListView_ChildrenChanged(Visual& content, EventArgs& e)
    {
        expandButton.SetVisibility(listView.GetChildCount() > 1 ? Visibility::Visible : Visibility::Collapsed);
    }

    void ComboBox::ComboBoxButton_InputScroll(InputContent& sender, MouseEventArgs& e)
    {
        HandleScroll(e);
    }

    void ComboBox::ComboBoxButton_ActiveChanged(IsActiveProperty& sender, EventArgs& e)
    {
        //popup.IsOpen = isEditable ? expandButton.IsActive : ComboBoxButton.IsActive;
        listView.ScrollItemIntoView();
    }

    void ComboBox::Popup_Closed(EventArgs& e)
    {
        // this must be done to prevent repopping up
        // if we click the button, on mouse down is fired and
        // popup looses focus, closes and calls this method/event.
        // if we now mouse up on the button we immediately
        // reactivate the button and it does not close.
        // if comboBoxButton.IsMouseOver we know that we actually press the button.

        if (isEditable)
        {
            if (!expandButton.IsMouseOver)
            {
                expandButton.SetIsActive(false);
            }
        }
        else
        {
            if (!ComboBoxButton.IsMouseOver)
            {
                ComboBoxButton.SetIsActive(false);
            }
        }
    }

    //void ComboBox::Popup_MouseUp(MouseEventArgs& e)
    //{
    //    popup.IsOpen = false;
    //}

    // void ComboBox::SelectedValueSetting_ValueChanged(const std::string& newValue)
    // {
    //     std::string selectedValue = listView.GetSelectedValue();

    //     if (listView.GetSelectedValueSetting()->Value() != selectedValue)
    //     {
    //         listView.SetSelectedValue(listView.GetSelectedValueSetting()->Value());
    //         SetText(listView.GetSelectedValueSetting()->Value());
    //     }

    //     // always update button content
    //     ComboBoxButton.SetText(isEditable ? std::string() : Text);
    // }

    void ComboBox::ListView_SelectionChanged(const std::string& selectedValue)
    {
        isSelectionChanging = true;
        SetText(selectedValue);
        isSelectionChanging = false;

        ComboBoxButton.SetText(isEditable ? std::string() : GetText());
        ComboBoxButton.SetIsActive(false);

        // if ((listView.GetSelectedValueSetting() != nullptr) && (!Text.empty()))
        // {
        //     listView.GetSelectedValueSetting()->SetValue(Text);
        // }

        SelectionChanged(selectedValue);
        OnSelectionChanged(selectedValue);
    }

    void ComboBox::TextBox_TextChanged(TextChangedEventArgs& e)
    {
        // if (isSelectionChanging || listView.GetItems()->Contains(GetText()))
        // {
        //     if (listView.GetSelectedValue().empty() || (listView.GetSelectedValue() != GetText()))
        //     {
        //         listView.SetSelectedValue(GetText());
        //     }
        // }
        // else if (!isEditable)
        // {
        //     //if (listView.SelectedItem is string)
        //     {
        //         listView.SetSelectedValue(std::string());
        //     }
        //     //else*/
        //     {
        //         //listView.SetSelectedValue(Text);
        //         //ComboBoxButton.SetText(Text);
        //     }
        // }

        TextChanged(e);
    }
    void ComboBox::TextBox_KeyDown(InputContent& sender, KeyEventArgs& e)
    {
        OnKeyDown(e);
        KeyDown(*this, e);
    }

    void ComboBox::HandleScroll(MouseEventArgs& e)
    {
        //if (ComboBoxButton.IsMouseOver)
        {
            int selectedIndex = listView.GetSelectedIndex();
            if (selectedIndex == -1)
                return;

            if (e.WheelDelta > 0)
            {
                if (selectedIndex > 0)
                {
                    listView.SetSelectedIndex(selectedIndex - 1);
                }
            }
            else
            {
                if ((size_t)selectedIndex < listView.GetItems()->size() - 1)
                {
                    listView.SetSelectedIndex(selectedIndex + 1);
                }
            }

            e.Handled = true;
        }
    }

    //******************************************************************************
    // Protected overrides
    //******************************************************************************

    void ComboBox::OnChildAdded(Visual& content, EventArgs& e)
    {
        Container::OnChildAdded(content, e);

        if (content == &textBox)
        {
            textBox.SetTextAlignment(GetTextAlignment());
        }
    }

    int ComboBox::OnMeasureWidth(int available)
    {
        if (GetHorizontalAlignment() == HorizontalAlignment::Stretch)
            return available;

        int width = textBox.MeasureWidth(available);
        int width2 = ComboBoxButton.MeasureWidth(available);
        int width3 = expandButton.MeasureWidth(available);

        width = width2 > width ? width2 : width;

        return width3 > width ? width3 : width;
    }
    int ComboBox::OnMeasureHeight(int available)
    {
        if (GetVerticalAlignment() == VerticalAlignment::Stretch)
            return available;

        int height = textBox.MeasureHeight(available);
        int height2 = ComboBoxButton.MeasureHeight(available);
        int height3 = expandButton.MeasureHeight(available);

        height = height2 > height ? height2 : height;

        return height3 > height ? height3 : height;
    }

    void ComboBox::OnInputScroll(MouseEventArgs& e)
    {
        HandleScroll(e);
        Container::OnInputScroll(e);
    }

    ////protected override void OnRenderSizeChanged(SizeChangedInfo sizeInfo)
    ////{
    ////    base.OnRenderSizeChanged(sizeInfo);
    ////    popup.MinWidth = sizeInfo.NewSize.Width;
    ////}

    void ComboBox::OnGotKeyboardFocus(EventArgs& e)
    {
        if (textBox.GetIsVisible())
        {
            textBox.Focus();
            e.Handled = true;
        }
        Container::OnGotKeyboardFocus(e);
    }

    void ComboBox::OnRender()
    {
        Container::OnRender();
    }

    //******************************************************************************
    // Protected
    //******************************************************************************

    void ComboBox::OnSelectionTextChanged() { }
    void ComboBox::OnSelectionChanged(const std::string& selectedValue) { }
}
