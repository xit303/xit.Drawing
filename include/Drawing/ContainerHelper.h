#pragma once

#include <Drawing/ContainerBase.h>
#include <Drawing/Visual.h>

namespace xit::Drawing::Utils
{
    // Utility class to help with container content management
    class ContainerHelper
    {
    public:
        // Force refresh all children in a container
        static void RefreshAllChildren(ContainerBase* container);
        
        // Ensure all children are properly sized and positioned
        static void ValidateChildrenLayout(ContainerBase* container);
        
        // Remove and re-add all children (sometimes fixes stuck layouts)
        static void ResetChildren(ContainerBase* container);
        
        // Check if children are properly connected to parent
        static bool ValidateParentChildRelationships(ContainerBase* container);
        
        // Force measure and arrange for container and all children
        static void ForceMeasureAndArrange(ContainerBase* container, const Rectangle& bounds);
    };
}
