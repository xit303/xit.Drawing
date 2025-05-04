#pragma once

#include <string>
#include <Event.h>

namespace xit
{
    /**
     * @brief Represents a property for a brush group.
     */
    class BrushGroupProperty
    {
    private:
        std::string brushGroup;

        /**
         * @brief Handles the brush group changed event.
         */
        void HandleBrushGroupChanged()
        {
            EventArgs e;
            BrushGroupChanged(*this, e);
            OnBrushGroupChanged(e);
        }

    protected:
        /**
         * @brief Called when the brush group is changed.
         * 
         * You can override this method in a derived class to handle the change in the brush group.
         * 
         * @param e Event arguments.
         */
        virtual void OnBrushGroupChanged(EventArgs &e) {}

    public:
        /**
         * @brief Gets the brush group value.
         * @return The brush group value.
         */
        __always_inline const std::string &GetBrushGroup() const { return brushGroup; }

        /**
         * @brief Sets the brush group value.
         * @param value The new brush group value.
         */
        void SetBrushGroup(const std::string &value)
        {
            if (brushGroup != value)
            {
                brushGroup = value;
                HandleBrushGroupChanged();
            }
        }

        /**
         * @brief Event triggered when the brush group is changed.
         */
        Event<BrushGroupProperty &, EventArgs &> BrushGroupChanged;

        /**
         * @brief Default constructor.
         */
        BrushGroupProperty() {}

        /**
         * @brief Constructor with brush group value.
         * @param brushGroup The initial brush group value.
         */
        BrushGroupProperty(std::string brushGroup) : brushGroup(brushGroup) {}

        /**
         * @brief Copy constructor.
         * @param other The other BrushGroupProperty to copy from.
         */
        BrushGroupProperty(const BrushGroupProperty &other) : brushGroup(other.brushGroup) {}

        /**
         * @brief Destructor.
         */
        virtual ~BrushGroupProperty() {}
    };
}