#include <Drawing/InputContent.h>
#include <Drawing/ToolTip.h>
#include <Input/InputHandler.h>

namespace xit::Drawing
{
    bool InputContent::HandleMouse() { return handleMouse; }
    void InputContent::SetHandleMouse(bool value)
    {
        if (handleMouse != value)
        {
            handleMouse = value;
            wasMouseHandled = value;
        }
    }

    void InputContent::SetIsMouseCaptured(bool value)
    {
        if (isMouseCaptured != value)
        {
            isMouseCaptured = value;

            if (!isMouseCaptured && !isMouseOver && isMouseDown)
                isMouseDown = false;
        }
    }

    bool InputContent::HandleKeyboard() { return handleKeyboard; }
    void InputContent::SetHandleKeyboard(bool value)
    {
        if (handleKeyboard != value)
        {
            handleKeyboard = value;
            wasKeyboardHandled = value;

            if (value)
            {
                // Keyboard::AddKeyDownHandler(this, (s, e) = > HandleKeyDown(s, e));
                // Keyboard::AddKeyUpHandler(this, (s, e) = > HandleKeyUp(s, e));
            }
            else
            {
                // Keyboard::RemoveKeyDownHandler(this);
                // Keyboard::RemoveKeyUpHandler(this);
            }
        }
    }

    void InputContent::SetActivateOnMouseDown(bool value)
    {
        if (activateOnMouseDown != value)
        {
            activateOnMouseDown = value;
        }
    }

    bool InputContent::CanFocus() { return GetCanFocus() && GetIsVisible() && GetEnabled(); }

    InputContent::InputContent()
    {
        handleMouse = false;
        wasMouseHandled = false;
        isMouseCaptured = false;
        activateOnMouseDown = false;

        isMouseDown = false;
        isMouseOver = false;

        isInputPressed = false;

        handleKeyboard = false;
        wasKeyboardHandled = false;

        toolTipHidden = false;
    }

    //******************************************************************************
    // Private
    //******************************************************************************

    void InputContent::HandleInputEnter(EventArgs &e)
    {
        toolTipHidden = false;
        isMouseOver = true;
        UpdateState();
        InputEnter(*this, e);
        OnInputEnter(e);
    }
    void InputContent::HandleInputLeave(EventArgs &e)
    {
        if (!GetToolTip().empty())
        {
            ToolTip::Hide();
        }

        if (!isMouseCaptured)
            isMouseDown = false;

        isMouseOver = false;
        isInputPressed = false;
        InputLeave(*this, e);

        MouseEventArgs me(InputHandler::GetLastMousePosition());
        OnInputLeave(me);
        UpdateState();
    }

    void InputContent::HandleInputPressed(MouseEventArgs &e)
    {
        if (!GetToolTip().empty())
        {
            toolTipHidden = true;
            ToolTip::Hide();
        }

        isInputPressed = true;
        InputPressed(*this, e);
        OnInputPressed(e);
        UpdateState();
    }
    void InputContent::HandleInputReleased(MouseEventArgs &e)
    {
        isInputPressed = false;
        InputReleased(*this, e);
        OnInputReleased(e);

        if (!e.Handled)
        {
            EventArgs e1;
            HandleClick(e1);

            if (e1.Handled)
                e.Handled = true;
        }
        UpdateState();
    }

    void InputContent::HandleInputScroll(MouseEventArgs &e)
    {
        InputScroll(*this, e);
        OnInputScroll(e);
    }
    void InputContent::HandleInputMove(MouseEventArgs &e)
    {
        InputMove(*this, e);
        OnInputMove(e);

        if (!toolTipHidden && (!GetToolTip().empty()))
        {
            ToolTip::Show(GetToolTip(), e.Position.X, e.Position.Y); // GetY() + GetActualHeight());
        }
    }

    void InputContent::HandleKeyDown(KeyEventArgs &e)
    {
        if (!e.Handled)
        {
            KeyDown(*this, e);
            OnKeyDown(e);
        }
    }
    void InputContent::HandleKeyUp(KeyEventArgs &e)
    {
        if (!e.Handled)
        {
            KeyUp(*this, e);
            OnKeyUp(e);
        }
    }

    void InputContent::HandleGotKeyboardFocus(EventArgs &e)
    {
        SetIsFocused(true);
        UpdateState();
        OnGotKeyboardFocus(e);
    }
    void InputContent::HandleLostKeyboardFocus(EventArgs &e)
    {
        SetIsFocused(false);
        UpdateState();
        OnLostKeyboardFocus(e);
    }

