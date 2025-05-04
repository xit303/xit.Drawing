#include <Drawing/VisualBase/LayoutManager.h>
#include <OpenGL/Scene2D.h>

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
        scaleX = 1;
        scaleY = 1;
        layoutVisualStateGroup = nullptr;
        currentLayoutVisualState = nullptr;
        isLayoutGroupChanging = false;
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
            needWidthRecalculation = true;
            needHeightRecalculation = true;
            needTopRecalculation = true;
            needLeftRecalculation = true;
            invalidated = true;

            EventArgs e;
            OnInvalidated(e);
            Scene2D::CurrentScene().Invalidate(this);
        }
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

        if (GetVisibility() != Visibility::Collapsed)
        {
            // if (this->bounds != newBounds || this->bounds.IsEmpty())
            {
                needWidthRecalculation = true;
                needHeightRecalculation = true;
                needTopRecalculation = true;
                needLeftRecalculation = true;
            }
            // else
            // {
            // if (bounds.GetLeft() != this->bounds.GetLeft())
            // {
            //     needLeftRecalculation = true;
            // }
            // if (bounds.GetTop() != this->bounds.GetTop())
            // {
            //     needTopRecalculation = true;
            // }
            // if ((newBounds.GetWidth() != this->bounds.GetWidth()) ||
            //     ((GetWidth() != -1) && (GetWidth() != actualWidth)))
            // {
            //     needWidthRecalculation = true;

            //     // in some cases we have to update the position as well
            //     if (GetHorizontalAlignment() != HorizontalAlignment::Stretch)
            //     {
            //         needTopRecalculation = true;
            //     }
            // }
            // if ((newBounds.GetHeight() != this->bounds.GetHeight()) ||
            //     ((GetHeight() != -1) && (GetHeight() != actualHeight)))
            // {
            //     needHeightRecalculation = true;

            //     // if height changes we always have to update top because
            //     // OpenGL 0,0 is on bottom left
            //     // if (VerticalAlignment != CVerticalAlignment::Stretch)
            //     {
            //         needTopRecalculation = true;
            //     }
            // }
            // }

            needRedraw = needLeftRecalculation || needTopRecalculation || needWidthRecalculation || needHeightRecalculation;

            if (needRedraw)
            {
                this->bounds = newBounds;
                OnUpdate(bounds);
            }
        }
        else
        {
            needRedraw = false;
        }

        return needRedraw || invalidated;
    }

    void LayoutManager::SetDPIScale(float scaleX, float scaleY)
    {
        if (scaleX <= 0)
            scaleX = 1;
        if (scaleY <= 0)
            scaleY = 1;

        this->scaleX = scaleX;
        this->scaleY = scaleY;

        Sizeable::Scale(scaleX, scaleY);
        SetMarginScale(scaleX, scaleY);
        SetPaddingScale(scaleX, scaleY);
        SetBorderThicknessScale(scaleX, scaleY);
    }

    //******************************************************************************
    // Protected
    //******************************************************************************

    void LayoutManager::UpdateLayoutVisualState()
    {
        LayoutVisualState *value = nullptr;
        if (layoutVisualStateGroup != nullptr && !isLayoutGroupChanging)
        {
            if ((value = layoutVisualStateGroup->GetVisualState(visualState)))
            {
                OnUpdateLayout(value);
                currentLayoutVisualState = value;
            }
            else if (currentLayoutVisualState)
            {
                visualState = currentLayoutVisualState->GetName();
            }
        }
        else
        {
            isLayoutGroupChanging = false;
            LayoutVisualStateGroup *visualStateGroup = ThemeManager::Default.GetLayoutVisualStateGroup(GetLayoutGroup());
            if (visualStateGroup)
            {
                if ((value = visualStateGroup->GetVisualState(visualState)))
                {
                    layoutVisualStateGroup = visualStateGroup;
                    OnUpdateLayout(value);
                    currentLayoutVisualState = value;
                    return;
                }
                else if (currentLayoutVisualState)
                {
                    visualState = currentLayoutVisualState->GetName();
                    return;
                }
            }
            OnUpdateLayout(nullptr);
            return;
        }
    }

    void LayoutManager::OnVisualStateChanged(EventArgs &e)
    {
        Invalidate();
    }

    void LayoutManager::OnHorizontalAlignmentChanged(EventArgs &e)
    {
        needWidthRecalculation = true;
        Invalidate();
    }

    void LayoutManager::OnVerticalAlignmentChanged(EventArgs &e)
    {
        needHeightRecalculation = true;
        Invalidate();
    }

    void LayoutManager::OnWidthChanged(EventArgs &e)
    {
        needWidthRecalculation = true; // TODO check if this is needed. They are overridden by OnSizeChanged
    }
    void LayoutManager::OnHeightChanged(EventArgs &e)
    {
        needHeightRecalculation = true; // TODO check if this is needed. They are overridden by OnSizeChanged
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

    void LayoutManager::OnLayoutGroupChanged(EventArgs &e)
    {
        isLayoutGroupChanging = true;
        UpdateLayoutVisualState();
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
                contentSpace = availableSize - GetMargin().GetWidth() - GetPadding().GetWidth() - GetBorderThickness().GetWidth();

                // Call OnMeasureWidth to calculate the content's width
                newSize = OnMeasureWidth(std::max(0, contentSpace));

                // Adjust size if HorizontalAlignment is Stretch
                // TODO i do not understand why && newSize < availableSize is needed.
                if (GetHorizontalAlignment() == HorizontalAlignment::Stretch && newSize < availableSize)
                {
                    contentSpace = newSize = availableSize - GetMargin().GetWidth();
                }
                else
                {
                    // Add padding and border thickness to get the total size
                    // hint: margin is not added because own size is ALWAYS without margin
                    newSize += GetPadding().GetWidth() + GetBorderThickness().GetWidth();
                }

                // Clamp the size to respect minimum and maximum width constraints
                newSize = CheckMinMaxWidth(*this, newSize);

                if (newSize != actualWidth)
                    std::cout << " MeasureWidth: availableSize=" << availableSize
                              << ", contentSpace=" << contentSpace
                              << ", newSize=" << newSize << std::endl;
            }

            desiredSize.SetWidth(newSize);
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
                int contentSpace = availableSize - GetMargin().GetHeight() - GetPadding().GetHeight() - GetBorderThickness().GetHeight();

                // Call OnMeasureWidth to calculate the content's width
                newSize = OnMeasureHeight(std::max(0, contentSpace));

                // Adjust size if VerticalAlignment is Stretch
                // TODO i do not understand why && newSize < availableSize is needed.
                if (GetVerticalAlignment() == VerticalAlignment::Stretch && newSize < availableSize)
                {
                    contentSpace = newSize = availableSize - GetMargin().GetHeight();
                }
                else
                {
                    // Add padding and border thickness to get the total size
                    // hint: margin is not added because own size is ALWAYS without margin
                    newSize += GetPadding().GetHeight() + GetBorderThickness().GetHeight();
                }

                // Clamp the size to respect minimum and maximum width constraints
                newSize = CheckMinMaxHeight(*this, newSize);

                if (newSize != actualHeight)
                    std::cout << " MeasureHeight: availableSize=" << availableSize
                              << ", contentSpace=" << contentSpace
                              << ", newSize=" << newSize << std::endl;
            }

            desiredSize.SetHeight(newSize);
            // TODO this is not correct. We should not set the actual height here because it is not the final value yet. But it works for now.
            actualHeight = newSize;
            needHeightRecalculation = false;
        }
        // else
        // {
        //     newSize = actualHeight;
        // }

        return newSize;
    }

    void LayoutManager::OnUpdateLayout(LayoutVisualState *value)
    {
        if (value)
        {
            SetWidth(value->GetWidth());
            SetMinWidth(value->GetMinWidth());
            SetMaxWidth(value->GetMaxWidth());

            SetHeight(value->GetHeight());
            SetMinHeight(value->GetMinHeight());
            SetMaxHeight(value->GetMaxHeight());

            SetMargin(value->GetMargin());
            SetPadding(value->GetPadding());
            SetBorderThickness(value->GetBorderThickness());

            SetMarginScale(scaleX, scaleY);
            SetPaddingScale(scaleX, scaleY);
            SetBorderThicknessScale(scaleX, scaleY);

            Sizeable::Scale(scaleX, scaleY);

            SetCornerRadius(value->GetCornerRadius());

            SetHorizontalAlignment(value->GetHorizontalAlignment());
            SetVerticalAlignment(value->GetVerticalAlignment());
        }
    }

    void LayoutManager::OnUpdate(const Rectangle &bounds)
    {
        static bool isUpdating = false;
        if (isUpdating)
            return; // Prevent recursive updates

        isUpdating = true;

        /*if (cancelInvalidate)
            return;*/

        // store for later update of buffers
        bool updateLocation = needLeftRecalculation || needTopRecalculation || GetIsAbsolutePosition();

        if (needWidthRecalculation || needHeightRecalculation)
        {
            const Size &s = bounds.GetSize();
            desiredSize = Measure(s);

            if (desiredSize.GetWidth() == GetWidth())
                actualWidth = GetWidth();
            else
                actualWidth = desiredSize.GetWidth() <= bounds.GetWidth()
                                  ? desiredSize.GetWidth()
                              : GetMinWidth() > bounds.GetWidth()
                                  ? GetMinWidth()
                                  : bounds.GetWidth();

            if (desiredSize.GetHeight() == GetHeight())
                actualHeight = GetHeight();
            else
                actualHeight = desiredSize.GetHeight() <= bounds.GetHeight()
                                   ? desiredSize.GetHeight()
                               : GetMinHeight() > bounds.GetHeight()
                                   ? GetMinHeight()
                                   : bounds.GetHeight();
        }

        if (!GetIsAbsolutePosition() && needLeftRecalculation)
        {
            if (GetHorizontalAlignment() == HorizontalAlignment::Left || GetHorizontalAlignment() == HorizontalAlignment::Stretch)
            {
                SetLeft(bounds.GetLeft() + GetMargin().GetLeft());
            }
            else if (GetHorizontalAlignment() == HorizontalAlignment::Center)
            {
                // ensure bounds with is always greater than actual width + margin width

                // int actualWidthPlusMargin = actualWidth + GetMargin().GetWidth();
                // int clientWidth;

                // if (bounds.GetWidth() < actualWidthPlusMargin)
                // {
                //     clientWidth = bounds.GetWidth() - GetMargin().GetWidth();
                // }
                // else
                // {
                //     clientWidth = bounds.GetWidth() - actualWidthPlusMargin;
                // }

                // if (clientWidth < 0)
                //     clientWidth = 0;

                // SetLeft(bounds.GetLeft() + GetMargin().GetLeft() + (clientWidth >> 1));

                SetLeft(bounds.GetLeft() + GetMargin().GetLeft() + ((bounds.GetWidth() - actualWidth - GetMargin().GetWidth()) >> 1));
            }
            else if (GetHorizontalAlignment() == HorizontalAlignment::Right)
            {
                SetLeft(bounds.GetRight() - actualWidth - GetMargin().GetRight());
            }

            needLeftRecalculation = false;
        }
        if (!GetIsAbsolutePosition() && needTopRecalculation)
        {
            if (GetVerticalAlignment() == VerticalAlignment::Top || GetVerticalAlignment() == VerticalAlignment::Stretch)
            {
                SetTop(bounds.GetTop() + GetMargin().GetTop());
            }
            else if (GetVerticalAlignment() == VerticalAlignment::Center)
            {
                // ensure bounds with is always greater than actual height + margin height

                // int actualHeightPlusMargin = actualHeight + GetMargin().GetHeight();
                // int clientHeight;

                // if (bounds.GetHeight() < actualHeightPlusMargin)
                // {
                //     clientHeight = bounds.GetHeight() - GetMargin().GetHeight();
                // }
                // else
                // {
                //     clientHeight = bounds.GetHeight() - actualHeightPlusMargin;
                // }

                // if (clientHeight < 0)
                //     clientHeight = 0;

                // SetTop(bounds.GetTop() + GetMargin().GetTop() + (clientHeight >> 1));

                SetTop(bounds.GetTop() + GetMargin().GetTop() + ((bounds.GetHeight() - actualHeight - GetMargin().GetHeight()) >> 1));
            }
            else if (GetVerticalAlignment() == VerticalAlignment::Bottom)
            {
                SetTop(bounds.GetBottom() - actualHeight - GetMargin().GetBottom());
            }

            needTopRecalculation = false;
        }

        // if (updateLocation)
        //{
        //     modelMatrix = mat4.identity();
        //     modelMatrix = glm.translate(modelMatrix, new vec3(GetLeft(), GetTop(), 0));
        // }

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
        isUpdating = false;
    }
}
