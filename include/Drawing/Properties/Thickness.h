#pragma once

#include <cmath>
#include <MathHelper.h>

namespace xit::Drawing
{
    /**
     * @brief Describes the thickness of a frame around a rectangle.
     * Four integer values describe the Thickness.Left, Thickness.Top, Thickness.Right,
     * and Thickness.Bottom sides of the rectangle, respectively.
     */
    struct Thickness
    {
        int left;
        int top;
        int right;
        int bottom;

        mutable int scaledLeft;
        mutable int scaledTop;
        mutable int scaledRight;
        mutable int scaledBottom;

        mutable int width;
        mutable int height;

        mutable bool isZeroWidth;
        mutable bool isZeroHeight;
        mutable bool isZero;
        mutable bool isUniform;

        mutable float scalingFactorX;
        mutable float scalingFactorY;

    public:
        /**
         * @brief Gets the width, in pixels, of the Left side of the bounding rectangle.
         * @return An integer that represents the width, in pixels, of the Left side of the bounding rectangle.
         */
        __always_inline int GetLeft() const { return scaledLeft; }

        /**
         * @brief Gets the width, in pixels, of the upper side of the bounding rectangle.
         * @return An integer that represents the width, in pixels, of the upper side of the bounding rectangle.
         */
        __always_inline int &GetTop() const { return scaledTop; }

        /**
         * @brief Gets the width, in pixels, of the Right side of the bounding rectangle.
         * @return An integer that represents the width, in pixels, of the Right side of the bounding rectangle.
         */
        __always_inline int &GetRight() const { return scaledRight; }

        /**
         * @brief Gets the width, in pixels, of the lower side of the bounding rectangle.
         * @return An integer that represents the width, in pixels, of the lower side of the bounding rectangle.
         */
        __always_inline int &GetBottom() const { return scaledBottom; }

        /**
         * @brief Gets the total width of the bounding rectangle.
         * @return The total width.
         */
        __always_inline int &GetWidth() const { return width; }

        /**
         * @brief Gets the total height of the bounding rectangle.
         * @return The total height.
         */
        __always_inline int &GetHeight() const { return height; }

        /**
         * @brief Checks if the thickness is zero.
         * @return True if the thickness is zero, false otherwise.
         */
        __always_inline bool &GetIsZero() const { return isZero; }

        /**
         * @brief Checks if the width is zero.
         * @return True if the width is zero, false otherwise.
         */
        __always_inline bool GetIsZeroWidth() const { return isZeroWidth; }

        /**
         * @brief Checks if the height is zero.
         * @return True if the height is zero, false otherwise.
         */
        __always_inline bool GetIsZeroHeight() const { return isZeroHeight; }

        /**
         * @brief Checks if the thickness is uniform.
         * @return True if the thickness is uniform, false otherwise.
         */
        __always_inline bool GetIsUniform() const { return isUniform; }

        /**
         * @brief Initializes a new instance of the Thickness structure that has
         * the specified uniform length of 0 on each side.
         */
        Thickness() : Thickness(0) {}

        /**
         * @brief Initializes a new instance of the Thickness structure that has
         * the specified uniform length on each side.
         * @param uniformLength The uniform length applied to all four sides of the bounding rectangle.
         */
        Thickness(int uniformLength)
        {
            scaledLeft = 0;
            scaledTop = 0;
            scaledRight = 0;
            scaledBottom = 0;

            width = 0;
            height = 0;

            isZeroWidth = true;
            isZeroHeight = true;
            isZero = true;
            isUniform = true;
            scalingFactorX = 1;
            scalingFactorY = 1;
            SetValues(uniformLength);
        }

        /**
         * @brief Initializes a new instance of the Thickness structure that has
         * specific lengths (supplied as an integer) applied to each side of the rectangle.
         * @param left The thickness for the Left side of the rectangle.
         * @param top The thickness for the upper side of the rectangle.
         * @param right The thickness for the Right side of the rectangle.
         * @param bottom The thickness for the lower side of the rectangle.
         */
        Thickness(int left, int top, int right, int bottom)
        {
            scalingFactorX = 1;
            scalingFactorY = 1;
            SetValues(left, top, right, bottom);
        }

        /**
         * @brief Initializes a new instance of the Thickness structure that has
         * specific uniform lengths (supplied as an integer) applied to each side of the rectangle.
         * @param leftRight The Thickness for the Left and the Right side of the rectangle.
         * @param topBottom The Thickness for the Top and the Bottom side of the rectangle.
         */
        Thickness(int leftRight, int topBottom)
        {
            scalingFactorX = 1;
            scalingFactorY = 1;
            SetValues(leftRight, topBottom);
        }

