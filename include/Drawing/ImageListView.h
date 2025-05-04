#pragma once

#include <Drawing/ListView.h>
#include <Drawing/ImageListItem.h>

namespace xit::Drawing
{
    class ImageListView : public ListView
    {
        protected:

        virtual ListItem* GetContainerForItemOverride() override { return new ImageListItem();}

    public:
        ImageListView()
        {
            SetListViewType(ListViewType::Image);
        }

        ~ImageListView() override = default;
    };
}