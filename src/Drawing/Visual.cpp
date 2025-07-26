#include <Drawing/Visual.h>
// #include <Drawing/Visual.h>
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
    {
        tag = nullptr;
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

    void Visual::NotifyParentOfInvalidation()
    {
        // Notify the parent about this child's invalidation for background buffer
        const ParentProperty *parentProp = GetParent();

#ifdef DEBUG_VISUAL
        std::cout << "NotifyParentOfInvalidation: " << GetName()
                  << " parent=" << (parentProp ? "exists" : "null") << std::endl;
#endif

        if (parentProp)
        {
            // Try to cast parent to LayoutManager to call OnChildInvalidated
            LayoutManager *parentLayout = dynamic_cast<LayoutManager *>(const_cast<ParentProperty *>(parentProp));
            if (parentLayout)
            {
#ifdef DEBUG_VISUAL
                std::cout << "  -> Notifying parent LayoutManager: " << parentLayout->GetName() << std::endl;
                std::cout << "  -> Calling OnChildInvalidated on parent: " << parentLayout->GetName() << std::endl;
#endif

                parentLayout->OnChildInvalidated(this);
            }
            else
            {
                // Fallback: try to invalidate parent directly if it's also a Visual
                Visual *parentVisual = dynamic_cast<Visual *>(const_cast<ParentProperty *>(parentProp));
                if (parentVisual)
                {
#ifdef DEBUG_VISUAL
                    std::cout << "  -> Fallback invalidating parent Visual: " << parentVisual->GetName() << std::endl;
#endif
                    parentVisual->Invalidate();
                }
#ifdef DEBUG_VISUAL
                std::cout << "  -> Parent exists but can't cast to LayoutManager or Visual" << std::endl;
#endif
            }
        }

        // Always ensure scene knows about the invalidation
        Scene2D::CurrentScene().Invalidate(this);
    }

    //******************************************************************************
    // Protected
    //******************************************************************************
}
