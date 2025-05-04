#pragma once

#include <Event.h>

namespace xit::Drawing
{
    /**
     * @brief Represents a property for a column.
     */
    class ColumnProperty
    {
    private:
        size_t column;

        /**
         * @brief Handles the column changed event.
         */
        void HandleColumnChanged()
        {
            EventArgs e;
            ColumnChanged(*this, e);
            OnColumnChanged(e);
        }

    protected:
        /**
         * @brief Called when the column is changed.
         * 
         * You can override this method in a derived class to handle the change in the column.
         * 
         * @param e Event arguments.
         */
        virtual void OnColumnChanged(EventArgs &e) {}

    public:
        /**
         * @brief Gets the column value.
         * @return The column value.
         */
        __always_inline const size_t GetColumn() const { return column; }

        /**
         * @brief Sets the column value.
         * @param value The new column value.
         */
        void SetColumn(const size_t value)
        {
            if (column != value)
            {
                column = value;
                HandleColumnChanged();
            }
        }

        /**
         * @brief Event triggered when the column is changed.
         */
        Event<ColumnProperty &, EventArgs &> ColumnChanged;

        /**
         * @brief Default constructor.
         */
        ColumnProperty() : column(0) {}

        /**
         * @brief Constructor with column value.
         * @param column The initial column value.
         */
        ColumnProperty(size_t column) : column(column) {}

        /**
         * @brief Copy constructor.
         * @param other The other ColumnProperty to copy from.
         */
        ColumnProperty(const ColumnProperty &other) : column(other.column) {}

        /**
         * @brief Destructor.
         */
        virtual ~ColumnProperty() {}
    };
}

using namespace xit::Drawing;
