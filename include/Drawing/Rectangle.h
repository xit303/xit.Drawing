#pragma once

#include <algorithm>

#include <Input/Point.h>
#include <Drawing/Size.h>

namespace xit::Drawing
{
    /// <summary>Stores a set of four integers that represent the location and size of a rectangle</summary>
    /// <filterpriority>1</filterpriority>
    struct Rectangle
    {
    private:
        int X;
        int Y;
        int width;
        int height;
        static const Rectangle empty;
        mutable Size size;

    public:
        /// <summary>Represents a <see cref="T:System.Drawing.Rectangle" /> structure with its properties left uninitialized.</summary>
        /// <filterpriority>1</filterpriority>
        static const Rectangle Empty() { return empty; }

        /// <summary>Gets or sets the coordinates of the upper-left corner of this <see cref="T:System.Drawing.Rectangle" /> structure.</summary>
        /// <returns>A <see cref="T:System.Drawing.Point" /> that represents the upper-left corner of this <see cref="T:System.Drawing.Rectangle" /> structure.</returns>
        /// <filterpriority>1</filterpriority>
        Point GetLocation()
        {
            return Point(X, Y);
        }
        void SetLocation(int x, int y)
        {
            X = x;
            Y = y;
        }
        void SetLocation(Point &value)
        {
            X = value.X;
            Y = value.Y;
        }

        /// <summary>Gets or sets the size of this <see cref="T:System.Drawing.Rectangle" />.</summary>
        /// <returns>A <see cref="T:System.Drawing.Size" /> that represents the width and height of this <see cref="T:System.Drawing.Rectangle" /> structure.</returns>
        /// <filterpriority>1</filterpriority>
        const Size &GetSize() const
        {
            size.SetWidth(width);
            size.SetHeight(height);
            return size;
        }
        void SetSize(Size &value)
        {
            width = value.GetWidth();
            height = value.GetHeight();
        }

        void SetSize(int width, int height)
        {
            this->width = width;
            this->height = height;
        }

        inline int GetLeft() const { return X; }
        inline void SetLeft(const int &value) { X = value; }

        inline int GetTop() const { return Y; }
        inline void SetTop(const int &value) { Y = value; }

        /// <summary>Gets or sets the width of this <see cref="T:System.Drawing.Rectangle" /> structure.</summary>
        /// <returns>The width of this <see cref="T:System.Drawing.Rectangle" /> structure. The default is 0.</returns>
        /// <filterpriority>1</filterpriority>
        __always_inline int GetWidth() const { return width; }
        void SetWidth(int value) { width = value; }

        /// <summary>Gets or sets the height of this <see cref="T:System.Drawing.Rectangle" /> structure.</summary>
        /// <returns>The height of this <see cref="T:System.Drawing.Rectangle" /> structure. The default is 0.</returns>
        /// <filterpriority>1</filterpriority>
        __always_inline int GetHeight() const { return height; }
        void SetHeight(int value) { height = value; }

        /// <summary>Gets the x-coordinate that is the sum of <see cref="P:System.Drawing.Rectangle.X" /> and <see cref="P:System.Drawing.Rectangle.Width" /> property values of this <see cref="T:System.Drawing.Rectangle" /> structure.</summary>
        /// <returns>The x-coordinate that is the sum of <see cref="P:System.Drawing.Rectangle.X" /> and <see cref="P:System.Drawing.Rectangle.Width" /> of this <see cref="T:System.Drawing.Rectangle" />.</returns>
        /// <filterpriority>1</filterpriority>
        int GetRight() const
        {
            return X + width;
        }

        /// <summary>Gets the y-coordinate that is the sum of the <see cref="P:System.Drawing.Rectangle.Y" /> and <see cref="P:System.Drawing.Rectangle.Height" /> property values of this <see cref="T:System.Drawing.Rectangle" /> structure.</summary>
        /// <returns>The y-coordinate that is the sum of <see cref="P:System.Drawing.Rectangle.Y" /> and <see cref="P:System.Drawing.Rectangle.Height" /> of this <see cref="T:System.Drawing.Rectangle" />.</returns>
        /// <filterpriority>1</filterpriority>
        int GetBottom() const
        {
            return Y + height;
        }

