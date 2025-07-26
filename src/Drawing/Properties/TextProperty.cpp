#include <Drawing/Properties/TextProperty.h>

#ifdef DEBUG_TEXT_PROPERTY
#include <iostream>
#endif

namespace xit::Drawing
{
    TextProperty::TextProperty()
    {
        SetTextWrapping(TextWrapping::NoWrap);
    }

    void TextProperty::SetText(const std::string &value)
    {
#ifdef DEBUG_TEXT_PROPERTY
        std::cout << "[DEBUG] TextProperty::SetText called with: '" << value << "'" << std::endl;
#endif
        if (text != value)
        {
#ifdef DEBUG_TEXT_PROPERTY
            std::cout << "[DEBUG] Text changed, updating from '" << text << "' to '" << value << "'" << std::endl;
#endif
            text = value;
            needMeasureText = true;
            OnTextChanged();
        }
        else
        {
#ifdef DEBUG_TEXT_PROPERTY
            std::cout << "[DEBUG] Text unchanged, not updating" << std::endl;
#endif
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