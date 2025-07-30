#pragma once

#include <Event.h>
#include <Drawing/Properties/Thickness.h>

namespace xit::Drawing
{
    /**
     * @brief Represents a property that defines the padding.
     */
    class PaddingProperty
    {
    private:
        Thickness padding;

        /**
         * @brief Handles the event when the padding changes.
         */
        void HandlePaddingChanged()
        {
            EventArgs e;
            PaddingChanged(*this, e);
            OnPaddingChanged(e);
        }

    protected:
        /**
         * @brief Called when the padding changes.
         *
         * You can override this method to add custom logic when the padding changes.
         *
         * @param e The event arguments.
         */
        virtual void OnPaddingChanged(EventArgs &e) { (void)e; }

    public:
        /**
         * @brief Gets the padding.
         * @return The padding.
         */
        inline const Thickness &GetPadding() const { return padding; }

        /**
         * @brief Sets the padding.
         * @param value The new padding value.
         */
        virtual void SetPadding(const Thickness &value)
        {
            if (padding != value)
            {
                padding = value;
                HandlePaddingChanged();
            }
        }
        /**
         * @brief Sets the padding with a single value for all sides.
         * @param value The new padding value.
         */
        virtual void SetPadding(const int value)
        {
            padding = Thickness(value);
            HandlePaddingChanged();
        }

        /**
         * @brief Sets the padding with separate values for each side.
         * @param left The new padding value for the left side.
         * @param top The new padding value for the top side.
         * @param right The new padding value for the right side.
         * @param bottom The new padding value for the bottom side.
         */
        virtual void SetPadding(const int left, const int top, const int right, const int bottom)
        {
            padding = Thickness(left, top, right, bottom);
            HandlePaddingChanged();
        }

        /**
         * @brief Sets the padding with separate values for X and Y axes.
         * @param leftRight The new padding value for the left and right sides.
         * @param topBottom The new padding value for the top and bottom sides.
         */
        virtual void SetPadding(const int leftRight, const int topBottom)
        {
            padding = Thickness(leftRight, topBottom);
            HandlePaddingChanged();
        }

        /**
         * @brief Sets the scale for the padding.
         * @param value The new scale value.
         */
        void SetPaddingScale(float value)
        {
            if (padding.Scale(value))
                HandlePaddingChanged();
        }

        /**
         * @brief Sets the scale for the padding with separate values for X and Y axes.
         * @param x The new scale value for the X axis.
         * @param y The new scale value for the Y axis.
         */
        void SetPaddingScale(float x, float y)
        {
            if (padding.Scale(x, y))
                HandlePaddingChanged();
        }

        /**
         * @brief Resets the scale for the padding to 1.
         */
        void ResetPaddingScale()
        {
            if (padding.ResetScale())
                HandlePaddingChanged();
        }

        /**
         * @brief Event triggered when the padding changes.
         */
        Event<PaddingProperty &, EventArgs &> PaddingChanged;

        /**
         * @brief Default constructor.
         */
        PaddingProperty() {}
    };
}
using namespace xit::Drawing;
