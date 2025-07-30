#pragma once

/**
 * @file GridLayoutHelper.h
 * @brief Provides helper functions for managing grid layouts, including size updates, position updates, and content measurement.
 */

#include <string>
#include <map>
#include <vector>
#include <Drawing/GridUpdateInfo.h>
#include <Drawing/Visual.h>

namespace xit::Drawing
{
    typedef int (Visual::*MeasureDelegate)(int availableSize);

    /**
     * @class GridLayoutHelper
     * @brief A utility class for managing grid layout operations such as updating sizes, positions, and handling auto and star values.
     */
    class GridLayoutHelper
    {
    public:
        /**
         * @brief Updates grid values based on old and new configurations.
         * @param oldValues The previous grid configuration as a string.
         * @param newValues The new grid configuration as a string.
         * @param fixedValues A map of fixed values indexed by their positions.
         * @param autoValues A vector of indices representing auto-sized values.
         * @param starValues A map of star-sized values indexed by their positions.
         * @return A GridUpdateInfo object containing the update results.
         */
        static GridUpdateInfo UpdateGridValues(std::string &oldValues, std::string &newValues, std::map<size_t, int> &fixedValues, std::vector<size_t> &autoValues, std::map<size_t, int> &starValues);

        /**
         * @brief Ensures the size and position lists match the expected number of values.
         * @param numberOfValues The expected number of values.
         * @param sizes A vector of sizes to be checked and updated.
         * @param positions A vector of positions to be checked and updated.
         */
        static void CheckSizeListLength(size_t numberOfValues, std::vector<int> &sizes, std::vector<int> &positions);

        /**
         * @brief Updates the sizes based on the provided values.
         * @param sizes A vector of sizes to be updated.
         * @param values A map of values to apply to the sizes.
         * @return The total size after the update.
         */
        static int UpdateSizes(std::vector<int> &sizes, std::map<size_t, int> &values);

        /**
         * @brief Checks and updates the content for auto-sized grid cells.
         * @param index The index of the grid cell.
         * @param span The span of the grid cell.
         * @param sizes A vector of sizes to be updated.
         * @param autoValues A vector of indices representing auto-sized values.
         * @param availableSize The available size for the grid cell.
         * @param measureDelegate A delegate for measuring the content size.
         * @param content A pointer to the content object.
         */
        static void CheckAutoContent(size_t index, size_t span, std::vector<int> &sizes, std::vector<size_t> &autoValues, int availableSize, MeasureDelegate measureDelegate, Visual *content);

        /**
         * @brief Updates the sizes for star-sized grid cells.
         * @param sizes A vector of sizes to be updated.
         * @param values A map of star-sized values to apply.
         * @param availableSize The total available size for the grid.
         * @return The remaining size after the update.
         */
        static int UpdateStar(std::vector<int> &sizes, std::map<size_t, int> &values, int availableSize);

        /**
         * @brief Updates the positions of grid cells based on sizes and spacing.
         * @param sizes A vector of sizes for the grid cells.
         * @param positions A vector of positions to be updated.
         * @param spacing The spacing between grid cells.
         * @param start The starting position for the grid.
         * @param forward A flag indicating whether to update positions in a forward direction.
         */
        static void UpdatePositions(std::vector<int> &sizes, std::vector<int> &positions, int spacing, int start, bool forward);
    }; 
}
