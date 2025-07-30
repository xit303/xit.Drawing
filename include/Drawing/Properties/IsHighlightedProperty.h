#pragma once

#include <Event.h>

namespace xit
{
    /**
     * @brief Represents a property that defines whether an object is highlighted.
     */
    class IsHighlightedProperty
    {
    private:
        bool isHighlighted;

        /**
         * @brief Handles the event when the highlighted state changes.
         */
        void HandleIsHighlightedChanged()
        {
            EventArgs e;
            IsHighlightedChanged(*this, e);
            OnIsHighlightedChanged(e);
        }

    protected:
        /**
         * @brief Called when the highlighted state changes.
         * 
         * You can override this method to add custom logic when the highlighted state changes.
         * 
         * @param e The event arguments.
         */
        virtual void OnIsHighlightedChanged(EventArgs &e) { (void)e; }

    public:
        /**
         * @brief Gets the highlighted state.
         * @return The highlighted state.
         */
        __always_inline const bool &GetIsHighlighted() const { return isHighlighted; }

        /**
         * @brief Sets the highlighted state.
         * @param value The new highlighted state value.
         */
        void SetIsHighlighted(const bool &value)
        {
            if (isHighlighted != value)
            {
                isHighlighted = value;
                HandleIsHighlightedChanged();
            }
        }

        /**
         * @brief Event triggered when the highlighted state changes.
         */
        Event<IsHighlightedProperty &, EventArgs &> IsHighlightedChanged;

        /**
         * @brief Default constructor.
         */
        IsHighlightedProperty() : isHighlighted(false) {}

        /**
         * @brief Constructor with highlighted state parameter.
         * @param isHighlighted The initial highlighted state value.
         */
        IsHighlightedProperty(const bool isHighlighted) : isHighlighted(isHighlighted) {}

        /**
         * @brief Copy constructor.
         * @param other The other IsHighlightedProperty to copy from.
         */
        IsHighlightedProperty(const IsHighlightedProperty &other) : isHighlighted(other.isHighlighted) {}

        /**
         * @brief Destructor.
         */
        virtual ~IsHighlightedProperty() {}
    };
}