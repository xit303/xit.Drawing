#include <Drawing/ContainerHelper.h>
#include <Drawing/DebugUtils.h>
#include <iostream>

namespace xit::Drawing::Utils
{
    void ContainerHelper::RefreshAllChildren(ContainerBase* container)
    {
        if (!container) return;
        
        std::cout << "Refreshing all children in container: " << container->GetName() << std::endl;
        
        for (Visual* child : container->GetChildren())
        {
            child->ForceInvalidate();
        }
        
        container->ForceInvalidate();
    }
    
    void ContainerHelper::ValidateChildrenLayout(ContainerBase* container)
    {
        if (!container) return;
        
        std::cout << "Validating children layout for: " << container->GetName() << std::endl;
        
        for (Visual* child : container->GetChildren())
        {
            auto issues = Debug::LayoutDiagnostics::CheckCommonIssues(child);
            if (!issues.empty())
            {
                std::cout << "Child " << child->GetName() << " has issues:" << std::endl;
                for (const auto& issue : issues)
                {
                    std::cout << "  - " << issue << std::endl;
                }
            }
        }
    }
    
    void ContainerHelper::ResetChildren(ContainerBase* container)
    {
        if (!container) return;
        
        std::cout << "Resetting children for container: " << container->GetName() << std::endl;
        
        // Store children temporarily
        auto children = container->GetChildren();
        
        // Remove all children
        for (Visual* child : children)
        {
            container->RemoveChild(child);
        }
        
        // Re-add all children
        for (Visual* child : children)
        {
            container->AddChild(child);
        }
        
        container->ForceInvalidate();
    }
    
    bool ContainerHelper::ValidateParentChildRelationships(ContainerBase* container)
    {
        if (!container) return false;
        
        bool allValid = true;
        
        for (Visual* child : container->GetChildren())
        {
            const ParentProperty* parent = child->GetParent();
            if (parent != container)
            {
                std::cout << "WARNING: Child " << child->GetName() 
                         << " has incorrect parent reference!" << std::endl;
                allValid = false;
            }
        }
        
        return allValid;
    }
    
    void ContainerHelper::ForceMeasureAndArrange(ContainerBase* container, const Rectangle& bounds)
    {
        if (!container) return;
        
        std::cout << "Force measure and arrange for: " << container->GetName() << std::endl;
        
        // Force measure
        container->Measure(bounds.GetSize());
        
        // Force update/arrange
        container->Update(bounds);
        
        // Ensure all children are also updated
        for (Visual* child : container->GetChildren())
        {
            child->ForceInvalidate();
        }
    }
}
