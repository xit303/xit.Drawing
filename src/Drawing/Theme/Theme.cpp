#include <Drawing/Theme/Theme.h>
#include <Drawing/Theme/ThemeManager.h>

namespace xit::Drawing
{
    Theme::Theme(const std::string &name)
        : NameProperty(name)
    {
    }

    Theme::Theme(Theme &other)
        : NameProperty(other)
    {
        for (BrushVisualStateGroup *fromOther : other.brushVisualStateGroups)
        {
            brushVisualStateGroups.push_back(fromOther);
        }
        for (LayoutVisualStateGroup *fromOther : other.layoutVisualStateGroups)
        {
            layoutVisualStateGroups.push_back(fromOther);
        }
    }

    // Theme::Theme(const Theme &other)
    //     : NameProperty(other)
    // {
    //     for (const BrushVisualStateGroup *fromOther : other.brushVisualStateGroups)
    //     {
    //         brushVisualStateGroups.push_back(fromOther);
    //     }
    //     // for (LayoutVisualStateGroup& fromOther : other.layoutVisualStateGroups.Values)
    //     // {
    //     //     layoutVisualStateGroups.push_back(fromOther);
    //     // }
    // }

    void Theme::AddLayoutVisualStateGroup(LayoutVisualStateGroup *value)
    {
        layoutVisualStateGroups.push_back(value);
    }

    BrushVisualStateGroup *Theme::GetBrushVisualStateGroup(const std::string &name)
    {
        for (BrushVisualStateGroup *group : brushVisualStateGroups)
        {
            if (group->GetName() == name)
                return group;
        }
        return nullptr;
    }

    LayoutVisualStateGroup *Theme::GetLayoutVisualStateGroup(const std::string &name)
    {
        for (LayoutVisualStateGroup *group : layoutVisualStateGroups)
        {
            if (group->GetName() == name)
                return group;
        }
        return nullptr;
    }

    // Theme* Theme::Clone()
    //{
    //     Theme* newTheme = new Theme(GetName());

    //    try
    //    {
    //        for (int i = 0; i < brushVisualStateGroups.Values.Count; i++)
    //        {
    //            BrushVisualStateGroup* visualStates = brushVisualStateGroups.Values[i];
    //            BrushVisualStateGroup* newValues = new BrushVisualStateGroup(visualStates.GetName());

    //            for (int j = 0; j < visualStates.Values.Count; j++)
    //            {
    //                BrushVisualState* visualState = visualStates.Values[j];

    //                newValues->Add(visualState);
    //            }

    //            newTheme->BrushVisualStateGroups.Add(newValues);
    //        }
    //    }
    //    catch (Exception ex)
    //    {
    //        Logger::Log("Theme", &ex);
    //    }

    //    try
    //    {
    //        for (int i = 0; i < layoutVisualStateGroups.Values.Count; i++)
    //        {
    //            LayoutVisualStateGroup* visualStates = layoutVisualStateGroups.Values[i];

    //            LayoutVisualStateGroup* values = new LayoutVisualStateGroup(visualStates.GetName());

    //            for (int j = 0; j < visualStates.Values.Count; j++)
    //            {
    //                LayoutVisualState* visualState = visualStates.Values[j];

    //                values->Add(visualState);
    //            }

    //            newTheme->LayoutVisualStateGroups.Add(values);
    //        }

    //        return newTheme;
    //    }
    //    catch (Exception ex)
    //    {
    //        Logger::Log("Theme", &ex);
    //    }

    //    return nullptr;
    //}

    void Theme::Save(const std::string &path)
    {
        for (BrushVisualStateGroup *visualStates : brushVisualStateGroups)
        {
            std::string p1 = path + GetName() + "/Brushes/" + visualStates->GetName() + ".json";
            // visualStates.SetFileName(p1);
        }

        for (LayoutVisualStateGroup *visualStates : layoutVisualStateGroups)
        {
            std::string p1 = path + GetName() + "/Layout/" + visualStates->GetName() + ".json";
            // visualStates->SetFileName(p1);
            //visualStates->Save();
        }
    }

