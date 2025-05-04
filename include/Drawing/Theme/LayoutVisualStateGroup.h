#pragma once

#include <map>
#include <IO/IO.h>
#include <Drawing/Theme/VisualStateGroup.h>
#include <Drawing/Theme/LayoutVisualState.h>

namespace xit::Drawing
{
    class LayoutVisualStateGroup : public VisualStateGroup<LayoutVisualState>
    {
    private:
        static std::map<std::string, LayoutVisualStateGroup *> loadedGroups;

        LayoutVisualStateGroup();

    public:
        LayoutVisualStateGroup(const std::string &name);
        LayoutVisualStateGroup(LayoutVisualStateGroup &other);
        LayoutVisualStateGroup(const LayoutVisualStateGroup &other);

    public:
        static LayoutVisualStateGroup *Load(std::string path, std::string name);
    };
}
