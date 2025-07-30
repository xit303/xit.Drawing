#pragma once

#include <Drawing/TextBox.h>
#include <Properties/MinMaxProperty.h>

namespace xit::Drawing
{
    class NumericTextBox : public TextBox, public Properties::MinMaxProperty
    {
    private:
        int step;
        // FloatSetting* valueSetting;

        // void ValueSetting_ValueChanged(float e)
        // {
        //     float newValue = valueSetting->Value();

        //     // does not trigger ValueChanged if value does not change
        //     SetValue(newValue);
        // }

    protected:
        virtual void OnValueChanged(float newValue) override
        {
            MinMaxProperty::OnValueChanged(newValue);

            // if (valueSetting != nullptr)
            // {
            //     valueSetting->SetValue(GetValue());
            // }

            size_t caretIndex = GetCaretIndex();
            SetText(std::to_string(GetValue()));
            SetCaretIndex(caretIndex);
        }

        void OnKeyDown(KeyEventArgs &e) override
        {
            if (e.Key == CKey::Up)
            {
                SetValue(GetValue() + static_cast<float>(step));

                e.Handled = true;
            }
            else if (e.Key == CKey::Down)
            {
                SetValue(GetValue() - static_cast<float>(step));

                e.Handled = true;
            }
            else if (e.Key == CKey::Enter)
            {
                SetValue(GetValue());

                e.Handled = true;

                ClearFocus();
            }
            else if (e.Key == CKey::Tab)
            {
                // on Tab we do not set Handled to true
                // because otherwise tab navigation no longer works

                SetValue(GetValue());
            }

            TextBox::OnKeyDown(e);
        }

        void OnTextChanged(TextChangedEventArgs &e) override
        {
            double value = atof(GetText().c_str());
            if (value || (GetText() == "0"))
            {
                if (GetIsError())
                {
                    SetIsError(false);
                }

                SetValue((float)value);

                e.Handled = true;
            }
            else
            {
                SetIsError(true);
            }

            TextBox::OnTextChanged(e);
        }

        void OnInputScroll(MouseEventArgs &e) override
        {
            if (GetIsFocused())
            {
                SetValue(e.WheelDelta > 0 ? GetValue() + static_cast<float>(step) : GetValue() - static_cast<float>(step));

                e.Handled = true;
            }

            TextBox::OnInputScroll(e);
        }

    public:
        // FloatSetting* ValueSetting() { return valueSetting; }
        // void SetValueSetting(FloatSetting* value)
        // {
        //     if (valueSetting != nullptr)
        //     {
        //         valueSetting->ValueChanged.Remove(&NumericTextBox::ValueSetting_ValueChanged, this);
        //     }

        //     valueSetting = value;

        //     if (valueSetting != nullptr)
        //     {
        //         SetValue(valueSetting->Value());
        //         valueSetting->ValueChanged.Add(&NumericTextBox::ValueSetting_ValueChanged, this);
        //         ValueSetting_ValueChanged(0);
        //     }
        // }

        int Step() { return step; }
        void Step(int value)
        {
            if (step != value)
            {
                step = value;
            }
        }

        NumericTextBox()
        {
            // valueSetting = nullptr;
            SetLayoutGroup("CenteredTextBox");
            step = 1;
        }
        NumericTextBox(float min, float max, float value)
            : MinMaxProperty(min, max, value)
        {
            // valueSetting = nullptr;
            SetLayoutGroup("CenteredTextBox");
            step = 1;
        }
        NumericTextBox(float min, float max, float value, int column, int row)
            : NumericTextBox(min, max, value)
        {
            SetGrid(column, row);
        }
    };
}
