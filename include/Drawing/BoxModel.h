#pragma once

#include <Drawing/Properties/MarginProperty.h>
#include <Drawing/Properties/BorderThicknessProperty.h>
#include <Drawing/Properties/PaddingProperty.h>

namespace xit::Drawing
{
    /**
     * @brief Represents a box model that includes margin, border thickness, and padding properties.
     */
    class BoxModel : public MarginProperty,
                     public BorderThicknessProperty,
                     public PaddingProperty
    {
    private:
        mutable bool needRecalculation = true;

        mutable int boxWidthWithoutMargin = 0;
        mutable int boxHeightWithoutMargin = 0;

        mutable int totalBoxWidth = 0;
        mutable int totalBoxHeight = 0;

        void RecalculateBoxModel() const
        {
            // Recalculation logic
            boxWidthWithoutMargin = GetPadding().GetWidth() + GetBorderThickness().GetWidth();
            boxHeightWithoutMargin = GetPadding().GetHeight() + GetBorderThickness().GetHeight();
            totalBoxWidth = GetMargin().GetWidth() + boxWidthWithoutMargin;
            totalBoxHeight = GetMargin().GetHeight() + boxHeightWithoutMargin;

            needRecalculation = false;
        }

    protected:
        virtual void OnMarginChanged(EventArgs &e) override
        {
            needRecalculation = true;
        }
        virtual void OnBorderThicknessChanged(EventArgs &e) override
        {
            needRecalculation = true;
        }
        virtual void OnPaddingChanged(EventArgs &e) override
        {
            needRecalculation = true;
        }

    public:
        BoxModel() = default;
        virtual ~BoxModel() = default;

        int GetTotalBoxWidth() const
        {
            if (needRecalculation)
            {
                RecalculateBoxModel();
            }
            return totalBoxWidth;
        }
        int GetTotalBoxHeight() const
        {
            if (needRecalculation)
            {
                RecalculateBoxModel();
            }
            return totalBoxHeight;
        }
        int GetBoxWidthWithoutMargin() const
        {
            if (needRecalculation)
            {
                RecalculateBoxModel();
            }
            return boxWidthWithoutMargin;
        }
        int GetBoxHeightWithoutMargin() const
        {
            if (needRecalculation)
            {
                RecalculateBoxModel();
            }
            return boxHeightWithoutMargin;
        }
    };
} // namespace xit::Drawing