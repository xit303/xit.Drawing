#pragma once

#include <Drawing/Bar.h>

namespace xit::Drawing
{
    class ProgressBar : public Bar
    {
    public:
        ProgressBar()
        {
            SetBrushGroup("ProgressBar");
            SetLayoutGroup("ProgressBar");
        }
    };
}
