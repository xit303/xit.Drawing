#pragma once

#include <Event.h>
#include <Input/IVisibility.h>

namespace xit::Drawing
{
    using Visibility = xit::Input::Visibility;

    /**
     * @brief Represents a property that defines the visibility.
     */
    class VisibilityProperty : public xit::Input::IVisibility
    {
    private:
        Visibility visibility;

        /**
         * @brief Handles the event when the visibility changes.
         */
        void HandleVisibilityChanged()
        {
            EventArgs e;
            VisibilityChanged(*this, e);
            OnVisibilityChanged(e);
        }

    protected:
        /**
         * @brief Called when the visibility changes.
         * 
         * You can override this method to add custom logic when the visibility changes.
         * 
         * @param e The event arguments.
         */
        virtual void OnVisibilityChanged(EventArgs &e) {}

    public:
        /**
         * @brief Gets the visibility.
         * @return The visibility.
         */
        virtual __always_inline Visibility GetVisibility() const override { return visibility; }

        /**
         * @brief Sets the visibility.
         * @param value The new visibility value.
         */
        virtual void SetVisibility(const Visibility &value) override
        {
            if (visibility != value)
            {
                visibility = value;
                HandleVisibilityChanged();
            }
        }

        /**
         * @brief Checks if the object is visible.
         * @return True if the object is visible, false otherwise.
         */
        virtual __always_inline bool GetIsVisible() const override { return visibility == Visibility::Visible; }

        /**
         * @brief Sets the visibility based on a boolean value.
         * @param value True to make the object visible, false to collapse it.
         */
        virtual void SetIsVisible(const bool value) override
        {
            if ((value && visibility != Visibility::Visible) || (!value && visibility != Visibility::Collapsed))
            {
                visibility = value ? Visibility::Visible : Visibility::Collapsed;
                HandleVisibilityChanged();
            }
        }

        /**
         * @brief Event triggered when the visibility changes.
         */
        Event<VisibilityProperty &, EventArgs &> VisibilityChanged;

        /**
         * @brief Default constructor.
         */
        VisibilityProperty() : visibility(Visibility::Visible) {}

        /**
         * @brief Constructor with visibility parameter.
         * @param visibility The initial visibility value.
         */
        VisibilityProperty(const Visibility &visibility) : visibility(visibility) {}
    };
}

using namespace xit::Drawing;
