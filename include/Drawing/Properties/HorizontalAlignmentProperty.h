#pragma once

#include <Event.h>
#include <Drawing/Properties/HorizontalAlignment.h>

namespace xit::Drawing
{
    /**
     * @class HorizontalAlignmentProperty
     * @brief Manages the horizontal alignment property.
     */
    class HorizontalAlignmentProperty
    {
    private:
        HorizontalAlignment horizontalAlignment;

        /**
         * @brief Handles the event when the horizontal alignment changes.
         */
        void HandleHorizontalAlignmentChanged()
        {
            EventArgs e;
            HorizontalAlignmentChanged(*this, e);
            OnHorizontalAlignmentChanged(e);
        }

    protected:
        /**
         * @brief Called when the horizontal alignment changes.
         * 
         * You can override this method to handle the event when the horizontal alignment changes.
         * 
         * @param e Event arguments.
         */
        virtual void OnHorizontalAlignmentChanged(EventArgs &e) { (void)e; }

    public:
        /**
         * @brief Gets the horizontal alignment.
         * @return The current horizontal alignment.
         */
        __always_inline HorizontalAlignment GetHorizontalAlignment() const { return horizontalAlignment; }

        /**
         * @brief Sets the horizontal alignment.
         * @param value The new horizontal alignment.
         */
        void SetHorizontalAlignment(const HorizontalAlignment &value)
        {
            if (horizontalAlignment != value)
            {
                horizontalAlignment = value;
                HandleHorizontalAlignmentChanged();
            }
        }

        /**
         * @brief Event triggered when the horizontal alignment changes.
         */
        Event<HorizontalAlignmentProperty &, EventArgs &> HorizontalAlignmentChanged;

        /**
         * @brief Default constructor.
         */
        HorizontalAlignmentProperty() : horizontalAlignment(HorizontalAlignment::Stretch) {}

        /**
         * @brief Constructor with initial horizontal alignment.
         * @param horizontalAlignment Initial horizontal alignment.
         */
        HorizontalAlignmentProperty(const HorizontalAlignment &horizontalAlignment) : horizontalAlignment(horizontalAlignment) {}
    };
}
using namespace xit::Drawing;
