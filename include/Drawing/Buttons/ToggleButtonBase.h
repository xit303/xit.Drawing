#pragma once

#include <Drawing/Buttons/ButtonBase.h>
#include <Drawing/Image.h>

namespace xit::Drawing
{
    class ToggleButtonBase : public ButtonBase
    {
    private:
        Image *activeImage;

        __always_inline const std::string &GetActiveImageSource() const { return activeImage->GetImageSource(); }
        void SetActiveImageSource(const std::string &value);

    protected:
        virtual void OnIsActiveChanged(EventArgs &e) override;
        virtual void OnUniformImageSizeChanged() override;

    public:
        ToggleButtonBase();

        Size Measure(const Size &availableSize) override;

        //******************************************************************************
        // #region Plus Minus
        //******************************************************************************

        // static ToggleButtonBase* Create(const std::string& name, bool isEnabled, const std::string& imageSource = std::string(), const std::string& defaultToolTip = std::string(), int column = 0, int row = 0, int columnSpan = 1, int rowSpan = 1);
        // static ToggleButtonBase* CreatePlusButton(const std::string& name, bool isEnabled, const std::string& defaultToolTip = std::string(), int column = 0, int row = 0, int columnSpan = 1, int rowSpan = 1);
        // static ToggleButtonBase* CreateMinusButton(const std::string& name, bool isEnabled, const std::string& defaultToolTip = std::string(), int column = 0, int row = 0, int columnSpan = 1, int rowSpan = 1);
        // static ToggleButtonBase* CreateCopyButton(const std::string& name, const std::string& defaultToolTip = std::string(), int column = 0, int row = 0, int columnSpan = 1, int rowSpan = 1);
        // static ToggleButtonBase* CreatePasteButton(const std::string& name, const std::string& defaultToolTip = std::string(), int column = 0, int row = 0, int columnSpan = 1, int rowSpan = 1);
        // static ToggleButtonBase* CreateResetButton(const std::string& name, const std::string& defaultToolTip = std::string(), int column = 0, int row = 0, int columnSpan = 1, int rowSpan = 1);
        // static ToggleButtonBase* CreateLinkButton(const std::string& name, const std::string& defaultToolTip = std::string(), int column = 0, int row = 0, int columnSpan = 1, int rowSpan = 1);
    };
}
