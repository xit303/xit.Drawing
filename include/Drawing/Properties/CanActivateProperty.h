#pragma once

#include <Event.h>

namespace xit
{
    /**
     * @class CanActivateProperty
     * @brief A class that represents a property which can be activated.
     */
    class CanActivateProperty
    {
    private:
        bool canActivate; ///< Indicates whether the property can be activated.

        /**
         * @brief Handles the change in the canActivate property.
         */
        void HandleCanActivateChanged()
        {
            EventArgs e;
            CanActivateChanged(*this, e);
            OnCanActivateChanged(e);
        }

    protected:
        /**
         * @brief Called when the canActivate property changes.
         * 
         * You can override this method in a derived class to handle the change in the canActivate property.
         * 
         * @param e The event arguments.
         */
        virtual void OnCanActivateChanged(EventArgs &e) {}

    public:
        /**
         * @brief Gets the value of the canActivate property.
         * @return True if the property can be activated, false otherwise.
         */
        __always_inline bool GetCanActivate() const noexcept { return canActivate; }

        /**
         * @brief Sets the value of the canActivate property.
         * @param value The new value of the canActivate property.
         */
        void SetCanActivate(bool value)
        {
            if (canActivate != value)
            {
                canActivate = value;
                HandleCanActivateChanged();
            }
        }

        Event<CanActivateProperty &, EventArgs &> CanActivateChanged;

        /**
         * @brief Default constructor.
         */
        CanActivateProperty() : canActivate(false) {}

        /**
         * @brief Parameterized constructor.
         * @param canActivate Initial value of the canActivate property.
         */
        CanActivateProperty(bool canActivate) : canActivate(canActivate) {}

        /**
         * @brief Copy constructor.
         * @param other The object to copy from.
         */
        CanActivateProperty(const CanActivateProperty &other) : canActivate(other.canActivate) {}

        /**
         * @brief Move constructor.
         * @param other The object to move from.
         */
        CanActivateProperty(CanActivateProperty &&other) noexcept : canActivate(other.canActivate) {}

        /**
         * @brief Copy assignment operator.
         * @param other The object to copy from.
         * @return Reference to this object.
         */
        CanActivateProperty& operator=(const CanActivateProperty &other)
        {
            if (this != &other)
            {
                canActivate = other.canActivate;
                HandleCanActivateChanged();
            }
            return *this;
        }

        /**
         * @brief Move assignment operator.
         * @param other The object to move from.
         * @return Reference to this object.
         */
        CanActivateProperty& operator=(CanActivateProperty &&other) noexcept
        {
            if (this != &other)
            {
                canActivate = other.canActivate;
                HandleCanActivateChanged();
            }
            return *this;
        }

        /**
         * @brief Destructor.
         */
        virtual ~CanActivateProperty() {}
    };
}