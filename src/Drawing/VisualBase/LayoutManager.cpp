#include <Drawing/VisualBase/LayoutManager.h>
#include <OpenGL/Scene2D.h>
#include <Drawing/DebugUtils.h>

namespace xit::Drawing::VisualBase
{
    //******************************************************************************
    // Public
    //******************************************************************************

    LayoutManager::LayoutManager()
    {
        actualWidth = 0;
        actualHeight = 0;
        renderLeft = 0;
        renderTop = 0;
        needWidthRecalculation = true;
        needHeightRecalculation = true;
        needLeftRecalculation = true;
        needTopRecalculation = true;
        invalidated = true;
    }

    void LayoutManager::Invalidate()
    {
        if (GetVisibility() != Visibility::Collapsed)
        {
            invalidated = true;

#ifdef DEBUG_LAYOUT_MANAGER
            std::cout << "Invalidating: " << GetName() << " (Type: " << typeid(*this).name() << ")" << std::endl;
#endif

            EventArgs e;
            OnInvalidated(e);
            NotifyWindowOfInvalidation();
        }
        else
        {
#ifdef DEBUG_LAYOUT_MANAGER
            std::cout << "Skipping invalidation for collapsed visual: " << GetName() << std::endl;
#endif
        }
    }

    void LayoutManager::NotifyWindowOfInvalidation()
    {
        // This method will be overridden by Visual class to access the parent properly
        // Base LayoutManager doesn't have access to parent, so this is a no-op
    }

    Size LayoutManager::Measure(const Size &availableSize)
    {
        MeasureWidth(availableSize.GetWidth());
        MeasureHeight(availableSize.GetHeight());
        return desiredSize;
    }

    bool LayoutManager::Update(const Rectangle &newBounds)
    {
        bool needRedraw = false;
        bool wasInvalidated = invalidated; // Capture invalidated state before OnUpdate resets it

        if (GetVisibility() != Visibility::Collapsed)
        {
            // Check if recalculation is needed based on actual changes
            bool boundsChanged = (bounds != newBounds);

            // Set recalculation flags for layout changes (bounds changed)
            if (boundsChanged)
            {
                needWidthRecalculation = true;
                needHeightRecalculation = true;
                needLeftRecalculation = true;
                needTopRecalculation = true;
            }

#ifdef DEBUG_LAYOUT_MANAGER
            if (boundsChanged || invalidated)
            {
                std::cout << "LayoutManager::Update - " << GetName() << " boundsChanged="
                          << boundsChanged << " invalidated=" << invalidated
                          << " layoutRecalc=" << (needWidthRecalculation || needHeightRecalculation || needLeftRecalculation || needTopRecalculation) << std::endl;
            }
#endif

            // Always update if invalidated (for visual refreshes) or if layout recalculation is needed
            needRedraw = needLeftRecalculation || needTopRecalculation || needWidthRecalculation || needHeightRecalculation || invalidated || boundsChanged;

            if (needRedraw)
            {
#ifdef DEBUG_LAYOUT_MANAGER
                std::cout << "Updating layout for: " << GetName()
                          << " invalidated=" << invalidated
                          << " needLeft=" << needLeftRecalculation
                          << " needTop=" << needTopRecalculation
                          << " needWidth=" << needWidthRecalculation
                          << " needHeight=" << needHeightRecalculation << std::endl;
#endif
                this->bounds = newBounds;
                OnUpdate(bounds);
            }
#ifdef DEBUG_LAYOUT_MANAGER
            else
            {
                std::cout << "NOT updating layout for: " << GetName()
                          << " (needRedraw=false) invalidated=" << invalidated
                          << " needLeft=" << needLeftRecalculation
                          << " needTop=" << needTopRecalculation
                          << " needWidth=" << needWidthRecalculation
                          << " needHeight=" << needHeightRecalculation << std::endl;
            }
#endif
        }
        else
        {
            needRedraw = false;
#ifdef DEBUG_LAYOUT_MANAGER
            std::cout << "NOT updating layout for: " << GetName() << " (collapsed)" << std::endl;
#endif
        }
#ifdef DEBUG_LAYOUT_MANAGER
        std::cout << "Update returning: " << (needRedraw || wasInvalidated)
                  << " for " << GetName()
                  << " (needRedraw=" << needRedraw << " wasInvalidated=" << wasInvalidated << ")" << std::endl;
#endif
        return needRedraw || wasInvalidated;
    }

