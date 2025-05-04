#pragma once

#include <Event.h>

namespace xit
{
    /**
     * @brief Represents a property that defines whether an object is in an error state.
     */
    class IsErrorProperty
    {
    private:
        bool isError;

        /**
         * @brief Handles the event when the error state changes.
         */
        void HandleIsErrorChanged()
        {
            EventArgs e;
            IsErrorChanged(*this, e);
            OnIsErrorChanged(e);
        }

    protected:
        /**
         * @brief Called when the error state changes.
         * 
         * You can override this method to add custom logic when the error state changes.
         * 
         * @param e The event arguments.
         */
        virtual void OnIsErrorChanged(EventArgs &e) {}

    public:
        /**
         * @brief Gets the error state.
         * @return The error state.
         */
        __always_inline virtual bool GetIsError() const { return isError; }

        /**
         * @brief Sets the error state.
         * @param value The new error state value.
         */
        virtual void SetIsError(const bool value)
        {
            if (isError != value)
            {
                isError = value;
                HandleIsErrorChanged();
            }
        }

        /**
         * @brief Event triggered when the error state changes.
         */
        Event<IsErrorProperty &, EventArgs &> IsErrorChanged;

        /**
         * @brief Default constructor.
         */
        IsErrorProperty() : isError(false) {}

        /**
         * @brief Constructor with error state parameter.
         * @param isError The initial error state value.
         */
        IsErrorProperty(const bool isError) : isError(isError) {}

        /**
         * @brief Copy constructor.
         * @param other The other IsErrorProperty to copy from.
         */
        IsErrorProperty(const IsErrorProperty &other) : isError(other.isError) {}

        /**
         * @brief Destructor.
         */
        virtual ~IsErrorProperty() {}
    };
}