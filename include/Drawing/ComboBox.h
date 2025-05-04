#pragma once

#include <Drawing/Container.h>
#include <Drawing/TextBox.h>
#include <Drawing/Buttons/ButtonBase.h>
#include <Drawing/ListView.h>

// #include "../Collections/NotifyCollectionChangedEventHandler.h"

namespace xit::Drawing
{
    class ComboBox : public Container
    {
    private:
        TextBox textBox;
        ButtonBase ComboBoxButton;
        ButtonBase expandButton;

        // Popup popup;
        ListView listView;

        bool isSelectionChanging;

        void *storedSelectedValue;

        bool isEditable;

        std::vector<std::string> *items;

    public:
        inline bool GetIsError() const override { return textBox.GetIsError(); }
        inline void SetIsError(bool value) override { textBox.SetIsError(value); }

        inline bool IsEditable() { return isEditable; }
        void SetIsEditable(bool value)
        {
            if (isEditable != value)
            {
                isEditable = value;

                ComboBoxButton.SetText(isEditable ? std::string() : GetText());
                ComboBoxButton.SetVisibility(isEditable ? Visibility::Collapsed : Visibility::Visible);

                textBox.SetVisibility(isEditable ? Visibility::Visible : Visibility::Hidden);
                textBox.SetBorderThickness(isEditable ? 1 : 0);

                // expandButton.IsHitTestVisible = isEditable;

                if (isEditable)
                {
                    // storedSelectedValue = listView.SelectedValue;
                }
            }
        }

        __always_inline bool GetCanSort() { return listView.GetCanSort(); }
        __always_inline void SetCanSort(bool value) { listView.SetCanSort(value); }

        __always_inline const std::string &GetText() const { return textBox.GetText(); }
        __always_inline void SetText(const std::string &value) { textBox.SetText(value); }

        __always_inline const std::string &HintText() const { return textBox.GetHintText(); }
        __always_inline void SetHintText(const std::string &value) { textBox.SetHintText(value); }

        // __always_inline const std::string &HintTextSource() const { return textBox.GetHintTextSource(); }
        // __always_inline void SetHintTextSource(const std::string &value) { textBox.SetHintTextSource(value); }

        __always_inline HorizontalAlignment GetTextAlignment() const { return textBox.GetTextAlignment(); }
        void SetTextAlignment(const HorizontalAlignment &value)
        {
            SetHorizontalContentAlignment(value);
            textBox.SetTextAlignment(value);
        }

        __always_inline const std::list<std::string> *GetItems() { return listView.GetItems(); }
        __always_inline void SetItems(std::list<std::string> *value) { listView.SetItems(value); }

        __always_inline int GetSelectedIndex() const { return listView.GetSelectedIndex(); }
        inline void SetSelectedIndex(int value) { listView.SetSelectedIndex(value); }

        __always_inline std::string GetSelectedValue() { return listView.GetSelectedValue(); }
        inline void SetSelectedValue(const std::string &value) { listView.SetSelectedValue(value); }

        // inline StringSetting *GetSelectedValueSetting() { return listView.GetSelectedValueSetting(); }
        // inline void SetSelectedValueSetting(StringSetting *value) { listView.SetSelectedValueSetting(value); }

        Event<const std::string &> SelectionChanged;
        Event<TextChangedEventArgs&> TextChanged;

        ComboBox();

    private:
        void ListView_ChildrenChanged(Visual &content, EventArgs &e);

        void ComboBoxButton_InputScroll(InputContent &sender, MouseEventArgs &e);

        void ComboBoxButton_ActiveChanged(IsActiveProperty &sender, EventArgs &e);

        void Popup_Closed(EventArgs &e);

        // void Popup_MouseUp(MouseEventArgs& e);

        void SelectedValueSetting_ValueChanged(const std::string &newValue);

        void ListView_SelectionChanged(const std::string &selectedValue);

        void TextBox_TextChanged(TextChangedEventArgs &e);
        void TextBox_KeyDown(InputContent &sender, KeyEventArgs &e);

        void HandleScroll(MouseEventArgs &e);

    protected:
        void OnChildAdded(Visual &content, EventArgs &e) override;

        int OnMeasureWidth(int available) override;
        int OnMeasureHeight(int available) override;

        void OnInputScroll(MouseEventArgs &e) override;

        ////protected override void OnRenderSizeChanged(SizeChangedInfo sizeInfo);

        void OnGotKeyboardFocus(EventArgs &e) override;

        void OnRender() override;

        virtual void OnSelectionTextChanged();
        virtual void OnSelectionChanged(const std::string &selectedValue);
    };
}
using namespace xit::Drawing;
