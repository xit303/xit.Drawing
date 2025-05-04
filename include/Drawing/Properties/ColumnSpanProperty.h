#pragma once

#include <Event.h>

namespace xit::Drawing
{
    /**
     * @brief Represents a property that defines the column span.
     */
    class ColumnSpanProperty
    {
    private:
        size_t columnSpan;

        /**
         * @brief Handles the event when the column span changes.
         */
        void HandleColumnSpanChanged()
        {
            EventArgs e;
            ColumnSpanChanged(*this, e);
            OnColumnSpanChanged(e);
        }

    protected:
        /**
         * @brief Called when the column span changes.
         * 
         * You can override this method to add custom logic when the column span changes.
         * 
         * @param e The event arguments.
         */
        virtual void OnColumnSpanChanged(EventArgs &e) {}

    public:
        /**
         * @brief Gets the column span.
         * @return The column span.
         */
        __always_inline size_t GetColumnSpan() const { return columnSpan; }

        /**
         * @brief Sets the column span.
         * @param value The new column span value.
         */
        void SetColumnSpan(const size_t value)
        {
            if (columnSpan != value)
            {
                columnSpan = value;
                HandleColumnSpanChanged();
            }
        }

        /**
         * @brief Event triggered when the column span changes.
         */
        Event<ColumnSpanProperty &, EventArgs &> ColumnSpanChanged;

        /**
         * @brief Default constructor.
         */
        ColumnSpanProperty() : columnSpan(1) {}

        /**
         * @brief Constructor with column span parameter.
         * @param columnSpan The initial column span value.
         */
        ColumnSpanProperty(const size_t columnSpan) : columnSpan(columnSpan) {}

        /**
         * @brief Copy constructor.
         * @param other The other ColumnSpanProperty to copy from.
         */
        ColumnSpanProperty(const ColumnSpanProperty &other) : columnSpan(other.columnSpan) {}

        /**
         * @brief Destructor.
         */
        virtual ~ColumnSpanProperty() {}
    };
}

using namespace xit::Drawing;
