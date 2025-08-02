#include <Drawing/ContainerBase.h>
#include <Input/InputHandler.h>
#ifdef DEBUG_GRID_PERFORMANCE
#include <chrono>
#include <iostream>
#endif

namespace xit::Drawing
{
    //******************************************************************************
    // Properties
    //******************************************************************************

    //******************************************************************************
    // Constructor
    //******************************************************************************

    ContainerBase::ContainerBase()
    {
        isVisibleChanging = false;
        grid.SetChildren(&children);
        grid.SetColumns(GetColumns());
        grid.SetRows(GetRows());

        SetName("ContainerBase");
    }

    void ContainerBase::AddChild(Visual *content)
    {
        // set all parameters for the new content
        content->SetDPIScale(GetScaleX(), GetScaleY());
        content->SetZIndex(GetZIndex());

        if (content->GetInheritForeground())
        {
            content->SetForeground(GetForeground());
        }
        // if (!content->GetIsVisible())
        // {
        //     // if content is hidden by default, we add it to the "blocked" content list
        //     //hiddenContent.push_back(content);
        // }
        // else if (!GetIsVisible())
        // {
        //     // if this container is invisible itself, we just hide our new content
        //     // we do not add it to hiddenContent because we want it to get visible
        //     // as soon as this container gets visible
        //     content->SetVisibility(GetVisibility());
        // }
        // content->VisibilityChanged.Add(&ContainerBase::Content_VisibleChanged, this);

        // if (!content->GetEnabled())
        // {
        //     // if content is disabled by default
        //     disabledContent.push_back(content);
        // }
        // else if (!GetEnabled())
        // {
        //     content->SetEnabled(false);
        // }
        // content->EnabledChanged.Add(&ContainerBase::Content_EnabledChanged, this);

        // if everything went well we store the content in the list.
        children.push_back(content);

        // SetParent MUST be called AFTER everything else because
        // SetParent will make content visible if parent is visible.
        // In that case hidden items wouldn't be added to hiddenContent etc.
        content->SetParent(this);
        InvokeChildAdded(*content);
    }

    void ContainerBase::InsertChild(size_t position, Visual *content)
    {
        // set all parameters for the new content
        content->SetDPIScale(GetScaleX(), GetScaleY());
        content->SetZIndex(GetZIndex());

        if (content->GetInheritForeground())
        {
            content->SetForeground(GetForeground());
        }
        // if (!content->GetIsVisible())
        // {
        //     // if content is hidden by default, we add it to the "blocked" content list
        //     //hiddenContent.push_back(content);
        // }
        // else if (!GetIsVisible())
        // {
        //     // if this container is invisible itself, we just hide our new content
        //     // we do not add it to hiddenContent because we want it to get visible
        //     // as soon as this container gets visible
        //     content->SetVisibility(GetVisibility());
        // }
        // content->VisibilityChanged.Add(&ContainerBase::Content_VisibleChanged, this);

        // if (!content->GetEnabled())
        // {
        //     // if content is disabled by default
        //     disabledContent.push_back(content);
        // }
        // else if (!GetEnabled())
        // {
        //     content->SetEnabled(false);
        // }
        // content->EnabledChanged.Add(&ContainerBase::Content_EnabledChanged, this);

        // if everything went well we store the content in the list.
        auto it = children.begin();
        std::advance(it, position);
        children.insert(it, content);

        // SetParent MUST be called AFTER everything else because
        // SetParent will make content visible if parent is visible.
        // In that case hidden items wouldn't be added to hiddenContent etc.
        content->SetParent(this);
        InvokeChildAdded(*content);
    }

