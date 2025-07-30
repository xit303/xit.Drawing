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
        {
            visualState = "Normal";
        }

        virtual void SetVisualState(const std::string &value)
        {
            if (visualState != value)
            {
                visualState = value;
                UpdateBrushVisualState();
                UpdateLayoutVisualState();

                EventArgs e;
                OnVisualStateChanged(e);
            }
        }

        virtual void UpdateBrushVisualState() = 0;
        virtual void UpdateLayoutVisualState() = 0;

        inline std::string GetVisualState() const { return visualState; }
    };
} // namespace xit::Drawing::VisualBase
