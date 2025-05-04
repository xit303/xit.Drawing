#pragma once

#include <Drawing/ScrollViewer.h>

namespace xit::Drawing::Pages
{
    class Page : public Container // ScrollViewer//Container
    {
    public:
        Page()
        {
            // ATTENTION: SetInheritForeground is ONLY valid if inherited from ScrollViewer
            SetInheritForeground(false);
            SetLayoutGroup("Page");
            SetBrushGroup("Page");
        }
    };
}