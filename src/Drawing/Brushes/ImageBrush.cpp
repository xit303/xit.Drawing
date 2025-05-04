#include <Drawing/Brushes/ImageBrush.h>

namespace xit::Drawing
{
    // bool ImageBrush::ShouldSerializeFileName() { return true; }

    // std::string ImageBrush::GetDefaultFileName() { return fileNameObject.DefaultValue(); }
    // void ImageBrush::SetDefaultFileName(const std::string &value) { fileNameObject.SetDefaultValue(value); }

    // std::string ImageBrush::GetLoadedFileName() { return fileNameObject.LoadedValue(); }
    // void ImageBrush::SetLoadedFileName(const std::string &value) { fileNameObject.SetLoadedValue(value); }

    // bool ImageBrush::GetIsSystemFile() { return isSystemFile; }
    // void ImageBrush::SetIsSystemFile(bool value)
    // {
    //     if (isSystemFile != value)
    //     {
    //         isSystemFile = value;
    //     }
    // }

    void ImageBrush::SetStretch(const Stretch &value)
    {
        if (stretch != value)
        {
            stretch = value;
            // NotifyPropertyChanged();
        }
    }

    ImageBrush::ImageBrush()
    {
        // fileNameObject.PropertyChanged += OnPropertyChanged;
        isSystemFile = false;
        stretch = Stretch::Uniform;
    }

    ImageBrush::ImageBrush(const std::string &fileName)
    {
        // fileNameObject.PropertyChanged += OnPropertyChanged;
        isSystemFile = false;
        SetFileName(fileName);
        stretch = Stretch::Uniform;
    }

    ImageBrush::ImageBrush(ImageBrush &other)
        : BrushBase(other)
    {
        isSystemFile = other.isSystemFile;

        if (!other.GetFileName().empty())
            SetFileName(other.GetFileName());

        stretch = other.stretch;
    }

    ImageBrush::~ImageBrush()
    {
    }

    // void ImageBrush::SetDefault()
    // {
    //     BrushBase::SetDefault();
    //     fileNameObject.SetDefault();

    //     stretch = Stretch::Uniform;
    // }

    // void ImageBrush::Reload()
    // {
    //     BrushBase::Reload();
    //     fileNameObject.Reload();
    // }

    // bool ImageBrush::SaveAs(const std::string &fileName)
    // {
    //     if (isSystemFile && (fileName == fileNameObject.DefaultValue()))
    //     {
    //         return false;
    //     }

    //     SetFileName(fileName);
    //     return BrushBase::Save();
    // }

    BrushBase *ImageBrush::Clone()
    {
        return new ImageBrush(*this);
    }

}
