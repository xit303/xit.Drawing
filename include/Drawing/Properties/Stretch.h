#pragma once

#include <string>

namespace xit::Drawing
{
    /**
     * @brief Describes how content is resized to fill its allocated space.
     */
    enum class Stretch
    {
        /**
         * @brief The content preserves its original size.
         */
        None,
        /**
         * @brief The content is resized to fill the destination dimensions. The aspect ratio is not preserved.
         */
        Fill,
        /**
         * @brief The content is resized to fit in the destination dimensions while it preserves its native aspect ratio.
         */
        Uniform,
        /**
         * @brief The content is resized to fill the destination dimensions while it preserves its native aspect ratio. If the aspect ratio of the destination rectangle differs from the source, the source content is clipped to fit in the destination dimensions.
         */
        UniformToFill
    };

    /**
     * @brief Helper class for converting Stretch enum to and from string.
     */
    class StretchHelper
    {
    public:
        /**
         * @brief Converts a string to a Stretch enum value.
         * @param value The string representation of the Stretch value.
         * @return The corresponding Stretch enum value.
         */
        static Stretch FromString(const std::string &value)
        {
            if (value == "UniformToFill")
            {
                return Stretch::UniformToFill;
            }
            else if (value == "Fill")
            {
                return Stretch::Fill;
            }
            else if (value == "Uniform")
            {
                return Stretch::Uniform;
            }
            return Stretch::None;
        }

        /**
         * @brief Converts a Stretch enum value to a string.
         * @param value The Stretch enum value.
         * @return The string representation of the Stretch value.
         */
        static std::string ToString(Stretch value)
        {
            switch (value)
            {
            case Stretch::Fill:
                return "Fill";

            case Stretch::Uniform:
                return "Uniform";

            case Stretch::UniformToFill:
                return "UniformToFill";

            case Stretch::None:
            default:
                return "None";
            }
        }
    };
}