    void ContainerBase::RemoveChild(Visual *content)
    {
        std::erase(children, content);

        // have to do this first because setting parent to nullptr will hide the content
        // content->VisibilityChanged.Remove(&ContainerBase::Content_VisibleChanged, this);
        // content->EnabledChanged.Remove(&ContainerBase::Content_EnabledChanged, this);
        content->SetParent(nullptr);

        // hiddenContent.remove(content);
        // disabledContent.remove(content);

        InvokeChildRemoved(*content);

        // removing items backwards prevents us from wrong indices while removing
        // for (int i = contentWidthFixedPositions.Count - 1; i < 0; i--)
        //{
        //    FixedContentPosition fixedContent = contentWidthFixedPositions[i];
        //    if (fixedContent.Visual == content)
        //    {
        //        contentWidthFixedPositions.RemoveAt(i);
        //    }
        //}
    }

    void ContainerBase::RemoveChildAt(size_t index)
    {
        if (index >= children.size())
            return;

        Visual *content = children[0];

        auto it = children.begin();
        children.erase(it);

        InvokeChildRemoved(*content);
    }

    bool ContainerBase::ContainsChild(Visual *content)
    {
        return std::find(children.begin(), children.end(), content) != children.end();
    }

    std::vector<Visual *> &ContainerBase::GetChildren()
    {
        return children;
    }

    Visual *ContainerBase::GetChildAt(size_t index)
    {
        if (index >= children.size())
            return nullptr;

        return children[index];
    }

    int ContainerBase::GetChildIndex(Visual *content)
    {
        auto it = std::find(children.begin(), children.end(), content);
        if (it == children.end())
            return -1;

        return static_cast<int>(std::distance(children.begin(), it));
    }

    size_t ContainerBase::GetChildCount()
    {
        return children.size();
    }

    //******************************************************************************
    // Private
    //******************************************************************************

    // #define contains(item, value) (std::find(item.begin(), item.end(), value) != item.end())

    // void ContainerBase::Content_EnabledChanged(EnabledProperty &sender, EventArgs &e)
    // {
    //     Visual *content = (Visual *)&sender;
    //     if (GetEnabled() && !sender.GetEnabled())
    //     {
    //         if (!contains(disabledContent, content))
    //         {
    //             disabledContent.push_back(content);
    //         }
    //     }
    //     else if (sender.GetEnabled())
    //     {
    //         disabledContent.remove(content);
    //     }
    // }
    // void ContainerBase::Content_VisibleChanged(VisibilityProperty &sender, EventArgs &e)
    // {
    //     Visual *content = (Visual *)&sender;
    //     // if content has been disabled but this container is still visible
    //     if (GetIsVisible() && !content->GetIsVisible())
    //     {
    //         // only add if not already in the list
    //         // just to be sure...
    //         if (!contains(hiddenContent, content))
    //         {
    //             hiddenContent.push_back(content);
    //         }
    //     }
    //     else if (content->GetIsVisible())
    //     {
    //         // content is visible now. no matter if it is in the list or not.
    //         // if it is in the list we remove it
    //         hiddenContent.remove(content);
    //     }
    // }

    //******************************************************************************
    // Protected overrides
    //******************************************************************************

    void ContainerBase::OnColumnsChanged(EventArgs &e)
    {
        grid.SetColumns(GetColumns());
        SetNumberOfColumns(grid.GetNumberOfColumns());
    }
    void ContainerBase::OnColumnSpacingChanged(EventArgs &e)
    {
        grid.SetColumnSpacing((int)std::round((float)GetColumnSpacing() * GetScaleX()));
    }
    void ContainerBase::OnRowsChanged(EventArgs &e)
    {
        grid.SetRows(GetRows());
        SetNumberOfRows(grid.GetNumberOfRows());
    }
    void ContainerBase::OnRowSpacingChanged(EventArgs &e)
    {
        grid.SetRowSpacing((int)std::round((float)GetRowSpacing() * GetScaleY()));
    }

    void ContainerBase::OnHorizontalContentAlignmentChanged(EventArgs &e)
    {
        grid.SetHorizontalAlignment(GetHorizontalContentAlignment());
    }
    void ContainerBase::OnVerticalContentAlignmentChanged(EventArgs &e)
    {
        grid.SetVerticalAlignment(GetVerticalContentAlignment());
    }

    // void ContainerBase::OnEnabledChanged(EventArgs &e)
    // {
    //     InputContent::OnEnabledChanged(e);

