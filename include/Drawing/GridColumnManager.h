/**
 * @file GridColumnManager.h
 * @brief Defines the GridColumnManager class for managing grid columns in a drawing context.
 */

#pragma once

#include <Drawing/GridDimensionManager.h>
#include <Drawing/Properties/HorizontalAlignmentProperty.h>

namespace xit::Drawing
{
    /**
     * @class GridColumnManager
     * @brief Manages the columns of a grid, including their dimensions, positions, and alignment.
     * 
     * The GridColumnManager class inherits from HorizontalAlignmentProperty and GridDimensionManager
     * to provide functionality for managing grid column properties such as widths, positions, spacing,
     * and alignment. It also supports setting bounds and managing child elements.
     */
    class GridColumnManager : public HorizontalAlignmentProperty, public GridDimensionManager
    {
    protected:
        /**
         * @brief Called when the horizontal alignment property changes.
         * @param e Event arguments associated with the change.
         */
        virtual void OnHorizontalAlignmentChanged(EventArgs &e) override;

        /**
         * @brief Calculates the starting position of a column.
         * @param start Reference to the starting position to be calculated.
         * @param total Total available space.
         * @return True if the alignment of the element is not Right.
         */
        virtual bool GetStart(int &start, int total) override;

        /**
         * @brief Gets the index and span of a content element.
         * @param content Pointer to the content element.
         * @param index Reference to the index to be set.
         * @param span Reference to the span to be set.
         */
        virtual void GetIndexAndSpan(Visual *content, size_t &index, size_t &span) const override;

    public:
        /**
         * @brief Constructs a GridColumnManager object.
         */
        GridColumnManager() : GridDimensionManager(&Visual::MeasureWidth) {}

        /**
         * @brief Destroys the GridColumnManager object.
         */
        ~GridColumnManager() = default;

        /**
         * @brief Sets the bounds of the grid columns.
         * @param value The rectangle defining the bounds.
         */
        void SetBounds(const Rectangle &value);

        /**
         * @brief Gets the width of the grid columns based on available space.
         * @param available The available width.
         * @return The calculated width.
         */
        int GetWidth(int available);

        /**
         * @brief Sets the child elements managed by the grid columns.
         * @param value Pointer to a vector of child content elements.
         */
        void SetChildren(std::vector<Visual *> *value);

        /**
         * @brief Gets the widths of all columns.
         * @return A reference to a vector containing the widths of the columns.
         */
        __always_inline const std::vector<int> &GetColumnWidths() const { return GetSizes(); }

        /**
         * @brief Gets the positions of all columns.
         * @return A reference to a vector containing the positions of the columns.
         */
        __always_inline const std::vector<int> &GetColumnPositions() const { return GetPositions(); }

        /**
         * @brief Gets the column definitions as a string.
         * @return A reference to the string containing column definitions.
         */
        __always_inline const std::string &GetColumns() const { return GetValues(); }

        /**
         * @brief Sets the column definitions.
         * @param value The string containing column definitions.
         */
        void SetColumns(const std::string &value);

        /**
         * @brief Gets the spacing between columns.
         * @return A reference to the spacing value.
         */
        __always_inline const int &GetColumnSpacing() const { return GetSpacing(); }

        /**
         * @brief Sets the spacing between columns.
         * @param value The spacing value to set.
         */
        void SetColumnSpacing(int value);

        /**
         * @brief Gets the number of columns.
         * @return A reference to the number of columns.
         */
        __always_inline const size_t &GetNumberOfColumns() const { return GetNumberOfValues(); }
    };
}