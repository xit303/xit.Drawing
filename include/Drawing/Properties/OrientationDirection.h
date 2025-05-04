#pragma once

namespace xit::Drawing
{
    /**
     * @brief Defines the different orientation directions that a control or layout can have.
     */
    enum class OrientationDirection
    {
        /**
         * @brief Control or layout should be in the normal orientation.
         */
        Normal,
        /**
         * @brief Control or layout should be in the inverted orientation.
         */
        Inverted
    };
}
using namespace xit::Drawing;
