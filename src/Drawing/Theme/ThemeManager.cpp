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
    std::vector<Theme *> &ThemeManager::Themes = GetThemesVector();

    std::vector<std::string> &ThemeManager::ThemeNames = GetThemeNamesVector();

    std::vector<std::string> &ThemeManager::VisualStateNames = GetVisualStateNamesVector();

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

    // Use Meyer's singleton pattern to avoid static destruction order issues
    std::vector<Theme *> &ThemeManager::GetThemesVector()
    {
        static std::vector<Theme *> themes;
        return themes;
    }

    std::vector<std::string> &ThemeManager::GetThemeNamesVector()
    {
        static std::vector<std::string> themeNames;
        return themeNames;
    }

    std::vector<std::string> &ThemeManager::GetVisualStateNamesVector()
    {
        static std::vector<std::string> visualStateNames;
        return visualStateNames;
    }

    void ThemeManager::AddSorted(Theme *theme)
    {
        bool found = false;

        for (size_t i = 0; i < GetThemesVector().size(); i++)
        {
            Theme &existing = *GetThemesVector()[i];

            if (existing.GetName().compare(theme->GetName()) > 0)
            {
                auto it = GetThemesVector().begin();
                std::advance(it, i);
                GetThemesVector().insert(it, theme);

                auto it2 = GetThemeNamesVector().begin();
                std::advance(it2, i);
                GetThemeNamesVector().insert(it2, theme->GetName());
                found = true;
                break;
            }
        }
        if (!found)
        {
            GetThemesVector().push_back(theme);
            GetThemeNamesVector().push_back(theme->GetName());
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

            for (Theme *availableTheme : GetThemesVector())
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
            if (std::find(GetThemesVector().begin(), GetThemesVector().end(), &defaultTheme) == GetThemesVector().end())
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
                auto it = std::find_if(GetThemesVector().begin(), GetThemesVector().end(),
                                       [&name](Theme *theme)
                                       { return theme->GetName() == name; });

                if (it != GetThemesVector().end())
                {
                    // call SetActive because it also saves the active theme if it has changes
                    SetActive(*it);

                    found = true;

                    Logger::Log(LogLevel::Info, "ThemeManager.SetActive", "Changed theme to %s", name);
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

    void ThemeManager::Cleanup()
    {
        std::lock_guard<std::mutex> lock(themesMutex);

        // Clear events to prevent further notifications
        ThemeChanged.Clear();
        Initialized.Clear();

        // Clear all themes except the default theme (which will be handled by its destructor)
        for (Theme *theme : GetThemesVector())
        {
            if (theme != &defaultTheme)
            {
                delete theme;
            }
        }
        GetThemesVector().clear();
        GetThemeNamesVector().clear();
        GetVisualStateNamesVector().clear();

        // Reset state
        activeTheme = nullptr;
        isInitialized = false;
        isInitializing = false;
        lastLoadedTheme.clear();
    }
}
