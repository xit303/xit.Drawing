#pragma once

#include <Event.h>
#include <Drawing/Properties/WindowStyle.h>

namespace xit::Drawing
{
    /**
     * @brief Represents a property that defines the window style.
     */
    class WindowStyleProperty
    {
    private:
        WindowStyle windowStyle;

        /**
         * @brief Handles the event when the window style changes.
         */
        void HandleWindowStyleChanged()
        {
            EventArgs e;
            WindowStyleChanged(*this, e);
            OnWindowStyleChanged(e);
        }

    protected:
        /**
         * @brief Called when the window style changes.
         * 
         * You can override this method to add custom logic when the window style changes.
         * 
         * @param e The event arguments.
         */
        virtual void OnWindowStyleChanged(EventArgs &e) { (void)e; }

    public:
        /**
         * @brief Gets the window style.
         * @return The window style.
         */
        __always_inline const WindowStyle &GetWindowStyle() const { return windowStyle; }

        /**
         * @brief Sets the window style.
         * @param value The new window style value.
         */
        void SetWindowStyle(const WindowStyle &value)
        {
            if (windowStyle != value)
            {
                windowStyle = value;
                HandleWindowStyleChanged();
            }
        }

        /**
         * @brief Event triggered when the window style changes.
         */
        Event<WindowStyleProperty &, EventArgs &> WindowStyleChanged;

        /**
         * @brief Default constructor.
         */
        WindowStyleProperty() : windowStyle(WindowStyle::SingleBorderWindow) {}

        /**
         * @brief Constructor with window style parameter.
         * @param windowStyle The initial window style value.
         */
        WindowStyleProperty(const WindowStyle windowStyle) : windowStyle(windowStyle) {}

        /**
         * @brief Copy constructor.
         * @param other The other WindowStyleProperty to copy from.
         */
        WindowStyleProperty(const WindowStyleProperty &other) : windowStyle(other.windowStyle) {}

        /**
         * @brief Destructor.
         */
        virtual ~WindowStyleProperty() {}
    };
}
