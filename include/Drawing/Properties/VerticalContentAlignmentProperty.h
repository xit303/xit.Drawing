#pragma once

#include <Event.h>
#include <Drawing/Properties/VerticalAlignment.h>

namespace xit::Drawing
{
    /**
     * @brief Represents a property that defines the vertical content alignment.
     */
    class VerticalContentAlignmentProperty
    {
    private:
        VerticalAlignment verticalContentAlignment;

        /**
         * @brief Handles the event when the vertical content alignment changes.
         */
        void HandleVerticalContentAlignmentChanged()
        {
            EventArgs e;
            VerticalContentAlignmentChanged(*this, e);
            OnVerticalContentAlignmentChanged(e);
        }

    protected:
        /**
         * @brief Called when the vertical content alignment changes.
         * 
         * You can override this method to add custom logic when the vertical content alignment changes.
         * 
         * @param e The event arguments.
         */
        virtual void OnVerticalContentAlignmentChanged(EventArgs &e) {}

    public:
        /**
         * @brief Gets the vertical content alignment.
         * @return The vertical content alignment.
         */
        __always_inline VerticalAlignment GetVerticalContentAlignment() const { return verticalContentAlignment; }

        /**
         * @brief Sets the vertical content alignment.
         * @param value The new vertical content alignment value.
         */
        virtual void SetVerticalContentAlignment(const VerticalAlignment &value)
        {
            if (verticalContentAlignment != value)
            {
                verticalContentAlignment = value;
                HandleVerticalContentAlignmentChanged();
            }
        }

        /**
         * @brief Event triggered when the vertical content alignment changes.
         */
        Event<VerticalContentAlignmentProperty &, EventArgs &> VerticalContentAlignmentChanged;

        /**
         * @brief Default constructor.
         */
        VerticalContentAlignmentProperty() : verticalContentAlignment(VerticalAlignment::Stretch) {}

        /**
         * @brief Constructor with vertical content alignment parameter.
         * @param verticalContentAlignment The initial vertical content alignment value.
         */
        VerticalContentAlignmentProperty(const VerticalAlignment &verticalContentAlignment) : verticalContentAlignment(verticalContentAlignment) {}
    };
}

using namespace xit::Drawing;
