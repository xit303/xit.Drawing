#include <Drawing/GridDimensionManager.h>
#ifdef DEBUG_GRID_PERFORMANCE
#include <chrono>
#include <iostream>
#endif

namespace xit::Drawing
{
    GridDimensionManager::GridDimensionManager(MeasureDelegate measureDelegate)
        : fixedTotalSize(0),
          autoTotalSize(0),
          starTotalSize(0),
          currentSize(0),
          totalSpacing(0),
          spacing(0),
          numberOfValues(0),
          boundsMax(0),
          boundsSize(0),
          measureDelegate(measureDelegate)
    {
        updateInfo.NumberOfCells = 1;
        updateInfo.SetAll(true);
        children = nullptr;
    }

    void GridDimensionManager::UpdateFixed()
    {
        if (updateInfo.UpdateFixed)
        {
            if (fixedValues.size() > 0)
            {
                fixedTotalSize = GridLayoutHelper::UpdateSizes(sizes, fixedValues);
            }

            updateInfo.UpdateFixed = false;
        }
    }
    void GridDimensionManager::UpdateAuto(int availableSize)
    {
        if (updateInfo.UpdateAuto && children != nullptr && children->size() > 0)
        {
#ifdef DEBUG_GRID_PERFORMANCE
            auto start = std::chrono::high_resolution_clock::now();
            std::cout << "GridDimensionManager::UpdateAuto - Processing " << children->size() 
                      << " children, " << autoValues.size() << " auto values" << std::endl;
#endif
            autoTotalSize = 0;

            if (autoValues.size() > 0)
            {
                // Performance critical: Reset auto sizes
                for (size_t a : autoValues)
                {
                    if (a >= sizes.size())
                    {
                        throw Exception("Invalid index in autoValues");
                    }
                    sizes[a] = 0;
                }

                // Performance critical: Measure all children for auto sizing
                for (Visual *content : *children)
                {
                    if (content->GetVisibility() != Visibility::Collapsed)
                    {
                        int index, span;
                        GetIndexAndSpan(content, index, span);
                        GridLayoutHelper::CheckAutoContent(index, span, sizes, autoValues, availableSize, measureDelegate, content);
                    }
                }

                // Performance critical: Sum auto sizes
                for (size_t a : autoValues)
                {
                    autoTotalSize += sizes[a];
                }

#ifdef DEBUG_GRID_PERFORMANCE
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                std::cout << "GridDimensionManager::UpdateAuto - Completed in " << duration.count() << "μs" << std::endl;
#endif

#ifdef DEBUG_GRID
                std::cout << "Auto values: ";
                for (size_t a : autoValues)
                {
                    std::cout << a << " ";
                }
                std::cout << std::endl;

                std::cout << "Auto sizes: ";
                for (size_t a : autoValues)
                {
                    std::cout << sizes[a] << " ";
                }
                std::cout << std::endl;

                std::cout << "Auto Total Size: " << autoTotalSize << std::endl;
#endif
            }

            updateInfo.UpdateAuto = false;
        }
    }
    void GridDimensionManager::UpdateStar(int availableSize)
    {
        if (updateInfo.UpdateStar)
        {
            if (starValues.size() > 0)
            {
                if (availableSize < 0)
                {
                    availableSize = 0;
                }

                starTotalSize = GridLayoutHelper::UpdateStar(sizes, starValues, availableSize);
            }

            updateInfo.UpdateStar = false;
        }
    }
    void GridDimensionManager::UpdateSpacing()
    {
        totalSpacing = (numberOfValues - 1) * spacing;
    }
    void GridDimensionManager::UpdateSizes()
    {
        if (updateInfo.NeedUpdate())
        {
#ifdef DEBUG_GRID_PERFORMANCE
            auto timing_start = std::chrono::high_resolution_clock::now();
            std::cout << "GridDimensionManager::UpdateSizes - Starting layout calculation" << std::endl;
            std::cout << "  Fixed values: " << fixedValues.size() 
                      << ", Auto values: " << autoValues.size() 
                      << ", Star values: " << starValues.size() << std::endl;
#endif
            
            GridLayoutHelper::CheckSizeListLength(numberOfValues, sizes, positions);

            UpdateFixed();

            int total = 0;
            int start = 0;

            if (boundsSize > 0)
            {
                int rest = boundsSize - totalSpacing;

                rest -= fixedTotalSize;
                rest = rest < 0 ? 0 : rest;

                UpdateAuto(rest);

                rest -= autoTotalSize;

                UpdateStar(rest);

                total = fixedTotalSize + autoTotalSize + starTotalSize + totalSpacing;

                bool forward = GetStart(start, total);
                GridLayoutHelper::UpdatePositions(sizes, positions, spacing, start, forward);
            }

            currentSize = total;
            
#ifdef DEBUG_GRID_PERFORMANCE
            auto timing_end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(timing_end - timing_start);
            std::cout << "GridDimensionManager::UpdateSizes - Completed in " << duration.count() 
                      << "μs, final size: " << currentSize << std::endl;
#endif
        }
    }

    int GridDimensionManager::GetSize(int available)
    {
        if (boundsSize != available)
        {
            boundsSize = available;
            updateInfo.UpdateAutoStar();
            UpdateSizes();
        }
        return currentSize;
    }

    void GridDimensionManager::SetBounds(const int &size, const int &max)
    {
        if (boundsSize != size || boundsMax != max)
        {
            boundsSize = size;
            boundsMax = max;
            updateInfo.UpdateAutoStar();
            UpdateSizes();
        }
    }
    void GridDimensionManager::SetChildren(std::vector<Visual *> *value)
    {
        if (children != value)
        {
            children = value;

            updateInfo.SetAll(true);
            if (boundsSize)
            {
                UpdateSizes();
            }
        }
    }

    void GridDimensionManager::SetValues(const std::string &value)
    {
        if (values != value)
        {
            std::string oldvalues = values;
            values = value;

            GridUpdateInfo result = GridLayoutHelper::UpdateGridValues(oldvalues, values, fixedValues, autoValues, starValues);

            numberOfValues = result.NumberOfCells;
            if (numberOfValues == 0)
                values.clear();

            UpdateSpacing();
            updateInfo.SetAll(true);
            UpdateSizes();
        }
    }

    void GridDimensionManager::SetSpacing(int value)
    {
        if (spacing != value)
        {
            spacing = value;
            UpdateSpacing();
            updateInfo.UpdateAutoStar();
            UpdateSizes();
        }
    }
}