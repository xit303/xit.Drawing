#pragma once

#include <Drawing/Visual.h>
#include <Drawing/Properties/FocusProperty.h>
#include <Input/KeyEventArgs.h>
#include <Input/MouseEventArgs.h>

// #include "../Input/Keyboard.h"

namespace xit::Drawing
{
    using CKey = xit::Input::CKey;
    using MouseEventArgs = xit::Input::MouseEventArgs;
    using KeyEventArgs = xit::Input::KeyEventArgs;

    class InputContent : public Visual, public FocusProperty
    {
    private:
        bool handleMouse;
        bool isInputPressed;
        bool isMouseOver;
        bool isMouseDown;
        bool isMouseCaptured;
        bool handleKeyboard;
        bool activateOnMouseDown;

        bool wasKeyboardHandled;
        bool wasMouseHandled;

        bool toolTipHidden;

    public:
        bool HandleMouse();
        void SetHandleMouse(bool value);
        const bool &IsInputPressed = isInputPressed;
        const bool &IsMouseOver = isMouseOver;

        const bool &IsMouseCaptured = isMouseCaptured;
        void SetIsMouseCaptured(bool value);

        bool HandleKeyboard();
        void SetHandleKeyboard(bool value);

        const bool &ActivateOnMouseDown = activateOnMouseDown;
        void SetActivateOnMouseDown(bool value);

        bool CanFocus();

        Event<InputContent &, EventArgs &> InputEnter;
        Event<InputContent &, EventArgs &> InputLeave;
        Event<InputContent &, MouseEventArgs &> InputPressed;
        Event<InputContent &, MouseEventArgs &> InputReleased;
        Event<InputContent &, MouseEventArgs &> InputScroll;
        Event<InputContent &, MouseEventArgs &> InputMove;
        Event<InputContent &, EventArgs &> Click;

        Event<InputContent &, KeyEventArgs &> KeyDown;
        Event<InputContent &, KeyEventArgs &> KeyUp;

        InputContent();

    private:
        void HandleInputEnter(EventArgs &e);
        void HandleInputLeave(EventArgs &e);

        void HandleInputPressed(MouseEventArgs &e);
        void HandleInputReleased(MouseEventArgs &e);

        void HandleInputScroll(MouseEventArgs &e);
        void HandleInputMove(MouseEventArgs &e);

        void HandleKeyDown(KeyEventArgs &e);
        void HandleKeyUp(KeyEventArgs &e);

        void HandleGotKeyboardFocus(EventArgs &e);
        void HandleLostKeyboardFocus(EventArgs &e);

    protected:
        virtual void OnVisibilityChanged(EventArgs &e) override;
        virtual void OnEnabledChanged(EventArgs &e) override;

        virtual void OnInputEnter(EventArgs &e) {}
        virtual void OnInputLeave(EventArgs &e) {}

        virtual void OnInputPressed(MouseEventArgs &e) {}
        virtual void OnInputReleased(MouseEventArgs &e) {}

        virtual void OnInputScroll(MouseEventArgs &e) {}
        virtual void OnInputMove(MouseEventArgs &e) {}

        virtual void OnKeyDown(KeyEventArgs &e) {}
        virtual void OnKeyUp(KeyEventArgs &e) {}

        virtual void OnGotKeyboardFocus(EventArgs &e) {}
        virtual void OnLostKeyboardFocus(EventArgs &e) {}

        void OnParentChanged(EventArgs &e) override;

        /// Must be protected because it is used in Container as well
        // TODO get rid if this protected part. I don't like that
        void HandleClick(EventArgs &e);
        virtual void OnClick() {}

    public:
        bool Focus();
        void ClearFocus(bool invalidateNow = true);

        virtual void ExecuteInputEnter(EventArgs &e);
        virtual void ExecuteInputLeave(EventArgs &e);
        virtual void ExecuteInputPressed(MouseEventArgs &e);
        virtual void ExecuteInputReleased(MouseEventArgs &e);
        virtual void ExecuteInputScroll(MouseEventArgs &e);
        virtual void ExecuteInputMove(MouseEventArgs &e);

        virtual void ExecuteKeyDown(KeyEventArgs &e);
        virtual void ExecuteKeyUp(KeyEventArgs &e);
    };
}
