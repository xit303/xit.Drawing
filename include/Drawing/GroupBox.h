#pragma once

#include "HeaderedContainer.h"
#include "Label.h"

namespace xit::Drawing
{
    class GroupBox : public HeaderedContainer
    {
    private:
        Container headerBorder;
        Label *headerText;

    protected:
        void OnNameChanged(EventArgs &e) override
        {
            HeaderedContainer::OnNameChanged(e);

            headerText->SetName(GetName() + "HeaderLabel");
        }

    public:
        inline void SetText(const std::string &value) { headerText->SetText(value); }
        // inline void SetTextSource(const std::string& value) { headerText->SetTextSource(value); }
        // inline void SetDefaultText(const std::string& value) { headerText->SetDefaultText(value); }

        Visual *HeaderContent() { return headerBorder.GetChildCount() > 1 ? headerBorder.GetChildAt(1) : nullptr; }
        void SetHeaderContent(Visual *value)
        {
            if (headerBorder.GetChildCount() > 1)
            {
                headerBorder.RemoveChildAt(1);
            }

            value->SetColumn(1);
            headerBorder.AddChild(value);
        }

        GroupBox()
        {
            headerText = nullptr;

            SetBrushGroup("Card");
            SetLayoutGroup("Card");

            headerBorder.SetBrushGroup("Header");
            headerBorder.SetLayoutGroup("Header");
            headerBorder.SetColumns("*,Auto");
            headerBorder.SetRow(0);
            SetHeader(&headerBorder);

            headerBorder.AddChild(headerText = Label::CreateHeader());

            SetRowSpacing(UIDefaults::RowSpacing);
        }
    };
}
