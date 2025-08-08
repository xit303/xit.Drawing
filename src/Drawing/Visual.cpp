#include <Drawing/Visual.h>
#include <Drawing/Window.h>
#include <Drawing/Brushes/ImageBrush.h>
#include <Drawing/VisualBase/LayoutManager.h>
#include <Drawing/DebugUtils.h>

#include <OpenGL/Graphics.h>
#include <OpenGL/Scene2D.h>

namespace xit::Drawing
{
    //******************************************************************************
    // Properties
    //******************************************************************************

    //******************************************************************************
    // Constructor
    //******************************************************************************

    Visual::Visual()
        : tag(nullptr)
    {
    }

    Window *Visual::GetWindow()
    {
        Visual *current = this;
        while (current->GetParent() != nullptr)
        {
            current = static_cast<Visual *>(current->GetParent());
        }
        return dynamic_cast<Window *>(current);
    }

    //******************************************************************************
    // Private
    //******************************************************************************

    //******************************************************************************
    // Protected overrides
    //******************************************************************************

    void Visual::OnNameChanged(EventArgs &e)
    {
        if (!GetName().empty())
        {
            // TODO Controller::Register(this);
            // TODO SetToolTipSource(GetName() + "ToolTip");
        }
    }

    void Visual::NotifyWindowOfInvalidation()
    {
        // Notify the window about this child's invalidation for background buffer
        if (auto *window = GetWindow())
        {
#ifdef DEBUG_VISUAL
            std::cout << "[DEBUG] Visual::NotifyWindowOfInvalidation: " << GetName()
                      << " window=" << (window ? "exists" : "null") << std::endl;
#endif
#ifdef DEBUG_VISUAL_STATES
            std::cout << "[DEBUG] Visual::NotifyWindowOfInvalidation() - " << GetName() 
                      << " notifying window, bounds(" << GetBounds().GetLeft() << "," 
                      << GetBounds().GetTop() << "," << GetBounds().GetWidth() << "," 
                      << GetBounds().GetHeight() << ")" << std::endl;
#endif
            window->InvalidateRegion(this, GetBounds());
        }
        else
        {
#ifdef DEBUG_VISUAL
            std::cout << "[DEBUG] Visual::NotifyWindowOfInvalidation: No window found for " << GetName() << std::endl;
#endif
#ifdef DEBUG_VISUAL_STATES
            std::cout << "[DEBUG] Visual::NotifyWindowOfInvalidation() - " << GetName() 
                      << " ERROR: No window found!" << std::endl;
#endif
        }
    }

    //******************************************************************************
    // Protected
    //******************************************************************************
}
