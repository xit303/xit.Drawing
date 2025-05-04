#pragma once

#include <Drawing/UIDefaults.h>
#include <Drawing/Container.h>
#include <Drawing/Label.h>
#include <Drawing/Border.h>
// #include <Input/Command.h>
// #include <Input/ICommandTarget.h>

namespace xit::Drawing
{
    // internal class Thumb : Visual
    //{

    //}

    // internal class Track : Visual
    //{

    //}

    class Switch : public Container //, public ICommandTarget
    {
    private:
        Label label;
        Label description;
        Border trackBorder;
        Border thumbBorder;

    protected:
        void OnIsActiveChanged(EventArgs &e) override;
        void OnNameChanged(EventArgs &e) override;

    public:
        const std::string &GetText() const { return label.GetText(); }
        inline void SetText(const std::string &value) { label.SetText(value); }

        // inline std::string GetTextSource() { return label.TextSource(); }
        // inline void SetTextSource(const std::string &value) { label.SetTextSource(value); }
        // inline void SetDescriptionTextSource(const std::string &value) { description.SetTextSource(value); }

        /*inline std::string GetDefaultText() { return label.DefaultText(); }
        inline void SetDefaultText(const std::string& value) { label.SetDefaultText(value); }*/

        void SetVisualState(const std::string &value) override;

        Switch();
        Switch(const std::string &name, const std::string &defaultText);
        Switch(const std::string &name, const std::string &defaultText, int column, int row);
    };
}
