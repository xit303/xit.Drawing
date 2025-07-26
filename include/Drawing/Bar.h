#pragma once

#include <Drawing/Container.h>
#include <Drawing/Border.h>
#include <Properties/MinMaxProperty.h>

namespace xit::Drawing
{
    class Bar : public Container, public Properties::MinMaxProperty
    {
    protected:
        Border valueIndicator;

    public:

        Bar() : MinMaxProperty(0, 100, 0)
        {
            SetInheritForeground(false);
            SetUseOrientation(true);

            SetName("Bar");

            //SetColumns("*");
            //SetRows("*");

            valueIndicator.SetBackground(GetForeground());
            valueIndicator.SetClipToBounds(true);
            valueIndicator.SetCornerRadius(GetCornerRadius());
            AddChild(&valueIndicator);

            EventArgs e;
            OnOrientationChanged(e);
        }

    protected:
        virtual void OnMinimumChanged(float value) override
        {
            OnUpdateValueIndicator();
        }

        virtual void OnMaximumChanged(float value) override
        {
            OnUpdateValueIndicator();
        }

        void OnCornerRadiusChanged(EventArgs& e) override
        {
            Container::OnCornerRadiusChanged(e);
            valueIndicator.SetCornerRadius(GetCornerRadius());
        }

        void OnForegroundChanged(EventArgs& e) override
        {
            Container::OnForegroundChanged(e);
            valueIndicator.SetBackground(GetForeground());
        }

        void OnOrientationChanged(EventArgs& e) override
        {
            Container::OnOrientationChanged(e);

            if (GetOrientation() == Orientation::Horizontal)
            {
                valueIndicator.SetHorizontalAlignment(GetOrientationDirection() == OrientationDirection::Normal ? HorizontalAlignment::Left : HorizontalAlignment::Right);
                valueIndicator.SetVerticalAlignment(VerticalAlignment::Stretch);

                valueIndicator.SetWidth(0);
                valueIndicator.SetHeight(-1);
            }
            else
            {
                valueIndicator.SetHorizontalAlignment(HorizontalAlignment::Stretch);
                valueIndicator.SetVerticalAlignment(GetOrientationDirection() == OrientationDirection::Normal ? VerticalAlignment::Top : VerticalAlignment::Bottom);

                valueIndicator.SetWidth(-1);
                valueIndicator.SetHeight(0);
            }

            OnUpdateValueIndicator();
        }

        virtual void OnUpdateValueIndicator()
        {
            if (GetOrientation() == Orientation::Horizontal)
            {
                if (GetActualWidth() > 0)
                {
                    int sub = GetBorderThickness().GetWidth();
                    int max = GetActualWidth() - sub;

                    int result = (int)std::round((float)max * ValueOfMaximum());

                    if (result != valueIndicator.GetWidth())
                    {
                        valueIndicator.SetWidth((int)((float)result / GetScaleX()));
                        Invalidate();
                    }
                }
            }
            else
            {
                if (GetActualHeight() > 0)
                {
                    int sub = GetBorderThickness().GetHeight();
                    int max = GetActualHeight() - sub;

                    int result = (int)std::round((float)max * ValueOfMaximum());

                    if (result != valueIndicator.GetHeight())
                    {
                        valueIndicator.SetHeight((int)((float)result / GetScaleY()));
                        Invalidate();
                    }
                }
            }
        }

        void OnSizeChanged(const Size& newSize) override
        {
            Container::OnSizeChanged(newSize);
            OnUpdateValueIndicator();
        }

        virtual void OnUpdate(const Rectangle& bounds) override
        {
            // TODO if bounds did not change, do we have to update? Only in case if items have been added or removed? Check the requirements! (This comment is also in Container::OnUpdate)
            Container::OnUpdate(bounds);
            OnUpdateValueIndicator();
        }
    };
}
