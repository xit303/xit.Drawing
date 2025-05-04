#pragma once

#include <glm.hpp>
#include <Event.h>
#include <iomanip>
#include <string>
#include <string.h>
#include <Exceptions.h>
#include <vector>

namespace xit::Drawing
{
    /**
     * @brief Represents a property for a color.
     */
    class ColorProperty
    {
    private:
        /**
         * @brief Handles the color changed event.
         */
        void HandleColorChanged()
        {
            EventArgs e;
            ColorChanged(*this, e);
            OnColorChanged(e);
        }

    protected:
        glm::vec4 color;

        /**
         * @brief Called when the color is changed.
         * 
         * You can override this method in a derived class to handle the change in the color.
         * 
         * @param e Event arguments.
         */
        virtual void OnColorChanged(EventArgs &e) {}

    public:
        /**
         * @brief Gets the color value.
         * @return The color value.
         */
        inline const glm::vec4 &GetColor() const { return color; }

        /**
         * @brief Sets the color value.
         * @param value The new color value.
         */
        void SetColor(const glm::vec4 &value)
        {
            if (color != value)
            {
                color = value;
                HandleColorChanged();
            }
        }

        /**
         * @brief Converts the color to a hex string.
         * @return The hex string representation of the color.
         */
        std::string ToHexString()
        {
            std::stringstream stream;
            stream << std::hex << color.a << color.r << color.g << color.b;
            return stream.str();
        }

        /**
         * @brief Converts an HTML color string to a glm::vec4 color.
         * @param colorString The HTML color string.
         * @return The glm::vec4 color.
         */
        static glm::vec4 FromHtml(std::string colorString)
        {
            size_t length = colorString.size();
            if (length < 3)
                return glm::vec4(0, 0, 0, 1);

            std::vector<char> data(length + 1, 0);
            strncpy(data.data(), colorString.c_str(), length);
            size_t index = 0;

            if (colorString.starts_with("#"))
            {
                index++;
            }

            for (size_t i = index; i < length; i++)
            {
                data[i] = std::tolower(data[i]);
            }

            uint rgb = 0; // atoi(data);
            // uint rgb = uint.Parse(data, NumberStyles.HexNumber);

            if (length == 3)
            {
                // RGB 3 digits

                uint red = data[index] - '0';
                if (red > 9)
                    red = data[index] - 'a' + 10;

                // make it a full byte (A = AA, 7 = 77 etc)
                red |= (red << 4);

                uint green = data[++index] - '0';
                if (green > 9)
                    green = data[index] - 'a' + 10;

                green |= (green << 4);

                uint blue = data[++index] - '0';
                if (blue > 9)
                    blue = data[index] - 'a' + 10;

                blue |= (blue << 4);

                return glm::vec4(red, green, blue, 1);
            }
            else if (length == 4)
            {
                // ARGB 4 digits

                uint alpha = data[index] - '0';
                if (alpha > 9)
                    alpha = data[index] - 'a' + 10;

                alpha |= (alpha << 4);

                uint red = data[++index] - '0';
                if (red > 9)
                    red = data[index] - 'a' + 10;

                // make it a full byte (A = AA, 7 = 77 etc)
                red |= (red << 4);

                uint green = data[++index] - '0';
                if (green > 9)
                    green = data[index] - 'a' + 10;

                green |= (green << 4);

                uint blue = data[++index] - '0';
                if (blue > 9)
                    blue = data[index] - 'a' + 10;

                blue |= (blue << 4);

                return glm::vec4(red, green, blue, alpha);
            }
            else if (length == 6)
            {
                // RGB 6 digits

                rgb |= 0xFF000000;

                uint red = data[index] - '0';
                if (red > 9)
                    red = data[index] - 'a' + 10;

                red <<= 4;

                uint red2 = data[++index] - '0';
                if (red2 > 9)
                    red2 = data[index] - 'a' + 10;

                red |= red2;

                uint green = data[++index] - '0';
                if (green > 9)
                    green = data[index] - 'a' + 10;

                green <<= 4;

                uint green2 = data[++index] - '0';
                if (green2 > 9)
                    green2 = data[index] - 'a' + 10;

                green |= green2;

                uint blue = data[++index] - '0';
                if (blue > 9)
                    blue = data[index] - 'a' + 10;

                blue <<= 4;

                uint blue2 = data[++index] - '0';
                if (blue2 > 9)
                    blue2 = data[index] - 'a' + 10;

                blue |= blue2;

                return glm::vec4(red, green, blue, 1);
            }
            else if (length == 8)
            {
                // ARGB

                uint alpha = data[index] - '0';
                if (alpha > 9)
                    alpha = data[index] - 'a' + 10;

                alpha <<= 4;

                uint alpha2 = data[++index] - '0';
                if (alpha2 > 9)
                    alpha2 = data[index] - 'a' + 10;

                alpha |= alpha2;

                uint red = data[++index] - '0';
                if (red > 9)
                    red = data[index] - 'a' + 10;

                red <<= 4;

                uint red2 = data[++index] - '0';
                if (red2 > 9)
                    red2 = data[index] - 'a' + 10;

                red |= red2;

                uint green = data[++index] - '0';
                if (green > 9)
                    green = data[index] - 'a' + 10;

                green <<= 4;

                uint green2 = data[++index] - '0';
                if (green2 > 9)
                    green2 = data[index] - 'a' + 10;

                green |= green2;

                uint blue = data[++index] - '0';
                if (blue > 9)
                    blue = data[index] - 'a' + 10;

                blue <<= 4;

                uint blue2 = data[++index] - '0';
                if (blue2 > 9)
                    blue2 = data[index] - 'a' + 10;

                blue |= blue2;

                return glm::vec4(red, green, blue, alpha);
            }
            else
            {
                uint value = atoi(colorString.c_str());
                if (errno == EINVAL)
                {
                    throw InvalidDataException();
                }
                return glm::vec4(value);
            }

            return glm::vec4(rgb);
        }

        /**
         * @brief Event triggered when the color is changed.
         */
        Event<ColorProperty &, EventArgs &> ColorChanged;

        /**
         * @brief Default constructor.
         */
        ColorProperty() : color(true) {}

        /**
         * @brief Constructor with color value.
         * @param color The initial color value.
         */
        ColorProperty(const glm::vec4 &color) : color(color) {}

        /**
         * @brief Constructor with hex color value.
         * @param hexColor The initial hex color value.
         */
        ColorProperty(unsigned int hexColor) : color(((hexColor >> 16) & 0xFF) / 255.0f, ((hexColor >> 8) & 0xFF) / 255.0f, (hexColor & 0xFF) / 255.0f, ((hexColor >> 24) & 0xFF) / 255.0f) {}

        /**
         * @brief Copy constructor.
         * @param other The other ColorProperty to copy from.
         */
        ColorProperty(const ColorProperty &other) : color(other.color) {}

        /**
         * @brief Constructor with pointer to another ColorProperty.
         * @param other The pointer to the other ColorProperty.
         */
        ColorProperty(const ColorProperty *other) : color(other->color) {}

        /**
         * @brief Destructor.
         */
        virtual ~ColorProperty() {}
    };
}
