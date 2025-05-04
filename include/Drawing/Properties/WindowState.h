#pragma once

namespace xit::Drawing
{
    /**
     * @brief Specifies whether a window is minimized, maximized, or restored. Used by the WindowState property.
     */
    enum class WindowState
    {
        /**
         * @brief The window is restored.
         */
        Normal,
        /**
         * @brief The window is minimized.
         */
        Minimized,
        /**
         * @brief The window is maximized.
         */
        Maximized
    };
}
