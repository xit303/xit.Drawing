#pragma once

namespace xit::Drawing
{
    /**
     * @brief Specifies the type of border that a Window has. Used by the WindowStyle property.
     */
    enum class WindowStyle
    {
        /**
         * @brief Only the client area is visible - the title bar and border are not shown. A Navigation.NavigationWindow with a .WindowStyle of WindowStyle.None will still display the navigation user interface (UI).
         */
        None,
        /**
         * @brief A window with a single border. This is the default value.
         */
        SingleBorderWindow,
        /**
         * @brief A window with a 3-D border.
         */
        ThreeDBorderWindow,
        /**
         * @brief A fixed tool window.
         */
        ToolWindow
    };
}
