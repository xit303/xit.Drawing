#pragma once

#include <Event.h>

namespace xit
{
    /**
     * @brief Represents a property that indicates if an object can be deactivated.
     */
    class CanDeactivateProperty
    {
    private:
        bool canDeactivate;

        /**
         * @brief Handles the can deactivate changed event.
         */
        void HandleCanDeactivateChanged()
        {
            EventArgs e;
            CanDeactivateChanged(*this, e);
            OnCanDeactivateChanged(e);
        }

    protected:
        /**
         * @brief Called when the can deactivate property is changed.
         * 
         * You can override this method in a derived class to handle the change in the can deactivate property.
         * 
         * @param e Event arguments.
         */
        virtual void OnCanDeactivateChanged(EventArgs &e) { (void)e; }

    public:
        /**
         * @brief Gets the can deactivate value.
         * @return The can deactivate value.
         */
        __always_inline bool GetCanDeactivate() const { return canDeactivate; }

        /**
         * @brief Sets the can deactivate value.
         * @param value The new can deactivate value.
         */
        void SetCanDeactivate(const bool &value)
        {
            if (canDeactivate != value)
            {
                canDeactivate = value;
                HandleCanDeactivateChanged();
            }
        }

        /**
         * @brief Event triggered when the can deactivate property is changed.
         */
        Event<CanDeactivateProperty &, EventArgs &> CanDeactivateChanged;

        /**
         * @brief Default constructor.
         */
        CanDeactivateProperty() : canDeactivate(false) {}

        /**
         * @brief Constructor with can deactivate value.
         * @param canDeactivate The initial can deactivate value.
         */
        CanDeactivateProperty(bool canDeactivate) : canDeactivate(canDeactivate) {}

        /**
         * @brief Copy constructor.
         * @param other The other CanDeactivateProperty to copy from.
         */
        CanDeactivateProperty(const CanDeactivateProperty &other) : canDeactivate(other.canDeactivate) {}

        /**
         * @brief Destructor.
         */
        virtual ~CanDeactivateProperty() {}
    };
}