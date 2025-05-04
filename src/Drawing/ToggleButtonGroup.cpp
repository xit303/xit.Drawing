#include <Drawing/ToggleButtonGroup.h>

namespace xit::Drawing
{
    void ToggleButtonGroup::SetMustSelectOne(bool value)
    {
        if (mustSelectOne != value)
        {
            mustSelectOne = value;
        }
    }

    ToggleButtonGroup::ToggleButtonGroup()
        : mustSelectOne(false),
          numberOfActiveButtons(0),
          activeButton(nullptr)
    {
        SetUseOrientation(true);
    }

    void ToggleButtonGroup::ButtonIsActiveChanged(IsActiveProperty &sender, EventArgs &e)
    {
        if (sender.GetIsActive())
        {
            numberOfActiveButtons++;

            if (activeButton != nullptr)
            {
                activeButton->SetCanDeactivate(true);
                activeButton->SetIsActive(false);
            }

            activeButton = dynamic_cast<Container *>(&sender);

            // if MustSelectOne is enabled we deactivate state changes for this button
            activeButton->SetCanDeactivate(!mustSelectOne);

            ToggleButtonChecked(*activeButton);
        }
        else
        {
            // button.CanDeactivate = true;

            if (numberOfActiveButtons > 0)
            {
                --numberOfActiveButtons;
            }
            if (numberOfActiveButtons == 0)
            {
                activeButton = nullptr;
                GroupClosed(*this);
            }
        }
    }

    void ToggleButtonGroup::OnChildAdded(Visual &content, EventArgs &e)
    {
        Container *container = dynamic_cast<Container *>(&content);
        if (container)
        {
            container->IsActiveChanged.Add(&ToggleButtonGroup::ButtonIsActiveChanged, this);
        }

        Container::OnChildAdded(content, e);
    }
    void ToggleButtonGroup::OnChildRemoved(Visual &content, EventArgs &e)
    {
        Container *container = dynamic_cast<Container *>(&content);
        if (container)
        {
            container->IsActiveChanged.Remove(&ToggleButtonGroup::ButtonIsActiveChanged, this);
        }

        Container::OnChildRemoved(content, e);
    }
}
