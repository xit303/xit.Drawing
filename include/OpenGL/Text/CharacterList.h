#pragma once

#include <map>
#include <MathHelper.h>

#include <IO/IO.h>
#include <OpenGL/Text/Character.h>
#include <Drawing/Size.h>

#include <glad/glad.h>

#include <ft2build.h>
#include FT_FREETYPE_H  

namespace xit::OpenGL
{
    class CharacterList : public std::map<char, Character>
    {
    private:
        int fontHeight;

    public:
        CharacterList()
            :fontHeight(12)
        {
        }

        CharacterList(const CharacterList& other)
        {
            fontHeight = other.fontHeight;

            for (std::pair<char, Character> existing : other)
            {
                emplace(existing);
            }
        }

        ~CharacterList()
        {
        }

        CharacterList& operator=(const CharacterList& other)
        {
            fontHeight = other.fontHeight;

            for (std::pair<char, Character> existing : other)
            {
                emplace(existing);
            }
            return *this;
        }

        const int FontHeight = fontHeight;

        void Measure(const std::string& text, Size& target)
        {
            if (text.empty())
            {
                target.SetWidth(0);
                target.SetHeight(fontHeight);
                return;
            }

            //SizeF size = new SizeF(0, FontHeight);
            int width = 0;
            //float height = 0;

            size_t len = text.length();

            int rows = 1;
            int rowWidth = 0;

            // iterate through all characters
            for (size_t i = 0; i < len; i++)
            {
                try
                {
                    Character ch = operator[](text[i]);
                    //if (TryGetValue(text[i], ch))
                    {
                        if (text[i] == '\n')
                        {
                            rows++;
                            width = rowWidth > width ? rowWidth : width;
                            rowWidth = 0;
                            continue;
                        }

                        rowWidth += ch.Advance;

                        //float tmp = ch->GlyphSize.GetHeight() - (ch->GlyphSize.GetHeight() - ch->Bearing.Y);

              /*          if (tmp > height)
                        {
                            height = tmp;
                        }*/

                        //if (i < text.Length - 1)
                        //    size.GetWidth() += (ch.Advance - size.GetWidth());
                    }
                }
                catch(...)
                {
                    Logger::Log(LogLevel::Error, "CharacterList", "Could not find character [%s] in character list", text[i]);
                }
            }

            width = rowWidth > width ? rowWidth : width;

            target.SetWidth(width);
            target.SetHeight(fontHeight * rows);
        }

        static void Create(const std::string& fontName, int fontSize, CharacterList &destination)
        {
            FT_Library library;

            if (FT_Init_FreeType(&library))
            {
                Logger::Log(LogLevel::Error, "CharacterList.Create", "Could not init FreeType Library");
                return;
            }

            FT_Error result;
            FT_Face face;
            if ((result = FT_New_Face(library, fontName.c_str(), 0, &face) != FT_Err_Ok))
            {
                Logger::Log(LogLevel::Error, "CharacterList.Create", "Failed to load font");
                return;
            }
            else
            {
                FT_Set_Pixel_Sizes(face, 0, (uint)fontSize);
            }

            glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

            int maxHeight = 0;

            for (uint c = 0; c < 255; c++)
            {
                // load character glyph 
                if ((result = FT_Load_Char(face, c, FT_LOAD_RENDER)) != FT_Err_Ok)
                {
                    Logger::Log(LogLevel::Error, "CharacterList.Create", "Failed to load Glyph %c", c);
                    continue;
                }

                // generate texture
                uint textureId = 0;
                glGenTextures(1, &textureId);
                glBindTexture(GL_TEXTURE_2D, textureId);
                glTexImage2D(
                    GL_TEXTURE_2D,
                    0,
                    GL_RED,
                    (int)face->glyph->bitmap.width,
                    (int)face->glyph->bitmap.rows,
                    0,
                    GL_RED,
                    GL_UNSIGNED_BYTE,
                    face->glyph->bitmap.buffer
                );
                // set texture options
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (int)GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (int)GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (int)GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (int)GL_LINEAR);

                // now store character for later use
                Character character;
                character.TextureID = textureId;
                character.GlyphSize.SetWidth((int)face->glyph->bitmap.width);
                character.GlyphSize.SetHeight((int)face->glyph->bitmap.rows);

                character.Bearing.X = face->glyph->bitmap_left;
                character.Bearing.Y = face->glyph->bitmap_top;

                character.Advance = face->glyph->advance.x >> 6;
                //character->Buffer = face->glyph->bitmap.buffer;

                maxHeight = character.GlyphSize.GetHeight() > maxHeight ? character.GlyphSize.GetHeight() : maxHeight;

                destination.emplace(std::make_pair((char)c, character));

                glBindTexture(GL_TEXTURE_2D, 0);
            }

            FT_Done_Face(face);
            FT_Done_FreeType(library);

            destination.fontHeight = maxHeight;
        }
    };
}