    //******************************************************************************
    // Protected
    //******************************************************************************

    void LayoutManager::OnHorizontalAlignmentChanged(EventArgs &e)
    {
#ifdef DEBUG_LAYOUT_MANAGER
        std::cout << "LayoutManager::OnHorizontalAlignmentChanged - " << GetName() << std::endl;
#endif
        needWidthRecalculation = true;
        needLeftRecalculation = true; // Position depends on alignment
        Invalidate();
    }

    void LayoutManager::OnVerticalAlignmentChanged(EventArgs &e)
    {
#ifdef DEBUG_LAYOUT_MANAGER
        std::cout << "LayoutManager::OnVerticalAlignmentChanged - " << GetName() << std::endl;
#endif
        needHeightRecalculation = true;
        needTopRecalculation = true; // Position depends on alignment
        Invalidate();
    }

    void LayoutManager::OnWidthChanged(EventArgs &e)
    {
#ifdef DEBUG_LAYOUT_MANAGER
        std::cout << "LayoutManager::OnWidthChanged - " << GetName() << std::endl;
#endif
        needWidthRecalculation = true;
        // Width change can affect horizontal position for non-stretch alignments
        needLeftRecalculation = true;
        Invalidate();
    }

    void LayoutManager::OnHeightChanged(EventArgs &e)
    {
        needHeightRecalculation = true;
        // Height change always affects vertical position in OpenGL coordinate system
        needTopRecalculation = true;
        Invalidate();
    }

    void LayoutManager::OnMinWidthChanged(EventArgs &e)
    {
        needWidthRecalculation = true;
        // Width constraint changes can affect horizontal position for center/right alignments
        needLeftRecalculation = true;
        Invalidate();
    }

    void LayoutManager::OnMaxWidthChanged(EventArgs &e)
    {
        needWidthRecalculation = true;
        // Width constraint changes can affect horizontal position for center/right alignments
        needLeftRecalculation = true;
        Invalidate();
    }

    void LayoutManager::OnMinHeightChanged(EventArgs &e)
    {
        needHeightRecalculation = true;
        // Height constraint changes can affect vertical position for center/bottom alignments
        needTopRecalculation = true;
        Invalidate();
    }

    void LayoutManager::OnMaxHeightChanged(EventArgs &e)
    {
        needHeightRecalculation = true;
        // Height constraint changes can affect vertical position for center/bottom alignments
        needTopRecalculation = true;
        Invalidate();
    }

    void LayoutManager::OnMarginChanged(EventArgs &e)
    {
        needLeftRecalculation = true;
        needTopRecalculation = true;
        needWidthRecalculation = true;
        needHeightRecalculation = true;
        Invalidate();
    }

    void LayoutManager::OnPaddingChanged(EventArgs &e)
    {
        needLeftRecalculation = true;
        needTopRecalculation = true;
        needWidthRecalculation = true;
        needHeightRecalculation = true;
        Invalidate();
    }

    void LayoutManager::OnBorderThicknessChanged(EventArgs &e)
    {
        needLeftRecalculation = true;
        needTopRecalculation = true;
        needWidthRecalculation = true;
        needHeightRecalculation = true;
        Invalidate();
    }

    void LayoutManager::OnLocationChanged(EventArgs &e)
    {
        needLeftRecalculation = true;
        needTopRecalculation = true;
        Invalidate();
    }

    void LayoutManager::OnSizeChanged(const Size &newSize)
    {
        needWidthRecalculation = true;
        needHeightRecalculation = true;
        // Size changes can affect position for non-stretch alignments
        needLeftRecalculation = true;
        needTopRecalculation = true;
        Invalidate();
    }

    void LayoutManager::OnVisibilityChanged(EventArgs &e)
    {
        needLeftRecalculation = true;
        needTopRecalculation = true;
        needWidthRecalculation = true;
        needHeightRecalculation = true;
        Invalidate();
    }

    void LayoutManager::OnScaleChanged(EventArgs &e)
    {
        float scaleX = GetScaleX();
        float scaleY = GetScaleY();

        Sizeable::Scale(scaleX, scaleY);
        SetMarginScale(scaleX, scaleY);
        SetPaddingScale(scaleX, scaleY);
        SetBorderThicknessScale(scaleX, scaleY);
    }

