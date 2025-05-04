#pragma once

#include <Event.h>

namespace xit
{
    /**
     * @brief Represents a property that defines whether an object is active.
     */
    class IsActiveProperty
    {
    private:
        bool isActive;

        /**
         * @brief Handles the event when the active state changes.
         */
        void HandleIsActiveChanged()
        {
            EventArgs e;
            IsActiveChanged(*this, e);
            OnIsActiveChanged(e);
        }

    protected:
        /**
         * @brief Called when the active state changes.
         * 
         * You can override this method to add custom logic when the active state changes.
         * 
         * @param e The event arguments.
         */
        virtual void OnIsActiveChanged(EventArgs &e) {}

    public:
        /**
         * @brief Gets the active state.
         * @return The active state.
         */
        __always_inline bool GetIsActive() const { return isActive; }

        /**
         * @brief Sets the active state.
         * @param value The new active state value.
         */
        void SetIsActive(const bool &value)
        {
            if (isActive != value)
            {
                isActive = value;
                HandleIsActiveChanged();
            }
        }

        /**
         * @brief Event triggered when the active state changes.
         */
        Event<IsActiveProperty &, EventArgs &> IsActiveChanged;

        /**
         * @brief Default constructor.
         */
        IsActiveProperty() : isActive(false) {}

        /**
         * @brief Constructor with active state parameter.
         * @param isActive The initial active state value.
         */
        IsActiveProperty(const bool isActive) : isActive(isActive) {}

        /**
         * @brief Copy constructor.
         * @param other The other IsActiveProperty to copy from.
         */
        IsActiveProperty(const IsActiveProperty &other) : isActive(other.isActive) {}

        /**
         * @brief Destructor.
         */
        virtual ~IsActiveProperty() {}
    };
}