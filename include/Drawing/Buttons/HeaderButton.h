#pragma once

#include <Drawing/Buttons/ButtonBase.h>

namespace xit::Drawing
{
    class HeaderButton : public ButtonBase
    {
    private:
        bool isExpandable;
        Visual *headerContent;

    protected:
        void OnColumnsChanged(EventArgs &e) override
        {
            ButtonBase::OnColumnsChanged(e);
        }

        void OnIsActiveChanged(EventArgs &e) override
        {
            if (isExpandable)
            {
                if (GetIsActive())
                    SetImageSource("Resources/Images/Buttons/ExpanderOpen.png");
                else
                    SetImageSource("Resources/Images/Buttons/ExpanderClosed.png");
            }

            ClearFocus();

            ButtonBase::OnIsActiveChanged(e);
        }

    public:
        bool IsExpandable() { return isExpandable; }
        void SetIsExpandable(bool value)
        {
            // if (isExpandable != value)
            {
                isExpandable = value;

                if (isExpandable && GetIsActive())
                    SetImageSource("Resources/Images/Buttons/ExpanderOpen.png");
                else
                    SetImageSource("Resources/Images/Buttons/ExpanderClosed.png");
            }
        }

        Visual *HeaderContent() { return headerContent; }
        void SetHeaderContent(Visual *value)
        {
            if (headerContent != value)
            {
                if (headerContent != nullptr)
                {
                    RemoveChild(headerContent);
                }

                headerContent = value;

                if (headerContent != nullptr)
                {
                    AddChild(headerContent);
                    headerContent->SetColumn(1);
                }
            }
        }

        HeaderButton()
        {
            headerContent = nullptr;
            isExpandable = true;

            SetBrushGroup("HeaderButton");
            SetLayoutGroup("HeaderButton");

            SetUseOrientation(false);

            SetColumns("*,Auto");
            SetColumnSpacing(UIDefaults::ColumnSpacing);

            SetCanActivate(true);

            SetToolTip("Click here to expand or collapse this menu");

            Image &image = GetImage();
            image.SetGrid(1, 0);
        }
    };
}
