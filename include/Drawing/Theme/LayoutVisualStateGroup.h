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
        static std::map<std::string, LayoutVisualStateGroup *>& GetLoadedGroupsMap();

        LayoutVisualStateGroup();

    public:
        explicit LayoutVisualStateGroup(const std::string &name);
        LayoutVisualStateGroup(LayoutVisualStateGroup &other);
        LayoutVisualStateGroup(const LayoutVisualStateGroup &other);

    public:
        static LayoutVisualStateGroup *Load(const std::string &path, const std::string &name);
    };
}
