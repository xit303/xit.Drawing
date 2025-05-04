#pragma once

#include <Application/App.h>
#include <Drawing/Theme/Theme.h>
// #include "../Collections/ObservableCollection.h"
#include <Drawing/Brushes/SolidColorBrush.h>
// #include <Drawing/Brushes/LinearGradientBrush.h>
// #include <Drawing/Brushes/ImageBrush.h>

namespace xit::Drawing
{
    class ThemeManager
    {
    private:
        static const std::string defaultText;
        static std::string systemThemesPath;
        static std::string userThemesPath;

        static bool isInitialized;
        static bool isInitializing;

        static Theme *activeTheme;
        static Theme defaultTheme;

        static std::mutex themesMutex;
        static std::vector<Theme *> themes;
        static std::vector<std::string> themeNames;
        static std::vector<std::string> visualStateNames;

        static std::string lastLoadedTheme;

        static void AddSorted(Theme *theme);
        static void LoadTheme(const std::string &directory, bool isSystemDirectory);

    public:
        static const int VisualStatesCount;
        static const std::string VisualStates[];

        static Theme &Active() { return *activeTheme; }
        static Theme &Default;

        static std::vector<Theme *> &Themes;
        static std::vector<std::string> &ThemeNames;
        static std::vector<std::string> &VisualStateNames;

        static std::string SystemThemesPath() { return systemThemesPath; }
        static std::string UserThemesPath() { return userThemesPath; }

        static bool &IsInitialized;

        static Event<EventArgs &> ThemeChanged;
        static Event<EventArgs &> Initialized;

    private:
        static void InitializeDefaultBrushes();

        static LayoutVisualState *CloneLayoutForState(LayoutVisualStateGroup *layoutVisualStateGroup, LayoutVisualState *layoutVisualState, const std::string &newStateName);
        static void CloneLayoutForAllStates(LayoutVisualStateGroup *layoutVisualStateGroup, LayoutVisualState *layoutVisualState);
        static void InitializeDefaultLayout();

    public:
        static void InitializeDefault();

        /// <summary>
        /// Activate a Theme by name.
        /// If theme does not exist, there will be no change.
        /// If an active theme has changes, it will be saved after the new theme has been applied.
        /// </summary>
        /// <param name="name">The name of the Theme to be activated.</param>
        static void SetActive(const std::string &name);

        /// <summary>
        /// Activate a theme by instance.
        /// This method is also called from <see cref="LoadTheme(string, bool)"/>.
        /// If an active theme has changes, it will be saved after the new theme has been applied.
        /// </summary>
        /// <param name="theme"></param>
        static void SetActive(Theme *theme);

        static void LoadAll(const std::string &path, bool isSystemDirectory);

        static void Save();
    };
}
