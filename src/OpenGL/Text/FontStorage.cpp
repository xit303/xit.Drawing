#include <OpenGL/Text/FontStorage.h>

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
        FontSizeCharacterList &fontSizeCharacterList = fontStorage[fontName];
        CharacterList& characterList = fontSizeCharacterList[fontSize];

        if (characterList.empty())
        {
            CharacterList::Create(fontName, fontSize, characterList); // TODO if we make characterList a parameter we do not need to copy, we can use it directly
        }

        return characterList;
    }

    void FontStorage::Clear()
    {
        fontStorage.clear();
    }
}
