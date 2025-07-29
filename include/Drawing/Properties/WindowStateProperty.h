#pragma once

#include <Event.h>
#include <Drawing/Properties/WindowState.h>

namespace xit::Drawing
{
    /**
     * @brief Represents a property that defines the window state.
     */
    class WindowStateProperty
    {
    private:
        WindowState windowState;
        WindowState lastWindowState;

        /**
         * @brief Handles the event when the window state changes.
         */
        void HandleWindowStateChanged()
        {
            EventArgs e;
            WindowStateChanged(*this, e);
            OnWindowStateChanged(e);
        }

    protected:
        /**
         * @brief Called when the window state changes.
         * 
         * You can override this method to add custom logic when the window state changes.
         * 
         * @param e The event arguments.
         */
        virtual void OnWindowStateChanged(EventArgs &e) {}

    public:
        /**
         * @brief Gets the window state.
         * @return The window state.
         */
        __always_inline const WindowState &GetWindowState() const { return windowState; }

        /**
         * @brief Sets the window state.
         * @param value The new window state value.
         */
        void SetWindowState(const WindowState &value)
        {
            if (windowState != value)
            {
                lastWindowState = windowState;
                windowState = value;
                HandleWindowStateChanged();
            }
        }

        void RestoreWindowState()
        {
            SetWindowState(lastWindowState);
        }

        /**
         * @brief Event triggered when the window state changes.
         */
        Event<WindowStateProperty &, EventArgs &> WindowStateChanged;

        /**
         * @brief Default constructor.
         */
        WindowStateProperty() : windowState(WindowState::Normal), lastWindowState(WindowState::Normal) {}

        /**
         * @brief Constructor with window state parameter.
         * @param windowState The initial window state value.
         */
        WindowStateProperty(const WindowState windowState) : windowState(windowState), lastWindowState(windowState) {}

        /**
         * @brief Copy constructor.
         * @param other The other WindowStateProperty to copy from.
         */
        WindowStateProperty(const WindowStateProperty &other) : windowState(other.windowState), lastWindowState(other.lastWindowState) {}

        /**
         * @brief Destructor.
         */
        virtual ~WindowStateProperty() {}
    };
}
