#pragma once

#include <Drawing/ContentContainer.h>

namespace xit::Drawing
{
    class HeaderedContainer : public ContentContainer
    {
    private:
        Visual *headerContent;

    public:
        inline Visual *GetHeader() { return headerContent; }
        inline void SetHeader(Visual *value)
        {
            if (headerContent != value)
            {
                if (headerContent)
                {
                    Container::RemoveChildAt(0);
                }

                headerContent = value;

                if (headerContent)
                {
                    headerContent->SetGrid(0, 0);
                    Container::InsertChild(0, headerContent);
                }
            }
        }

        HeaderedContainer()
        {
            headerContent = nullptr;

            Container::SetRows("Auto,Auto");
            SetHandleMouse(true);
            SetHandleKeyboard(true);
            SetUseOrientation(false);

            Container::AddChild(&GetContentContainer());
        }
    };
}
