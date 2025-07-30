#pragma once

#include <string>
#include <Event.h>

namespace xit
{
    /**
     * @brief Represents a property that defines the layout group.
     */
    class LayoutGroupProperty
    {
    private:
        std::string layoutGroup;

        /**
         * @brief Handles the event when the layout group changes.
         */
        void HandleLayoutGroupChanged()
        {
            EventArgs e;
            LayoutGroupChanged(*this, e);
            OnLayoutGroupChanged(e);
        }

    protected:
        /**
         * @brief Called when the layout group changes.
         * 
         * You can override this method to add custom logic when the layout group changes.
         * 
         * @param e The event arguments.
         */
        virtual void OnLayoutGroupChanged(EventArgs &e) { (void)e; }

    public:
        /**
         * @brief Gets the layout group.
         * @return The layout group.
         */
        __always_inline const std::string &GetLayoutGroup() const { return layoutGroup; }

        /**
         * @brief Sets the layout group.
         * @param value The new layout group value.
         */
        void SetLayoutGroup(const std::string &value)
        {
            if (layoutGroup != value)
            {
                layoutGroup = value;
                HandleLayoutGroupChanged();
            }
        }

        /**
         * @brief Event triggered when the layout group changes.
         */
        Event<LayoutGroupProperty &, EventArgs &> LayoutGroupChanged;

        /**
         * @brief Default constructor.
         */
        LayoutGroupProperty() {}

        /**
         * @brief Constructor with layout group parameter.
         * @param layoutGroup The initial layout group value.
         */
        LayoutGroupProperty(std::string layoutGroup) : layoutGroup(layoutGroup) {}

        /**
         * @brief Copy constructor.
         * @param other The other LayoutGroupProperty to copy from.
         */
        LayoutGroupProperty(const LayoutGroupProperty &other) : layoutGroup(other.layoutGroup) {}

        /**
         * @brief Destructor.
         */
        virtual ~LayoutGroupProperty() {}
    };
}