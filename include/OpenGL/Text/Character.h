#pragma once

#include <Drawing/Size.h>
#include <Input/Point.h>

#ifndef GLAD_INCLUDED
#include <glad/glad.h>
#define GLAD_INCLUDED
#endif

namespace xit::OpenGL
{
    using namespace xit::Drawing;

    struct Character
    {
    public:
        GLuint TextureID; // ID handle of the glyph texture
        Size GlyphSize;   // Size of glyph
        Point Bearing;    // Offset from baseline to left/top of glyph
        int Advance;      // Offset to advance to next glyph
        float *Buffer;    // Storage for vertex data so we dont have to create it over and over again

        Character()
            : TextureID(UINT32_MAX),
              GlyphSize(0, 0),
              Bearing(0, 0),
              Advance(0),
              Buffer(nullptr)
        {
        }

        Character(const Character &other)
            : TextureID(other.TextureID),
              GlyphSize(other.GlyphSize),
              Bearing(other.Bearing),
              Advance(other.Advance),
              Buffer(other.Buffer)
        {
        }

        bool empty()
        {
            return TextureID == UINT32_MAX;
        }
    };
}
