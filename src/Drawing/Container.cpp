#include <Drawing/Container.h>

#ifdef DEBUG_VISUAL_STATES
#include <iostream>
#endif

namespace xit::Drawing
{
    void Container::OnOrientationChanged(EventArgs &e)
    {
        UpdateOrientation();
    }
    void Container::OnOrientationDirectionChanged(EventArgs &e)
    {
        UpdateOrientation();
    }

    Container::Container()
        : wasPressed(false), useOrientation(false)
    // isActiveSetting(nullptr)
    {
        UpdateState();
        SetName("Container");
    }

    void Container::UpdateOrientation()
    {
        if (!useOrientation)
        {
            return;
        }

        switch (GetOrientation())
        {
        case Orientation::Horizontal:
            SetColumns(columnsOrRows.empty() ? "*" : columnsOrRows);
            SetRows("Auto");
            break;

        case Orientation::Vertical:
            SetColumns("Auto");
            SetRows(columnsOrRows.empty() ? "*" : columnsOrRows);
            break;
        }

        int increment = GetOrientationDirection() == OrientationDirection::Normal ? 1 : -1;
        size_t index = GetOrientationDirection() == OrientationDirection::Normal ? 0 : GetChildren().size() - 1;

        for (Visual *content : GetChildren())
        {
            switch (GetOrientation())
            {
            case Orientation::Vertical:
                content->SetGrid(0, index);
                break;

            case Orientation::Horizontal:
                content->SetGrid(index, 0);
                break;
            }

            index += increment;
        }
    }

    void Container::OnIsErrorChanged(EventArgs &e)
    {
        UpdateState();
        IsErrorProperty::OnIsErrorChanged(e);
    }

    void Container::OnIsActiveChanged(EventArgs &e)
    {
        if (GetCanFocus() && GetIsActive())
        {
            Focus();
        }

        // if (isActiveSetting != nullptr)
        // {
        //     isActiveSetting->SetValue(isActive);
        // }

        UpdateState();

        IsActiveProperty::OnIsActiveChanged(e);
    }

    void Container::UpdateState()
    {
        std::string newState = GetState();
#ifdef DEBUG_VISUAL_STATES
        std::cout << "[DEBUG] Container::UpdateState() - " << GetName()
                  << " changing state from " << GetVisualState() << " to: " << newState << std::endl;
#endif
        // before we execute the code below we need to check if this BrushVisualStateGroup has the requested state in the list
        // If not we return the current state
        if (!HasVisualState(newState))
        {
#ifdef DEBUG_VISUAL_STATES
            std::cout << "[DEBUG] Container::UpdateState() - " << GetName()
                      << " requested state not found, using current state: " << GetVisualState() << std::endl;
#endif
            return;
        }

        SetVisualState(newState);
    }

    std::string Container::GetState()
    {
#ifdef DEBUG_VISUAL_STATES
        std::cout << "[DEBUG] Container::GetState() - " << GetName() 
                  << " IsMouseOver: " << (GetIsMouseOver() ? "true" : "false")
                  << " IsActive: " << (GetIsActive() ? "true" : "false") 
                  << " IsFocused: " << (GetIsFocused() ? "true" : "false") << std::endl;
#endif

        if (!GetEnabled())
            return "Disabled";

        if (GetIsError())
            return "Error";

        if (IsInputPressed && GetCanDeactivate())
            return "Pressed";

        if (GetIsFocused())
            return "Focused";

        if (GetIsHighlighted())
            return "Highlight";

        if (GetIsMouseOver())
        {
            if (GetIsActive())
                return "ActiveHovered";
            return "Hovered";
        }

        if (GetIsActive())
            return "Active";

        return "Normal";
    }

    void Container::OnChildAdded(Visual &content, EventArgs &e)
    {
        ContainerBase::OnChildAdded(content, e);

        if (useOrientation)
        {
            columnsOrRows = GetOrientation() == Orientation::Horizontal ? GetColumns() : GetRows();
            if (GetChildren().size() > 1)
                columnsOrRows += ",Auto";

            UpdateOrientation();
        }
    }
    void Container::OnChildRemoved(Visual &content, EventArgs &e)
    {
        ContainerBase::OnChildRemoved(content, e);

        if (useOrientation)
        {
            UpdateOrientation();
        }
    }

