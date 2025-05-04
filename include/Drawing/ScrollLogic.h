#pragma once

#include <algorithm>
#include <Drawing/Properties/Thickness.h>

namespace xit::Drawing
{
    /**
     * @brief This class manages the scroll logic for a view.
     *
     * It keeps track of the extent (total size) of the content, the viewport size,
     * and the current scroll offset. It provides methods to scroll the content
     * horizontally and vertically, as well as methods to scroll to specific
     * positions.
     */
    class ScrollLogic
    {
    private:
        int extentWidth;
        int extentHeight;
        int scrollMarginLeft;
        int scrollMarginTop;

    public:
        ScrollLogic() : extentWidth(0), extentHeight(0), scrollMarginLeft(0), scrollMarginTop(0) {}

        /**
         * @brief Sets the extent of the scrollable content.
         *
         * @param width The width of the content.
         * @param height The height of the content.
         */
        void SetExtent(int width, int height)
        {
            extentWidth = width;
            extentHeight = height;
        }

        /**
         * @brief Scrolls the content horizontally.
         *
         * @param delta The amount to scroll. Positive values scroll to the right,
         * negative values scroll to the left.
         * @param viewportWidth The width of the viewport.
         */
        void ScrollHorizontal(int delta, int viewportWidth)
        {
            int maxOffset = extentWidth - viewportWidth;
            scrollMarginLeft = std::clamp(scrollMarginLeft + delta, -maxOffset, 0);
        }

        /**
         * @brief Scrolls the content to a specific horizontal offset.
         *
         * @param offset The offset to scroll to.
         * @param delta The amount to scroll. Positive values scroll to the right,
         * negative values scroll to the left.
         * @param viewportWidth The width of the viewport.
         */
        void ScrollToHorizontalOffset(int offset, int delta, int viewportWidth)
        {
            int maxOffset = extentWidth - viewportWidth;
            scrollMarginLeft = std::clamp(-offset, -maxOffset, 0);
        }

        /**
         * @brief Scrolls the content vertically.
         *
         * @param delta The amount to scroll. Positive values scroll down,
         * negative values scroll up.
         * @param viewportHeight The height of the viewport.
         */
        void ScrollVertical(int delta, int viewportHeight)
        {
            int maxOffset = extentHeight - viewportHeight;
            scrollMarginTop = std::clamp(scrollMarginTop + delta, -maxOffset, 0);
        }

        /**
         * @brief Scrolls the content to a specific vertical offset.
         *
         * @param offset The offset to scroll to.
         * @param viewportHeight The height of the viewport.
         */
        void ScrollToVerticalOffset(int offset, int viewportHeight)
        {
            int maxOffset = extentHeight - viewportHeight;
            scrollMarginTop = std::clamp(-offset, -maxOffset, 0);
        }

        /**
         * @brief Scrolls the content to the top.
         */
        void ScrollToTop()
        {
            scrollMarginTop = 0;
        }

        /**
         * @brief Scrolls the content to the left.
         */
        void ScrollToLeft()
        {
            scrollMarginLeft = 0;
        }

        /**
         * @brief Scrolls the content to the right.
         */
        void ScrollToRight()
        {
            scrollMarginLeft = -extentWidth;
        }

        /**
         * @brief Scrolls the content to the bottom.
         */
        void ScrollToBottom()
        {
            scrollMarginTop = -extentHeight;
        }

        /**
         * @brief Scrolls the content to a specific horizontal offset.
         *
         * @param offset The offset to scroll to.
         */
        void ScrollToHorizontalOffset(int offset)
        {
            scrollMarginLeft = -offset;
        }

        /**
         * @brief Scrolls the content to a specific vertical offset.
         *
         * @param offset The offset to scroll to.
         */
        void ScrollToVerticalOffset(int offset)
        {
            scrollMarginTop = -offset;
        }

        /**
         * @brief Gets the extent width.
         *
         * @return The extent width.
         */
        __always_inline int GetExtentWidth() const { return extentWidth; }
        /**
         * @brief Sets the extent width.
         *
         * @param value The extent width.
         */
        void SetExtentWidth(int value) { extentWidth = value; }

        /**
         * @brief Gets the extent height.
         *
         * @return The extent height.
         */
        __always_inline int GetExtentHeight() const { return extentHeight; }
        /**
         * @brief Sets the extent height.
         *
         * @param value The extent height.
         */
        void SetExtentHeight(int value) { extentHeight = value; }

        /**
         * @brief Gets the horizontal offset.
         *
         * @return The horizontal offset.
         */
        __always_inline int GetHorizontalOffset() const { return -scrollMarginLeft; }
        /**
         * @brief Gets the vertical offset.
         *
         * @return The vertical offset.
         */
        __always_inline int GetVerticalOffset() const { return -scrollMarginTop; }

        /**
         * @brief Gets the scroll margin.
         *
         * @return The scroll margin.
         */
        __always_inline Thickness GetScrollMargin() const
        {
            return Thickness(scrollMarginLeft, scrollMarginTop, 0, 0);
        }
        /**
         * @brief Sets the scroll margin.
         *
         * @param left The left scroll margin.
         * @param top The top scroll margin.
         */
        __always_inline void SetScrollMargin(int left, int top)
        {
            scrollMarginLeft = left;
            scrollMarginTop = top;
        }

        /**
         * @brief Gets the left scroll margin.
         *
         * @return The left scroll margin.
         */
        __always_inline int GetScrollMarginLeft() const { return scrollMarginLeft; }
        /**
         * @brief Sets the left scroll margin.
         *
         * @param value The left scroll margin.
         */
        __always_inline void SetScrollMarginLeft(int value) { scrollMarginLeft = value; }

        /**
         * @brief Gets the top scroll margin.
         *
         * @return The top scroll margin.
         */
        __always_inline int GetScrollMarginTop() const { return scrollMarginTop; }
        /**
         * @brief Sets the top scroll margin.
         *
         * @param value The top scroll margin.
         */
        __always_inline void SetScrollMarginTop(int value) { scrollMarginTop = value; }
    };
}