#pragma once

#include <Event.h>

namespace xit::Drawing
{
    /**
     * @brief Represents a property that defines the row span.
     */
    class RowSpanProperty
    {
    private:
        size_t rowSpan;

        /**
         * @brief Handles the event when the row span changes.
         */
        void HandleRowSpanChanged()
        {
            EventArgs e;
            RowSpanChanged(*this, e);
            OnRowSpanChanged(e);
        }

    protected:
        /**
         * @brief Called when the row span changes.
         * 
         * You can override this method to add custom logic when the row span changes.
         * 
         * @param e The event arguments.
         */
        virtual void OnRowSpanChanged(EventArgs &e) {}

    public:
        /**
         * @brief Gets the row span.
         * @return The row span.
         */
        __always_inline const size_t &GetRowSpan() const { return rowSpan; }

        /**
         * @brief Sets the row span.
         * @param value The new row span value.
         */
        void SetRowSpan(const size_t &value)
        {
            if (rowSpan != value)
            {
                rowSpan = value;
                HandleRowSpanChanged();
            }
        }

        /**
         * @brief Event triggered when the row span changes.
         */
        Event<RowSpanProperty &, EventArgs &> RowSpanChanged;

        /**
         * @brief Default constructor.
         */
        RowSpanProperty() : rowSpan(1) {}

        /**
         * @brief Constructor with row span parameter.
         * @param rowSpan The initial row span value.
         */
        RowSpanProperty(const size_t rowSpan) : rowSpan(rowSpan) {}

        /**
         * @brief Copy constructor.
         * @param other The other RowSpanProperty to copy from.
         */
        RowSpanProperty(const RowSpanProperty &other) : rowSpan(other.rowSpan) {}

        /**
         * @brief Destructor.
         */
        virtual ~RowSpanProperty() {}
    };
}

using namespace xit::Drawing;
