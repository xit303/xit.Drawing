#pragma once

namespace xit::Drawing
{
    /**
     * @brief Describes how a child element is vertically positioned or stretched within a parent's layout slot.
     */
    enum class VerticalAlignment
    {
        /**
         * @brief The child element is aligned to the top of the parent's layout slot.
         */
        Top,
        /**
         * @brief The child element is aligned to the center of the parent's layout slot.
         */
        Center,
        /**
         * @brief The child element is aligned to the bottom of the parent's layout slot.
         */
        Bottom,
        /**
         * @brief The child element stretches to fill the parent's layout slot.
         */
        Stretch
    };
}
using namespace xit::Drawing;
