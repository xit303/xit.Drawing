#pragma once

#include <Drawing/Buttons/ButtonBase.h>

namespace xit::Drawing
{
    class ListItem : public ButtonBase
    {
    public:
        ListItem()
        {
            SetBrushGroup("ListItem");
            SetLayoutGroup("ListItem");

            SetColumns("Auto,*");

            SetFontName(UIDefaults::DefaultFont);

            // added because columns or rows would be overwritten if child is added and orientation is used
            // TODO this should be checked
            SetUseOrientation(true);

            SetCanActivate(true);
            SetCanDeactivate(false);
            SetActivateOnMouseDown(true);
            SetShowImage(true);
        }

    protected:
        void OnOrientationChanged(EventArgs& e) override
        {
            // added because columns or rows would be overwritten if child is added and orientation is used
            // TODO this should be checked

            ButtonBase::OnOrientationChanged(e);
        }

#ifdef DEBUG
        int OnMeasureWidth(int available) override
        {
            return ButtonBase::OnMeasureWidth(available);
        }
        int OnMeasureHeight(int available) override
        {
            return ButtonBase::OnMeasureHeight(available);
        }
        void OnRender() override
        {
            ButtonBase::OnRender();
        }

#endif

#ifdef DEBUG
    public:
        Size Measure(const Size &availableSize) override
        {
            return ButtonBase::Measure(availableSize);
        }
#endif
    };
}
