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
        virtual void OnChildAdded(Visual &content, EventArgs &e) override;
        virtual void OnUpdateLayout(LayoutVisualState *value) override;

        virtual void OnOrientationChanged(EventArgs &e) override;

        virtual void OnHorizontalContentAlignmentChanged(EventArgs &e) override;
        virtual void OnVerticalContentAlignmentChanged(EventArgs &e) override;

        virtual void OnVisibilityChanged(EventArgs &e) override;

        __always_inline Image &GetImage() { return image; }

#ifdef DEBUG
        virtual int OnMeasureWidth(int available) override;
        virtual int OnMeasureHeight(int available) override;
        virtual void OnRender() override;
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
