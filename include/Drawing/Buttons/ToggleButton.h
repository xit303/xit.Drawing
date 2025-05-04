#pragma once

#include <Drawing/Buttons/ToggleButtonBase.h>

namespace xit::Drawing
{
    class ToggleButton : public ToggleButtonBase
    {
    public:
        ToggleButton();

        static ToggleButton* CreateRenameButton();
        //static ToggleButton* CreateImageToggleButton(const std::string& imageSource, const std::string& toolTipSource, const std::string& defaultToolTip, int column = 0, int row = 0);
    };
}
