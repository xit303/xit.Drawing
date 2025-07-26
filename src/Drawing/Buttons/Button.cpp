#include <Drawing/Buttons/Button.h>

namespace xit::Drawing
{
    Button::Button()
    {
        SetBrushGroup("Button");
        SetLayoutGroup("Button");

        SetName("Button");

        SetUniformImageSize(UIDefaults::ButtonImageHeight);
    }
}