    void Theme::CopyThemeData(const std::string &themeName, std::vector<BrushVisualStateGroup *> &destination, std::vector<BrushVisualStateGroup *> &loadedVisualStateGroups, bool isSystemDirectory)
    {
        for (BrushVisualStateGroup *loadedStates : loadedVisualStateGroups)
        {
            bool found = false;
            for (BrushVisualStateGroup *destinationState : destination)
            {
                if (loadedStates->GetName() == destinationState->GetName())
                {
                    // state already exists, so override values
                    found = true;

                    // for (const BrushVisualState &loadedState : loadedStates)
                    // {
                    //     //const BrushVisualStateGroup &destinationStates = destination[loadedStates.GetName()];

                    //     if (!destinationStates.contains(loadedState.GetName()))
                    //     {
                    //         // update the whole state is not allowed right now
                    //         // Note: this is only possible to get here if the user has created own states!
                    //         // destinationStates.AddChild(loadedState);

                    //         Logger::Log(LogLevel::Error, "CopyThemeData", "Theme %s Unknown visual state [%s] has been loaded in visual state group [%s]", themeName, loadedState.GetName(), loadedStates.GetName());
                    //     }
                    //     else
                    //     {
                    //         BrushVisualState &current = destinationStates[loadedState.GetName()];

                    //         if (isSystemDirectory)
                    //         {

                    //             // files from system directory will set DEFAULT values
                    //             if (!loadedState.Background.GetValue().Empty())
                    //                 current.Background.SetDefaultValue(loadedState.Background.GetValue());
                    //             if (!loadedState.Foreground.GetValue().Empty())
                    //                 current.Foreground.SetDefaultValue(loadedState.Foreground.GetValue());
                    //             if (!loadedState.BorderBrush.GetValue().Empty())
                    //                 current.BorderBrush.SetDefaultValue(loadedState.BorderBrush.GetValue());
                    //         }
                    //         else
                    //         {
                    //             // files from user directories will set LOADED values
                    //             // destinationStates->operator[](loadedState.GetName())->SetLoadedValues(loadedState);

                    //             if (!loadedState.Background.GetValue().Empty())
                    //                 current.Background.SetLoadedValue(loadedState.Background.GetValue());
                    //             if (!loadedState.Foreground.GetValue().Empty())
                    //                 current.Foreground.SetLoadedValue(loadedState.Foreground.GetValue());
                    //             if (!loadedState.BorderBrush.GetValue().Empty())
                    //                 current.BorderBrush.SetLoadedValue(loadedState.BorderBrush.GetValue());
                    //         }
                    //     }
                    // }
                    break;
                }
            }

            if (!found)
            {
                // add the whole groups
                // Note: this is only possible to get here if the user has created own groups!

                // TODO basically we have to do the same as above because of isSystemDirectory
                // and because of Setting can be SettingsGroup (SetLoadedValues / SetDefaultValues)

                destination.push_back(loadedStates);
            }
        }
    }
    void Theme::CopyThemeData(const std::string &themeName, std::vector<LayoutVisualStateGroup *> &destination, std::vector<LayoutVisualStateGroup *> &loadedVisualStateGroups, bool isSystemDirectory)
    {
        // for (LayoutVisualStateGroup *loadedStates : loadedVisualStateGroups)
        // {
        //     if (destination.Contains(loadedStates.GetName()))
        //     {
        //         for (LayoutVisualState *loadedState : loadedStates.Values)
        //         {
        //             LayoutVisualStateGroup &destinationStates = destination[loadedStates.GetName()];

        //             if (!destinationStates.Contains(loadedState.GetName()))
        //             {
        //                 // update the whole state is not allowed right now
        //                 // Note: this is only possible to get here if the user has created own states!
        //                 // destinationStates.AddChild(loadedState);

        //                 Logger::Log(LogLevel::Error, "Theme.CopyThemeData", "Theme %s Unknown visual state [&s] has been loaded in visual state group [%s]", themeName, loadedState.GetName(), loadedStates.GetName());
        //             }
        //             else
        //             {
        //                 if (isSystemDirectory)
        //                 {
        //                     // files from system directory will set DEFAULT values
        //                     destinationStates[loadedState.GetName()].SetDefaultValues(loadedState);
        //                 }
        //                 else
        //                 {
        //                     // files from user directories will set LOADED values
        //                     destinationStates[loadedState.GetName()].SetLoadedValues(loadedState);
        //                 }
        //             }
        //         }
        //     }
        //     else
        //     {
        //         // add the whole groups
        //         // Note: this is only possible to get here if the user has created own groups!

        //         // TODO basically we have to do the same as above because of isSystemDirectory
        //         // and because of Setting can be SettingsGroup (SetLoadedValues / SetDefaultValues)

        //         destination.AddChild(loadedStates);
        //     }
        // }
    }

