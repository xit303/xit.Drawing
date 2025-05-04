#pragma once

#include <Event.h>
#include <Drawing/Properties/Thickness.h>

namespace xit::Drawing
{
    /**
     * @class BorderThicknessProperty
     * @brief A class that represents a property for border thickness.
     */
    class BorderThicknessProperty
    {
    private:
        Thickness borderThickness; ///< The thickness of the border.

        /**
         * @brief Handles the change in the border thickness.
         */
        void HandleBorderThicknessChanged()
        {
            EventArgs e;
            BorderThicknessChanged(*this, e);
            OnBorderThicknessChanged(e);
        }

    protected:
        /**
         * @brief Called when the border thickness changes.
         *
         * You can override this method in a derived class to handle the change in the border thickness.
         *
         * @param e The event arguments.
         */
        virtual void OnBorderThicknessChanged(EventArgs &e) {}

    public:
        /**
         * @brief Gets the border thickness.
         * @return The current border thickness.
         */
        __always_inline const Thickness &GetBorderThickness() const { return borderThickness; }

        /**
         * @brief Sets the border thickness.
         * @param value The new border thickness.
         */
        void SetBorderThickness(const Thickness &value)
        {
            if (borderThickness != value)
            {
                borderThickness = value;
                HandleBorderThicknessChanged();
            }
        }

        /**
         * @brief Sets the border thickness uniformly.
         * @param value The new uniform border thickness.
         */
        void SetBorderThickness(int value)
        {
            if (borderThickness.GetLeft() != value ||
                borderThickness.GetTop() != value ||
                borderThickness.GetRight() != value ||
                borderThickness.GetBottom() != value)
            {
                borderThickness.SetValues(value);
                HandleBorderThicknessChanged();
            }
        }

        /**
         * @brief Sets the border thickness for left-right and top-bottom.
         * @param leftRight The new left and right border thickness.
         * @param topBottom The new top and bottom border thickness.
         */
        void SetBorderThickness(int leftRight, int topBottom)
        {
            if (borderThickness.GetLeft() != leftRight ||
                borderThickness.GetTop() != topBottom ||
                borderThickness.GetRight() != leftRight ||
                borderThickness.GetBottom() != topBottom)
            {
                borderThickness.SetValues(leftRight, topBottom);
                HandleBorderThicknessChanged();
            }
        }

        /**
         * @brief Sets the border thickness for each side individually.
         * @param left The new left border thickness.
         * @param top The new top border thickness.
         * @param right The new right border thickness.
         * @param bottom The new bottom border thickness.
         */
        void SetBorderThickness(int left, int top, int right, int bottom)
        {
            if (borderThickness.GetLeft() != left ||
                borderThickness.GetTop() != top ||
                borderThickness.GetRight() != right ||
                borderThickness.GetBottom() != bottom)
            {
                borderThickness.SetValues(left, top, right, bottom);
                HandleBorderThicknessChanged();
            }
        }

        /**
         * @brief Sets the scale for the border thickness.
         * @param value The new scale value.
         */
        void SetBorderThicknessScale(float value)
        {
            if (borderThickness.Scale(value))
                HandleBorderThicknessChanged();
        }

        /**
         * @brief Sets the scale for the border thickness with separate values for X and Y axes.
         * @param valueX The new scale value for the X axis.
         * @param valueY The new scale value for the Y axis.
         */
        void SetBorderThicknessScale(float valueX, float valueY)
        {
            if (borderThickness.Scale(valueX, valueY))
                HandleBorderThicknessChanged();
        }

        /**
         * @brief Resets the scale for the border thickness.
         */
        void ResetBorderThicknessScale()
        {
            if (borderThickness.ResetScale())
                HandleBorderThicknessChanged();
        }

        /**
         * @brief Event triggered when the border thickness changes.
         */
        Event<BorderThicknessProperty &, EventArgs &> BorderThicknessChanged;

        /**
         * @brief Default constructor.
         */
        BorderThicknessProperty() {}

        /**
         * @brief Parameterized constructor.
         * @param borderThickness Initial value of the border thickness.
         */
        BorderThicknessProperty(Thickness borderThickness) : borderThickness(borderThickness) {}

        /**
         * @brief Copy constructor.
         * @param other The object to copy from.
         */
        BorderThicknessProperty(const BorderThicknessProperty &other) : borderThickness(other.borderThickness) {}

        /**
         * @brief Destructor.
         */
        virtual ~BorderThicknessProperty() {}
    };
}