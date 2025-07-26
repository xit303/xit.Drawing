#include <Drawing/Buttons/ToggleButtonBase.h>

namespace xit::Drawing
{
    ToggleButtonBase::ToggleButtonBase()
        : activeImage(nullptr)
    {
        SetBrushGroup("ToggleButton");
        SetLayoutGroup("ToggleButton");
        SetShowLabel(false);
        SetName("ToggleButtonBase");
    }

    Size ToggleButtonBase::Measure(const Size &availableSize)
    {
        /*if (IsActive && activeImage)
            return activeImage->Measure(availableSize);

        if (!activeImage)
        {
            image.Measure(availableSize);
        }*/

        return ButtonBase::Measure(availableSize);
    }

    void ToggleButtonBase::SetActiveImageSource(const std::string &value)
    {
        if (activeImage == nullptr)
        {
            activeImage = new Image();
            activeImage->SetInheritForeground(true);
            AddChild(activeImage);

            // need to update grid positions
            EventArgs e;
            OnOrientationChanged(e);
        }

        activeImage->SetImageSource(value);

        OnUniformImageSizeChanged();
        OnShowImageChanged();
    }

    void ToggleButtonBase::OnIsActiveChanged(EventArgs &e)
    {
        if (activeImage != nullptr)
        {
            SetShowImage(!GetIsActive());
            activeImage->SetIsVisible(GetIsActive());
        }

        ButtonBase::OnIsActiveChanged(e);
    }

    void ToggleButtonBase::OnUniformImageSizeChanged()
    {
        ButtonBase::OnUniformImageSizeChanged();

        if (activeImage != nullptr)
        {
            activeImage->SetHeight(GetUniformImageSize());
            activeImage->SetWidth(GetUniformImageSize());
        }
    }

    //******************************************************************************
    // #region Plus Minus
    //******************************************************************************

    // static ToggleButtonBase* Create(const std::string& name, bool isEnabled, const std::string& imageSource = std::string(), const std::string& defaultToolTip = std::string(), int column = 0, int row = 0, int columnSpan = 1, int rowSpan = 1)
    // {
    //     ToggleButtonBase* element = new ToggleButtonBase();
    //     element->SetName(name);
    //     element->SetDefaultToolTip(defaultToolTip);
    //     element->SetEnabled(isEnabled);
    //     element->SetShowImage(true);
    //     element->SetImageSource(imageSource);
    //     element->SetGrid(column, row, columnSpan, rowSpan);

    //     return element;
    // }

    // static ToggleButtonBase* CreatePlusButton(const std::string& name, bool isEnabled, const std::string& defaultToolTip = std::string(), int column = 0, int row = 0, int columnSpan = 1, int rowSpan = 1)
    // {
    //     ToggleButtonBase* imageButton = Create(name, isEnabled, "PlusButton.png", defaultToolTip, column, row, columnSpan, rowSpan);
    //     //imageButton->SetBrushGroup("Button");
    //     return imageButton;
    // }

    // static ToggleButtonBase* CreateMinusButton(const std::string& name, bool isEnabled, const std::string& defaultToolTip = std::string(), int column = 0, int row = 0, int columnSpan = 1, int rowSpan = 1)
    // {
    //     ToggleButtonBase* imageButton = Create(name, isEnabled, "MinusButton.png", defaultToolTip, column, row, columnSpan, rowSpan);
    //     //imageButton.BrushGroup = "TextButton";
    //     return imageButton;
    // }

    // static ToggleButtonBase* CreateCopyButton(const std::string& name, const std::string& defaultToolTip = std::string(), int column = 0, int row = 0, int columnSpan = 1, int rowSpan = 1)
    // {
    //     ToggleButtonBase* imageButton = Create(name, true, "CopyButton.png", defaultToolTip, column, row, columnSpan, rowSpan);
    //     //imageButton.BrushGroup = "TextButton";
    //     return imageButton;
    // }

    // static ToggleButtonBase* CreatePasteButton(const std::string& name, const std::string& defaultToolTip = std::string(), int column = 0, int row = 0, int columnSpan = 1, int rowSpan = 1)
    // {
    //     ToggleButtonBase* imageButton = Create(name, true, "PasteButton.png", defaultToolTip, column, row, columnSpan, rowSpan);
    //     //imageButton.BrushGroup = "TextButton";
    //     return imageButton;
    // }

    // static ToggleButtonBase* CreateResetButton(const std::string& name, const std::string& defaultToolTip = std::string(), int column = 0, int row = 0, int columnSpan = 1, int rowSpan = 1)
    // {
    //     ToggleButtonBase* imageButton = Create(name, true, "ResetButton.png", defaultToolTip, column, row, columnSpan, rowSpan);
    //     //imageButton.BrushGroup = "TextButton";
    //     return imageButton;
    // }

    // static ToggleButtonBase* CreateLinkButton(const std::string& name, const std::string& defaultToolTip = std::string(), int column = 0, int row = 0, int columnSpan = 1, int rowSpan = 1)
    // {
    //     ToggleButtonBase* imageButton = Create(name, true, "LinkButton.png", defaultToolTip, column, row, columnSpan, rowSpan);
    //     //imageButton.BrushGroup = "TextButton";
    //     return imageButton;
    // }
}
