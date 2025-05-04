#pragma once

#include <map>
#include <IO/IO.h>
#include <Drawing/Theme/VisualStateGroup.h>
#include <Drawing/Theme/BrushVisualState.h>

namespace xit::Drawing
{
    class BrushVisualStateGroup : public VisualStateGroup<BrushVisualState>
    {
    private:
        static std::map<std::string, BrushVisualStateGroup *> loadedGroups;

        BrushVisualStateGroup();

    public:
        BrushVisualStateGroup(const std::string &name);
        BrushVisualStateGroup(BrushVisualStateGroup &other);
        BrushVisualStateGroup(const BrushVisualStateGroup &other);

    public:
        static BrushVisualStateGroup *Load(const std::string &path, const std::string &name, bool isSystemDirectory);
    };
}
