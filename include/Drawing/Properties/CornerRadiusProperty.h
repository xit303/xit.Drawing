#pragma once

#include <Event.h>
#include <Drawing/Properties/CornerRadius.h>

namespace xit::Drawing
{
    /**
     * @class CornerRadiusProperty
     * @brief Manages the corner radius property.
     */
    class CornerRadiusProperty
    {
    private:
        CornerRadius cornerRadius;

        /**
         * @brief Handles the event when the corner radius changes.
         */
        void HandleCornerRadiusChanged()
        {
            EventArgs e;
            CornerRadiusChanged(*this, e);
            OnCornerRadiusChanged(e);
        }

    protected:
        /**
         * @brief Called when the corner radius changes.
         * 
         * You can override this method to handle the event when the corner radius changes.
         * 
         * @param e Event arguments.
         */
        virtual void OnCornerRadiusChanged(EventArgs &e) {}

    public:
        /**
         * @brief Gets the corner radius.
         * @return The current corner radius.
         */
        __always_inline const CornerRadius &GetCornerRadius() const { return cornerRadius; }

        /**
         * @brief Sets the corner radius.
         * @param value The new corner radius.
         */
        void SetCornerRadius(const CornerRadius &value)
        {
            if (cornerRadius != value)
            {
                cornerRadius = value;
                HandleCornerRadiusChanged();
            }
        }

        /**
         * @brief Sets a uniform corner radius.
         * @param uniformValue The uniform radius value for all corners.
         */
        void SetCornerRadius(const double uniformValue)
        {
            cornerRadius.TopLeft = uniformValue;
            cornerRadius.TopRight = uniformValue;
            cornerRadius.BottomRight = uniformValue;
            cornerRadius.BottomLeft = uniformValue;

            HandleCornerRadiusChanged();
        }

        /**
         * @brief Event triggered when the corner radius changes.
         */
        Event<CornerRadiusProperty &, EventArgs &> CornerRadiusChanged;
    };
}
using namespace xit::Drawing;
