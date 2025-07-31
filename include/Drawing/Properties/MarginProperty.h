#pragma once

#include <Event.h>
#include <Drawing/Properties/Thickness.h>

namespace xit::Drawing
{
    /**
     * @brief Represents a property that defines the margin.
     */
    class MarginProperty
    {
    private:
        Thickness margin;

        /**
         * @brief Handles the event when the margin changes.
         */
        void HandleMarginChanged()
        {
            EventArgs e;
            MarginChanged(*this, e);
            OnMarginChanged(e);
        }

    protected:
        /**
         * @brief Called when the margin changes.
         *
         * You can override this method to add custom logic when the margin changes.
         *
         * @param e The event arguments.
         */
        virtual void OnMarginChanged(EventArgs &e) { (void)e; }

    public:
        /**
         * @brief Gets the margin.
         * @return The margin.
         */
        __always_inline const Thickness &GetMargin() const { return margin; }

        /**
         * @brief Sets the margin.
         * @param value The new margin value.
         */
        void SetMargin(const Thickness &value)
        {
            if (margin != value)
            {
                margin = value;
                HandleMarginChanged();
            }
        }

        /**
         * @brief Sets the margin with a single value for all sides.
         * @param value The new margin value for all sides.
         */
        void SetMargin(int value)
        {
            if (margin.GetLeft() != value ||
                margin.GetTop() != value ||
                margin.GetRight() != value ||
                margin.GetBottom() != value)
            {
                margin.SetValues(value);
                HandleMarginChanged();
            }
        }

        /**
         * @brief Sets the margin with separate values for left-right and top-bottom.
         * @param leftRight The new margin value for left and right.
         * @param topBottom The new margin value for top and bottom.
         */
        void SetMargin(int leftRight, int topBottom)
        {
            if (margin.GetLeft() != leftRight ||
                margin.GetTop() != topBottom ||
                margin.GetRight() != leftRight ||
                margin.GetBottom() != topBottom)
            {
                margin.SetValues(leftRight, topBottom);
                HandleMarginChanged();
            }
        }

        /**
         * @brief Sets the margin with separate values for each side.
         * @param left The new margin value for the left side.
         * @param top The new margin value for the top side.
         * @param right The new margin value for the right side.
         * @param bottom The new margin value for the bottom side.
         */
        void SetMargin(int left, int top, int right, int bottom)
        {
            if (margin.GetLeft() != left ||
                margin.GetTop() != top ||
                margin.GetRight() != right ||
                margin.GetBottom() != bottom)
            {
                margin.SetValues(left, top, right, bottom);
                HandleMarginChanged();
            }
        }

        /**
         * @brief Sets the scale for the margin.
         * @param value The new scale value.
         */
        void SetMarginScale(float value)
        {
            if (margin.Scale(value))
                HandleMarginChanged();
        }

        /**
         * @brief Sets the scale for the margin with separate values for X and Y axes.
         * @param x The new scale value for the X axis.
         * @param y The new scale value for the Y axis.
         */
        void SetMarginScale(float x, float y)
        {
            if (margin.Scale(x, y))
                HandleMarginChanged();
        }

        /**
         * @brief Resets the scale for the margin to 1.
         */
        void ResetMarginScale()
        {
            if (margin.ResetScale())
                HandleMarginChanged();
        }

        /**
         * @brief Event triggered when the margin changes.
         */
        Event<MarginProperty &, EventArgs &> MarginChanged;

        /**
         * @brief Default constructor.
         */
        MarginProperty() {}

        /**
         * @brief Constructor with margin parameter.
         * @param margin The initial margin value.
         */
        explicit MarginProperty(const Thickness &margin)
            : margin(margin)
        {
        }

        /**
         * @brief Copy constructor.
         * @param other The other MarginProperty to copy from.
         */
        MarginProperty(const MarginProperty &other)
            : margin(other.margin)
        {
        }

        /**
         * @brief Destructor.
         */
        virtual ~MarginProperty() {}
    };
}

using namespace xit::Drawing;
