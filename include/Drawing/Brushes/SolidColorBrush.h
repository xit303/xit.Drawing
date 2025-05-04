#pragma once

// #include "Color.h"
#include <Drawing/Properties/ColorProperty.h>
#include <Drawing/Brushes/BrushBase.h>

namespace xit::Drawing
{
    class SolidColorBrush : public BrushBase, public ColorProperty
    {
    public:
        std::string Argb() { return ToHexString(); }
        void Argb(const std::string &value)
        {
            color = FromHtml(value);
        }

        SolidColorBrush() {}
        // SolidColorBrush(Drawing::Color *color);
        SolidColorBrush(const glm::vec4 &color) : ColorProperty(color) {}
        SolidColorBrush(unsigned int hexColor) : ColorProperty(hexColor) {}
        SolidColorBrush(int intColor) : ColorProperty(intColor) {}
        SolidColorBrush(SolidColorBrush &other) : ColorProperty(other) {}
        SolidColorBrush(const SolidColorBrush *other) : ColorProperty(other) {}

        SolidColorBrush &operator=(SolidColorBrush &other)
        {
            this->SetOpacity(other.GetOpacity());
            this->color = other.color;
            return *this;
        }

        virtual BrushBase *Clone() override
        {
            return new SolidColorBrush(*this);
        }
    };
}

using namespace xit::Drawing;
