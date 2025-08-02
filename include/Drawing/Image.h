#pragma once

#include <map>

#include <Drawing/Visual.h>
#include <Drawing/Brushes/ImageBrush.h>
#include <Drawing/Properties/Stretch.h>

namespace xit::Drawing
{
    class Image : public Visual
    {
    private:
        std::string imageSource;
        Stretch stretch;
        float scale;

        static std::map<std::string, ImageBrush>& GetImageBrushesMap();
        static std::vector<std::string>& GetFailedImagesList();

        void ImageSourceChanged();

    protected:
        virtual int OnMeasureWidth(int available) override;
        virtual int OnMeasureHeight(int available) override;

    public:
        __always_inline const std::string &GetImageSource() const { return imageSource; }
        void SetImageSource(const std::string &value);

        __always_inline Stretch GetStretch() const { return stretch; }
        void SetStretch(const Stretch value);

        bool Empty();

        Image();
        Image(int column, int row, int columnSpan = 1, int rowSpan = 1);
        ~Image();

        void Rotate(float rotationX, float rotationY, float rotationZ);
        Size Measure(const Size &availableSize) override;
    };
}
