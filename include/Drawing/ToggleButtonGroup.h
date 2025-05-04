#pragma once

#include <Drawing/Container.h>
#include <Drawing/Buttons/ButtonBase.h>

namespace xit::Drawing
{
    class ToggleButtonGroup : public Container
    {
    private:
        bool mustSelectOne;
        int numberOfActiveButtons;
        Container* activeButton;

        void ButtonIsActiveChanged(IsActiveProperty& sender, EventArgs& e);

    protected:
        void OnChildAdded(Visual& content, EventArgs& e) override;
        void OnChildRemoved(Visual& content, EventArgs& e) override;

    public:
        __always_inline bool GetMustSelectOne() { return mustSelectOne; }
        void SetMustSelectOne(bool value);

        Event<Container&> ToggleButtonChecked;
        Event<ToggleButtonGroup&> GroupClosed;

        ToggleButtonGroup();
    };
}
