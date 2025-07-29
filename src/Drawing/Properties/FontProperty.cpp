#include <Drawing/Properties/FontProperty.h>
#include <Drawing/UIDefaults.h>

namespace xit::Drawing
{
    FontProperty::FontProperty()
    {
        needMeasureFont = true;
        fontName = UIDefaults::DefaultFont;
        SetFontSize(UIDefaults::DefaultFontSize);
    }

    void FontProperty::SetFontName(const std::string &value)
    {
        if (fontName != value)
        {
            fontName = value;
            needMeasureFont = true;
        }
    }

    void FontProperty::SetFontSize(int value)
    {
        if (fontSize != value)
        {
            fontSize = value;
            needMeasureFont = true;
            OnFontSizeChanged();
        }
    }
}