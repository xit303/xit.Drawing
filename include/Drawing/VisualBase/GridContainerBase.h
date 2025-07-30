#pragma once

#include <string>
#include <Event.h>
#include <Drawing/Properties/HorizontalContentAlignmentProperty.h>
#include <Drawing/Properties/VerticalContentAlignmentProperty.h>

namespace xit::Drawing
{
    class GridContainerBase : public HorizontalContentAlignmentProperty, 
                              public VerticalContentAlignmentProperty
    {
    private:
        std::string columns;
        int columnSpacing;
        std::string rows;
        int rowSpacing;
        size_t numberOfColumns;
        size_t numberOfRows;

        // TODO ?? how ?? Rectangle clientBounds;

        inline void HandleColumnsChanged()
        {
            EventArgs e;
            OnColumnsChanged(e);
        }
        inline void HandleColumnSpacingChanged()
        {
            EventArgs e;
            OnColumnSpacingChanged(e);
        }
        inline void HandleRowsChanged()
        {
            EventArgs e;
            OnRowsChanged(e);
        }
        inline void HandleRowSpacingChanged()
        {
            EventArgs e;
            OnRowSpacingChanged(e);
        }

    protected:
        virtual void OnColumnsChanged(EventArgs &e) { (void)e; }
        virtual void OnColumnSpacingChanged(EventArgs &e) { (void)e; }
        virtual void OnRowsChanged(EventArgs &e) { (void)e; }
        virtual void OnRowSpacingChanged(EventArgs &e) { (void)e; }

        void SetNumberOfColumns(size_t value)
        {
            if (numberOfColumns != value)
            {
                numberOfColumns = value;
            }
        }
        void SetNumberOfRows(size_t value)
        {
            if (numberOfRows != value)
            {
                numberOfRows = value;
            }
        }

    public:
        __always_inline const std::string &GetColumns() const { return columns; }
        void SetColumns(const std::string &value)
        {
            if (columns != value)
            {
                columns = value;
                HandleColumnsChanged();
            }
        }

        __always_inline int GetColumnSpacing() const { return columnSpacing; }
        void SetColumnSpacing(int value)
        {
            if (columnSpacing != value)
            {
                columnSpacing = value;
                HandleColumnSpacingChanged();
            }
        }

        __always_inline const std::string &GetRows() const { return rows; }
        void SetRows(const std::string &value)
        {
            if (rows != value)
            {
                rows = value;
                HandleRowsChanged();
            }
        }

        __always_inline int GetRowSpacing() const { return rowSpacing; }
        void SetRowSpacing(int value)
        {
            if (rowSpacing != value)
            {
                rowSpacing = value;
                HandleRowSpacingChanged();
            }
        }

        __always_inline size_t GetNumberOfColumns() const { return numberOfColumns; }
        __always_inline size_t GetNumberOfRows() const { return numberOfRows; }

        // TODO ?? how ?? const Rectangle& ClientBounds = clientBounds;

        GridContainerBase()
        {
            columns = "*";
            rows = "*";

            columnSpacing = rowSpacing = 0;
            numberOfColumns = numberOfRows = 0;
        }
    };
}
