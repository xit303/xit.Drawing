#include <Drawing/Buttons/Button.h>

namespace xit::Drawing
{
    Button::Button()
    {
        SetBrushGroup("Button");
        SetLayoutGroup("Button");

        SetUniformImageSize(UIDefaults::ButtonImageHeight);
    }
}
