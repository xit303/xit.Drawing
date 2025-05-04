#pragma once

#include <Drawing/ListItem.h>

namespace xit::Drawing
{
    class ImageListItem : public ListItem
    {
    public:
        ImageListItem() : ListItem()
        {
            SetBrushGroup("ListItem");
            SetLayoutGroup("ImageListItem");
        }
        ~ImageListItem() override = default;
    };
}
