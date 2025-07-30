#pragma once

#include <Event.h>

namespace xit::Drawing
{
    /**
     * @brief Represents a property that defines the Z-index.
     */
    class ZIndexProperty
    {
    private:
        int zIndex;

        /**
         * @brief Handles the event when the Z-index changes.
         */
        void HandleZIndexChanged()
        {
            EventArgs e;
            ZIndexChanged(*this, e);
            OnZIndexChanged(e);
        }

    protected:
        /**
         * @brief Called when the Z-index changes.
         * 
         * You can override this method to add custom logic when the Z-index changes.
         * 
         * @param e The event arguments.
         */
        virtual void OnZIndexChanged(EventArgs &e) { (void)e; }

    public:
        /**
         * @brief Gets the Z-index.
         * @return The Z-index.
         */
        __always_inline int GetZIndex() const { return zIndex; }

        /**
         * @brief Sets the Z-index.
         * @param value The new Z-index value.
         */
        void SetZIndex(const int value)
        {
            if (zIndex != value)
            {
                zIndex = value;
                HandleZIndexChanged();
            }
        }

        /**
         * @brief Event triggered when the Z-index changes.
         */
        Event<ZIndexProperty &, EventArgs &> ZIndexChanged;

        /**
         * @brief Default constructor.
         */
        ZIndexProperty() : zIndex(0) {}

        /**
         * @brief Constructor with Z-index parameter.
         * @param zIndex The initial Z-index value.
         */
        ZIndexProperty(const int zIndex) : zIndex(zIndex) {}
    };
}

using namespace xit::Drawing;
