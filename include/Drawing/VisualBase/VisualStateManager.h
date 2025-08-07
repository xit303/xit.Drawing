#pragma once

#include <string>

namespace xit::Drawing::VisualBase
{
    class VisualStateManager
    {
    protected:
        std::string visualState;

        virtual void OnVisualStateChanged(EventArgs &e) { (void)e; }

    public:
        VisualStateManager()
            : visualState("Normal")
        {
        }

        virtual void SetVisualState(const std::string &value)
        {
            if (visualState != value)
            {
                visualState = value;
                UpdateBrushVisualState();

                // Only update layout if there are actual layout changes defined for this state
                if (ShouldUpdateLayoutForState(value))
                {
                    UpdateLayoutVisualState();
                }

                EventArgs e;
                OnVisualStateChanged(e);
            }
        }

        // Virtual method to determine if layout should be updated for a given state
        // Derived classes can override this to be more intelligent about when layout updates are needed
        virtual bool ShouldUpdateLayoutForState(const std::string &state)
        {
            // Default behavior: always update layout (maintaining backward compatibility)
            // Derived classes like Renderable can override this to check if theme has layout for the state
            return true;
        }

        virtual void UpdateBrushVisualState() = 0;
        virtual void UpdateLayoutVisualState() = 0;

        inline std::string GetVisualState() const { return visualState; }
    };
} // namespace xit::Drawing::VisualBase
