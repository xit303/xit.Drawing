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

        if (xit::Drawing::Debug::LayoutDiagnostics::IsDebugEnabled(xit::Drawing::Debug::DebugFlags::Visual))
        {
            std::cout << "NotifyParentOfInvalidation: " << GetName()
                      << " parent=" << (parentProp ? "exists" : "null") << std::endl;
        }

        if (parentProp)
        {
            // Try to cast parent to LayoutManager to call OnChildInvalidated
            LayoutManager *parentLayout = dynamic_cast<LayoutManager *>(const_cast<ParentProperty *>(parentProp));
            if (parentLayout)
            {
                if (xit::Drawing::Debug::LayoutDiagnostics::IsDebugEnabled(xit::Drawing::Debug::DebugFlags::Visual))
                {
                    std::cout << "  -> Notifying parent LayoutManager: " << parentLayout->GetName() << std::endl;
                    std::cout << "  -> Calling OnChildInvalidated on parent: " << parentLayout->GetName() << std::endl;
                }

                parentLayout->OnChildInvalidated(this);
            }
            else
            {
                // Fallback: try to invalidate parent directly if it's also a Visual
                Visual *parentVisual = dynamic_cast<Visual *>(const_cast<ParentProperty *>(parentProp));
                if (parentVisual)
                {
                    if (xit::Drawing::Debug::LayoutDiagnostics::IsDebugEnabled(xit::Drawing::Debug::DebugFlags::Visual))
                    {
                        std::cout << "  -> Fallback invalidating parent Visual: " << parentVisual->GetName() << std::endl;
                    }
                    parentVisual->Invalidate();
                }
                if (xit::Drawing::Debug::LayoutDiagnostics::IsDebugEnabled(xit::Drawing::Debug::DebugFlags::Visual))
                {
                    std::cout << "  -> Parent exists but can't cast to LayoutManager or Visual" << std::endl;
                }
                else
                {
                    std::cout << "  -> Parent exists but can't cast to LayoutManager or Visual" << std::endl;
                }
            }
        }

        // Always ensure scene knows about the invalidation
        Scene2D::CurrentScene().Invalidate(this);
    }

    //******************************************************************************
    // Protected
    //******************************************************************************
}