    //     for (Visual *content : children)
    //     {
    //         if (!GetEnabled() && content->GetEnabled())
    //         {
    //             content->SetEnabled(false);
    //         }
    //         else if (GetEnabled() && (!contains(disabledContent, content)))
    //         {
    //             content->SetEnabled(true);
    //         }
    //     }
    // }
    // void ContainerBase::OnVisibilityChanged(EventArgs &e)
    // {
    //     isVisibleChanging = true;

    //     InputContent::OnVisibilityChanged(e);

    //     for (Visual *content : children)
    //     {
    //         if (!GetIsVisible() && content->GetIsVisible())
    //         {
    //             content->SetIsVisible(false);
    //         }
    //         else if (GetIsVisible() && (!contains(hiddenContent, content)))
    //         {
    //             content->SetIsVisible(true);
    //         }
    //     }

    //     isVisibleChanging = false;
    // }

    void ContainerBase::OnZIndexChanged(EventArgs &e)
    {
        InputContent::OnZIndexChanged(e);

        for (Visual *content : children)
        {
            content->SetZIndex(GetZIndex());
        }
    }
    void ContainerBase::OnForegroundChanged(EventArgs &e)
    {
        InputContent::OnForegroundChanged(e);

        for (Visual *content : children)
        {
            if (content->GetInheritForeground())
            {
                content->SetForeground(GetForeground());
            }
        }
    }
    void ContainerBase::OnUpdateLayout(LayoutVisualState* value)
    {
        InputContent::OnUpdateLayout(value);

        if (value)
        {
            SetHorizontalContentAlignment(value->GetHorizontalContentAlignment());
            SetVerticalContentAlignment(value->GetVerticalContentAlignment());
        }
    }

    int ContainerBase::OnMeasureWidth(int available)
    {
        return grid.GetWidth(available);
    }
    int ContainerBase::OnMeasureHeight(int available)
    {
        return grid.GetHeight(available);
    }

