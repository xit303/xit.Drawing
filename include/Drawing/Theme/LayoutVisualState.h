#pragma once

#include <Drawing/UIDefaults.h>
#include <Drawing/Properties/Sizeable.h>
#include <Drawing/Properties/HorizontalAlignmentProperty.h>
#include <Drawing/Properties/VerticalAlignmentProperty.h>
#include <Drawing/Properties/HorizontalContentAlignmentProperty.h>
#include <Drawing/Properties/VerticalContentAlignmentProperty.h>
#include <Drawing/Properties/MarginProperty.h>
#include <Drawing/Properties/PaddingProperty.h>
#include <Drawing/Properties/BorderThicknessProperty.h>
#include <Drawing/Properties/CornerRadiusProperty.h>
#include <Drawing/Properties/Thickness.h>
#include <Drawing/Properties/CornerRadius.h>
#include <Drawing/Properties/HorizontalAlignment.h>
#include <Drawing/Properties/VerticalAlignment.h>
#include <Properties/NameProperty.h>

namespace xit::Drawing
{
    class LayoutVisualState : public Properties::NameProperty,
                              public Sizeable,
                              public HorizontalAlignmentProperty,
                              public VerticalAlignmentProperty,
                              public HorizontalContentAlignmentProperty,
                              public VerticalContentAlignmentProperty,
                                public MarginProperty,
                                public PaddingProperty,
                                public BorderThicknessProperty,
                                public CornerRadiusProperty
    {
    private:
        int elevation = 0;
        int fontSize = UIDefaults::DefaultFontSize;

    public:
        // static std::string LayoutPropertyNames;

        __always_inline int GetElevation() const { return elevation; }
        void SetElevation(int value) { elevation = value; }

        //******************************************************************************
        // #region FontSize
        //******************************************************************************

        __always_inline int GetFontSize() const { return fontSize; }
        void SetFontSize(int value) { fontSize = value; }

        //******************************************************************************
        // #region Constructors
        //******************************************************************************

        LayoutVisualState()
        {
        }

        LayoutVisualState(const std::string &name)
            : NameProperty(name)
        {
        }

        LayoutVisualState(LayoutVisualState &other)
            : NameProperty(other)
        {
            SetDefaultValues(other);
        }

        LayoutVisualState(const LayoutVisualState &other)
            : NameProperty(other)
        {
            SetDefaultValues((LayoutVisualState &)other);
        }

        LayoutVisualState(const std::string &name, const LayoutVisualState &other)
            : NameProperty(name)
        {
            SetDefaultValues((LayoutVisualState &)other);
        }

        ~LayoutVisualState() = default;

        //******************************************************************************

        //******************************************************************************

        void SetDefaultValues(LayoutVisualState &settingsGroup)
        {
            elevation = settingsGroup.elevation;

            SetWidth(settingsGroup.GetWidth());
            SetMinWidth(settingsGroup.GetMinWidth());
            SetMaxWidth(settingsGroup.GetMaxWidth());

            SetHeight(settingsGroup.GetHeight());
            SetMinHeight(settingsGroup.GetMinHeight());
            SetMaxHeight(settingsGroup.GetMaxHeight());

            SetMargin(settingsGroup.GetMargin());
            SetPadding(settingsGroup.GetPadding());
            SetBorderThickness(settingsGroup.GetBorderThickness());
            SetCornerRadius(settingsGroup.GetCornerRadius());

            SetHorizontalAlignment(settingsGroup.GetHorizontalAlignment());
            SetVerticalAlignment(settingsGroup.GetVerticalAlignment());

            SetHorizontalContentAlignment(settingsGroup.GetHorizontalContentAlignment());
            SetVerticalContentAlignment(settingsGroup.GetVerticalContentAlignment());

            fontSize = settingsGroup.fontSize;
        }

        void SetLoadedValues(LayoutVisualState &settingsGroup)
        {
            // elevation.SetLoadedValue(settingsGroup.elevation.Value());

            // width.SetLoadedValue(settingsGroup.width.Value());
            // minWidth.SetLoadedValue(settingsGroup.minWidth.Value());
            // maxWidth.SetLoadedValue(settingsGroup.maxWidth.Value());

            // height.SetLoadedValue(settingsGroup.height.Value());
            // minHeight.SetLoadedValue(settingsGroup.minHeight.Value());
            // maxHeight.SetLoadedValue(settingsGroup.maxHeight.Value());

            // margin.SetLoadedValue(settingsGroup.margin.Value());
            // padding.SetLoadedValue(settingsGroup.padding.Value());
            // borderThickness.SetLoadedValue(settingsGroup.borderThickness.Value());

            // cornerRadius.SetLoadedValue(settingsGroup.cornerRadius.Value());

            // horizontalAlignment.SetLoadedValue(settingsGroup.horizontalAlignment.Value());
            // verticalAlignment.SetLoadedValue(settingsGroup.verticalAlignment.Value());

            // horizontalContentAlignment.SetLoadedValue(settingsGroup.horizontalContentAlignment.Value());
            // verticalContentAlignment.SetLoadedValue(settingsGroup.verticalContentAlignment.Value());

            // fontSize.SetLoadedValue(settingsGroup.fontSize.Value());
        }

        //******************************************************************************

        //******************************************************************************

        bool Save() // TODO override
        {
            // if (SettingsGroup::Save())
            // {
            //     for (SettingBase& value : Values)
            //     {
            //         if (value.ShouldSerialize())
            //         {
            //             value.Save();
            //         }
            //     }
            //     return true;
            // }

            return false;
        }

        static LayoutVisualState GetSerializationData(LayoutVisualState &source)
        {
            LayoutVisualState changedElements(source.GetName());
            // changedElements.SetLoadedName(source.Name);

            // for (SettingBase& value : source.Values)
            // {
            //     if (value.ShouldSerialize())
            //     {
            //         value.Save();
            //         changedElements.Values.Add(value);
            //     }
            // }

            return changedElements;
        }

        // object Clone()
        //{
        //     LayoutVisualState group = new LayoutVisualState(Name);
        //     group.Clear();

        //    foreach (Setting value in Values)
        //    {
        //        group.Values.Add((Setting)value.Clone());
        //    }

        //    return group;
        //}

        // std::string ToString() override
        //{
        //     return Name + ", Values: " + Values.Count + ", Changed: " + HasChanged + ", Serialize: " + ShouldSerialize;
        // }
    };
}
