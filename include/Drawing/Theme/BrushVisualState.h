#pragma once

#include <Drawing/Brushes/BrushBase.h>

namespace xit::Drawing
{
    class BrushVisualState : public Properties::NameProperty
    {
        BrushBase *background;
        BrushBase *foreground;
        BrushBase *borderBrush;

    public:
        const BrushBase *GetBackground() const { return background; }
        const BrushBase *GetForeground() const { return foreground; }
        const BrushBase *GetBorderBrush() const { return borderBrush; }

        BrushVisualState() {}
        explicit BrushVisualState(const std::string &name)
            : NameProperty(name), background(nullptr),
              foreground(nullptr),
              borderBrush(nullptr)
        {
        }
        BrushVisualState(const std::string &name, BrushBase *background, BrushBase *foreground, BrushBase *borderBrush)
            : BrushVisualState(name)
        {
            this->background = background;
            this->foreground = foreground;
            this->borderBrush = borderBrush;
        }

        BrushVisualState(BrushVisualState &other)
            : NameProperty(other), background(other.background), foreground(other.foreground), borderBrush(other.borderBrush)
        {
        }

        BrushVisualState(const BrushVisualState &other)
            : NameProperty(other), background(other.background), foreground(other.foreground), borderBrush(other.borderBrush)
        {
        }

        bool operator==(const BrushVisualState &other)
        {
            return (this == &other); // || background == other.background;
        }
        bool operator!=(const BrushVisualState &other)
        {
            return !(this == &other); // || background == other.background;
        }

        BrushVisualState &operator=(const BrushVisualState &other)
        {
            this->SetName(other.GetName());
            this->background = other.background;
            this->foreground = other.foreground;
            this->borderBrush = other.borderBrush;
            return *this;
        }

        BrushVisualState &operator=(BrushVisualState &other)
        {
            this->SetName(other.GetName());
            this->background = other.background;
            this->foreground = other.foreground;
            this->borderBrush = other.borderBrush;
            return *this;
        }
    };
}
