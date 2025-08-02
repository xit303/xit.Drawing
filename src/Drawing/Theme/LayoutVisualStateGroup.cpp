#include <Drawing/Theme/LayoutVisualStateGroup.h>

namespace xit::Drawing
{
    std::map<std::string, LayoutVisualStateGroup *> &LayoutVisualStateGroup::GetLoadedGroupsMap()
    {
        static std::map<std::string, LayoutVisualStateGroup *> loadedGroups;
        return loadedGroups;
    }

    LayoutVisualStateGroup::LayoutVisualStateGroup() {}
    LayoutVisualStateGroup::LayoutVisualStateGroup(const std::string &name) : VisualStateGroup(name) {}
    LayoutVisualStateGroup::LayoutVisualStateGroup(LayoutVisualStateGroup &other) : VisualStateGroup(other)
    {
        for (LayoutVisualState *state : other.visualStates)
        {
            AddState(new LayoutVisualState(*state));
        }
    }

    LayoutVisualStateGroup::LayoutVisualStateGroup(const LayoutVisualStateGroup &other) : VisualStateGroup(other)
    {
        for (LayoutVisualState *state : other.visualStates)
        {
            AddState(new LayoutVisualState(*state));
        }
    }

    LayoutVisualStateGroup *LayoutVisualStateGroup::Load(const std::string &path, const std::string &name)
    {
        std::string fileName = path + "/" + name + ".json";

        if (GetLoadedGroupsMap().contains(fileName))
            return GetLoadedGroupsMap()[fileName];

        LayoutVisualStateGroup *data = GetLoadedGroupsMap()[fileName]; // XmlFile<LayoutVisualStateGroup>::Load(xmlFileName);

        // if (data != nullptr)
        // {
        //     data->SetName(name);
        //     // data->IsSerialized = true;

        //     /*foreach (BrushSettingsGroup visualState in data.Values)
        //     {
        //         visualState.IsSerialized = true;
        //     }*/

        //     Logger::Log(LogLevel::Info, "LayoutVisualStateGroup", "Loaded LayoutVisualStateGroup %s from %s", name, path);
        // }
        // else
        // {
        //     data = new LayoutVisualStateGroup(name);
        //     Logger::Log(LogLevel::Info, "LayoutVisualStateGroup", "LayoutVisualStateGroup %s did not exist and has been created", name);
        // }

        // data->SetFileName(xmlFileName);

        return data;
    }
}
