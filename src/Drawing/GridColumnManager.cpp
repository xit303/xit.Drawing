#include <Drawing/GridColumnManager.h>
#include <Exceptions.h>
#include <iostream>

namespace xit::Drawing
{
    void GridColumnManager::SetBounds(const Rectangle &value)
    {
        GridDimensionManager::SetBounds(value.GetWidth(), value.GetRight());
    }

    int GridColumnManager::GetWidth(int available)
    {
        return GridDimensionManager::GetSize(available);
    }

    void GridColumnManager::SetChildren(std::vector<Visual *> *value)
    {
        GridDimensionManager::SetChildren(value);
    }

    void GridColumnManager::SetColumns(const std::string &value)
    {
        GridDimensionManager::SetValues(value);
    }

    void GridColumnManager::SetColumnSpacing(int value)
    {
        GridDimensionManager::SetSpacing(value);
    }

    void GridColumnManager::OnHorizontalAlignmentChanged(EventArgs &e)
    {
        HorizontalAlignmentProperty::OnHorizontalAlignmentChanged(e);
        UpdateSizes();
    }

    bool GridColumnManager::GetStart(int &start, int total)
    {
        if (GetHorizontalAlignment() == HorizontalAlignment::Right)
        {
            start = GetBoundsMax();
        }
        else if (GetHorizontalAlignment() == HorizontalAlignment::Center)
        {
            start = (GetBoundsSize() - total) >> 1;
        }
        else
        {
            start = 0;
        }

        if (start < 0)
        {
            start = 0;
        }

        return GetHorizontalAlignment() != HorizontalAlignment::Right;
    }

    void GridColumnManager::GetIndexAndSpan(Visual *content, int &index, int &span) const
    {
        index = content->GetColumn();
        span = content->GetColumnSpan();
    }
}