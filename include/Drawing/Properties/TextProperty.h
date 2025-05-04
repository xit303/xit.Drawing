#pragma once

#include <string>
#include <Drawing/TextWrapping.h>

namespace xit::Drawing
{
    class TextProperty
    {
    private:
        TextWrapping textWrapping;
        bool needMeasureText;
        std::string text;

    protected:
        virtual void OnTextChanged() {}
        virtual void OnTextWrappingChanged() {}

        __always_inline const bool GetNeedMeasureText() { return needMeasureText; }
        void SetNeedMeasureText(bool value) { needMeasureText = value; }

    public:
        TextProperty();

        __always_inline const std::string &GetText() const { return text; }
        void SetText(const std::string &value);

        __always_inline const TextWrapping &GetTextWrapping() const { return textWrapping; }
        void SetTextWrapping(const TextWrapping &value);
    };
}
