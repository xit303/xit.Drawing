#pragma once

#include <Properties/NameProperty.h>

namespace xit::Drawing
{
    class BrushBase : public Properties::NameProperty
    {
    private:
        double opacity;

    protected:
        /*void OnPropertyChanged(Visual* sender, PropertyChangedEventArgs* e)
        {
            HasBrushChanged = true;

            Object::OnPropertyChanged(sender, e);
        }*/

    public:
        const double GetOpacity() const { return opacity; }
        void SetOpacity(double value)
        {
            if (opacity != value)
            {
                opacity = value;
                // NotifyPropertyChanged();
            }
        }

        bool HasBrushChanged;

        BrushBase()
            : NameProperty(), opacity(1.0), HasBrushChanged(true)
        {
        }

        BrushBase(const std::string &name, double opacity)
            : NameProperty(name), opacity(opacity), HasBrushChanged(false)
        {
        }

        BrushBase(BrushBase &other)
            : NameProperty(other), opacity(other.opacity), HasBrushChanged(false)
        {
        }

        BrushBase(const BrushBase &other)
            : NameProperty(other), opacity(other.opacity), HasBrushChanged(false)
        {
        }

        virtual ~BrushBase() {}

        bool operator ==(const BrushBase &other)
        {
            return this == &other;
        }

        bool operator !=(const BrushBase &other)
        {
            return !(this == &other);
        }

        BrushBase &operator=(const BrushBase &other)
        {
            this->HasBrushChanged = false;
            this->opacity = other.opacity;
            return *this;
        }

        virtual bool Empty() const
        {
            return !HasBrushChanged && (opacity == 1);
        }

        virtual BrushBase *Clone()
        {
            return new BrushBase(GetName(), opacity);
        }

        // static bool IsSameBrush(const BrushBase &first, const BrushBase &second);
    };
}
using namespace xit::Drawing;
