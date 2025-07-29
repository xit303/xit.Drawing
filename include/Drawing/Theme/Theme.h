#pragma once

#include <Properties/NameProperty.h>
#include <Drawing/Theme/BrushVisualStateGroup.h>
#include <Drawing/Theme/LayoutVisualStateGroup.h>

namespace xit::Drawing
{
    class Theme : public Properties::NameProperty
    {
    protected:
        std::vector<BrushVisualStateGroup*> brushVisualStateGroups;
        std::vector<LayoutVisualStateGroup*> layoutVisualStateGroups;

    public:
        std::vector<BrushVisualStateGroup*> &GetBrushVisualStateGroups() { return brushVisualStateGroups; }
        std::vector<LayoutVisualStateGroup*> &GetLayoutVisualStateGroups() { return layoutVisualStateGroups; }

        Theme(const std::string &name);
        Theme(Theme &other);
        //Theme(const Theme &other);
        ~Theme();

        // Theme* Clone();

        void AddLayoutVisualStateGroup(LayoutVisualStateGroup *value);

        BrushVisualStateGroup *GetBrushVisualStateGroup(const std::string &name);
        LayoutVisualStateGroup *GetLayoutVisualStateGroup(const std::string &name);

        void Save(const std::string &path);

        static void CopyThemeData(const std::string &themeName, std::vector<BrushVisualStateGroup*> &destination, std::vector<BrushVisualStateGroup*> &loadedVisualStateGroups, bool isSystemDirectory);
        static void CopyThemeData(const std::string &themeName, std::vector<LayoutVisualStateGroup*> &destination, std::vector<LayoutVisualStateGroup*> &loadedVisualStateGroups, bool isSystemDirectory);

    private:
        static void Load(std::list<std::string> &files, const std::string &directory, std::vector<BrushVisualStateGroup*> &destination, bool isSystemDirectory);
        static void Load(std::list<std::string> &files, const std::string &directory, std::vector<LayoutVisualStateGroup*> &destination, bool isSystemDirectory);

    public:
        static Theme *FromDirectory(const std::string &directory, bool isSystemDirectory);
    };
}
