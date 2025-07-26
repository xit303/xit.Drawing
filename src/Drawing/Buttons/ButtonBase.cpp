#include <Drawing/Buttons/ButtonBase.h>
#include <StringHelper.h>

namespace xit::Drawing
{
    //******************************************************************************
    // Properties
    //******************************************************************************

    void ButtonBase::SetShowImage(bool value)
    {
        if (showImage != value)
        {
            showImage = value;
            OnShowImageChanged();
        }
    }

    void ButtonBase::SetImageSource(const std::string &value)
    {
        UniformImageSizeChanged();
        image.SetImageSource(value);
        
        OnShowImageChanged();
    }

    void ButtonBase::SetUniformImageSize(int value)
    {
        if (uniformImageSize != value)
        {
            uniformImageSize = value;
            UniformImageSizeChanged();
        }
    }

    //******************************************************************************
    // Constructor
    //******************************************************************************

    ButtonBase::ButtonBase()
    {
        SetName("ButtonBase");
        
        SetHandleMouse(true);
        SetHandleKeyboard(true);
        SetCanDeactivate(true);
        SetCanFocus(true);
        SetUseOrientation(true);
        SetClipToBounds(true);

        GetLabel().SetInheritForeground(true);
        AddChild(&GetLabel());

        image.SetInheritForeground(true);
        image.SetIsVisible(false);
        AddChild(&image);

        SetFontName(UIDefaults::ButtonFont);

        showImage = false;

        UpdateSpacing();
        EventArgs e;
        OnOrientationChanged(e);
    }

    //******************************************************************************
    // Private
    //******************************************************************************

    void ButtonBase::UpdateSpacing()
    {
        if (GetShowLabel() && showImage)
        {
            SetColumnSpacing(UIDefaults::ButtonSpacing);
            SetRowSpacing(UIDefaults::ButtonRowSpacing);
        }
        else
        {
            SetColumnSpacing(0);
            SetRowSpacing(0);
        }
    }
    void ButtonBase::UniformImageSizeChanged()
    {
        // if (!image.Empty())
        {
            image.SetWidth(uniformImageSize != 0 ? uniformImageSize : -1);
            image.SetHeight(uniformImageSize != 0 ? uniformImageSize : -1);
        }
        OnUniformImageSizeChanged();
    }

    //******************************************************************************
    // Protected overrides
    //******************************************************************************

    void ButtonBase::OnChildAdded(Visual &content, EventArgs &e)
    {
        Container::OnChildAdded(content, e);

        UniformImageSizeChanged();
    }
    void ButtonBase::OnUpdateLayout(LayoutVisualState *value)
    {
        Container::OnUpdateLayout(value);
        if (value)
            SetFontSize(value->GetFontSize());
    }

    void ButtonBase::OnOrientationChanged(EventArgs &e)
    {
        if (!GetUseOrientation())
            return;

        const bool isNormal = (GetOrientationDirection() == OrientationDirection::Normal);
        const bool hasImageAndLabel = (showImage && GetShowLabel());

        if (GetOrientation() == Orientation::Horizontal)
        {
            // only set rows to columns if they are swapped
            if (GetRows() == "*")
            {
                return;
            }

            SetRows("*");

            // this is not good
            if (hasImageAndLabel)
            {
                std::string currentRows = GetRows();
                std::string newColumns;

                if (isNormal)
                {
                    newColumns = currentRows;
                }
                else
                {
                    // invert currentRows
                    std::vector<std::string> rows = StringHelper::Split(currentRows, ',');

                    size_t rowsCount = rows.size();
                    for (size_t i = 0; i < rowsCount; i++)
                    {
                        if (i > 0)
                            newColumns += ",";
                        newColumns += rows[rowsCount - 1 - i];
                    }
                }

                SetColumns(newColumns);
                image.SetGrid(isNormal ? 0 : 1, 0);
                GetLabel().SetGrid(isNormal ? 1 : 0, 0);

                int index = 0;
                // iterate over all children and set the grid for them
                for (Visual *child : GetChildren())
                {
                    child->SetGrid(index++, 0);
                }
            }
            else
            {
                SetColumns("*");
                image.SetGrid(0, 0);
                GetLabel().SetGrid(0, 0);
            }
        }
        else
        {
            if (GetColumns() == "*")
            {
                return;
            }

            SetColumns("*");

            if (hasImageAndLabel)
            {
                std::string currentColumns = GetColumns();
                std::string newRows;

                if (isNormal)
                {
                    newRows = currentColumns;
                }
                else
                {
                    // invert currentColumns
                    std::vector<std::string> rows = StringHelper::Split(currentColumns, ',');

                    size_t rowsCount = rows.size();
                    for (size_t i = 0; i < rowsCount; i++)
                    {
                        if (i > 0)
                            newRows += ",";
                        newRows += rows[rowsCount - 1 - i];
                    }
                }

                SetColumns(newRows);

                image.SetGrid(0, isNormal ? 0 : 1);
                GetLabel().SetGrid(0, isNormal ? 1 : 0);

                int index = 0;
                // iterate over all children and set the grid for them
                for (Visual *child : GetChildren())
                {
                    child->SetGrid(0, index++);
                }
            }
            else
            {
                image.SetGrid(0, 0);
                GetLabel().SetGrid(0, 0);
            }
        }
    }

    void ButtonBase::OnHorizontalContentAlignmentChanged(EventArgs &e)
    {
        Container::OnHorizontalContentAlignmentChanged(e);
        GetLabel().SetHorizontalAlignment(GetHorizontalContentAlignment());
        image.SetHorizontalAlignment(GetHorizontalContentAlignment());
    }
    void ButtonBase::OnVerticalContentAlignmentChanged(EventArgs &e)
    {
        Container::OnVerticalContentAlignmentChanged(e);
        GetLabel().SetVerticalAlignment(GetVerticalContentAlignment());
        image.SetVerticalAlignment(GetVerticalContentAlignment());
    }

    void ButtonBase::OnVisibilityChanged(EventArgs &e)
    {
        Container::OnVisibilityChanged(e);

        OnShowLabelChanged();
        OnShowImageChanged();
    }

#ifdef DEBUG
    int ButtonBase::OnMeasureWidth(int available)
    {
        return Container::OnMeasureWidth(available);
    }
    int ButtonBase::OnMeasureHeight(int available)
    {
        return Container::OnMeasureHeight(available);
    }
    void ButtonBase::OnRender()
    {
        Container::OnRender();
    }
#endif

    //******************************************************************************
    // Protected
    //******************************************************************************

    void ButtonBase::OnShowLabelChanged()
    {
        LabelProperty::OnShowLabelChanged();
        UpdateSpacing();

        EventArgs e;
        OnOrientationChanged(e);
    }
    void ButtonBase::OnShowImageChanged()
    {
        image.SetVisibility(showImage ? Visibility::Visible : Visibility::Collapsed);
        UpdateSpacing();

        EventArgs e;
        OnOrientationChanged(e);
    }

    void ButtonBase::OnUniformImageSizeChanged() {}

    //******************************************************************************
    // Public
    //******************************************************************************
#ifdef DEBUG
    Size ButtonBase::Measure(const Size &availableSize)
    {
        return Container::Measure(availableSize);
    }
#endif
}
