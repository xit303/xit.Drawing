#pragma once

#include <Event.h>
#include <Drawing/Properties/HorizontalAlignment.h>

namespace xit::Drawing
{
    /**
     * @class HorizontalContentAlignmentProperty
     * @brief Manages the horizontal content alignment property.
     */
    class HorizontalContentAlignmentProperty
    {
    private:
        HorizontalAlignment horizontalContentAlignment;

        /**
         * @brief Handles the event when the horizontal content alignment changes.
         */
        void HandleHorizontalContentAlignmentChanged()
        {
            EventArgs e;
            HorizontalContentAlignmentChanged(*this, e);
            OnHorizontalContentAlignmentChanged(e);
        }

    protected:
        /**
         * @brief Called when the horizontal content alignment changes.
         * @param e Event arguments.
         */
        virtual void OnHorizontalContentAlignmentChanged(EventArgs &e) {}

    public:
        /**
         * @brief Gets the horizontal content alignment.
         * @return The current horizontal content alignment.
         */
        __always_inline HorizontalAlignment GetHorizontalContentAlignment() const { return horizontalContentAlignment; }

        /**
         * @brief Sets the horizontal content alignment.
         * @param value The new horizontal content alignment.
         */
        virtual void SetHorizontalContentAlignment(const HorizontalAlignment &value)
        {
            if (horizontalContentAlignment != value)
            {
                horizontalContentAlignment = value;
                HandleHorizontalContentAlignmentChanged();
            }
        }

        /**
         * @brief Event triggered when the horizontal content alignment changes.
         */
        Event<HorizontalContentAlignmentProperty &, EventArgs &> HorizontalContentAlignmentChanged;

        /**
         * @brief Default constructor.
         */
        HorizontalContentAlignmentProperty() : horizontalContentAlignment(HorizontalAlignment::Stretch) {}

        /**
         * @brief Constructor with initial horizontal content alignment.
         * @param horizontalContentAlignment Initial horizontal content alignment.
         */
        HorizontalContentAlignmentProperty(const HorizontalAlignment &horizontalContentAlignment) : horizontalContentAlignment(horizontalContentAlignment) {}
    };
}
using namespace xit::Drawing;