        /// <summary>Tests whether all numeric properties of this <see cref="T:System.Drawing.Rectangle" /> have values of zero.</summary>
        /// <returns>This property returns true if the <see cref="P:System.Drawing.Rectangle.Width" />, <see cref="P:System.Drawing.Rectangle.Height" />, <see cref="P:System.Drawing.Rectangle.X" />, and <see cref="P:System.Drawing.Rectangle.Y" /> properties of this <see cref="T:System.Drawing.Rectangle" /> all have values of zero; otherwise, false.</returns>
        /// <filterpriority>1</filterpriority>
        bool IsEmpty() const
        {
            return height == 0 && width == 0 && X == 0 && Y == 0;
        }

        /// <summary>Initializes a new instance of the <see cref="T:System.Drawing.Rectangle" /> class with the location and size of 0.</summary>
        Rectangle()
        {
            this->X = 0;
            this->Y = 0;
            this->width = 0;
            this->height = 0;
        }

        /// <summary>Initializes a new instance of the <see cref="T:System.Drawing.Rectangle" /> class with the specified location and size.</summary>
        /// <param name="x">The x-coordinate of the upper-left corner of the rectangle. </param>
        /// <param name="y">The y-coordinate of the upper-left corner of the rectangle. </param>
        /// <param name="width">The width of the rectangle. </param>
        /// <param name="height">The height of the rectangle. </param>
        Rectangle(int x, int y, int width, int height)
        {
            this->X = x;
            this->Y = y;
            this->width = width;
            this->height = height;
        }

        /// <summary>Initializes a new instance of the <see cref="T:System.Drawing.Rectangle" /> class with the specified location and size.</summary>
        /// <param name="location">A <see cref="T:System.Drawing.Point" /> that represents the upper-left corner of the rectangular region. </param>
        /// <param name="size">A <see cref="T:System.Drawing.Size" /> that represents the width and height of the rectangular region. </param>
        Rectangle(Point &location, const Drawing::Size &size)
        {
            this->X = location.X;
            this->Y = location.Y;
            this->width = size.GetWidth();
            this->height = size.GetHeight();
        }

        Rectangle(Rectangle &other)
        {
            this->X = other.X;
            this->Y = other.Y;
            this->width = other.width;
            this->height = other.height;
        }

        Rectangle(const Rectangle &other)
        {
            this->X = other.X;
            this->Y = other.Y;
            this->width = other.width;
            this->height = other.height;
        }

        /// <summary>Creates a <see cref="T:System.Drawing.Rectangle" /> structure with the specified edge locations.</summary>
        /// <returns>The new <see cref="T:System.Drawing.Rectangle" /> that this method creates.</returns>
        /// <param name="left">The x-coordinate of the upper-left corner of this <see cref="T:System.Drawing.Rectangle" /> structure. </param>
        /// <param name="top">The y-coordinate of the upper-left corner of this <see cref="T:System.Drawing.Rectangle" /> structure. </param>
        /// <param name="right">The x-coordinate of the lower-right corner of this <see cref="T:System.Drawing.Rectangle" /> structure. </param>
        /// <param name="bottom">The y-coordinate of the lower-right corner of this <see cref="T:System.Drawing.Rectangle" /> structure. </param>
        static Rectangle *FromLTRB(int left, int top, int right, int bottom)
        {
            return new Rectangle(left, top, right - left, bottom - top);
        }

        /// <summary>Tests whether <paramref name="obj" /> is a <see cref="T:System.Drawing.Rectangle" /> structure with the same location and size of this <see cref="T:System.Drawing.Rectangle" /> structure.</summary>
        /// <returns>This method returns true if <paramref name="obj" /> is a <see cref="T:System.Drawing.Rectangle" /> structure and its <see cref="P:System.Drawing.Rectangle.X" />, <see cref="P:System.Drawing.Rectangle.Y" />, <see cref="P:System.Drawing.Rectangle.Width" />, and <see cref="P:System.Drawing.Rectangle.Height" /> properties are equal to the corresponding properties of this <see cref="T:System.Drawing.Rectangle" /> structure; otherwise, false.</returns>
        /// <param name="obj">The <see cref="T:System.Object" /> to test. </param>
        // public override bool Equals(object obj)
        //{
        //	if (!(obj is Rectangle))
        //	{
        //		return false;
        //	}
        //	Rectangle rectangle = (Rectangle)obj;
        //	return rectangle.X == this->X && rectangle.Y == this->Y && rectangle.Width == this->Width && rectangle.Height == this->Height;
        // }

