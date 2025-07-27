#pragma once

#include <algorithm>
#include <Drawing/Properties/MarginProperty.h>
#include <Drawing/Properties/BorderThicknessProperty.h>
#include <Drawing/Properties/PaddingProperty.h>
#include <Drawing/Rectangle.h>

namespace xit::Drawing
{
    /**
     * @brief Represents a box model that includes margin, border thickness, and padding properties.
     */
    class BoxModel : public MarginProperty,
                     public BorderThicknessProperty,
                     public PaddingProperty
    {
    private:
        // No caching needed - calculations are lightweight

    protected:

    public:
        BoxModel() = default;
        virtual ~BoxModel() = default;

        // Total box dimensions including margin, border, and padding
        __always_inline int GetTotalBoxWidth() const
        {
            return GetMargin().GetWidth() + GetPadding().GetWidth() + GetBorderThickness().GetWidth();
        }
        __always_inline int GetTotalBoxHeight() const
        {
            return GetMargin().GetHeight() + GetPadding().GetHeight() + GetBorderThickness().GetHeight();
        }

        // Non-content dimensions (border + padding) - used for clientBounds calculations
        __always_inline int GetNonContentWidth() const
        {
            return GetPadding().GetWidth() + GetBorderThickness().GetWidth();
        }
        __always_inline int GetNonContentHeight() const
        {
            return GetPadding().GetHeight() + GetBorderThickness().GetHeight();
        }

        // Calculate client area size from total size (removes border + padding)
        __always_inline int GetClientWidth(int totalWidth) const
        {
            return std::max(0, totalWidth - GetNonContentWidth());
        }
        __always_inline int GetClientHeight(int totalHeight) const
        {
            return std::max(0, totalHeight - GetNonContentHeight());
        }

        // Calculate total size needed for given client area (adds border + padding)
        __always_inline int GetTotalWidthFromClient(int clientWidth) const
        {
            return clientWidth + GetNonContentWidth();
        }
        __always_inline int GetTotalHeightFromClient(int clientHeight) const
        {
            return clientHeight + GetNonContentHeight();
        }

        /**
         * @brief Calculate client rectangle from element bounds (removes border + padding from edges)
         * @param elementBounds The total bounds of the element
         * @return The client rectangle (content area)
         */
        __always_inline Rectangle GetClientRectangle(const Rectangle& elementBounds) const
        {
            const Thickness& padding = GetPadding();
            const Thickness& borderThickness = GetBorderThickness();
            
            return Rectangle(
                elementBounds.GetLeft() + padding.GetLeft() + borderThickness.GetLeft(),
                elementBounds.GetTop() + padding.GetTop() + borderThickness.GetTop(),
                elementBounds.GetWidth() - GetNonContentWidth(),
                elementBounds.GetHeight() - GetNonContentHeight()
            );
        }

        /**
         * @brief Calculate client rectangle from element bounds (output parameter version)
         * @param elementBounds The total bounds of the element
         * @param[out] clientRect The client rectangle to fill
         */
        __always_inline void GetClientRectangle(const Rectangle& elementBounds, Rectangle& clientRect) const
        {
            const Thickness& padding = GetPadding();
            const Thickness& borderThickness = GetBorderThickness();
            
            clientRect.Set(
                elementBounds.GetLeft() + padding.GetLeft() + borderThickness.GetLeft(),
                elementBounds.GetTop() + padding.GetTop() + borderThickness.GetTop(),
                elementBounds.GetWidth() - GetNonContentWidth(),
                elementBounds.GetHeight() - GetNonContentHeight()
            );
        }

        /**
         * @brief Calculate client rectangle from position and size
         * @param left Left position of the element
         * @param top Top position of the element  
         * @param width Width of the element
         * @param height Height of the element
         * @return The client rectangle (content area)
         */
        __always_inline Rectangle GetClientRectangle(int left, int top, int width, int height) const
        {
            return GetClientRectangle(Rectangle(left, top, width, height));
        }

        // Legacy method names for backward compatibility
        __always_inline int GetBorderAndPaddingWidth() const
        {
            return GetNonContentWidth();
        }
        __always_inline int GetBorderAndPaddingHeight() const
        {
            return GetNonContentHeight();
        }
        __always_inline int GetBoxWidthWithoutMargin() const
        {
            return GetNonContentWidth();
        }
        __always_inline int GetBoxHeightWithoutMargin() const
        {
            return GetNonContentHeight();
        }

        // Additional utility methods for common layout calculations
        
        /**
         * @brief Calculate content width from total width (removes margin, border, padding)
         * @param totalWidth The total available width
         * @return The content width
         */
        __always_inline int GetContentWidthFromTotal(int totalWidth) const
        {
            return std::max(0, totalWidth - GetTotalBoxWidth());
        }
        
        /**
         * @brief Calculate content height from total height (removes margin, border, padding) 
         * @param totalHeight The total available height
         * @return The content height
         */
        __always_inline int GetContentHeightFromTotal(int totalHeight) const
        {
            return std::max(0, totalHeight - GetTotalBoxHeight());
        }
    };
} // namespace xit::Drawing