#include <Drawing/InputContent.h>
#include <Drawing/ToolTip.h>
#include <Input/InputHandler.h>

#ifdef DEBUG_INPUT_EVENTS
#include <iostream>
#endif

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
        // if (activateOnMouseDown != value)
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

        SetName("InputContent");
    }

    //******************************************************************************
    // Private
    //******************************************************************************

    void InputContent::HandleInputEnter(EventArgs &e)
    {
#ifdef DEBUG_INPUT_EVENTS
        std::cout << "[DEBUG] InputContent::HandleInputEnter() - " << GetName() << " mouse entered" << std::endl;
#endif
        toolTipHidden = false;
        isMouseOver = true;
        UpdateState();
        InputEnter(*this, e);
        OnInputEnter(e);
    }
    void InputContent::HandleInputLeave(EventArgs &e)
    {
#ifdef DEBUG_INPUT_EVENTS
        std::cout << "[DEBUG] InputContent::HandleInputLeave() - " << GetName() << " mouse left" << std::endl;
#endif
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
#ifdef DEBUG_INPUT_EVENTS
        std::cout << "[DEBUG] InputContent::HandleInputPressed() - " << GetName() << " mouse pressed" << std::endl;
#endif

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
#ifdef DEBUG_INPUT_EVENTS
        std::cout << "[DEBUG] InputContent::HandleInputReleased() - " << GetName() << " mouse released" << std::endl;
#endif

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
#ifdef DEBUG_INPUT_EVENTS
        std::cout << "[DEBUG] InputContent::HandleInputScroll() - " << GetName() << " mouse scrolled" << std::endl;
#endif

        InputScroll(*this, e);
        OnInputScroll(e);
    }
    void InputContent::HandleInputMove(MouseEventArgs &e)
    {
#ifdef DEBUG_INPUT_EVENTS_MOVE
        std::cout << "[DEBUG] InputContent::HandleInputMove() - " << GetName() << " mouse moved to (" 
                  << e.Position.X << ", " << e.Position.Y << ")" << std::endl;
#endif

        InputMove(*this, e);
        OnInputMove(e);

        if (!toolTipHidden && (!GetToolTip().empty()))
        {
            ToolTip::Show(GetToolTip(), e.Position.X, e.Position.Y); // GetY() + GetActualHeight());
        }
    }

    void InputContent::HandleKeyDown(KeyEventArgs &e)
    {
#ifdef DEBUG_INPUT_EVENTS
        std::cout << "[DEBUG] InputContent::HandleKeyDown() - " << GetName() << " key down: " 
                  << std::to_string((int)e.Key) << " (" << e.KeyChar << ")" << std::endl;
#endif

        if (!e.Handled)
        {
            KeyDown(*this, e);
            OnKeyDown(e);
        }
    }
    void InputContent::HandleKeyUp(KeyEventArgs &e)
    {
#ifdef DEBUG_INPUT_EVENTS
        std::cout << "[DEBUG] InputContent::HandleKeyUp() - " << GetName() << " key up: " 
                  << std::to_string((int)e.Key) << " (" << e.KeyChar << ")" << std::endl;
#endif

        if (!e.Handled)
        {
            KeyUp(*this, e);
            OnKeyUp(e);
        }
    }

    void InputContent::HandleGotKeyboardFocus(EventArgs &e)
    {
#ifdef DEBUG_INPUT_EVENTS
        std::cout << "[DEBUG] InputContent::HandleGotKeyboardFocus() - " << GetName() << " got keyboard focus" << std::endl;
#endif

        SetIsFocused(true);
        UpdateState();
        OnGotKeyboardFocus(e);
    }
    void InputContent::HandleLostKeyboardFocus(EventArgs &e)
    {
#ifdef DEBUG_INPUT_EVENTS
        std::cout << "[DEBUG] InputContent::HandleLostKeyboardFocus() - " << GetName() << " lost keyboard focus" << std::endl;
#endif

        SetIsFocused(false);
        UpdateState();
        OnLostKeyboardFocus(e);
    }

    void InputContent::HandleClick(EventArgs &e)
    {
#ifdef DEBUG_INPUT_EVENTS
        std::cout << "[DEBUG] InputContent::HandleClick() - " << GetName() << " clicked" << std::endl;
#endif

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
            // Let InputHandler manage the focus transition
            // This will call back to our HandleGotKeyboardFocus if successful
            bool retval = InputHandler::SetFocus(this);

            if (retval)
            {
                EventArgs e;
                HandleGotKeyboardFocus(e);
                Invalidate();
            }

            return retval;
        }
        return GetIsFocused(); // Return true if already focused
    }
    void InputContent::ClearFocus(bool invalidateNow)
    {
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
