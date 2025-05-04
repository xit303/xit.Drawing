#pragma once

#include <Properties/FileNameProperty.h>
#include <Drawing/Brushes/BrushBase.h>
#include <Drawing/Properties/Stretch.h>
// #include "../IFileObject.h"
// #include "../LoadableObject.h"

namespace xit::Drawing
{
    class ImageBrush : public BrushBase, public Properties::FileNameProperty //, public IFileObject
    {
    private:
        mutable Stretch stretch;
        bool isSystemFile;

        int width;
        int height;

    public:
        // std::string GetDefaultFileName() override;
        // void SetDefaultFileName(const std::string &value) override;

        // std::string GetLoadedFileName() override;
        // void SetLoadedFileName(const std::string &value);

        // bool GetIsSystemFile() override;
        // void SetIsSystemFile(bool value) override;

        __always_inline Stretch &GetStretch() const { return stretch; }
        void SetStretch(const Stretch &value);

        __always_inline int GetWidth() const { return width; }
        void SetWidth(int value) { width = value; }

        __always_inline int GetHeight() const { return height; }
        void SetHeight(int value) { height = value; }

        ImageBrush();
        ImageBrush(const std::string &fileName);
        ImageBrush(ImageBrush &other);
        virtual ~ImageBrush();

        // void SetDefault() override;
        // void Reload() override;
        // bool SaveAs(const std::string &fileName) override;

        virtual BrushBase *Clone() override;
    };
}