        /**
         * @brief Copy constructor.
         * @param other The other Thickness instance to copy from.
         */
        Thickness(const Thickness &other)
        {
            scalingFactorX = other.scalingFactorX;
            scalingFactorY = other.scalingFactorY;
            SetValues(other.left, other.top, other.right, other.bottom);
        }

        /**
         * @brief Sets the values of the thickness uniformly.
         * @param uniformLength The uniform length to set.
         */
        void SetValues(int uniformLength)
        {
            left = top = right = bottom = uniformLength;
            Scale(scalingFactorX, scalingFactorY);
        }

        /**
         * @brief Sets the values of the thickness.
         * @param left The thickness for the Left side.
         * @param top The thickness for the Top side.
         * @param right The thickness for the Right side.
         * @param bottom The thickness for the Bottom side.
         */
        void SetValues(int left, int top, int right, int bottom)
        {
            this->left = left;
            this->top = top;
            this->right = right;
            this->bottom = bottom;

            Scale(scalingFactorX, scalingFactorY);
        }

        /**
         * @brief Sets the values of the thickness.
         * @param leftRight The thickness for the Left and Right sides.
         * @param topBottom The thickness for the Top and Bottom sides.
         */
        void SetValues(int leftRight, int topBottom)
        {
            this->left = leftRight;
            this->top = topBottom;
            this->right = leftRight;
            this->bottom = topBottom;

            Scale(scalingFactorX, scalingFactorY);
        }

        /**
         * @brief Compares the value of two Thickness structures for equality.
         * @param other The other structure to compare.
         * @return True if the two instances of Thickness are equal, false otherwise.
         */
        bool operator==(const Thickness &other) const
        {
            return (left == other.left) && (top == other.top) && (right == other.right) && (bottom == other.bottom) && (scalingFactorX == other.scalingFactorX) && (scalingFactorY == other.scalingFactorY);
        }

        /**
         * @brief Compares two Thickness structures for inequality.
         * @param other The other structure to compare.
         * @return True if the two instances of Thickness are not equal, false otherwise.
         */
        bool operator!=(const Thickness &other) const
        {
            return !(*this == other);
        }

        /**
         * @brief Assignment operator.
         * @param other The other Thickness instance to assign from.
         * @return A reference to this instance.
         */
        Thickness operator=(const Thickness &other)
        {
            scalingFactorX = other.scalingFactorX;
            scalingFactorY = other.scalingFactorY;
            SetValues(other.left, other.top, other.right, other.bottom);
            return *this;
        }

        /**
         * @brief Scales the thickness by a given factor.
         * @param factor The scaling factor.
         */
        bool Scale(float factor) const
        {
            if (factor == scalingFactorX && factor == scalingFactorY)
                return false;

            scalingFactorX = scalingFactorY = factor;

            scaledLeft = (int)std::round((float)left * factor);
            scaledTop = (int)std::round((float)top * factor);
            scaledRight = (int)std::round((float)right * factor);
            scaledBottom = (int)std::round((float)bottom * factor);

            width = scaledLeft + scaledRight;
            height = scaledTop + scaledBottom;

            isZeroWidth = width == 0;
            isZeroHeight = height == 0;
            isZero = isZeroWidth && isZeroHeight;

            isUniform = left == top && left == right && left == bottom;
            return true;
        }

        /**
         * @brief Scales the thickness by a given factor.
         * @param factorX The scaling factor for the X axis.
         * @param factorY The scaling factor for the Y axis.
         */
        bool Scale(float factorX, float factorY) const
        {
            bool hasChanged = false;

            if (factorX != scalingFactorX)
            {
                scalingFactorX = factorX;
                hasChanged = true;
            }

            if (factorY != scalingFactorY)
            {
                scalingFactorY = factorY;
                hasChanged = true;
            }

            scaledLeft = (int)std::round((float)left * scalingFactorX);
            scaledRight = (int)std::round((float)right * scalingFactorX);
            width = scaledLeft + scaledRight;
            isZeroWidth = width == 0;
            isZero = isZeroWidth && isZeroHeight;
            isUniform = left == top && left == right && left == bottom;

            scaledTop = (int)std::round((float)top * scalingFactorY);
            scaledBottom = (int)std::round((float)bottom * scalingFactorY);
            height = scaledTop + scaledBottom;
            isZeroHeight = height == 0;

            return hasChanged;
        }

        /**
         * @brief Resets the scaling factor to 1.
         */
        bool ResetScale()
        {
            scalingFactorX = 1;
            scalingFactorY = 1;
            return Scale(scalingFactorX, scalingFactorY);
        }

        // bool IsValid(bool allowNegative, bool allowNaN, bool allowPositiveInfinity, bool allowNegativeInfinity);
    };
}
