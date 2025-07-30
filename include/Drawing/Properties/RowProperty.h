#pragma once

#include <Event.h>

namespace xit::Drawing
{
    /**
     * @brief Represents a property that defines the row.
     */
    class RowProperty
    {
    private:
        size_t row;

        /**
         * @brief Handles the event when the row changes.
         */
        void HandleRowChanged()
        {
            EventArgs e;
            RowChanged(*this, e);
            OnRowChanged(e);
        }

    protected:
        /**
         * @brief Called when the row changes.
         * 
         * You can override this method to add custom logic when the row changes.
         * 
         * @param e The event arguments.
         */
        virtual void OnRowChanged(EventArgs &e) { (void)e; }

    public:
        /**
         * @brief Gets the row.
         * @return The row.
         */
        __always_inline const size_t GetRow() const { return row; }

        /**
         * @brief Sets the row.
         * @param value The new row value.
         */
        void SetRow(const size_t value)
        {
            if (row != value)
            {
                row = value;
                HandleRowChanged();
            }
        }

        /**
         * @brief Event triggered when the row changes.
         */
        Event<RowProperty &, EventArgs &> RowChanged;

        /**
         * @brief Default constructor.
         */
        RowProperty() : row(0) {}

        /**
         * @brief Constructor with row parameter.
         * @param row The initial row value.
         */
        RowProperty(const size_t row) : row(row) {}

        /**
         * @brief Copy constructor.
         * @param other The other RowProperty to copy from.
         */
        RowProperty(const RowProperty &other) : row(other.row) {}

        /**
         * @brief Destructor.
         */
        virtual ~RowProperty() {}
    };
}

using namespace xit::Drawing;
