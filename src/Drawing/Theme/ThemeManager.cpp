#include <Drawing/Theme/ThemeManager.h>
// #include <Drawing/Brushes/Brushes.h>

namespace xit::Drawing
{
    const std::string ThemeManager::defaultText = "Default";
    std::string ThemeManager::systemThemesPath;
    std::string ThemeManager::userThemesPath;

    bool ThemeManager::isInitialized = false;
    bool ThemeManager::isInitializing = false;

    Theme *ThemeManager::activeTheme = nullptr;
    // const Theme& ThemeManager::Active = ThemeManager::activeTheme;

    Theme ThemeManager::defaultTheme = Theme(defaultText);
    Theme &ThemeManager::Default = ThemeManager::defaultTheme;

    std::mutex ThemeManager::themesMutex;
    std::vector<Theme *> ThemeManager::themes;
    std::vector<Theme *> &ThemeManager::Themes = themes;

    std::vector<std::string> ThemeManager::themeNames;
    std::vector<std::string> &ThemeManager::ThemeNames = themeNames;

    std::vector<std::string> ThemeManager::visualStateNames;
    std::vector<std::string> &ThemeManager::VisualStateNames = visualStateNames;

    std::string ThemeManager::lastLoadedTheme;

    const int ThemeManager::VisualStatesCount = 8;
    const std::string ThemeManager::VisualStates[] =
        {
            "Disabled",
            "Normal",
            "Hovered",
            "Pressed",
            "Focused",
            "Active",
            "ActiveHovered",
            "MidiLearn",
    };

    bool &ThemeManager::IsInitialized = ThemeManager::isInitialized;

    Event<EventArgs &> ThemeManager::ThemeChanged;
    Event<EventArgs &> ThemeManager::Initialized;

    void ThemeManager::AddSorted(Theme *theme)
    {
        bool found = false;

        for (size_t i = 0; i < themes.size(); i++)
        {
            Theme &existing = *themes[i];

            if (existing.GetName().compare(theme->GetName()) > 0)
            {
                auto it = themes.begin();
                std::advance(it, i);
                themes.insert(it, theme);

                auto it2 = themeNames.begin();
                std::advance(it2, i);
                themeNames.insert(it2, theme->GetName());
                found = true;
                break;
            }
        }
        if (!found)
        {
            themes.push_back(theme);
            themeNames.push_back(theme->GetName());
        }
    }

    void ThemeManager::LoadTheme(const std::string &directory, bool isSystemDirectory)
    {
        Theme *theme = Theme::FromDirectory(directory, isSystemDirectory);

        std::lock_guard<std::mutex> lock(themesMutex);
        {
            // empty directory
            if (theme == nullptr)
            {
                if (!isSystemDirectory)
                {
                    theme = new Theme(Default);
                    // TODO theme->SetDefaultName(Path::GetFileName(directory));

                    AddSorted(theme);
                }
                return;
            }

            for (Theme *availableTheme : themes)
            {
                if (availableTheme->GetName() == theme->GetName())
                {
                    Theme::CopyThemeData(theme->GetName(), availableTheme->GetBrushVisualStateGroups(), theme->GetBrushVisualStateGroups(), isSystemDirectory);
                    // Theme::CopyThemeData(theme->SetName(), availableTheme.LayoutVisualStateGroups, theme->LayoutVisualStateGroups, isSystemDirectory);
                    return;
                }
            }

            // to be sure that we will have all basic theme data in the new theme we copy them first
            Theme *newTheme = new Theme(Default);
            // TODO newTheme->SetDefaultName(Path::GetFileName(directory));
            // TODO newTheme->SetName(newTheme->GetDefaultName());

            // after this we overwrite data with the loaded values
            Theme::CopyThemeData(newTheme->GetName(), newTheme->GetBrushVisualStateGroups(), theme->GetBrushVisualStateGroups(), isSystemDirectory);
            // Theme::CopyThemeData(newTheme->SetName(), newTheme->LayoutVisualStateGroups, theme->LayoutVisualStateGroups, isSystemDirectory);

            AddSorted(newTheme);
            // AddSorted(theme);
        }
    }

