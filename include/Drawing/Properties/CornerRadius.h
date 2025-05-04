#pragma once

#include <cmath>
#include <limits>

namespace xit::Drawing
{
    /**
     * @struct CornerRadius
     * @brief Represents the radii of a rectangle's corners.
     */
    struct CornerRadius
    {
    public:
        /**
         * @brief Gets or sets the radius of the top-left corner.
         */
        double TopLeft;

        /**
         * @brief Gets or sets the radius of the top-right corner.
         */
        double TopRight;

        /**
         * @brief Gets or sets the radius of the bottom-right corner.
         */
        double BottomRight;

        /**
         * @brief Gets or sets the radius of the bottom-left corner.
         */
        double BottomLeft;

        /**
         * @brief Checks if all corner radii are zero.
         * @return True if all corner radii are zero, false otherwise.
         */
        bool IsZero() const
        {
            return TopLeft == 0 && TopRight == 0 && BottomRight == 0 && BottomLeft == 0;
        }

        /**
         * @brief Default constructor. Initializes all corner radii to zero.
         */
        CornerRadius() : CornerRadius(0) {}

        /**
         * @brief Initializes a new instance with a uniform radius value for all corners.
         * @param uniformRadius The radius value applied to all corners.
         */
        CornerRadius(double uniformRadius)
        {
            TopLeft = TopRight = BottomLeft = BottomRight = uniformRadius;
        }

        /**
         * @brief Initializes a new instance with specified radius values for each corner.
         * @param topLeft The radius of the top-left corner.
         * @param topRight The radius of the top-right corner.
         * @param bottomRight The radius of the bottom-right corner.
         * @param bottomLeft The radius of the bottom-left corner.
         */
        CornerRadius(double topLeft, double topRight, double bottomRight, double bottomLeft)
        {
            TopLeft = topLeft;
            TopRight = topRight;
            BottomRight = bottomRight;
            BottomLeft = bottomLeft;
        }

        /**
         * @brief Sets a uniform radius value for all corners.
         * @param uniformRadius The uniform radius value.
         */
        void SetValues(double uniformRadius)
        {
            TopLeft = TopRight = BottomLeft = BottomRight = uniformRadius;
        }

        /**
         * @brief Sets specified radius values for each corner.
         * @param topLeft The radius of the top-left corner.
         * @param topRight The radius of the top-right corner.
         * @param bottomRight The radius of the bottom-right corner.
         * @param bottomLeft The radius of the bottom-left corner.
         */
        void SetValues(double topLeft, double topRight, double bottomRight, double bottomLeft)
        {
            TopLeft = topLeft;
            TopRight = topRight;
            BottomRight = bottomRight;
            BottomLeft = bottomLeft;
        }

        /**
         * @brief Compares two CornerRadius structures for equality.
         * @param cr2 The other CornerRadius to compare.
         * @return True if all corners have equal values, false otherwise.
         */
        bool operator ==(const CornerRadius& cr2) const
        {
            if ((TopLeft == cr2.TopLeft || (std::isnan(TopLeft) && std::isnan(cr2.TopLeft))) &&
                (TopRight == cr2.TopRight || (std::isnan(TopRight) && std::isnan(cr2.TopRight))) &&
                (BottomRight == cr2.BottomRight || (std::isnan(BottomRight) && std::isnan(cr2.BottomRight))))
            {
                if (BottomLeft != cr2.BottomLeft)
                {
                    return std::isnan(BottomLeft) && std::isnan(cr2.BottomLeft);
                }

                return true;
            }
            return false;
        }

        /**
         * @brief Compares two CornerRadius structures for inequality.
         * @param cr2 The other CornerRadius to compare.
         * @return True if any corner has different values, false otherwise.
         */
        inline bool operator !=(const CornerRadius& cr2) const
        {
            return !(*this == cr2);
        }

        /**
         * @brief Checks if the corner radii are valid based on specified conditions.
         * @param allowNegative Allow negative values.
         * @param allowNaN Allow NaN values.
         * @param allowPositiveInfinity Allow positive infinity values.
         * @param allowNegativeInfinity Allow negative infinity values.
         * @return True if the corner radii are valid based on the specified conditions, false otherwise.
         */
        bool IsValid(bool allowNegative, bool allowNaN, bool allowPositiveInfinity, bool allowNegativeInfinity) const
        {
            constexpr double inf = std::numeric_limits<double>::infinity();
            constexpr double neginf = -inf;
            return (allowNegative || (TopLeft >= 0.0 && TopRight >= 0.0 && BottomLeft >= 0.0 && BottomRight >= 0.0)) &&
                (allowNaN || (!std::isnan(TopLeft) && !std::isnan(TopRight) && !std::isnan(BottomLeft) && !std::isnan(BottomRight))) &&
                (allowPositiveInfinity || (inf != TopLeft && inf != TopRight && inf != BottomLeft && inf != BottomRight)) &&
                (allowNegativeInfinity || (neginf != TopLeft && neginf != TopRight && neginf != BottomLeft && neginf != BottomRight));
        }
    };
}
using namespace xit::Drawing;
