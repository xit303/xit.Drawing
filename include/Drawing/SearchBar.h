#pragma once

#include "Image.h"
#include "TextBox.h"

namespace xit::Drawing
{
    class SearchBar : public Container
    {
    private:
        Image magnifierImage;
        TextBox searchTextBox;

        // StringSetting *textSetting;
        std::vector<std::string> searchPatterns;

        void TextSetting_ValueChanged(const std::string &newValue)
        {
            searchTextBox.SetText(newValue);
        }

        void SearchTextBox_TextChanged(TextChangedEventArgs &e)
        {
            searchPatterns = StringHelper::Split(GetText(), ' ');

            EventArgs ev;
            SearchTextChanged(ev);

            // if (textSetting != nullptr)
            // {
            //     textSetting->SetValue(Text);
            // }
        }

    public:
        const std::string &GetText() { return searchTextBox.GetText(); }

        const std::vector<std::string> &SearchPatterns = searchPatterns;

        // StringSetting* TextSetting() { return textSetting; }
        // void SetTextSetting(StringSetting* value)
        // {
        //     if (textSetting != nullptr)
        //     {
        //         textSetting->ValueChanged.Remove(&SearchBar::TextSetting_ValueChanged, this);
        //     }

        //     textSetting = value;

        //     if (textSetting != nullptr)
        //     {
        //         textSetting->ValueChanged.Add(&SearchBar::TextSetting_ValueChanged, this);
        //     }

        //     TextSetting_ValueChanged(textSetting ? textSetting->Value() : std::string());
        // }

        void SetHintText(const std::string &value) { searchTextBox.SetHintText(value); }

        Event<EventArgs &> SearchTextChanged;

        SearchBar()
        {
            SetLayoutGroup("SearchBar");

            SetColumns("Auto,*");
            SetRows("*");
            SetColumnSpacing(UIDefaults::HalfColumnSpacing);

            magnifierImage.SetImageSource("Resources/Images/Magnifier.png");
            magnifierImage.SetHeight(UIDefaults::DefaultItemHeight);
            magnifierImage.SetHorizontalAlignment(HorizontalAlignment::Left); // TODO if we do not set it to lef Visual::OnMeasureWidth will occupy the whole width because of Stretch
            magnifierImage.SetGrid(0, 0);
            AddChild(&magnifierImage);

            searchTextBox.SetHintText("Start typing to search...");
            searchTextBox.SetGrid(1, 0);
            searchTextBox.TextChanged.Add(&SearchBar::SearchTextBox_TextChanged, this);
            AddChild(&searchTextBox);
        }
    };
}
