#pragma once

namespace xit::Drawing
{
    class Size
    {
    private:
        int width;
        int height;

    public:
        __inline __attribute__ ((__always_inline__)) int GetWidth() const { return width; }
        __inline __attribute__ ((__always_inline__)) void SetWidth(int value) { width = value; }

        __inline __attribute__ ((__always_inline__)) int GetHeight() const { return height; }
        __inline __attribute__ ((__always_inline__)) void SetHeight(int value) { height = value; }

        Size();
        Size(int width, int height);
        Size(int uniform);

        bool IsEmpty();
        static const Size &Empty;

        Size &operator=(const Size &other)
        {
            width = other.width;
            height = other.height;
            return *this;
        }
        bool operator==(const Size &other) const;
        bool operator!=(const Size &other) const;
    };
}
