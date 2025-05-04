#include "Drawing/Size.h"

namespace xit::Drawing
{
    const Size& Size::Empty = Size();

    Size::Size() 
        : Size(0, 0) 
    {
    }
    Size::Size(int width, int height)
        : width(width), height(height)
    {
    }
    Size::Size(int uniform)
        : Size(uniform, uniform)
    {
    }
    bool Size::IsEmpty() 
    { 
        return width == 0 && height == 0; 
    }

    bool Size::operator==(const Size& other) const
    {
        return width == other.width && height == other.height;
    }

    bool Size::operator!=(const Size& other) const
    {
        return !(*this == other);
    }
}
