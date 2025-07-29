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
        
        // Copy constructor - deep copy the visual states
        VisualStateGroup(const VisualStateGroup& other) : NameProperty(other)
        {
            for (T* state : other.visualStates)
            {
                visualStates.push_back(new T(*state));
            }
        }
        
        // Copy assignment operator
        VisualStateGroup& operator=(const VisualStateGroup& other)
        {
            if (this != &other)
            {
                // Clean up existing states
                for (T* state : visualStates)
                {
                    delete state;
                }
                visualStates.clear();
                
                // Copy name
                NameProperty::operator=(other);
                
                // Deep copy visual states
                for (T* state : other.visualStates)
                {
                    visualStates.push_back(new T(*state));
                }
            }
            return *this;
        }

    public:
        VisualStateGroup(const std::string &name) : NameProperty(name) {}

        // Add virtual destructor to properly clean up visual states
        virtual ~VisualStateGroup()
        {
            for (T *state : visualStates)
            {
                delete state;
            }
            visualStates.clear();
        }

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