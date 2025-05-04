#include <Drawing/GridRowManager.h>
#include <Exceptions.h>
#include <iostream>

namespace xit::Drawing
{
    void GridRowManager::SetBounds(const Rectangle &value)
    {
        GridDimensionManager::SetBounds(value.GetHeight(), value.GetBottom());
    }

    int GridRowManager::GetHeight(int available)
    {
        return GridDimensionManager::GetSize(available);
    }

    void GridRowManager::SetChildren(std::vector<Visual *> *value)
    {
        GridDimensionManager::SetChildren(value);
    }

    void GridRowManager::SetRows(const std::string &value)
    {
        GridDimensionManager::SetValues(value);
    }

    void GridRowManager::SetRowSpacing(int value)
    {
        GridDimensionManager::SetSpacing(value);
    }

    void GridRowManager::OnVerticalAlignmentChanged(EventArgs &e)
    {
        VerticalAlignmentProperty::OnVerticalAlignmentChanged(e);
        UpdateSizes();
    }

    bool GridRowManager::GetStart(int &start, int total)
    {
        if (GetVerticalAlignment() == VerticalAlignment::Bottom)
        {
            start = GetBoundsMax();
            if (start < 0)
            {
                start = 0;
            }
        }
        else if ((GetVerticalAlignment() != VerticalAlignment::Bottom) &&
                 (GetVerticalAlignment() == VerticalAlignment::Center))
        {
            start = (GetBoundsSize() - total) >> 1;
            if (start < 0)
            {
                start = 0;
            }
        }

        return GetVerticalAlignment() != VerticalAlignment::Bottom;
    }

    void GridRowManager::GetIndexAndSpan(Visual *content, int &index, int &span) const
    {
        index = content->GetRow();
        span = content->GetRowSpan();
    }
}