/**
 * @file GridRowManager.h
 * @brief Defines the GridRowManager class for managing grid rows in a drawing context.
 */

#pragma once

#include <Drawing/GridDimensionManager.h>
#include <Drawing/Properties/VerticalAlignmentProperty.h>

namespace xit::Drawing
{
    /**
     * @class GridRowManager
     * @brief Manages the rows of a grid, including their dimensions, positions, and alignment.
     * 
     * The GridRowManager class inherits from VerticalAlignmentProperty and GridDimensionManager
     * to provide functionality for managing grid row properties such as heights, positions, spacing,
     * and alignment. It also supports setting bounds and managing child elements.
     */
    class GridRowManager : public VerticalAlignmentProperty, public GridDimensionManager
    {
    protected:
        /**
         * @brief Called when the vertical alignment property changes.
         * @param e Event arguments associated with the change.
         */
        virtual void OnVerticalAlignmentChanged(EventArgs &e) override;

        /**
         * @brief Calculates the starting position of a row.
         * @param start Reference to the starting position to be calculated.
         * @param total Total available space.
         * @return True if the alignment of the element is not Bottom.
         */
        virtual bool GetStart(int &start, int total) override;

        /**
         * @brief Gets the index and span for a content element.
         * @param content Pointer to the content element.
         * @param index Reference to the index to be set.
         * @param span Reference to the span to be set.
         */
        virtual void GetIndexAndSpan(Visual *content, size_t &index, size_t &span) const override;

    public:
        /**
         * @brief Constructs a GridRowManager object.
         */
        GridRowManager() : GridDimensionManager(&Visual::MeasureHeight) {}

        /**
         * @brief Destroys the GridRowManager object.
         */
        ~GridRowManager() = default;

        /**
         * @brief Sets the bounds of the grid rows.
         * @param value The rectangle defining the bounds.
         */
        void SetBounds(const Rectangle &value);

        /**
         * @brief Gets the height of the grid rows based on available space.
         * @param available The available height.
         * @return The calculated height.
         */
        int GetHeight(int available);

        /**
         * @brief Sets the child elements managed by the grid rows.
         * @param value Pointer to a vector of child content elements.
         */
        void SetChildren(std::vector<Visual *> *value);

        /**
         * @brief Gets the heights of all rows.
         * @return A reference to a vector containing the heights of the rows.
         */
        __always_inline const std::vector<int> &GetRowHeights() const { return GetSizes(); }

        /**
         * @brief Gets the positions of all rows.
         * @return A reference to a vector containing the positions of the rows.
         */
        __always_inline const std::vector<int> &GetRowPositions() const { return GetPositions(); }

        /**
         * @brief Gets the row definitions as a string.
         * @return A reference to the string containing row definitions.
         */
        __always_inline const std::string &GetRows() const { return GetValues(); }

        /**
         * @brief Sets the row definitions.
         * @param value The string containing row definitions.
         */
        void SetRows(const std::string &value);

        /**
         * @brief Gets the spacing between rows.
         * @return A reference to the spacing value.
         */
        __always_inline const int &GetRowSpacing() const { return GetSpacing(); }

        /**
         * @brief Sets the spacing between rows.
         * @param value The spacing value to set.
         */
        void SetRowSpacing(int value);

        /**
         * @brief Gets the number of rows.
         * @return The number of rows.
         */
        __always_inline size_t GetNumberOfRows() const { return GetNumberOfValues(); }
    };
}