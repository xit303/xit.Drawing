#include <Drawing/Visual.h>
// #include <Drawing/Visual.h>
#include <Drawing/Brushes/ImageBrush.h>
#include <Drawing/VisualBase/LayoutManager.h>

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
        const ParentProperty* parentProp = GetParent();
        if (parentProp)
        {
            // Try to cast parent to LayoutManager to call OnChildInvalidated
            LayoutManager* parentLayout = dynamic_cast<LayoutManager*>(const_cast<ParentProperty*>(parentProp));
            if (parentLayout)
            {
                parentLayout->OnChildInvalidated(this);
            }
        }
    }

    //******************************************************************************
    // Protected
    //******************************************************************************
}
