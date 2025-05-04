#pragma once

#include <Event.h>
#include <Drawing/Properties/VerticalAlignment.h>

namespace xit::Drawing
{
    /**
     * @brief Represents a property that defines the vertical alignment.
     */
    class VerticalAlignmentProperty
    {
    private:
        VerticalAlignment verticalAlignment;

        /**
         * @brief Handles the event when the vertical alignment changes.
         */
        void HandleVerticalAlignmentChanged()
        {
            EventArgs e;
            VerticalAlignmentChanged(*this, e);
            OnVerticalAlignmentChanged(e);
        }

    protected:
        /**
         * @brief Called when the vertical alignment changes.
         * 
         * You can override this method to add custom logic when the vertical alignment changes.
         * 
         * @param e The event arguments.
         */
        virtual void OnVerticalAlignmentChanged(EventArgs &e) {}

    public:
        /**
         * @brief Gets the vertical alignment.
         * @return The vertical alignment.
         */
        __always_inline VerticalAlignment GetVerticalAlignment() const { return verticalAlignment; }

        /**
         * @brief Sets the vertical alignment.
         * @param value The new vertical alignment value.
         */
        void SetVerticalAlignment(const VerticalAlignment &value)
        {
            if (verticalAlignment != value)
            {
                verticalAlignment = value;
                HandleVerticalAlignmentChanged();
            }
        }

        /**
         * @brief Event triggered when the vertical alignment changes.
         */
        Event<VerticalAlignmentProperty &, EventArgs &> VerticalAlignmentChanged;

        /**
         * @brief Default constructor.
         */
        VerticalAlignmentProperty() : verticalAlignment(VerticalAlignment::Stretch) {}

        /**
         * @brief Constructor with vertical alignment parameter.
         * @param verticalAlignment The initial vertical alignment value.
         */
        VerticalAlignmentProperty(const VerticalAlignment &verticalAlignment) : verticalAlignment(verticalAlignment) {}
    };
}

using namespace xit::Drawing;
