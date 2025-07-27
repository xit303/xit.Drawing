#include <OpenGL/Text/FontStorage.h>

#ifdef DEBUG_FONT_PERFORMANCE
#include <chrono>
#include <iostream>
#endif

namespace xit::OpenGL
{
    FontStorage::FontSizeCharacterList::FontSizeCharacterList()
    {
    }

    FontStorage::FontSizeCharacterList::FontSizeCharacterList(const FontSizeCharacterList &other)
    {
    }

    FontStorage::FontSizeCharacterList &FontStorage::FontSizeCharacterList::operator=(const FontSizeCharacterList &other)
    {
        for (std::pair<int, CharacterList> value : other)
        {
            emplace(value);
        }

        return *this;
    }

    std::map<std::string, FontStorage::FontSizeCharacterList> FontStorage::fontStorage;

    CharacterList &FontStorage::FindOrCreate(const std::string &fontName, int fontSize)
    {
#ifdef DEBUG_FONT_PERFORMANCE
        auto start = std::chrono::high_resolution_clock::now();
        std::cout << "FontStorage::FindOrCreate - Looking for font '" << fontName 
                  << "' size " << fontSize << std::endl;
#endif

        FontSizeCharacterList &fontSizeCharacterList = fontStorage[fontName];
        CharacterList& characterList = fontSizeCharacterList[fontSize];

        if (characterList.empty())
        {
#ifdef DEBUG_FONT_PERFORMANCE
            std::cout << "FontStorage::FindOrCreate - Character list empty, creating new one" << std::endl;
            auto createStart = std::chrono::high_resolution_clock::now();
#endif

            CharacterList::Create(fontName, fontSize, characterList); // TODO if we make characterList a parameter we do not need to copy, we can use it directly

#ifdef DEBUG_FONT_PERFORMANCE
            auto createEnd = std::chrono::high_resolution_clock::now();
            auto createDuration = std::chrono::duration_cast<std::chrono::microseconds>(createEnd - createStart);
            std::cout << "FontStorage::FindOrCreate - CharacterList::Create() took " << createDuration.count() 
                      << "μs" << std::endl;
#endif
        }
#ifdef DEBUG_FONT_PERFORMANCE
        else
        {
            std::cout << "FontStorage::FindOrCreate - Using cached character list" << std::endl;
        }
#endif

#ifdef DEBUG_FONT_PERFORMANCE
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "FontStorage::FindOrCreate - Total operation took " << duration.count() << "μs" << std::endl;
#endif

        return characterList;
    }

    void FontStorage::Clear()
    {
        fontStorage.clear();
    }
}