    void ContainerBase::OnUpdate(const Rectangle &bounds)
    {
        // TODO if bounds did not change, do we have to update? Only in case if items have been added or removed? Check the requirements!
        bool updateSize = GetNeedWidthRecalculation() || GetNeedHeightRecalculation();
        bool updateLocations = GetNeedLeftRecalculation() || GetNeedTopRecalculation();

#ifdef DEBUG_GRID_PERFORMANCE
        auto start = std::chrono::high_resolution_clock::now();
        std::cout << "ContainerBase::OnUpdate - " << GetName() << " with " << children.size() 
                  << " children, updateSize=" << updateSize << ", updateLocations=" << updateLocations << std::endl;
#endif

        InputContent::OnUpdate(bounds);

        // Use cached client bounds from LayoutManager for optimal performance
        Rectangle stored = GetClientBounds();

#ifdef DEBUG_GRID_PERFORMANCE
        std::cout << "ContainerBase::OnUpdate - Client bounds: (" << stored.GetLeft() << "," 
                  << stored.GetTop() << "," << stored.GetWidth() << "," << stored.GetHeight() << ")" << std::endl;
#endif

        // Handle negative margin (special case for SplitContainer)
        int left = stored.GetLeft();
        int top = stored.GetTop();
        int width = stored.GetWidth();
        int height = stored.GetHeight();

        const Thickness &margin = GetMargin();

        // add margin to get the real bounds (1 - (-1) = 2)
        if (margin.GetTop() < 0)
            top -= margin.GetTop();
        // if (margin.GetLeft() < 0)
        //     left += margin.GetLeft();

        // TODO this order is different to ScrollViewer
#ifdef DEBUG_GRID_PERFORMANCE
        auto gridStart = std::chrono::high_resolution_clock::now();
#endif
        grid.SetBounds(stored);
#ifdef DEBUG_GRID_PERFORMANCE
        auto gridEnd = std::chrono::high_resolution_clock::now();
        auto gridDuration = std::chrono::duration_cast<std::chrono::microseconds>(gridEnd - gridStart);
        std::cout << "ContainerBase::OnUpdate - Grid.SetBounds() took " << gridDuration.count() << "μs" << std::endl;
#endif

        if (updateSize || updateLocations)
        {
            for (Visual *content : children)
            {
                if (!content->GetIsVisible())
                {
                    continue;
                }

                left = stored.GetLeft();
                width = 0;

                if (grid.GetColumnWidths().empty() || (grid.GetColumnWidths().size() <= 1 && content->GetHorizontalAlignment() == HorizontalAlignment::Stretch))
                {
                    width = stored.GetWidth();
                }
                else
                {
                    size_t max = grid.GetColumnPositions().size() - 1;
                    size_t column = content->GetColumn();
                    size_t columnSpan = content->GetColumnSpan();
                    size_t end = column + columnSpan;

                    column = column > max ? max : column;
                    max++;
                    end = end > max ? max : end;

                    left += grid.GetColumnPositions()[column];

                    // TODO try to get rid of this loop
                    for (size_t i = column; i < end; i++)
                    {
                        width += grid.GetColumnWidths()[i];

                        if (columnSpan > 1 && i < end - 1)
                        {
                            width += GetColumnSpacing();
                        }
                    }

                    width = width > stored.GetWidth() ? stored.GetWidth() : width;
                }

                width = width < 0 ? 0 : width;

                top = stored.GetTop();
                height = 0;

                if (grid.GetRowHeights().empty() || (grid.GetRowHeights().size() <= 1 && content->GetVerticalAlignment() == VerticalAlignment::Stretch))
                {
                    height = stored.GetHeight();
                }
                else
                {
                    size_t max = grid.GetRowPositions().size() - 1;
                    size_t row = content->GetRow();
                    size_t rowSpan = content->GetRowSpan();
                    size_t end = row + rowSpan;

                    row = row > max ? max : row;
                    max++;
                    end = end > max ? max : end;

                    top += grid.GetRowPositions()[row];

                    // TODO try to get rid of this loop
                    for (size_t i = row; i < end; i++)
                    {
                        height += grid.GetRowHeights()[i];

                        if (rowSpan > 1 && i < end)
                        {
                            height += GetRowSpacing();
                        }
                    }
                }

                height = height > stored.GetHeight() ? stored.GetHeight() : height;
                height = height < 0 ? 0 : height;

                Rectangle thisClientsBounds(left, top, width, height);
                content->Update(thisClientsBounds);
            }
        }

#ifdef DEBUG_GRID_PERFORMANCE
        auto end = std::chrono::high_resolution_clock::now();
        auto totalDuration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "ContainerBase::OnUpdate - " << GetName() << " total time: " << totalDuration.count() << "μs" << std::endl;
#endif
    }
    void ContainerBase::OnRender()
    {
        InputContent::OnRender();

        for (Visual *content : children)
        {
            content->Render();
        }
    }

    void ContainerBase::OnGotKeyboardFocus(EventArgs &e)
    {
        InputContent::OnGotKeyboardFocus(e);
    }
    void ContainerBase::OnLostKeyboardFocus(EventArgs &e)
    {
        InputContent::OnLostKeyboardFocus(e);
    }

    //******************************************************************************
    // Protected
    //******************************************************************************

    void ContainerBase::InvokeChildAdded(Visual &content)
    {
        EventArgs e;
        ChildAdded(content, e);
        OnChildAdded(content, e);
    }
    void ContainerBase::InvokeChildRemoved(Visual &content)
    {
        EventArgs e;
        ChildRemoved(content, e);
        OnChildRemoved(content, e);
    }

    void ContainerBase::OnChildAdded(Visual &content, EventArgs &e) {}
    void ContainerBase::OnChildRemoved(Visual &content, EventArgs &e) {}

    //******************************************************************************
    // Public overrides
    //******************************************************************************

