#include <Drawing/Grid.h>

namespace xit::Drawing
{
    void Grid::SetBounds(const Rectangle &value)
    {
        GridColumnManager::SetBounds(value);
        GridRowManager::SetBounds(value);
    }

    void Grid::SetChildren(std::vector<Visual *> *value)
    {
        GridColumnManager::SetChildren(value);
        GridRowManager::SetChildren(value);
    }

    void Grid::SetGrid(Visual &content, int column, int row, int columnSpan, int rowSpan)
    {
        if (column < 0)
            column = 0;

        content.SetColumn(column);

        if (row < 0)
            row = 0;

        content.SetRow(row);

        if (columnSpan < 1)
            columnSpan = 1;

        content.SetColumnSpan(columnSpan);

        if (rowSpan < 1)
            rowSpan = 1;

        content.SetRowSpan(rowSpan);
    }
}