    void LayoutManager::OnCornerRadiusChanged(EventArgs &e)
    {
        // Corner radius changes may affect layout, so we need to recalculate
        needWidthRecalculation = true;
        needHeightRecalculation = true;
        needLeftRecalculation = true;
        needTopRecalculation = true;
        Invalidate();
    }

    int LayoutManager::OnMeasureWidth(int availableSize)
    {
        if (availableSize == 0)
        {
            return 0; // Invisible objects or no available space
        }

        int width = 0;

        if (GetHorizontalAlignment() == HorizontalAlignment::Stretch)
            width = availableSize; // Stretch to fill available space
        else if (GetWidth() > 0)
            width = GetWidth();
        else if (GetMinWidth() > 0)
            width = GetMinWidth();
        else if (GetMaxWidth() > 0)
            width = GetMaxWidth();
        else
            width = GetBoxWidthWithoutMargin();

        // Ensure the width respects min and max constraints
        if (GetMinWidth() > 0)
            width = std::max(width, GetMinWidth());
        if (GetMaxWidth() > 0)
            width = std::min(width, GetMaxWidth());

        return width;
    }

    int LayoutManager::OnMeasureHeight(int availableSize)
    {
        if (availableSize == 0)
        {
            return 0; // Invisible objects or no available space
        }

        int height = 0;

        if (GetVerticalAlignment() == VerticalAlignment::Stretch)
            height = availableSize; // Stretch to fill available space
        else if (GetHeight() > 0)
            height = GetHeight();
        else if (GetMinHeight() > 0)
            height = GetMinHeight();
        else if (GetMaxHeight() > 0)
            height = GetMaxHeight();
        else
            height = GetBoxHeightWithoutMargin();

        // Ensure the height respects min and max constraints
        if (GetMinHeight() > 0)
            height = std::max(height, GetMinHeight());
        if (GetMaxHeight() > 0)
            height = std::min(height, GetMaxHeight());

        return height;
    }

    int LayoutManager::MeasureWidth(int availableSize)
    {
        int newSize;

        if (availableSize == 0)
        {
            return 0; // Invisible objects or no available space
        }

        if (availableSize < 0)
        {
            std::cout << "Available width cannot be negative " << std::to_string(availableSize) << std::endl;
            return 0; // Or some default value
        }

        // TODO needWidthRecalculation still does not work correctly for ToolTip and MainMenuButtons.
        // if (needWidthRecalculation)
        {
            if (this->GetWidth() > -1)
            {
                // width is WITHOUT margin, padding and border, so do not subtract it here
                newSize = this->GetWidth();
                // No need to check min and max because if width is set, min and max will be checked automatically
            }
            else if ((GetMinWidth() != -1) && (availableSize < GetMinWidth()))
            {
                // TODO is this correct to use min width? What about child elements?
                newSize = GetMinWidth();
            }
            else
            {
                int contentSpace = 0;

                // Calculate content space for content calculation
                // hint: Margin is outside of the available size for the content.
                contentSpace = availableSize - GetTotalBoxWidth();

                // Call OnMeasureWidth to calculate the content's width
                newSize = OnMeasureWidth(std::max(0, contentSpace));

                // Adjust size if HorizontalAlignment is Stretch
                if (GetHorizontalAlignment() == HorizontalAlignment::Stretch)
                {
                    // For stretch, use all available space minus margin
                    newSize = availableSize - GetMargin().GetWidth();
                }
                else
                {
                    // Add padding and border thickness to get the total size
                    // hint: margin is not added because own size is ALWAYS without margin
                    newSize += GetNonContentWidth();
                }

                // Clamp the size to respect minimum and maximum width constraints
                newSize = CheckMinMaxWidth(*this, newSize);

#ifdef DEBUG_LAYOUT_MANAGER
                if (newSize != actualWidth)
                    std::cout << " MeasureWidth: availableSize=" << availableSize
                              << ", contentSpace=" << contentSpace
                              << ", newSize=" << newSize << std::endl;
#endif
            }

            desiredSize.SetWidth(newSize);
            // Don't set actualWidth here - it should be set in OnUpdate after bounds are finalized
            needWidthRecalculation = false;
        }
        // else
        // {
        //     newSize = actualWidth;
        // }

        return newSize;
    }