    void Container::OnInputPressed(MouseEventArgs &e)
    {
        wasPressed = true;

        ContainerBase::OnInputPressed(e);

        if (ActivateOnMouseDown)
        {
            if (!GetIsActive())
            {
                SetIsActive(true);
                e.Handled = true;
            }
            else if (GetIsActive() && GetCanDeactivate())
            {
                SetIsActive(false);
                e.Handled = true;
            }
        }
    }
    void Container::OnInputReleased(MouseEventArgs &e)
    {
        if (ActivateOnMouseDown)
        {
            return;
        }

        if (wasPressed)
        {
            wasPressed = false;

            if (!GetCanActivate())
            {
                // normal button
                // if (this is ToggleButton)
                //{
                //    IsActive = !IsActive;
                //    e.Handled = true;
                //}
                // else
                {
                    // perform click
                    SetIsActive(true);
                    SetIsActive(false);

                    // IsMouseOver = true;
                }
            }
            else
            {
                if (GetIsActive() && GetCanDeactivate())
                {
                    SetIsActive(false);
                    ClearFocus();
                    e.Handled = true;
                }
                else if (!GetIsActive())
                {
                    SetIsActive(true);
                    e.Handled = true;
                }
                else
                {
                    UpdateState();
                }
            }
        }
        else
        {
            UpdateState();
        }

        ContainerBase::OnInputReleased(e);
    }

    void Container::OnKeyDown(KeyEventArgs &e)
    {
        ContainerBase::OnKeyDown(e);

        if (e.Key == CKey::Enter)
        {
            if (GetCanActivate())
            {
                if (!GetIsActive())
                {
                    if (GetIsFocused())
                    {
                        // ClearFocus();
                    }

                    SetIsActive(true);
                }
                else if (GetCanDeactivate())
                {
                    if (GetIsFocused())
                    {
                        // ClearFocus();
                    }

                    SetIsActive(false);
                }
                e.Handled = true;
            }
            else
            {
                // if (mouseHandler != nullptr)
                {
                    // isInputPressed = true;

                    e.Handled = true;
                    EventArgs e;
                    HandleClick(e);

                    if (GetIsFocused())
                    {
                        // ClearFocus must be AFTER HandleClick because
                        // this will set Focus if not already set
                        ClearFocus();
                    }
                }
            }
            Invalidate();
        }
        else if (e.Key == CKey::Escape)
        {
            if (GetIsFocused())
            {
                ClearFocus();
            }
            if (GetCanDeactivate() && GetIsActive())
                SetIsActive(false);
        }
    }
    void Container::OnKeyUp(KeyEventArgs &e)
    {
        if (e.Key == CKey::Enter)
        {
            if (!GetCanActivate())
            {
                // isInputPressed = false;
                UpdateState();
                e.Handled = true;
            }
        }

        ContainerBase::OnKeyUp(e);
    }

    void Container::OnInvalidated(EventArgs &e)
    {
        ContainerBase::OnInvalidated(e);
        for (Visual *content : GetChildren())
        {
            content->Invalidate();
        }
    }

    void Container::UpdateColumns(Container &container, int startIndex)
    {
        if (startIndex != -1)
        {
            int emptyChildCount = 0;
            const std::vector<Visual *> &children = container.GetChildren();

            for (size_t i = startIndex; i < children.size(); i++)
            {
                if (children[i] == nullptr)
                {
                    emptyChildCount++;
                }
                else
                {
                    children[i]->SetColumn(i - emptyChildCount);
                }
            }
        }
    }

    /// <summary>
    /// Updates all childs row indices of the given grid from startIndex to the end.
    /// Mostly used if a child has been removed inbetween.
    /// </summary>
    /// <param name="container">The container which holds the items</param>
    /// <param name="startIndex">The index where the update should start. Passing 0 will update all children.</param>
    void Container::UpdateRows(Container &container, int startIndex)
    {
        if (startIndex != -1)
        {
            int emptyChildCount = 0;
            const std::vector<Visual *> &children = container.GetChildren();

            for (size_t i = startIndex; i < children.size(); i++)
            {
                if (children[i] == nullptr)
                {
                    emptyChildCount++;
                }
                else
                {
                    children[i]->SetRow(i - emptyChildCount);
                }
            }
        }
    }
}
