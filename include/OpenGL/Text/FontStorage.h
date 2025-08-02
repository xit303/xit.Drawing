#pragma once

#include <map>
#include <OpenGL/Text/CharacterList.h>

namespace xit::OpenGL
{
    class FontStorage
    {
    private:
        class FontSizeCharacterList : public std::map<int, CharacterList>
        {
        public:
            FontSizeCharacterList();
            FontSizeCharacterList(const FontSizeCharacterList& other);

            FontSizeCharacterList& operator=(const FontSizeCharacterList& other);

            bool operator==(const FontSizeCharacterList& other) const = default;
        };

        static std::map<std::string, FontSizeCharacterList>& GetFontStorageMap();

    public:
        static CharacterList& FindOrCreate(const std::string& fontName, int fontSize);

        static void Clear();
    };
}
using namespace xit::OpenGL;
