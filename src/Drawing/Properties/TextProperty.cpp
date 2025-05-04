#include <Drawing/Properties/TextProperty.h>

namespace xit::Drawing
{
    TextProperty::TextProperty()
    {
        SetTextWrapping(TextWrapping::NoWrap);
    }

    void TextProperty::SetText(const std::string &value)
    {
        if (text != value)
        {
            text = value;
            needMeasureText = true;
            OnTextChanged();
        }
    }

    void TextProperty::SetTextWrapping(const TextWrapping &value)
    {
        if (textWrapping != value)
        {
            textWrapping = value;
            OnTextWrappingChanged();
        }
    }
}