    void ThemeManager::InitializeDefault()
    {
        int sleepCounter = 0;
        while (isInitializing)
        {
            // xit::Threading::Thread::Sleep(10);
            if (++sleepCounter > 20)
            {
                throw InvalidOperationException("ThemeManager is trying to InitializeDefault while initializing. Timed out. Same process?");
            }
        }

        isInitializing = true;

        if (isInitialized)
        {
            return;
        }

        systemThemesPath = App::XITPath() + "/Themes/System/";
        userThemesPath = App::XITPath() + "/Themes/User/";
        std::string lastTheme = App::Settings().GetLastTheme();

        InitializeDefaultBrushes();
        InitializeDefaultLayout();

        lastLoadedTheme = lastTheme;

        Logger::Log(LogLevel::Info, "ThemeManager.Init", "Initialized");

        themesMutex.lock();
        {
            if (std::find(themes.begin(), themes.end(), &defaultTheme) == themes.end())
            {
                AddSorted(&defaultTheme);
            }
        }
        themesMutex.unlock();

        if (!lastTheme.empty())
        {
            std::list<std::string> directories;

            bool found = false;

            if (Directory::Exists(systemThemesPath))
            {
                directories = Directory::GetDirectories(systemThemesPath);

                for (std::string directory : directories)
                {
                    if (Path::GetFileName(directory) == lastTheme)
                    {
                        LoadTheme(directory, true);
                        found = true;
                        break;
                    }
                }
            }

            if (Directory::Exists(userThemesPath))
            {
                directories = Directory::GetDirectories(userThemesPath);

                for (std::string directory : directories)
                {
                    if (Path::GetFileName(directory) == lastTheme)
                    {
                        LoadTheme(directory, false);
                        found = true;
                        break;
                    }
                }
            }

            if (found)
            {
                SetActive(lastTheme);
            }
            else
            {
                SetActive(&defaultTheme);
            }
        }
        else
        {
            lastLoadedTheme = Default.GetName();

            if (Directory::Exists(userThemesPath))
            {
                std::list<std::string> directories = Directory::GetDirectories(userThemesPath);

                for (std::string directory : directories)
                {
                    if (Path::GetFileName(directory) == Default.GetName())
                    {
                        LoadTheme(directory, false);
                        break;
                    }
                }
            }

            activeTheme = &defaultTheme;
        }

        // TODO these do not work anymore
        // App::AddParallelInitializationAction([]() -> void
        // {
        //     LoadAll(systemThemesPath, true);
        // });
        // App::AddParallelInitializationAction([]() -> void
        // {
        //     LoadAll(userThemesPath, false);
        //     EventArgs args;
        //     Initialized(args);
        // });

        isInitialized = true;
        isInitializing = false;
    }

    void ThemeManager::SetActive(const std::string &name)
    {
        if (activeTheme == nullptr || (!name.empty() && (name != activeTheme->GetName())))
        {
            bool found = false;

            themesMutex.lock();
            {
                for (Theme *theme : themes)
                {
                    if (theme->GetName() == name)
                    {
                        // call SetActive because it also saves the active theme if it has changes
                        SetActive(theme);

                        found = true;

                        Logger::Log(LogLevel::Info, "ThemeManager.SetActive", "Changed theme to %s", name);
                        break;
                    }
                }
            }
            themesMutex.unlock();

            if (!found)
            {
                Logger::Log(LogLevel::Error, "ThemeManager.SetActive", "Theme with name [%s] not found. Abort theme change.", name);
            }
        }
    }
    void ThemeManager::SetActive(Theme *theme)
    {
        if (theme != activeTheme)
        {
            Theme *lastActiveTheme = activeTheme;

            try
            {
                activeTheme = theme;
                EventArgs args;
                ThemeChanged(args);
            }
            catch (Exception &ex)
            {
                Logger::Log(LogLevel::Error, "ThemeManager", "Could not load Theme:\n%s", ex.Message);

                // revert and make sure we dont do something stupid
                activeTheme = lastActiveTheme ? lastActiveTheme : &defaultTheme;

                try
                {
                    EventArgs args;
                    ThemeChanged(args);
                }
                catch (Exception &ex1)
                {
                    Logger::Log("ThemeManager", ex1);
                }
            }

            App::Settings().SetLastTheme(activeTheme->GetName());

            if (activeTheme != lastActiveTheme)
            {
                // store after changing to not disturb UI update
                if (lastActiveTheme)
                    lastActiveTheme->Save(userThemesPath);
            }
        }
    }

    void ThemeManager::LoadAll(const std::string &path, bool isSystemDirectory)
    {
        // TODO this can take really long if we have a lot of files
        // therefore we should only load themes which are in the list close to the selected one
        // and only if the theme window is opened

        // another option would be to create one big file but this involves
        // total damage of a file if something is wrong in just one component

        if (Directory::Exists(path))
        {
            std::list<std::string> directories = Directory::GetDirectories(path);

            // load data from disk
            for (std::string directory : directories)
            {
                try
                {
                    if (Path::GetFileName(directory) != lastLoadedTheme)
                    {
                        LoadTheme(directory, isSystemDirectory);
                    }
                }
                catch (Exception &ex)
                {
                    Logger::Log(LogLevel::Error, "ThemeManager", ex.Message);
                    // MessageBox.Show(ex.Message);
                }
            }
        }
    }

    void ThemeManager::Save()
    {
        if (activeTheme)
            activeTheme->Save(userThemesPath);
    }
}
