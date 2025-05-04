#pragma once

#include <Drawing/Buttons/ButtonBase.h>

namespace xit::Drawing
{
    class FloatingActionButton : public ButtonBase
    {
    public:
        FloatingActionButton()
        {
            SetBrushGroup("FloatingActionButton");
            SetLayoutGroup("FloatingActionButton");

            SetShowLabel(false);
            SetUniformImageSize(UIDefaults::FloatingActionButtonImageHeight);
        }
    };
}
