#pragma once

#include <Event.h>
#include <glm.hpp>

namespace xit::Drawing
{
    /**
     * @brief Represents a property that defines the Rotation.
     */
    class RotationProperty
    {
    private:
        glm::vec3 rotation;

        /**
         * @brief Handles the event when the Rotation changes.
         */
        void HandleRotationChanged()
        {
            EventArgs e;
            RotationChanged(*this, e);
            OnRotationChanged(e);
        }

    protected:
        /**
         * @brief Called when the Rotation changes.
         * 
         * You can override this method to add custom logic when the Rotation changes.
         * 
         * @param e The event arguments.
         */
        virtual void OnRotationChanged(EventArgs &e) {}

    public:
        /**
         * @brief Gets the Rotation.
         * @return The Rotation.
         */
        __always_inline const glm::vec3 &GetRotation() const { return rotation; }

        /**
         * @brief Sets the Rotation.
         * @param value The new Rotation value.
         */
        void SetRotation(const glm::vec3 value)
        {
            if (rotation != value)
            {
                rotation = value;
                HandleRotationChanged();
            }
        }

        /**
         * @brief Event triggered when the Rotation changes.
         */
        Event<RotationProperty &, EventArgs &> RotationChanged;

        /**
         * @brief Initializes a new instance of the RotationProperty class.
         */
        RotationProperty() : rotation(0.0f) {}
    };
}
