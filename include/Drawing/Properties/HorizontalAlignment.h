#pragma once

namespace xit::Drawing
{
    /**
     * @enum HorizontalAlignment
     * @brief Indicates where an element should be displayed on the horizontal axis relative to the allocated layout slot of the parent element.
     */
    enum class HorizontalAlignment
    {
        /**
         * @brief An element aligned to the left of the layout slot for the parent element.
         */
        Left,
        /**
         * @brief An element aligned to the center of the layout slot for the parent element.
         */
        Center,
        /**
         * @brief An element aligned to the right of the layout slot for the parent element.
         */
        Right,
        /**
         * @brief An element stretched to fill the entire layout slot of the parent element.
         */
        Stretch
    };
}
using namespace xit::Drawing;