    int LayoutManager::MeasureHeight(int availableSize)
    {
        int newSize;

        if (availableSize == 0)
        {
            return 0; // Invisible objects or no available space
        }

        if (availableSize < 0)
        {
            std::cout << "Available height cannot be negative " << std::to_string(availableSize) << std::endl;
            return 0; // Or some default value
        }

        // TODO needHeightRecalculation still does not work correctly for ToolTip and MainMenuButtons.
        // if (needHeightRecalculation)
        {
            if (this->GetHeight() > -1)
            {
                // height is WITHOUT margin, padding and border, so do not subtract it here
                newSize = this->GetHeight();
                // No need to check min and max because if width is set, min and max will be checked automatically
            }
            else if ((GetMinHeight() != -1) && (availableSize < GetMinHeight()))
            {
                // TODO is this correct to use min height? What about child elements?
                newSize = GetMinHeight();
            }
            else
            {
                // Calculate content space for content calculation
                // hint: Margin is outside of the available size for the content.
                int contentSpace = availableSize - GetTotalBoxHeight();

                // Call OnMeasureHeight to calculate the content's height
                newSize = OnMeasureHeight(std::max(0, contentSpace));

                // Adjust size if VerticalAlignment is Stretch
                if (GetVerticalAlignment() == VerticalAlignment::Stretch)
                {
                    // For stretch, use all available space minus margin
                    newSize = availableSize - GetMargin().GetHeight();
                }
                else
                {
                    // Add padding and border thickness to get the total size
                    // hint: margin is not added because own size is ALWAYS without margin
                    newSize += GetNonContentHeight();
                }

                // Clamp the size to respect minimum and maximum width constraints
                newSize = CheckMinMaxHeight(*this, newSize);

#ifdef DEBUG_LAYOUT_MANAGER
                if (newSize != actualHeight)
                    std::cout << " MeasureHeight: availableSize=" << availableSize
                              << ", contentSpace=" << contentSpace
                              << ", newSize=" << newSize << std::endl;
#endif
            }

            desiredSize.SetHeight(newSize);
            // Remove premature actualHeight assignment - it should be set in OnUpdate
            needHeightRecalculation = false;
        }
        // else
        // {
        //     newSize = actualHeight;
        // }

        return newSize;
    }

    void LayoutManager::OnUpdate(const Rectangle &bounds)
    {
        // Perform the core layout calculations
        PerformLayout(bounds);

        // Allow derived classes to do additional work while flags are still available
        OnLayoutCompleted(bounds);

        // Reset invalidated flag after successful update - this must be done here
        // so the Update() function can use it in its return value
        invalidated = false;
    }

