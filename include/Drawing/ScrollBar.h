#pragma once

#include <Drawing/Bar.h>

namespace xit::Drawing
{
    class ScrollBar : public Bar
    {
    protected:
        float extensionFactor = 1;

    public:
        ScrollBar()
        {
            SetBrushGroup("ScrollBar");
            SetBorderThickness(1);
            SetHandleMouse(true);
        }

    protected:
        void OnMaximumChanged(float value) override
        {
            if (GetOrientation() == Orientation::Horizontal)
            {
                float width = (float)GetActualWidth();
                width -= (float)(GetBorderThickness().GetWidth() + GetMargin().GetWidth() + GetPadding().GetWidth());
                width = width < 1 ? 0 : (float)GetActualWidth();

                float factor = value > 0 ? width / value : 1;

                valueIndicator.SetHeight(GetHeight() - GetBorderThickness().GetHeight());
                float result = width * factor;
                if (result > width)
                {
                    result = width;
                }

                valueIndicator.SetWidth((int)std::round(result));

                float extension = width - (float)valueIndicator.GetWidth();
                extensionFactor = extension / width;
            }
            else
            {
                float height = (float)GetActualHeight();
                height -= (float)(GetBorderThickness().GetHeight() + GetMargin().GetHeight() + GetPadding().GetHeight());
                height = height < 1 ? 0 : (float)GetActualHeight();

                float factor = value > 0 ? height / value : 1;

                valueIndicator.SetWidth(GetWidth() - GetBorderThickness().GetWidth());
                valueIndicator.SetHeight((int)std::round(height * factor));

                float extension = height - (float)valueIndicator.GetHeight();
                extensionFactor = extension / height;
            }
        }

        void OnSizeChanged(const Size& newSize) override
        {
            OnMaximumChanged(GetMaximum());
            Bar::OnSizeChanged(newSize);
        }
    };

    class HScrollBar : public ScrollBar
    {
    public:
        HScrollBar()
        {
            SetLayoutGroup("HScrollBar");
            SetOrientation(Orientation::Horizontal);
        }

    protected:
        void OnUpdateValueIndicator() override
        {
            if (GetActualWidth() == 0)
            {
                return;
            }

            float left = GetValue() * extensionFactor;

            left = left == -1 ? 0 : std::round(left);

            if (GetOrientationDirection() == OrientationDirection::Normal)
                valueIndicator.SetMargin((int)left, 0, 0, 0);
            else
                valueIndicator.SetMargin(0, 0, (int)left, 0);
        }
    };

    class VScrollBar : public ScrollBar
    {
    public:
        VScrollBar()
        {
            SetLayoutGroup("VScrollBar");
            SetOrientation(Orientation::Vertical);
        }
    protected:

        void OnUpdateValueIndicator() override
        {
            if (GetActualHeight() == 0)
            {
                return;
            }

            float top = GetValue() * extensionFactor;

            top = top == -1 ? 0 : std::round(top);

            if (GetOrientationDirection() == OrientationDirection::Normal)
                valueIndicator.SetMargin(0, (int)top, 0, 0);
            else
                valueIndicator.SetMargin(0, 0, 0, (int)top);
        }
    };
}
