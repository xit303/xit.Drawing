#include <StringHelper.h>
#include <Exceptions.h>
#include <Drawing/GridLayoutHelper.h>
#ifdef DEBUG_GRID_PERFORMANCE
#include <chrono>
#include <iostream>
#endif

namespace xit::Drawing
{
    GridUpdateInfo GridLayoutHelper::UpdateGridValues(std::string &oldValues, std::string &newValues, std::map<size_t, int> &fixedValues, std::vector<size_t> &autoValues, std::map<size_t, int> &starValues)
    {
        GridUpdateInfo result;

        // Split and trim old values
        std::vector<std::string> oldValuesSplitted;
        if (!oldValues.empty())
        {
            StringHelper::Trim(oldValues);
            oldValuesSplitted = StringHelper::Split(oldValues, ',');
        }

        size_t oldValueCount = oldValuesSplitted.size();

        // Handle empty new values
        if (newValues.empty())
        {
            result.UpdateFixed = !fixedValues.empty();
            result.UpdateAuto = !autoValues.empty();
            result.UpdateStar = !starValues.empty();
            return result;
        }

        // Split and trim new values
        StringHelper::Trim(newValues);
        std::vector<std::string> newValuesSplitted = StringHelper::Split(newValues, ',');
        size_t newValueCount = newValuesSplitted.size();
        result.NumberOfCells = newValueCount;

        // Adjust size of fixed, auto, and star values
        if (oldValueCount > newValueCount)
        {
            for (size_t i = newValueCount; i < oldValueCount; ++i)
            {
                fixedValues.erase(i);
                autoValues.erase(std::remove(autoValues.begin(), autoValues.end(), i), autoValues.end());
                starValues.erase(i);
            }
        }

        // Process each new value
        for (size_t i = 0; i < newValueCount; ++i)
        {
            std::string value = newValuesSplitted[i];
            StringHelper::Trim(value);
            std::string oldValue = (i < oldValueCount) ? oldValuesSplitted[i] : "";

            if (value != oldValue)
            {
                if (value == "Auto")
                {
                    result.UpdateAuto = true;
                    autoValues.push_back(i);
                    if (starValues.erase(i))
                        result.UpdateStar = true;
                    if (fixedValues.erase(i))
                        result.UpdateFixed = true;
                }
                else if (value.find('*') != std::string::npos)
                {
                    result.UpdateStar = true;
                    autoValues.erase(std::remove(autoValues.begin(), autoValues.end(), i), autoValues.end());

                    if (std::erase(autoValues, i) != 0)
                        result.UpdateAuto = true;

                    if (fixedValues.erase(i))
                        result.UpdateFixed = true;

                    value.erase(std::remove(value.begin(), value.end(), '*'), value.end());
                    StringHelper::Trim(value);
                    int multiplier = value.empty() ? 1 : std::max(1, atoi(value.c_str()));
                    starValues[i] = multiplier;
                }
                else
                {
                    result.UpdateFixed = true;
                    if (std::erase(autoValues, i) != 0)
                        result.UpdateAuto = true;

                    if (starValues.erase(i))
                        result.UpdateStar = true;

                    int number = atoi(value.c_str());
                    if (number > 0)
                    {
                        fixedValues[i] = number;
                    }
                    else
                    {
                        throw Exception("Grid.Columns contains invalid value");
                    }
                }
            }
        }

        return result;
    }

    void GridLayoutHelper::CheckSizeListLength(size_t numberOfValues, std::vector<int> &sizes, std::vector<int> &positions)
    {
        while (sizes.size() > numberOfValues)
        {
            size_t pos = sizes.size() - 1;
            sizes.erase(sizes.begin() + pos);
            positions.erase(positions.begin() + pos);
        }
        while (sizes.size() < numberOfValues)
        {
            sizes.push_back(0);
            positions.push_back(0);
        }
    }

    int GridLayoutHelper::UpdateSizes(std::vector<int> &sizes, std::map<size_t, int> &values)
    {
        int total = 0;

        for (std::pair<size_t, int> value : values)
        {
            int index = static_cast<int>(value.first);

            sizes[index] = value.second > 0 ? value.second : 0;

            total += sizes[index];
        }

        return total;
    }

    void GridLayoutHelper::CheckAutoContent(size_t index, size_t span, std::vector<int> &sizes, std::vector<size_t> &autoValues, int availableSize, MeasureDelegate measureDelegate, Visual *content)
    {
        auto item = std::find(autoValues.begin(), autoValues.end(), index);
        if ((item != autoValues.end()) &&
            content->GetVisibility() != Visibility::Collapsed)
        {
#ifdef DEBUG_GRID_PERFORMANCE
            auto start = std::chrono::high_resolution_clock::now();
            std::cout << "GridLayoutHelper::CheckAutoContent - Measuring " << content->GetName() 
                      << " at index " << index << ", span " << span << std::endl;
#endif
            
            size_t contentSize = (content->*measureDelegate)(availableSize);

#ifdef DEBUG_GRID_PERFORMANCE
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            std::cout << "GridLayoutHelper::CheckAutoContent - Measurement took " << duration.count() 
                      << "μs, result: " << contentSize << std::endl;
#endif

            if (span == 1)
            {
                size_t autoSize = sizes[index];

                if (contentSize > autoSize)
                {
                    sizes[index] = static_cast<int>(contentSize);
                }
            }
            else if (span > 1)
            {
                size_t total = 0;
                for (size_t i = index; i < index + span && i < sizes.size(); i++)
                {
                    total += sizes[i];
                }

                if (total < contentSize)
                {
                    size_t minSingleSize = contentSize / span;

                    for (size_t i = index; i < index + span && i < sizes.size(); i++)
                    {
                        size_t size = sizes[i];

                        if (size < minSingleSize)
                            sizes[i] = static_cast<int>(minSingleSize);
                    }
                }
            }
        }
    }

    int GridLayoutHelper::UpdateStar(std::vector<int> &sizes, std::map<size_t, int> &values, int availableSize)
    {
        int divisor = 0;
        int total = 0;

        for (std::pair<size_t, int> value : values)
        {
            divisor += value.second;
        }

        if (divisor < 1)
        {
            divisor = 1;
        }

        availableSize = availableSize < 0 ? 0 : availableSize;

        int singlePartSize = (int)(availableSize / divisor);
        int missing = (int)(availableSize - (singlePartSize * divisor));

        for (std::pair<size_t, int> value : values)
        {
            int size = value.second * (int)singlePartSize;
            if (missing > 0)
            {
                size++;
                missing--;
            }

            size = size < 0 ? 0 : size;
            if (size > 0)
            {
                total += size;
            }

            sizes[value.first] = size;
        }

        return total;
    }

    void GridLayoutHelper::UpdatePositions(std::vector<int> &sizes, std::vector<int> &positions, int spacing, int start, bool forward)
    {
        int position = start;
        size_t size = sizes.size();

        if (forward)
        {
            for (size_t i = 0; i < size; i++)
            {
                positions[i] = position;
                if (i < size - 1)
                {
                    position += sizes[i];

                    if (sizes[i] != 0)
                    {
                        position += spacing;
                    }
                }
            }
        }
        else
        {
            for (int i = static_cast<int>(size) - 1; i >= 0; i--)
            {
                positions[i] = position - sizes[i];

                if (i > 0)
                {
                    position -= sizes[i];

                    if (sizes[i] != 0)
                    {
                        position -= spacing;
                    }
                }
            }
        }
    }
} // namespace xit::Drawing