    void Theme::Load(std::list<std::string> &files, const std::string &directory, std::vector<BrushVisualStateGroup *> &destination, bool isSystemDirectory)
    {
        if (!files.empty())
        {
            // Parallel.ForEach(files, (file) =>
            for (std::string file : files)
            {
                BrushVisualStateGroup *visualStates = BrushVisualStateGroup::Load(directory, Path::GetFileNameWithoutExtension(file), isSystemDirectory);

                if (visualStates->Size() > 0)
                {
                    // for (int i = 0; i < visualStates.Values.Count; i++)
                    //{
                    //     BrushVisualState* visualState = visualStates.Values[i];
                    //     if (isSystemDirectory)
                    //     {
                    //         visualState.SetDefa
                    //     }
                    // }
                    destination.push_back(visualStates);
                }
                else
                {
                    std::string fileName = Path::GetFileName(file);
                    Logger::Log(LogLevel::Warning, "Theme.FromDirectory", "Could not load VisualStateGroup from file [%s], value is nullptr", fileName);
                }
            }
            //});
        }
    }
    void Theme::Load(std::list<std::string> &files, const std::string &directory, std::vector<LayoutVisualStateGroup *> &destination, bool isSystemDirectory)
    {
        if (!files.empty())
        {
            // Parallel.ForEach(files, (file) =>
            for (std::string file : files)
            {
                LayoutVisualStateGroup *visualStates = LayoutVisualStateGroup::Load(directory, Path::GetFileNameWithoutExtension(file));

                if (visualStates->Size() > 0)
                {
                    // if (isSystemDirectory)
                    // {
                    //     // if loaded from system directory, we have to set default values
                    //     for (LayoutVisualState &visualState : visualStates.Values)
                    //     {
                    //         visualState.SetDefaultValues(visualState);
                    //     }
                    // }
                    // else
                    // {
                    //     // if loaded from user directory we have to set (nothing? because Serialization sets LoadedValue) the loadedValues

                    //     // foreach (BrushGroup visualState in visualStates.Values)
                    //     //{
                    //     //     foreach (BrushBase brushBase in visualState.Values)
                    //     //     {
                    //     //         brushBase.SetLoadedValues(brushBase);
                    //     //     }
                    //     // }
                    // }

                    destination.push_back(visualStates);
                }
                else
                {
                    Logger::Log(LogLevel::Warning, "Theme.FromDirectory", "Could not load VisualStateGroup from file [%s], value is nullptr", Path::GetFileName(file));
                }
            }
            //});
        }
    }

    Theme *Theme::FromDirectory(const std::string &directory, bool isSystemDirectory)
    {
        std::string brushDirectory = directory + "/Brushes/";
        std::string layoutDirectory = directory + "/Layout/";

        std::list<std::string> brushFiles = Directory::Exists(brushDirectory) ? Directory::EnumerateFiles(brushDirectory, "*.json") : std::list<std::string>();
        std::list<std::string> layoutFiles = Directory::Exists(layoutDirectory) ? Directory::EnumerateFiles(layoutDirectory, "*.json") : std::list<std::string>();

        // create a copy of default theme
        Theme *theme = new Theme(ThemeManager::Default);

        std::string fileName = Path::GetFileName(directory);

        if ((brushFiles.size() > 0) ||
            (layoutFiles.size() > 0))
        {
            theme = new Theme(fileName);
            // theme->SetDefaultName(fileName);

            Load(brushFiles, brushDirectory, theme->GetBrushVisualStateGroups(), isSystemDirectory);
            Load(layoutFiles, layoutDirectory, theme->GetLayoutVisualStateGroups(), isSystemDirectory);
        }
        return theme;
    }
}
