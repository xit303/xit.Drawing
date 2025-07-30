#pragma once

#include <Event.h>

namespace xit::Drawing::VisualBase
{
    class ParentProperty
    {
    private:
        ParentProperty *parent;

        virtual void HandleParentChanged()
        {
            EventArgs e;
            ParentChanged(*this, e);
            OnParentChanged(e);
        }

    protected:
        virtual void OnParentChanged(EventArgs &e) { (void)e; }


    public:
        ParentProperty()
        {
            parent = nullptr;
        }

        Event<ParentProperty &, EventArgs &> ParentChanged;

        /*!
         * @brief
         */
        ParentProperty *GetParent() { return parent; }

        /*!
         * @brief
         */
        void SetParent(ParentProperty *value) // TODO make this const and parent mutable? I do not likt the idea but what else could we do here?
        {
            if (parent != value)
            {
                parent = value;
                HandleParentChanged();
            }
        }
    };
} // namespace xit::Drawing::VisualBase
