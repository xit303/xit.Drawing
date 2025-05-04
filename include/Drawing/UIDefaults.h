#pragma once

#include <MathHelper.h>
#include <string>

namespace xit::Drawing
{
    class UIDefaults
    {
    private:
        static const int defaultItemHeight;
        static const int columnSpacing;
        static const int rowSpacing;

    public:
        static const int DefaultItemHeight;
        static const int DefaultBorderThickness;

        static const int CornerRadius;
        static const int BigCornerRadius;

        //#region ColumnSpacing / RowSpacing

        static const int MinimumColumnSpacing;
        static const int HalfColumnSpacing;
        static const int ColumnSpacing;

        static const int MinimumRowSpacing;
        static const int HalfRowSpacing;
        static const int RowSpacing;

        static const int ContainerPadding;
        static const int SmallContainerPaddingTop;

        //#region Menu Button

        static const int MenuButtonMinWidth;
        static const int MenuButtonImageSize;
        static const int MenuButtonHorizontalHeight;
        static const int MenuButtonVerticalHeight;

        //#region Button

        static const std::string ButtonFont;
        static const int ButtonMinWidth;

        static const int ButtonHeight;
        static const int ButtonPaddingLeftRight;
        //const int ButtonPaddingTopBottom;

        static const int ButtonImageHeight;
        //static const int ButtonPaddingLeft;
        //static const int ButtonPaddingRight;
        static const int ButtonSpacing;
        static const int ButtonRowSpacing;
        //static const int ButtonImageHeight;
        //static const int ButtonTextSize;
        //static const int ButtonPaddingTopBottom  = ButtonHeight - ButtonImageHeight;

        //#region FAB

        static const int FloatingActionButtonSize;
        static const int FloatingActionButtonImageHeight;

        //#region ToggleButton

        static const int ToggleButtonHeight;
        static const int ToggleButtonImageHeight;
        static const int ToggleButtonPaddingLeftRight;
        static const int ToggleButtonPaddingTopBottom;

        //#region TextBox

        static const int TextBoxHeight;
        static const int TextBoxPaddingLeft;
        static const int TextBoxPaddingRight;

        //#region ProgressBar

        static const int ProgressBarMinHeight;

        //#region Font Sizes

        static const std::string DefaultFont;
        static const int DefaultFontSize;
        static const int SmallFontSize;
        static const int MinimumButtonFontSize;
        static const int ButtonFontSize;
        static const int HeaderFontSize;
    };
}
