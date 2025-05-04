#include <Drawing/UIDefaults.h>

namespace xit::Drawing
{
    const int UIDefaults::defaultItemHeight = 36;
    const int UIDefaults::columnSpacing = 16;
    const int UIDefaults::rowSpacing = 16;

    const int UIDefaults::DefaultItemHeight = defaultItemHeight;
    const int UIDefaults::DefaultBorderThickness = 1;

    const int UIDefaults::CornerRadius = defaultItemHeight >> 3;
    const int UIDefaults::BigCornerRadius = defaultItemHeight >> 2;

    //#region ColumnSpacing / RowSpacing

    const int UIDefaults::MinimumColumnSpacing = 2;
    const int UIDefaults::HalfColumnSpacing = columnSpacing >> 1;
    const int UIDefaults::ColumnSpacing = columnSpacing;

    const int UIDefaults::MinimumRowSpacing = 2;
    const int UIDefaults::HalfRowSpacing = rowSpacing >> 1;
    const int UIDefaults::RowSpacing = rowSpacing;

    const int UIDefaults::ContainerPadding = 16;
    const int UIDefaults::SmallContainerPaddingTop = 8;

    //#region Menu Button

    const int UIDefaults::MenuButtonMinWidth = 96;
    const int UIDefaults::MenuButtonImageSize = 18;
    const int UIDefaults::MenuButtonHorizontalHeight = 48;
    const int UIDefaults::MenuButtonVerticalHeight = 72;

    //#region Button

    const std::string UIDefaults::ButtonFont = "Resources/Fonts/ROBOTO-REGULAR.TTF";
    const int UIDefaults::ButtonMinWidth = 64;

    const int UIDefaults::ButtonHeight = UIDefaults::defaultItemHeight;
    const int UIDefaults::ButtonPaddingLeftRight = 16;
    //const int ButtonPaddingTopBottom  = 10;

    const int UIDefaults::ButtonImageHeight = UIDefaults::defaultItemHeight;
    //const int UIDefaults::ContainedImageButtonPaddingLeft = 12;
    //const int UIDefaults::ContainedImageButtonPaddingRight = 16;
    const int UIDefaults::ButtonSpacing = 8;
    const int UIDefaults::ButtonRowSpacing = 8;
    //const int UIDefaults::ButtonImageHeight = 18;
    //const int UIDefaults::ContainedImageButtonTextSize = 14;
    //const int ContainedImageButtonPaddingTopBottom  = ContainedImageButtonHeight - ButtonImageHeight;

    //#region FAB

    const int UIDefaults::FloatingActionButtonSize = 48;
    const int UIDefaults::FloatingActionButtonImageHeight = 24;

    //#region ToggleButton

    const int UIDefaults::ToggleButtonHeight = UIDefaults::defaultItemHeight;
    const int UIDefaults::ToggleButtonImageHeight = 24;
    const int UIDefaults::ToggleButtonPaddingLeftRight = 6;
    const int UIDefaults::ToggleButtonPaddingTopBottom = (UIDefaults::ToggleButtonHeight - UIDefaults::ToggleButtonImageHeight) >> 1;

    //#region TextBox

    const int UIDefaults::TextBoxHeight = UIDefaults::defaultItemHeight;
    const int UIDefaults::TextBoxPaddingLeft = 8;
    const int UIDefaults::TextBoxPaddingRight = 8;

    //#region ProgressBar

    const int UIDefaults::ProgressBarMinHeight = 4;

    //#region Font Sizes

    const std::string UIDefaults::DefaultFont = "Resources/Fonts/ROBOTO-REGULAR.TTF";
    const int UIDefaults::DefaultFontSize = 12;
    const int UIDefaults::SmallFontSize = 10;
    const int UIDefaults::MinimumButtonFontSize = 12;
    const int UIDefaults::ButtonFontSize = 14;
    const int UIDefaults::HeaderFontSize = 14;
}
