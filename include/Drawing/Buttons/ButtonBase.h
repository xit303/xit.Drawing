#pragma once

#include <Drawing/Container.h>
#include <Drawing/Properties/LabelProperty.h>
#include <Drawing/Image.h>

namespace xit::Drawing
{
    class ButtonBase : public Container, public LabelProperty
    {
    private:
        Image image;
        bool showImage;
        int uniformImageSize;

        void UpdateSpacing();
        void UniformImageSizeChanged();

    protected:
        void OnChildAdded(Visual &content, EventArgs &e) override;
        void OnUpdateLayout(LayoutVisualState *value) override;

        void OnOrientationChanged(EventArgs &e) override;

        void OnHorizontalContentAlignmentChanged(EventArgs &e) override;
        void OnVerticalContentAlignmentChanged(EventArgs &e) override;

        void OnVisibilityChanged(EventArgs &e) override;

        __always_inline Image &GetImage() { return image; }

#ifdef DEBUG
        int OnMeasureWidth(int available) override;
        int OnMeasureHeight(int available) override;
        void OnRender() override;
#endif

        virtual void OnShowLabelChanged() override;
        virtual void OnShowImageChanged();
        virtual void OnUniformImageSizeChanged();

    public:
        __always_inline const bool GetShowImage() const { return showImage; }
        void SetShowImage(bool value);

        __always_inline const std::string &GetImageSource() const { return image.GetImageSource(); }
        void SetImageSource(const std::string &value);

        __always_inline const int GetUniformImageSize() const { return uniformImageSize; }
        void SetUniformImageSize(int value);

        ButtonBase();

#ifdef DEBUG
        Size Measure(const Size &availableSize) override;
#endif
    };
}
