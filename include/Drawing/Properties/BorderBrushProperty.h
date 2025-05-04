#pragma once

#include <Event.h>
#include <Drawing/Brushes/BrushBase.h>

namespace xit::Drawing
{
    /**
     * @class BorderBrushProperty
     * @brief A class that represents a property for border brushes.
     */
    class BorderBrushProperty
    {
    private:
        const BrushBase *brush; ///< The brush used for the border.

        /**
         * @brief Handles the change in the border brush.
         */
        void HandleBorderBrushChanged()
        {
            EventArgs e;
            BorderBrushChanged(*this, e);
            OnBorderBrushChanged(e);
        }

    protected:
        /**
         * @brief Called when the border brush changes.
         * 
         * You can override this method in a derived class to handle the change in the border brush.
         * 
         * @param e The event arguments.
         */
        virtual void OnBorderBrushChanged(EventArgs &e) {}

    public:
        /**
         * @brief Gets the border brush.
         * @return The current border brush.
         */
        const BrushBase *GetBorderBrush() const { return brush; }

        /**
         * @brief Sets the border brush.
         * @param value The new border brush.
         */
        void SetBorderBrush(const BrushBase *value)
        {
            if (brush != value)
            {
                brush = value;
                HandleBorderBrushChanged();
            }
        }

        /**
         * @brief Event triggered when the border brush changes.
         */
        Event<BorderBrushProperty &, EventArgs &> BorderBrushChanged;

        /**
         * @brief Default constructor.
         */
        BorderBrushProperty() : brush(nullptr) {}
    };
}