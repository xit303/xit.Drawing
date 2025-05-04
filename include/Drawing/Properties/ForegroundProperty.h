#pragma once

#include <Event.h>
#include <Drawing/Brushes/BrushBase.h>

namespace xit::Drawing
{
    /**
     * @class ForegroundProperty
     * @brief Manages the foreground property.
     */
    class ForegroundProperty
    {
    private:
        const BrushBase *brush;
        bool inheritForeground;

        /**
         * @brief Handles the event when the foreground changes.
         */
        void HandleForegroundChanged()
        {
            EventArgs e;
            ForegroundChanged(*this, e);
            OnForegroundChanged(e);
        }

        /**
         * @brief Handles the event when the inherit foreground property changes.
         */
        void HandleInheritForegroundChanged()
        {
            EventArgs e;
            InheritForegroundChanged(*this, e);
            OnInheritForegroundChanged(e);
        }

    protected:
        /**
         * @brief Called when the foreground changes.
         * 
         * You can override this method to handle the event when the foreground changes.
         * 
         * @param e Event arguments.
         */
        virtual void OnForegroundChanged(EventArgs &e) {}

        /**
         * @brief Called when the inherit foreground property changes.
         * 
         * You can override this method to handle the event when the inherit foreground property changes.
         * 
         * @param e Event arguments.
         */
        virtual void OnInheritForegroundChanged(EventArgs &e) {}

    public:
        /**
         * @brief Gets the foreground brush.
         * @return The current foreground brush.
         */
        const BrushBase *GetForeground() const { return brush; }

        /**
         * @brief Sets the foreground brush.
         * @param value The new foreground brush.
         */
        void SetForeground(const BrushBase *value)
        {
            if (brush != value)
            {
                brush = value;
                HandleForegroundChanged();
            }
        }

        /**
         * @brief Gets the inherit foreground property.
         * @return True if the foreground is inherited, false otherwise.
         */
        __always_inline bool GetInheritForeground() const { return inheritForeground; }

        /**
         * @brief Sets the inherit foreground property.
         * @param value True to inherit the foreground, false otherwise.
         */
        void SetInheritForeground(bool value)
        {
            if (inheritForeground != value)
            {
                inheritForeground = value;
                HandleInheritForegroundChanged();
            }
        }

        /**
         * @brief Event triggered when the foreground changes.
         */
        Event<ForegroundProperty &, EventArgs &> ForegroundChanged;

        /**
         * @brief Event triggered when the inherit foreground property changes.
         */
        Event<ForegroundProperty &, EventArgs &> InheritForegroundChanged;

        /**
         * @brief Default constructor.
         */
        ForegroundProperty() : brush(nullptr), inheritForeground(false) {}
    };
}
using namespace xit::Drawing;