        Rectangle &operator=(const Rectangle &other)
        {
            X = other.X;
            Y = other.Y;
            width = other.width;
            height = other.height;

            return *this;
        }

        /// <summary>Tests whether two <see cref="T:System.Drawing.Rectangle" /> structures have equal location and size.</summary>
        /// <returns>This operator returns true if the two <see cref="T:System.Drawing.Rectangle" /> structures have equal <see cref="P:System.Drawing.Rectangle.X" />, <see cref="P:System.Drawing.Rectangle.Y" />, <see cref="P:System.Drawing.Rectangle.Width" />, and <see cref="P:System.Drawing.Rectangle.Height" /> properties.</returns>
        /// <param name="left">The <see cref="T:System.Drawing.Rectangle" /> structure that is to the left of the equality operator. </param>
        /// <param name="right">The <see cref="T:System.Drawing.Rectangle" /> structure that is to the right of the equality operator. </param>
        bool operator==(const Rectangle &right)
        {
            return X == right.X && Y == right.Y && width == right.width && height == right.height;
        }

        /// <summary>Tests whether two <see cref="T:System.Drawing.Rectangle" /> structures differ in location or size.</summary>
        /// <returns>This operator returns true if any of the <see cref="P:System.Drawing.Rectangle.X" />, <see cref="P:System.Drawing.Rectangle.Y" />, <see cref="P:System.Drawing.Rectangle.Width" /> or <see cref="P:System.Drawing.Rectangle.Height" /> properties of the two <see cref="T:System.Drawing.Rectangle" /> structures are unequal; otherwise false.</returns>
        /// <param name="left">The <see cref="T:System.Drawing.Rectangle" /> structure that is to the left of the inequality operator. </param>
        /// <param name="right">The <see cref="T:System.Drawing.Rectangle" /> structure that is to the right of the inequality operator. </param>
        bool operator!=(const Rectangle &right)
        {
            return !(*this == right);
        }

        /// <summary>Converts the specified <see cref="T:System.Drawing.RectangleF" /> structure to a <see cref="T:System.Drawing.Rectangle" /> structure by rounding the <see cref="T:System.Drawing.RectangleF" /> values to the next higher integer values.</summary>
        /// <returns>Returns a <see cref="T:System.Drawing.Rectangle" />.</returns>
        /// <param name="value">The <see cref="T:System.Drawing.RectangleF" /> structure to be converted. </param>
        // static Rectangle* Ceiling(RectangleF value)
        //{
        //	return new Rectangle((int)Math::Ceiling((double)value.X), (int)Math::Ceiling((double)value.Y), (int)Math::Ceiling((double)value.Width), (int)Math::Ceiling((double)value.Height));
        // }

        /// <summary>Converts the specified <see cref="T:System.Drawing.RectangleF" /> to a <see cref="T:System.Drawing.Rectangle" /> by truncating the <see cref="T:System.Drawing.RectangleF" /> values.</summary>
        /// <returns>A <see cref="T:System.Drawing.Rectangle" />.</returns>
        /// <param name="value">The <see cref="T:System.Drawing.RectangleF" /> to be converted. </param>
        // static Rectangle* Truncate(RectangleF value)
        //{
        //	return new Rectangle((int)value.X, (int)value.Y, (int)value.Width, (int)value.Height);
        // }

        /// <summary>Converts the specified <see cref="T:System.Drawing.RectangleF" /> to a <see cref="T:System.Drawing.Rectangle" /> by rounding the <see cref="T:System.Drawing.RectangleF" /> values to the nearest integer values.</summary>
        /// <returns>A <see cref="T:System.Drawing.Rectangle" />.</returns>
        /// <param name="value">The <see cref="T:System.Drawing.RectangleF" /> to be converted. </param>
        // static Rectangle* Round(RectangleF value)
        //{
        //	return new Rectangle((int)Math::Round((double)value.X), (int)Math::Round((double)value.Y), (int)Math::Round((double)value.Width), (int)Math::Round((double)value.Height));
        // }

