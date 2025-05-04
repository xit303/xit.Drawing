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
        {
            HasBrushChanged = true;
            opacity = 1;
        }

        BrushBase(const std::string &name, double opacity)
            : NameProperty(name)
        {
            HasBrushChanged = false;
            this->opacity = opacity;
        }

        BrushBase(BrushBase &other)
            : NameProperty(other)
        {
            HasBrushChanged = false;
            this->opacity = other.opacity;
        }

        BrushBase(const BrushBase &other)
            : NameProperty(other)
        {
            HasBrushChanged = false;
            this->opacity = other.opacity;
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
