#include <Drawing/Image.h>
#include <OpenGL/Graphics.h>

namespace xit::Drawing
{
    std::map<std::string, ImageBrush> Image::imageBrushes;
    std::vector<std::string> Image::failedImages;

    static Size ScaleImage(const Size &availableSize, float scaleFactor, const OpenGL::Texture *texture)
    {
        float scaledWidth = texture->Width * scaleFactor;
        float scaledHeight = texture->Height * scaleFactor;

        if (scaledWidth > availableSize.GetWidth())
        {
            scaleFactor = availableSize.GetWidth() / texture->Width;
            scaledWidth = texture->Width * scaleFactor;
            scaledHeight = texture->Height * scaleFactor;
        }

        if (scaledHeight > availableSize.GetHeight())
        {
            scaleFactor = availableSize.GetHeight() / texture->Height;
            scaledWidth = texture->Width * scaleFactor;
            scaledHeight = texture->Height * scaleFactor;
        }

        return Size(scaledWidth, scaledHeight);
    }

    Image::Image()
        : stretch(Stretch::Uniform)
    {
        SetClipToBounds(true);
    }

    Image::Image(int column, int row, int columnSpan, int rowSpan)
        : Image()
    {
        SetGrid(column, row, columnSpan, rowSpan);
    }

    Image::~Image()
    {
    }

    void Image::SetImageSource(const std::string &value)
    {
        if (imageSource != value)
        {
            imageSource = value;
            ImageSourceChanged();
        }
    }

    void Image::SetStretch(const Stretch value)
    {
        if (stretch != value)
        {
            stretch = value;
        }
    }

    bool Image::Empty()
    {
        return imageSource.empty();
    }

    void Image::Rotate(float rotationX, float rotationY, float rotationZ)
    {
        SetRotation(glm::vec3(rotationX, rotationY, rotationZ));
        // SetSize(GetHeight(), GetWidth());
        Invalidate();
    }

    Size Image::Measure(const Size &availableSize)
    {
        const ImageBrush *imageBrush = dynamic_cast<const ImageBrush *>(GetBackground());

        if (imageBrush)
        {
            if (!backgroundTexture || (backgroundTexture->Width == 0) || (backgroundTexture->Height == 0))
                return Size(0);

            float widthFactor = (float)availableSize.GetWidth() / (float)backgroundTexture->Width;
            float heightFactor = (float)availableSize.GetHeight() / (float)backgroundTexture->Height;

            float scaleFactor;

            switch (stretch)
            {
            case Stretch::None:
                return Size(backgroundTexture->Width * GetScaleX(), backgroundTexture->Height * GetScaleY());

            case Stretch::Fill:
                return Size(availableSize.GetWidth(), availableSize.GetHeight());

            case Stretch::Uniform:

                if ((backgroundTexture->Width < availableSize.GetWidth()) &&
                    (backgroundTexture->Height < availableSize.GetHeight()))
                {
                    // image is smaller than the area
                    return Size(backgroundTexture->Width * GetScaleX(), backgroundTexture->Height * GetScaleY());
                }

                scaleFactor = std::min(widthFactor, heightFactor);
                return ScaleImage(availableSize, scaleFactor, backgroundTexture);

            case Stretch::UniformToFill:
                scaleFactor = std::max(widthFactor, heightFactor);
                return ScaleImage(availableSize, scaleFactor, backgroundTexture);

            default:
                Logger::Log(LogLevel::Warning, "Image", "Unknown stretch mode %i", stretch);
                break;
            }
        }

        return Visual::Measure(availableSize);
    }

    int Image::OnMeasureWidth(int available)
    {
        switch (stretch)
        {
        case Stretch::None:
            break;

        case Stretch::Fill:
            return backgroundTexture->Width;

        case Stretch::Uniform:
            if (GetWidth() != -1)
                return GetWidth();
            else if (GetHeight() != -1)
                return GetHeight();
            else if (backgroundTexture)
                return backgroundTexture->Width * GetScaleX();

            // no width and height set and no background texture.
            // do not occupy any space
            return 0;

        case Stretch::UniformToFill:
            break;

        default:
            break;
        }
        return available;
    }

    int Image::OnMeasureHeight(int available)
    {
        switch (stretch)
        {
        case Stretch::None:
            break;

        case Stretch::Fill:
            return backgroundTexture->Height;

        case Stretch::Uniform:
            if (GetHeight() != -1)
                return GetHeight();
            else if (GetWidth() != -1)
                return GetWidth();
            else if (backgroundTexture)
                return backgroundTexture->Height * GetScaleY();

            // no width and height set and no background texture.
            // do not occupy any space
            return 0;

        case Stretch::UniformToFill:
            break;
        default:
            break;
        }
        return available;
    }

    void Image::ImageSourceChanged()
    {
        if (!imageSource.empty())
        {
            if (File::Exists(imageSource))
            {
                ImageBrush &imageBrush = imageBrushes[imageSource];
                imageBrush.SetWidth(GetWidth());
                imageBrush.SetHeight(GetHeight());
                imageBrush.SetFileName(imageSource);

                SetBackground(&imageBrush);
            }
            else
            {
                Logger::Log(LogLevel::Error, "Image", "Image source " + imageSource + " not found");
                failedImages.push_back(imageSource);
            }
        }
    }
}
