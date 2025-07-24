#pragma once

#include <iostream>

#include <Event.h>
#include <Properties/NameProperty.h>
#include <Input/ISizeable.h>
#include <Drawing/Size.h>
#include <Drawing/BoxModel.h>
#include <Drawing/Rectangle.h>
// #include <Drawing/Properties/CornerRadiusProperty.h>
// #include <Drawing/Properties/Sizeable.h>
#include <Drawing/Properties/HorizontalAlignmentProperty.h>
#include <Drawing/Properties/LayoutGroupProperty.h>
#include <Drawing/Properties/Location.h>
#include <Drawing/Properties/VerticalAlignmentProperty.h>
#include <Drawing/Properties/VisibilityProperty.h>
#include <Drawing/VisualBase/VisualStateManager.h>
#include <Drawing/Theme/ThemeManager.h>

namespace xit::Drawing::VisualBase
{
    class LayoutManager : public Properties::NameProperty,
                          public CornerRadiusProperty,
                          public Sizeable,
                          public ISizeable,
                          public BoxModel,
                          public HorizontalAlignmentProperty,
                          public VerticalAlignmentProperty,
                          public VisibilityProperty,
                          public LayoutGroupProperty,
                          public Location,
                          public VisualStateManager
    {
    private:
        float scaleX;
        float scaleY;

        LayoutVisualStateGroup *layoutVisualStateGroup;
        LayoutVisualState *currentLayoutVisualState;
        bool isLayoutGroupChanging;

        bool invalidated;

    protected:
        Size desiredSize;

        int renderTop;
        int renderLeft;
        int actualWidth;
        int actualHeight;

        bool needWidthRecalculation;
        bool needHeightRecalculation;
        bool needLeftRecalculation;
        bool needTopRecalculation;

        Rectangle bounds;

        void UpdateLayoutVisualState();
        virtual void OnVisualStateChanged(EventArgs &e) override;

        virtual void OnInvalidated(EventArgs &e) {}

        virtual void OnHorizontalAlignmentChanged(EventArgs &e) override;
        virtual void OnVerticalAlignmentChanged(EventArgs &e) override;

        virtual void OnWidthChanged(EventArgs &e) override;
        virtual void OnHeightChanged(EventArgs &e) override;

        virtual void OnMarginChanged(EventArgs &e) override;
        virtual void OnPaddingChanged(EventArgs &e) override;
        virtual void OnLocationChanged(EventArgs &e) override;
        virtual void OnSizeChanged(const Size &newSize);
        virtual void OnVisibilityChanged(EventArgs &e) override;
        virtual void OnLayoutGroupChanged(EventArgs &e) override;

        virtual int OnMeasureWidth(int availableSize);
        virtual int OnMeasureHeight(int availableSize);

        virtual void OnUpdateLayout(LayoutVisualState *value);
        virtual void OnUpdate(const Rectangle &bounds);

        static inline int CheckMinMaxWidth(const LayoutManager &visual, int value)
        {
            return Math::CheckMinMax(visual.GetMinWidth(), visual.GetMaxWidth(), value);
        }
        static inline int CheckMinMaxHeight(const LayoutManager &visual, int value)
        {
            return Math::CheckMinMax(visual.GetMinHeight(), visual.GetMaxHeight(), value);
        }

    public:
        LayoutManager();

        virtual void Invalidate();

        virtual int MeasureWidth(int availableSize);
        virtual int MeasureHeight(int availableSize);
        virtual Size Measure(const Size &availableSize);

        bool Update(const Rectangle &newBounds);

        virtual inline int GetActualWidth() const override { return actualWidth; }
        virtual inline int GetActualHeight() const override { return actualHeight; }
        inline const Size &GetDesiredSize() const { return desiredSize; }

        __always_inline float GetScaleX() const { return scaleX; }
        __always_inline float GetScaleY() const { return scaleY; }

        __always_inline const Rectangle &GetBounds() const { return bounds; }

        virtual void SetDPIScale(float scaleX, float scaleY);

        virtual void OnBackgroundChanged(EventArgs &e) {}
        virtual void OnForegroundChanged(EventArgs &e) {}
        virtual void OnBorderBrushChanged(EventArgs &e) {}
    };
} // namespace xit::Drawing::VisualBase