    void InputContent::HandleClick(EventArgs &e)
    {
        if (GetCanFocus())
        {
            Focus();
        }

        Click(*this, e);
        OnClick();
    }

    //******************************************************************************
    // Protected
    //******************************************************************************

    void InputContent::OnVisibilityChanged(EventArgs &e)
    {
        Visual::OnVisibilityChanged(e);
        if (!GetIsVisible() && GetIsFocused())
            ClearFocus();
    }
    void InputContent::OnEnabledChanged(EventArgs &e)
    {
        Visual::OnEnabledChanged(e);
        if (!GetEnabled() && GetIsFocused())
            ClearFocus();
    }

    void InputContent::OnParentChanged(EventArgs &e)
    {
        Visual::OnParentChanged(e);

        if (GetParent() == nullptr)
        {
            if (GetIsFocused())
                ClearFocus();

            if (handleKeyboard)
            {
                handleKeyboard = false;
            }
            if (handleMouse)
            {
                handleMouse = false;
            }
        }
        else
        {
            handleKeyboard = wasKeyboardHandled;
            handleMouse = wasMouseHandled;
        }
    }

    //******************************************************************************
    // Public
    //******************************************************************************

    bool InputContent::Focus()
    {
        if (!(GetEnabled() && GetIsVisible()))
            return false;

        if (GetCanFocus() && !GetIsFocused())
        {
            EventArgs e;
            HandleGotKeyboardFocus(e);

            Invalidate();

            bool retval;

            if (!e.Handled)
                retval = InputHandler::SetFocus(this);
            else
                retval = true;

            return retval;
        }
        return false;
    }
    void InputContent::ClearFocus(bool invalidateNow)
    {
        if (!(GetEnabled() && GetIsVisible()))
            return;

        if (GetIsFocused())
        {
            EventArgs e;
            HandleLostKeyboardFocus(e);
            if (invalidateNow)
                Invalidate();
        }
    }

    void InputContent::ExecuteInputEnter(EventArgs &e)
    {
        if (!(GetEnabled() && GetIsVisible()))
            return;

        HandleInputEnter(e);
        Invalidate();
        e.Handled = true;
    }
    void InputContent::ExecuteInputLeave(MouseEventArgs &e)
    {
        if (!(GetEnabled() && GetIsVisible()))
            return;

        HandleInputLeave(e);
        Invalidate();
    }
    void InputContent::ExecuteInputPressed(MouseEventArgs &e)
    {
        if (!(GetEnabled() && GetIsVisible()))
            return;

        if (!isMouseOver)
        {
            HandleInputEnter(e);
        }
        isMouseDown = true;
        HandleInputPressed(e);
        Invalidate();
    }
    void InputContent::ExecuteInputReleased(MouseEventArgs &e)
    {
        if (!(GetEnabled() && GetIsVisible()))
            return;

        if (!isMouseOver)
        {
            HandleInputEnter(e);
        }
        if (isMouseDown)
        {
            isMouseDown = false;
            HandleInputReleased(e);
            Invalidate();
        }
    }
    void InputContent::ExecuteInputScroll(MouseEventArgs &e)
    {
        if (!(GetEnabled() && GetIsVisible()))
            return;

        if (!isMouseOver)
        {
            HandleInputEnter(e);
        }

        HandleInputScroll(e);
        Invalidate();
    }
    void InputContent::ExecuteInputMove(MouseEventArgs &e)
    {
        if (!(GetEnabled() && GetIsVisible()))
            return;

        if (!isMouseOver)
        {
            HandleInputEnter(e);
            Invalidate();
        }
        HandleInputMove(e);
    }

    void InputContent::ExecuteKeyDown(KeyEventArgs &e)
    {
        if (!(GetEnabled() && GetIsVisible()))
            return;

        if (GetIsFocused() || isMouseOver)
        {
            HandleKeyDown(e);
        }
    }
    void InputContent::ExecuteKeyUp(KeyEventArgs &e)
    {
        if (!(GetEnabled() && GetIsVisible()))
            return;

        if (GetIsFocused())
        {
            HandleKeyUp(e);
        }
    }

    //******************************************************************************
    // Static methods
    //******************************************************************************
}
