#pragma once

#include <iostream>

#include <Event.h>
#include <Properties/NameProperty.h>
#include <Input/ISizeable.h>
#include <Drawing/Size.h>
#include <Drawing/BoxModel.h>
#include <Drawing/Rectangle.h>
#include <Drawing/Properties/HorizontalAlignmentProperty.h>
#include <Drawing/Properties/LayoutGroupProperty.h>
#include <Drawing/Properties/Location.h>
#include <Drawing/Properties/ScaleProperty.h>
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
                          public ScaleProperty,
                          public VerticalAlignmentProperty,
                          public VisibilityProperty,
                          public LayoutGroupProperty,
                          public Location,
                          public VisualStateManager
    {
    private:
        bool invalidated;

        bool needWidthRecalculation;
        bool needHeightRecalculation;
        bool needLeftRecalculation;
        bool needTopRecalculation;

        Rectangle clientBounds;

    protected:
        Size desiredSize;

        int renderTop;
        int renderLeft;
        int actualWidth;
        int actualHeight;

        Rectangle bounds;

        virtual void OnInvalidated(EventArgs &e) {}

        virtual void OnHorizontalAlignmentChanged(EventArgs &e) override;
        virtual void OnVerticalAlignmentChanged(EventArgs &e) override;

        virtual void OnWidthChanged(EventArgs &e) override;
        virtual void OnHeightChanged(EventArgs &e) override;
        virtual void OnMinWidthChanged(EventArgs &e) override;
        virtual void OnMaxWidthChanged(EventArgs &e) override;
        virtual void OnMinHeightChanged(EventArgs &e) override;
        virtual void OnMaxHeightChanged(EventArgs &e) override;

        virtual void OnMarginChanged(EventArgs &e) override;
        virtual void OnPaddingChanged(EventArgs &e) override;
        virtual void OnBorderThicknessChanged(EventArgs &e) override;
        virtual void OnLocationChanged(EventArgs &e) override;
        virtual void OnSizeChanged(const Size &newSize);
        virtual void OnVisibilityChanged(EventArgs &e) override;

        virtual void OnScaleChanged(EventArgs &e) override;

        virtual int OnMeasureWidth(int availableSize);
        virtual int OnMeasureHeight(int availableSize);

        virtual void OnUpdate(const Rectangle &bounds);

        // Core layout calculation method - performs the actual layout work
        virtual void PerformLayout(const Rectangle &bounds);

        // Called after layout is complete but before flags are reset
        // Override this for additional calculations that need the recalculation flags
        virtual void OnLayoutCompleted(const Rectangle &bounds);

        // Method to reset recalculation flags - call this after derived classes have processed the flags
        virtual void ResetRecalculationFlags();

        // Parent notification methods for background buffer support
        virtual void NotifyParentOfInvalidation();

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

        __always_inline const Rectangle &GetBounds() const { return bounds; }
        __always_inline const Rectangle &GetClientBounds() const { return clientBounds; }

        // Public getters for recalculation flags - useful for derived classes
        __always_inline bool GetNeedWidthRecalculation() const { return needWidthRecalculation; }
        __always_inline bool GetNeedHeightRecalculation() const { return needHeightRecalculation; }
        __always_inline bool GetNeedLeftRecalculation() const { return needLeftRecalculation; }
        __always_inline bool GetNeedTopRecalculation() const { return needTopRecalculation; }
        __always_inline bool GetInvalidated() const { return invalidated; }

        virtual void OnBackgroundChanged(EventArgs &e) {}
        virtual void OnForegroundChanged(EventArgs &e) {}
        virtual void OnBorderBrushChanged(EventArgs &e) {}

        // Child invalidation notification for background buffer support
        virtual void OnChildInvalidated(LayoutManager *childLayout);
    };
} // namespace xit::Drawing::VisualBase
