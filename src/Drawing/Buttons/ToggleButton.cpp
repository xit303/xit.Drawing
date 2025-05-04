#include <Drawing/Buttons/ToggleButton.h>

namespace xit::Drawing
{
    ToggleButton::ToggleButton()
    {
        SetCanActivate(true);
        SetShowImage(true);
    }

    ToggleButton* ToggleButton::CreateRenameButton()
    {
        ToggleButton* toggleButton = new ToggleButton();
        toggleButton->SetImageSource("Resources/Images/Buttons/RenameEdit.png");
        return toggleButton;
    }

    // ToggleButton* ToggleButton::CreateImageToggleButton(const std::string& imageSource, const std::string& toolTipSource, const std::string& defaultToolTip, int column, int row)
    // {
    //     ToggleButton* toggleButton = new ToggleButton();
    //     toggleButton->SetImageSource(imageSource);
    //     toggleButton->SetToolTipSource(toolTipSource);
    //     toggleButton->SetDefaultToolTip(defaultToolTip);
    //     toggleButton->SetGrid(column, row);
    //     return toggleButton;
    // }
}
