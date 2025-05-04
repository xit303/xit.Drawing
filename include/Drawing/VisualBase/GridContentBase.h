#pragma once

#include <Event.h>
#include <Drawing/Properties/ColumnProperty.h>
#include <Drawing/Properties/ColumnSpanProperty.h>
#include <Drawing/Properties/RowProperty.h>
#include <Drawing/Properties/RowSpanProperty.h>

namespace xit::Drawing::VisualBase
{
    class GridContentBase : public ColumnProperty, public ColumnSpanProperty, public RowProperty, public RowSpanProperty
    {
    public:
        GridContentBase() {}

        void SetGrid(size_t column, size_t row, size_t columnSpan = 1, size_t rowSpan = 1)
        {
            this->SetColumn(column);
            this->SetRow(row);
            this->SetColumnSpan(columnSpan);
            this->SetRowSpan(rowSpan);
        }
    };
}
using namespace xit::Drawing::VisualBase;
