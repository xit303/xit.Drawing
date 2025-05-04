#pragma once

#include <string>

namespace xit::Drawing
{
    class FontProperty
    {
    private:
        std::string fontName;
        int fontSize;
        bool needMeasureFont;

    protected:
        virtual void OnFontSizeChanged() {}

        __always_inline const bool GetNeedMeasureFont() const { return needMeasureFont; }
        void SetNeedMeasureFont(bool value) { needMeasureFont = value; }

    public:
        FontProperty();

        __always_inline const std::string &GetFontName() const { return fontName; }
        void SetFontName(const std::string &value);

        __always_inline int GetFontSize() const { return fontSize; }
        void SetFontSize(int value);
    };
}