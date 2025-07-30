#pragma once

#include <Event.h>
#include <Drawing/Brushes/BrushBase.h>

namespace xit::Drawing
{
    /**
     * @class BackgroundProperty
     * @brief A class that represents a property for background brushes.
     */
    class BackgroundProperty
    {
    private:
        const BrushBase *brush; ///< The brush used for the background.

        /**
         * @brief Handles the change in the background brush.
         */
        void HandleBackgroundChanged()
        {
            EventArgs e;
            BackgroundChanged(*this, e);
            OnBackgroundChanged(e);
        }

    protected:
        /**
         * @brief Called when the background brush changes.
         * 
         * You can override this method in a derived class to handle the change in the background brush.
         * 
         * @param e The event arguments.
         */
        virtual void OnBackgroundChanged(EventArgs &e) { (void)e; }

    public:
        /**
         * @brief Gets the background brush.
         * @return The current background brush.
         */
        const BrushBase *GetBackground() const { return brush; }

        /**
         * @brief Sets the background brush.
         * @param value The new background brush.
         */
        void SetBackground(const BrushBase *value)
        {
            if (brush != value)
            {
                brush = value;
                HandleBackgroundChanged();
            }
        }

        /**
         * @brief Event triggered when the background brush changes.
         */
        Event<BackgroundProperty &, EventArgs &> BackgroundChanged;

        /**
         * @brief Default constructor.
         */
        BackgroundProperty() : brush(nullptr) {}
    };
}