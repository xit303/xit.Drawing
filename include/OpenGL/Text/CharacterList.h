#pragma once

#include <map>
#include <MathHelper.h>

#include <IO/IO.h>
#include <OpenGL/Text/Character.h>
#include <Drawing/Size.h>

#include <ft2build.h>
#include FT_FREETYPE_H  

#ifdef DEBUG_FONT_PERFORMANCE
#include <chrono>
#include <iostream>
#endif

namespace xit::OpenGL
{
    class CharacterList : public std::map<char, Character>
    {
    private:
        int fontHeight;
        std::string fontName;
        int fontSize;
        FT_Library library;
        FT_Face face;
        bool initialized;

    public:
        CharacterList()
            :fontHeight(12), initialized(false)
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
            if (initialized)
            {
                FT_Done_Face(face);
                FT_Done_FreeType(library);
            }
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

        void LoadSingleCharacter(char c)
        {
            if (!initialized)
            {
                Logger::Log(LogLevel::Error, "CharacterList.LoadSingleCharacter", "Font not initialized");
                return;
            }

#ifdef DEBUG_FONT_PERFORMANCE
            auto start = std::chrono::high_resolution_clock::now();
#endif

            FT_Error result;
            // load character glyph 
            if ((result = FT_Load_Char(face, c, FT_LOAD_RENDER)) != FT_Err_Ok)
            {
                Logger::Log(LogLevel::Error, "CharacterList.LoadSingleCharacter", "Failed to load Glyph %c", c);
                return;
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

            int charHeight = character.GlyphSize.GetHeight();
            fontHeight = charHeight > fontHeight ? charHeight : fontHeight;

            emplace(std::make_pair(c, character));

            glBindTexture(GL_TEXTURE_2D, 0);

#ifdef DEBUG_FONT_PERFORMANCE
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            std::cout << "CharacterList::LoadSingleCharacter - Character '" << c << "' loaded in " << duration.count() << "μs" << std::endl;
#endif
        }

        void Measure(const std::string& text, Size& target)
        {
#ifdef DEBUG_FONT_PERFORMANCE
            auto start = std::chrono::high_resolution_clock::now();
#endif

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
                    char c = text[i];
                    
                    // Lazy loading: only create character if it doesn't exist
                    if (find(c) == end())
                    {
#ifdef DEBUG_FONT_PERFORMANCE
                        std::cout << "CharacterList::Measure - Lazy loading character '" << c << "' (ASCII " << (int)c << ")" << std::endl;
#endif
                        LoadSingleCharacter(c);
                    }
                    
                    Character ch = operator[](c);
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

#ifdef DEBUG_FONT_PERFORMANCE
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            std::cout << "CharacterList::Measure - Text '" << text << "' measured in " << duration.count() 
                      << "μs, result: " << target.GetWidth() << "x" << target.GetHeight() << std::endl;
#endif
        }

        static void Create(const std::string& fontName, int fontSize, CharacterList &destination)
        {
#ifdef DEBUG_FONT_PERFORMANCE
            auto totalStart = std::chrono::high_resolution_clock::now();
            std::cout << "CharacterList::Create - Initializing font '" << fontName << "' size " << fontSize << " (lazy loading)" << std::endl;
#endif

            if (FT_Init_FreeType(&destination.library))
            {
                Logger::Log(LogLevel::Error, "CharacterList.Create", "Could not init FreeType Library");
                return;
            }

#ifdef DEBUG_FONT_PERFORMANCE
            auto initEnd = std::chrono::high_resolution_clock::now();
            auto initDuration = std::chrono::duration_cast<std::chrono::microseconds>(initEnd - totalStart);
            std::cout << "CharacterList::Create - FreeType init took " << initDuration.count() << "μs" << std::endl;
#endif

            FT_Error result;
            if ((result = FT_New_Face(destination.library, fontName.c_str(), 0, &destination.face) != FT_Err_Ok))
            {
                Logger::Log(LogLevel::Error, "CharacterList.Create", "Failed to load font");
                FT_Done_FreeType(destination.library);
                return;
            }
            else
            {
                FT_Set_Pixel_Sizes(destination.face, 0, (uint)fontSize);
            }

#ifdef DEBUG_FONT_PERFORMANCE
            auto faceEnd = std::chrono::high_resolution_clock::now();
            auto faceDuration = std::chrono::duration_cast<std::chrono::microseconds>(faceEnd - initEnd);
            std::cout << "CharacterList::Create - Font face loading took " << faceDuration.count() << "μs" << std::endl;
#endif

            glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

            // Store font info for lazy loading
            destination.fontName = fontName;
            destination.fontSize = fontSize;
            destination.initialized = true;
            destination.fontHeight = fontSize; // Initial estimate, will be updated as characters are loaded

#ifdef DEBUG_FONT_PERFORMANCE
            auto totalEnd = std::chrono::high_resolution_clock::now();
            auto totalDuration = std::chrono::duration_cast<std::chrono::microseconds>(totalEnd - totalStart);
            std::cout << "CharacterList::Create - Font initialization completed in " << totalDuration.count() 
                      << "μs (characters will be loaded on-demand)" << std::endl;
#endif
        }
    };
}