        /// <summary>Determines if the specified point is contained within this <see cref="T:System.Drawing.Rectangle" /> structure.</summary>
        /// <returns>This method returns true if the point defined by <paramref name="x" /> and <paramref name="y" /> is contained within this <see cref="T:System.Drawing.Rectangle" /> structure; otherwise false.</returns>
        /// <param name="x">The x-coordinate of the point to test. </param>
        /// <param name="y">The y-coordinate of the point to test. </param>
        bool Contains(int x, int y)
        {
            return this->X <= x && x < this->X + this->width && this->Y <= y && y < this->Y + this->height;
        }

        /// <summary>Determines if the specified point is contained within this <see cref="T:System.Drawing.Rectangle" /> structure.</summary>
        /// <returns>This method returns true if the point represented by <paramref name="pt" /> is contained within this <see cref="T:System.Drawing.Rectangle" /> structure; otherwise false.</returns>
        /// <param name="pt">The <see cref="T:System.Drawing.Point" /> to test. </param>
        bool Contains(Point &pt)
        {
            return this->Contains(pt.X, pt.Y);
        }

        /// <summary>Determines if the rectangular region represented by <paramref name="rect" /> is entirely contained within this <see cref="T:System.Drawing.Rectangle" /> structure.</summary>
        /// <returns>This method returns true if the rectangular region represented by <paramref name="rect" /> is entirely contained within this <see cref="T:System.Drawing.Rectangle" /> structure; otherwise false.</returns>
        /// <param name="rect">The <see cref="T:System.Drawing.Rectangle" /> to test. </param>
        bool Contains(const Rectangle &rect)
        {
            return this->X <= rect.X && rect.X + rect.width <= this->X + this->width && this->Y <= rect.Y && rect.Y + rect.height <= this->Y + this->height;
        }

        /// <summary>Enlarges this <see cref="T:System.Drawing.Rectangle" /> by the specified amount.</summary>
        /// <param name="width">The amount to inflate this <see cref="T:System.Drawing.Rectangle" /> horizontally. </param>
        /// <param name="height">The amount to inflate this <see cref="T:System.Drawing.Rectangle" /> vertically. </param>
        void Inflate(int width, int height)
        {
            this->X -= width;
            this->Y -= height;
            this->width += 2 * width;
            this->height += 2 * height;
        }

        /// <summary>Enlarges this <see cref="T:System.Drawing.Rectangle" /> by the specified amount.</summary>
        /// <param name="size">The amount to inflate this rectangle. </param>
        void Inflate(const Drawing::Size &size)
        {
            Inflate(size.GetWidth(), size.GetHeight());
        }

        /// <summary>Creates and returns an enlarged copy of the specified <see cref="T:System.Drawing.Rectangle" /> structure. The copy is enlarged by the specified amount. The original <see cref="T:System.Drawing.Rectangle" /> structure remains unmodified.</summary>
        /// <returns>The enlarged <see cref="T:System.Drawing.Rectangle" />.</returns>
        /// <param name="rect">The <see cref="T:System.Drawing.Rectangle" /> with which to start. This rectangle is not modified. </param>
        /// <param name="x">The amount to inflate this <see cref="T:System.Drawing.Rectangle" /> horizontally. </param>
        /// <param name="y">The amount to inflate this <see cref="T:System.Drawing.Rectangle" /> vertically. </param>
        static Rectangle Inflate(Rectangle rect, int x, int y)
        {
            Rectangle result = rect;
            result.Inflate(x, y);
            return result;
        }

        /// <summary>Replaces this <see cref="T:System.Drawing.Rectangle" /> with the intersection of itself and the specified <see cref="T:System.Drawing.Rectangle" />.</summary>
        /// <param name="rect">The <see cref="T:System.Drawing.Rectangle" /> with which to intersect. </param>
        void Intersect(const Rectangle &rect)
        {
            Rectangle *rectangle = Intersect(rect, *this);
            this->X = rectangle->X;
            this->Y = rectangle->Y;
            this->width = rectangle->width;
            this->height = rectangle->height;
            delete rectangle;
        }

