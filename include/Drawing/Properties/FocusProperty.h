#pragma once

#include <Event.h>
#include <Input/IFocus.h>

namespace xit
{
    /**
     * @class FocusProperty
     * @brief Manages the focus property.
     */
    class FocusProperty : public xit::Input::IFocus
    {
    private:
        bool canFocus;
        bool isFocused;

        /**
         * @brief Handles the event when the can focus property changes.
         */
        void HandleCanFocusChanged()
        {
            EventArgs e;
            CanFocusChanged(*this, e);
            OnCanFocusChanged(e);
        }

        /**
         * @brief Handles the event when the is focused property changes.
         */
        void HandleIsFocusedChanged()
        {
            EventArgs e;
            IsFocusedChanged(*this, e);
            OnIsFocusedChanged(e);
        }

    protected:
        /**
         * @brief Called when the can focus property changes.
         * 
         * You can override this method to handle the event when the can focus property changes.
         * 
         * @param e Event arguments.
         */
        virtual void OnCanFocusChanged(EventArgs &e) {}

        /**
         * @brief Called when the is focused property changes.
         * 
         * You can override this method to handle the event when the is focused property changes.
         * 
         * @param e Event arguments.
         */
        virtual void OnIsFocusedChanged(EventArgs &e) {}

    public:
        /**
         * @brief Gets the can focus property.
         * @return True if the element can be focused, false otherwise.
         */
        __always_inline bool GetCanFocus() const { return canFocus; }

        /**
         * @brief Sets the can focus property.
         * @param value True to allow focusing, false otherwise.
         */
        void SetCanFocus(bool value)
        {
            if (canFocus != value)
            {
                canFocus = value;
                HandleCanFocusChanged();
            }
        }

        /**
         * @brief Gets the is focused property.
         * @return True if the element is focused, false otherwise.
         */
        __always_inline bool GetIsFocused() const { return isFocused; }

        /**
         * @brief Sets the is focused property.
         * @param value True to set the element as focused, false otherwise.
         */
        void SetIsFocused(bool value)
        {
            if (isFocused != value)
            {
                isFocused = value;
                HandleIsFocusedChanged();
            }
        }

        /**
         * @brief Attempts to focus the element.
         * @return True if the element was successfully focused, false otherwise.
         */
        // bool Focus()
        // {
        //     if (canFocus && !isFocused)
        //     {
        //         EventArgs e;
        //         HandleGotKeyboardFocus(e);

        //         Invalidate();

        //         bool retval;

        //         if (!e.Handled)
        //             retval = InputHandler::SetFocus(this);
        //         else
        //             retval = true;

        //         return retval;
        //     }
        //     return false;
        // }

        /**
         * @brief Clears the focus from the element.
         * @param invalidateNow Whether to invalidate the element immediately.
         */
        // void ClearFocus(bool invalidateNow = true)
        // {
        //     if (isFocused)
        //     {
        //         EventArgs e;
        //         HandleLostKeyboardFocus(e);
        //         if (invalidateNow)
        //             Invalidate();
        //     }
        // }

        /**
         * @brief Event triggered when the can focus property changes.
         */
        Event<FocusProperty &, EventArgs &> CanFocusChanged;

        /**
         * @brief Event triggered when the is focused property changes.
         */
        Event<FocusProperty &, EventArgs &> IsFocusedChanged;

        /**
         * @brief Default constructor.
         */
        FocusProperty() : canFocus(false), isFocused(false) {}

        /**
         * @brief Constructor with initial can focus and is focused properties.
         * @param canFocus Initial can focus property.
         * @param isFocused Initial is focused property.
         */
        FocusProperty(bool canFocus, bool isFocused) : canFocus(canFocus), isFocused(isFocused) {}

        /**
         * @brief Copy constructor.
         * @param other The other FocusProperty to copy.
         */
        FocusProperty(const FocusProperty &other) : canFocus(other.canFocus), isFocused(other.isFocused) {}

        /**
         * @brief Destructor.
         */
        virtual ~FocusProperty() {}
    };
}