    void ContainerBase::SetDPIScale(float scaleX, float scaleY)
    {
        InputContent::SetDPIScale(scaleX, scaleY);

        grid.SetColumnSpacing((int)std::round(static_cast<float>(GetColumnSpacing()) * GetScaleX()));
        grid.SetRowSpacing((int)std::round(static_cast<float>(GetRowSpacing()) * GetScaleY()));

        for (Visual *content : children)
        {
            content->SetDPIScale(scaleX, scaleY);
        }
    }

    void ContainerBase::ExecuteInputLeave(MouseEventArgs &e)
    {
        for (Visual *content : children)
        {
            if (InputHandler::CheckInputLeave(dynamic_cast<IFocus*>(content), e))
                return;
        }
        if (!e.Handled)
            InputContent::ExecuteInputLeave(e);
    }

    void ContainerBase::ExecuteInputPressed(MouseEventArgs &e)
    {
        for (Visual *content : children)
        {
            if (InputHandler::CheckInputPressed(dynamic_cast<IFocus*>(content), e))
            {
                return;
            }
        }
        if (!e.Handled)
            InputContent::ExecuteInputPressed(e);
    }
    void ContainerBase::ExecuteInputReleased(MouseEventArgs &e)
    {
        for (Visual *content : children)
        {
            if (InputHandler::CheckInputReleased(dynamic_cast<IFocus*>(content), e))
            {
                return;
            }
        }
        if (!e.Handled)
            InputContent::ExecuteInputReleased(e);
    }

    void ContainerBase::ExecuteInputMove(MouseEventArgs &e)
    {
        for (Visual *content : children)
        {
            InputHandler::CheckInputMove(dynamic_cast<IFocus*>(content), e);
        }
        if (!e.Handled)
            InputContent::ExecuteInputMove(e);
    }
    void ContainerBase::ExecuteInputScroll(MouseEventArgs &e)
    {
        for (Visual *content : children)
        {
            if (InputHandler::CheckInputScroll(dynamic_cast<IFocus*>(content), e))
            {
                return;
            }
        }
        if (!e.Handled)
            InputContent::ExecuteInputScroll(e);
    }

    void ContainerBase::ExecuteKeyDown(KeyEventArgs &e)
    {
        for (Visual *content : children)
        {
            if (InputHandler::CheckKeyDown(dynamic_cast<IFocus*>(content), e))
            {
                return;
            }
        }

        if (!e.Handled)
            InputContent::ExecuteKeyDown(e);
    }
    void ContainerBase::ExecuteKeyUp(KeyEventArgs &e)
    {
        for (Visual *content : children)
        {
            if (InputHandler::CheckKeyUp(dynamic_cast<IFocus*>(content), e))
            {
                return;
            }
        }

        if (!e.Handled)
            InputContent::ExecuteKeyUp(e);
    }

    void ContainerBase::SetLeft(Visual &content, int value)
    {
        std::lock_guard<std::mutex> lock(contentWidthFixedPositionsMutex);
        {
            bool found = false;
            for (FixedContentPosition *fixedContentPosition : contentWidthFixedPositions)
            {
                if (fixedContentPosition->GetContent() == &content)
                {
                    Point position = fixedContentPosition->GetPosition();
                    position.X = value;
                    fixedContentPosition->SetPosition(position);
                    found = true;
                }
            }

            if (!found)
            {
                contentWidthFixedPositions.push_back(new FixedContentPosition(&content, value, 0));
            }

            Invalidate();
        }
    }
    void ContainerBase::SetTop(Visual &content, int value)
    {
        std::lock_guard<std::mutex> lock(contentWidthFixedPositionsMutex);
        {
            bool found = false;
            for (FixedContentPosition *fixedContentPosition : contentWidthFixedPositions)
            {
                if (fixedContentPosition->GetContent() == &content)
                {
                    Point position = fixedContentPosition->GetPosition();
                    position.Y = value;
                    fixedContentPosition->SetPosition(position);
                    found = true;
                }
            }

            if (!found)
            {
                contentWidthFixedPositions.push_back(new FixedContentPosition(&content, 0, value));
            }

            Invalidate();
        }
    }
}