        /// <summary>Returns a third <see cref="T:System.Drawing.Rectangle" /> structure that represents the intersection of two other <see cref="T:System.Drawing.Rectangle" /> structures. If there is no intersection, an empty <see cref="T:System.Drawing.Rectangle" /> is returned.</summary>
        /// <returns>A <see cref="T:System.Drawing.Rectangle" /> that represents the intersection of <paramref name="a" /> and <paramref name="b" />.</returns>
        /// <param name="a">A rectangle to intersect. </param>
        /// <param name="b">A rectangle to intersect. </param>
        static Rectangle *Intersect(const Rectangle &a, const Rectangle &b)
        {
            int num = std::max(a.X, b.X);
            int num2 = std::min(a.X + a.width, b.X + b.width);
            int num3 = std::max(a.Y, b.Y);
            int num4 = std::min(a.Y + a.height, b.Y + b.height);
            if (num2 >= num && num4 >= num3)
            {
                return new Rectangle(num, num3, num2 - num, num4 - num3);
            }
            return new Rectangle();
        }

        /// <summary>Determines if this rectangle intersects with <paramref name="rect" />.</summary>
        /// <returns>This method returns true if there is any intersection, otherwise false.</returns>
        /// <param name="rect">The rectangle to test. </param>
        bool IntersectsWith(const Rectangle &rect)
        {
            return rect.X < this->X + this->width && this->X < rect.X + rect.width && rect.Y < this->Y + this->height && this->Y < rect.Y + rect.height;
        }

        /// <summary>Gets a <see cref="T:System.Drawing.Rectangle" /> structure that contains the union of two <see cref="T:System.Drawing.Rectangle" /> structures.</summary>
        /// <returns>A <see cref="T:System.Drawing.Rectangle" /> structure that bounds the union of the two <see cref="T:System.Drawing.Rectangle" /> structures.</returns>
        /// <param name="a">A rectangle to union. </param>
        /// <param name="b">A rectangle to union. </param>
        static Rectangle *Union(const Rectangle &a, const Rectangle &b)
        {
            int num = std::min(a.X, b.X);
            int num2 = std::max(a.X + a.width, b.X + b.width);
            int num3 = std::min(a.Y, b.Y);
            int num4 = std::max(a.Y + a.height, b.Y + b.height);
            return new Rectangle(num, num3, num2 - num, num4 - num3);
        }

        /// <summary>Adjusts the location of this rectangle by the specified amount.</summary>
        /// <param name="pos">Amount to offset the location. </param>
        void Offset(Point &pos)
        {
            Offset(pos.X, pos.Y);
        }

        /// <summary>Adjusts the location of this rectangle by the specified amount.</summary>
        /// <param name="x">The horizontal offset. </param>
        /// <param name="y">The vertical offset. </param>
        void Offset(int x, int y)
        {
            this->X += x;
            this->Y += y;
        }

        void Set(int x, int y, int width, int height)
        {
            this->X = x;
            this->Y = y;
            this->width = width;
            this->height = height;
        }

        /// <summary>Converts the attributes of this <see cref="T:System.Drawing.Rectangle" /> to a human-readable string.</summary>
        /// <returns>A string that contains the position, width, and height of this <see cref="T:System.Drawing.Rectangle" /> structure � for example, {X=20, Y=20, Width=100, Height=50} </returns>
        // string ToString() override
        //{
        //	return string.Concat(new string[]
        //		{
        //			"{X=",
        //			this->X.ToString(CultureInfo.CurrentCulture),
        //			",Y=",
        //			this->Y.ToString(CultureInfo.CurrentCulture),
        //			",Width=",
        //			this->Width.ToString(CultureInfo.CurrentCulture),
        //			",Height=",
        //			this->Height.ToString(CultureInfo.CurrentCulture),
        //			"}"
        //		});
        // }
    };
}

using namespace xit::Drawing;
