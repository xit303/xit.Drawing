/**
 * @file GridDimensionManager.h
 * @brief Defines the GridDimensionManager class for managing grid dimensions in a layout.
 */

#pragma once

#include <Drawing/GridLayoutHelper.h>

namespace xit::Drawing
{
    /**
     * @class GridDimensionManager
     * @brief Manages the dimensions of a grid layout, including fixed, auto, and star values.
     * 
     * This class provides functionality to calculate and update grid dimensions
     * based on fixed, auto, and star sizing strategies. It also manages spacing
     * and bounds for the grid layout.
     */
    class GridDimensionManager
    {
    private:
        std::map<size_t, int> fixedValues; ///< Map of fixed values for grid dimensions.
        std::map<size_t, int> starValues; ///< Map of star values for proportional sizing.
        std::vector<size_t> autoValues; ///< List of auto-sized grid dimensions.

        std::vector<int> sizes; ///< Calculated sizes for each grid dimension.
        std::vector<int> positions; ///< Calculated positions for each grid dimension.

        GridUpdateInfo updateInfo; ///< Information about the grid update state.

        int fixedTotalSize; ///< Total size of fixed dimensions.
        int autoTotalSize; ///< Total size of auto dimensions.
        int starTotalSize; ///< Total size of star dimensions.
        int currentSize; ///< Current total size of the grid.
        size_t totalSpacing; ///< Total spacing between grid elements.
        std::string values; ///< String representation of grid values.
        int spacing; ///< Spacing between grid elements.
        size_t numberOfValues; ///< Total number of grid values.

        int boundsMax; ///< Maximum bounds of the grid (including left/top).
        int boundsSize; ///< Size of the grid bounds.

        std::vector<Visual *> *children; ///< Pointer to the list of child elements.
        MeasureDelegate measureDelegate; ///< Delegate for measuring grid elements. E.g. MeasureWidth or MeasureHeight.

    protected:
        /**
         * @brief Updates the fixed dimensions of the grid.
         */
        void UpdateFixed();

        /**
         * @brief Updates the auto-sized dimensions of the grid.
         * @param availableSize The available size for auto dimensions.
         */
        void UpdateAuto(int availableSize);

        /**
         * @brief Updates the star-sized dimensions of the grid.
         * @param availableSize The available size for star dimensions.
         */
        void UpdateStar(int availableSize);

        /**
         * @brief Updates the spacing between grid elements.
         */
        void UpdateSpacing();

        /**
         * @brief Updates the sizes of all grid dimensions.
         */
        void UpdateSizes();

        /**
         * @brief Gets the starting position for the grid layout.
         * @param start Reference to store the starting position.
         * @param total The total size of the grid.
         * @return True if the alignment of the element is not Right or Bottom.
         */
        virtual bool GetStart(int &start, int total) = 0;

        /**
         * @brief Gets the grid index and span for the current dimension (row or column).
         * @param content The content element to query.
         * @param index Reference to store the index (row or column).
         * @param span Reference to store the span (row span or column span).
         */
        virtual void GetIndexAndSpan(Visual *content, int &index, int &span) const = 0;

        /**
         * @brief Gets the calculated sizes of the grid dimensions.
         * @return A constant reference to the vector of sizes.
         */
        __always_inline const std::vector<int> &GetSizes() const { return sizes; }

        /**
         * @brief Gets the calculated positions of the grid dimensions.
         * @return A constant reference to the vector of positions.
         */
        __always_inline const std::vector<int> &GetPositions() const { return positions; }

        /**
         * @brief Calculates the size of the grid based on the available size.
         * @param available The available size for the grid.
         * @return The calculated size of the grid.
         */
        int GetSize(int available);

        /**
         * @brief Gets the maximum bounds of the grid.
         * @return The maximum bounds of the grid.
         */
        __always_inline const int GetBoundsMax() const { return boundsMax; }

        /**
         * @brief Gets the size of the grid bounds.
         * @return The size of the grid bounds.
         */
        __always_inline const int GetBoundsSize() const { return boundsSize; }

        /**
         * @brief Sets the bounds of the grid.
         * @param size The size of the bounds.
         * @param max The maximum bounds (including left/top).
         */
        void SetBounds(const int &size, const int &max);

        /**
         * @brief Sets the child elements of the grid.
         * @param value Pointer to the list of child elements.
         */
        void SetChildren(std::vector<Visual *> *value);

        /**
         * @brief Gets the string representation of grid values.
         * @return A constant reference to the string of values.
         */
        __always_inline const std::string &GetValues() const { return values; }

        /**
         * @brief Sets the string representation of grid values.
         * @param value The string of values to set.
         */
        void SetValues(const std::string &value);

        /**
         * @brief Gets the spacing between grid elements.
         * @return The spacing value.
         */
        __always_inline const int &GetSpacing() const { return spacing; }

        /**
         * @brief Sets the spacing between grid elements.
         * @param value The spacing value to set.
         */
        void SetSpacing(int value);

        /**
         * @brief Gets the total number of grid values.
         * @return The total number of values.
         */
        __always_inline const size_t &GetNumberOfValues() const { return numberOfValues; }

    public:
        /**
         * @brief Constructs a GridDimensionManager with a measure delegate.
         * @param measureDelegate The delegate for measuring grid elements.
         */
        GridDimensionManager(MeasureDelegate measureDelegate);
    };
}