    void LayoutManager::PerformLayout(const Rectangle &bounds)
    {
        static thread_local bool isUpdating = false; // Make thread-local to avoid conflicts
        if (isUpdating)
        {
#ifdef DEBUG_LAYOUT_MANAGER
            std::cout << "WARNING: Recursive update prevented for: " << GetName() << std::endl;
#endif
            return; // Prevent recursive updates
        }

        isUpdating = true;

        // Use RAII to ensure isUpdating is always reset
        struct UpdateGuard
        {
            ~UpdateGuard() { isUpdating = false; }
        } guard;

        /*if (cancelInvalidate)
            return;*/

        // store for later update of buffers
        bool updateLocation = needLeftRecalculation || needTopRecalculation || GetIsAbsolutePosition() || invalidated;

        // Always measure when invalidated to handle visual content changes (like text updates)
        if (needWidthRecalculation || needHeightRecalculation || invalidated)
        {
            const Size &s = bounds.GetSize();
            Size oldDesiredSize = desiredSize;
            desiredSize = Measure(s);

            // Check if content size changed significantly (this indicates layout change needed)
            bool contentSizeChanged = (oldDesiredSize.GetWidth() != desiredSize.GetWidth() ||
                                       oldDesiredSize.GetHeight() != desiredSize.GetHeight());

            // Recalculate actual dimensions if layout flags are set OR if content size changed
            if (needWidthRecalculation || needHeightRecalculation || contentSizeChanged)
            {
                // Calculate actualWidth
                if (GetWidth() > -1)
                    actualWidth = GetWidth(); // Use explicitly set width
                else if (desiredSize.GetWidth() <= bounds.GetWidth())
                    actualWidth = desiredSize.GetWidth(); // Use desired size if it fits
                else if (GetMinWidth() > 0 && GetMinWidth() <= bounds.GetWidth())
                    actualWidth = GetMinWidth(); // Use minimum width if it fits
                else
                    actualWidth = std::max(0, bounds.GetWidth()); // Use available width as fallback

                // Calculate actualHeight
                if (GetHeight() > -1)
                    actualHeight = GetHeight(); // Use explicitly set height
                else if (desiredSize.GetHeight() <= bounds.GetHeight())
                    actualHeight = desiredSize.GetHeight(); // Use desired size if it fits
                else if (GetMinHeight() > 0 && GetMinHeight() <= bounds.GetHeight())
                    actualHeight = GetMinHeight(); // Use minimum height if it fits
                else
                    actualHeight = std::max(0, bounds.GetHeight()); // Use available height as fallback

                // If content size changed, we may need to update location too
                if (contentSizeChanged)
                    updateLocation = true;
            }
            // If only visual invalidated without content size change, keep existing actualWidth/actualHeight
            // but still call Measure() to update content (like text rendering)
        }

        if (!GetIsAbsolutePosition() && needLeftRecalculation)
        {
            if (GetHorizontalAlignment() == HorizontalAlignment::Left || GetHorizontalAlignment() == HorizontalAlignment::Stretch)
            {
                SetLeft(bounds.GetLeft() + GetMargin().GetLeft());
            }
            else if (GetHorizontalAlignment() == HorizontalAlignment::Center)
            {
                SetLeft(bounds.GetLeft() + GetMargin().GetLeft() + ((bounds.GetWidth() - actualWidth - GetMargin().GetWidth()) >> 1));
            }
            else if (GetHorizontalAlignment() == HorizontalAlignment::Right)
            {
                SetLeft(bounds.GetRight() - actualWidth - GetMargin().GetRight());
            }
        }

        if (!GetIsAbsolutePosition() && needTopRecalculation)
        {
            if (GetVerticalAlignment() == VerticalAlignment::Top || GetVerticalAlignment() == VerticalAlignment::Stretch)
            {
                SetTop(bounds.GetTop() + GetMargin().GetTop());
            }
            else if (GetVerticalAlignment() == VerticalAlignment::Center)
            {
                SetTop(bounds.GetTop() + GetMargin().GetTop() + ((bounds.GetHeight() - actualHeight - GetMargin().GetHeight()) >> 1));
            }
            else if (GetVerticalAlignment() == VerticalAlignment::Bottom)
            {
                SetTop(bounds.GetBottom() - actualHeight - GetMargin().GetBottom());
            }
        }

        if (updateLocation)
        {
            renderTop = Scene2D::CurrentScene().GetHeight() - GetTop() - actualHeight;
            renderLeft = GetLeft();

            // add margin to get the real bounds(1 - (-1) = 2)

            // render top
            if (GetMargin().GetTop() < 0)
                renderTop -= GetMargin().GetTop();
            if (GetMargin().GetLeft() < 0)
                renderLeft += GetMargin().GetLeft();
        }

        if (updateLocation || needWidthRecalculation || needHeightRecalculation)
            clientBounds = GetClientRectangle(GetLeft(), GetTop(), actualWidth, actualHeight);

#ifdef DEBUG_LAYOUT_MANAGER
        std::cout << "LayoutManager::PerformLayout - Updating clientBounds for " << GetName()
                  << " to (" << clientBounds.GetLeft() << "," << clientBounds.GetTop()
                  << "," << clientBounds.GetWidth() << "," << clientBounds.GetHeight() << ")"
                  << " from GetLeft()=" << GetLeft() << " GetTop()=" << GetTop()
                  << " actualWidth=" << actualWidth << " actualHeight=" << actualHeight << std::endl;
#endif
    }

    void LayoutManager::OnLayoutCompleted(const Rectangle &bounds)
    {
        // Base implementation does nothing
        // Derived classes can override this to perform additional calculations
        // while recalculation flags are still available
    }

    void LayoutManager::ResetRecalculationFlags()
    {
        needWidthRecalculation = false;
        needHeightRecalculation = false;
        needLeftRecalculation = false;
        needTopRecalculation = false;
    }
}
