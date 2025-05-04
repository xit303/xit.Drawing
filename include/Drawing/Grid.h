#pragma once

#include <vector>
#include <Drawing/GridColumnManager.h>
#include <Drawing/GridRowManager.h>

namespace xit::Drawing
{
    class Grid : public GridColumnManager,
                 public GridRowManager
    {
    public:
        void SetBounds(const Rectangle &value);
        void SetChildren(std::vector<Visual *> *value);

        Grid() = default;
        ~Grid() = default;

        static void SetGrid(Visual &content, int column, int row, int columnSpan, int rowSpan);
    };
}
