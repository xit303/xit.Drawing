#pragma once

// #include <Event.h>
#include <Drawing/Label.h>

namespace xit
{
    class LabelProperty
    {
    private:
        bool showLabel;
        Label label;

    protected:
        __always_inline Label &GetLabel() { return label; }

        virtual void OnShowLabelChanged()
        {
            label.SetVisibility(showLabel ? Visibility::Visible : Visibility::Collapsed);
        }

    public:
        __always_inline const std::string &GetText() const { return label.GetText(); }
        inline void SetText(const std::string &value) { label.SetText(value); }

        // __always_inline const std::string &GetTextSource() const { return label.GetTextSource(); }
        // inline void SetTextSource(const std::string &value) { label.SetTextSource(value); }

        __always_inline const TextWrapping &GetTextWrapping() const { return label.GetTextWrapping(); }
        inline void SetTextWrapping(const TextWrapping &value) { label.SetTextWrapping(value); }

        __always_inline const std::string &GetFontName() const { return label.GetFontName(); }
        inline void SetFontName(const std::string &value) { label.SetFontName(value); }

        __always_inline const int GetFontSize() const { return label.GetFontSize(); }
        inline void SetFontSize(int value) { label.SetFontSize(value); }

        __always_inline const bool GetShowLabel() const { return showLabel; }
        void SetShowLabel(bool value)
        {
            if (showLabel != value)
            {
                showLabel = value;
                OnShowLabelChanged();
            }
        }

        LabelProperty() : showLabel(true) {}
        virtual ~LabelProperty() {}
    };
}