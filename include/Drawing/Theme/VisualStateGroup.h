#pragma once

#include <vector>
#include <Properties/NameProperty.h>

namespace xit::Drawing
{
    template <class T>
    class VisualStateGroup : public Properties::NameProperty
    {
    protected:
        std::vector<T *> visualStates;

        VisualStateGroup() {}

    public:
        VisualStateGroup(const std::string &name) : NameProperty(name) {}

        __always_inline size_t Size() { return visualStates.size(); }

        void AddState(T *state)
        {
            if (std::find(visualStates.begin(), visualStates.end(), state) == visualStates.end())
                visualStates.push_back(state);
        }

        T *GetVisualState(const std::string &name)
        {
            for (T *state : visualStates)
            {
                if (state->GetName() == name)
                    return state;
            }
            return nullptr;
        }
    };
}