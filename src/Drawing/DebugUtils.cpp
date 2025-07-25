#include <Drawing/DebugUtils.h>
#include <Drawing/Visual.h>
#include <Drawing/VisualBase/LayoutManager.h>
#include <Drawing/ContainerBase.h>
#include <Drawing/Properties/ParentProperty.h>
#include <Drawing/Window.h>

namespace xit::Drawing::Debug
{
    bool LayoutDiagnostics::debugEnabled = false;
    
    void LayoutDiagnostics::SetDebugEnabled(bool enabled)
    {
        debugEnabled = enabled;
    }
    
    bool LayoutDiagnostics::IsDebugEnabled()
    {
        return debugEnabled;
    }
    
    void LayoutDiagnostics::PrintVisualTree(const xit::Drawing::Visual* root, int depth)
    {
        if (!root) return;
        
        std::string indent(depth * 2, ' ');
        std::cout << indent << "Visual: " << root->GetName() 
                  << " Type: " << typeid(*root).name()
                  << " Visible: " << (root->GetIsVisible() ? "true" : "false")
                  << " Size: " << root->GetActualWidth() << "x" << root->GetActualHeight()
                  << " Pos: (" << root->GetLeft() << "," << root->GetTop() << ")"
                  << std::endl;
        
        // Try to get children if this is a container
        const xit::Drawing::ContainerBase* container = dynamic_cast<const xit::Drawing::ContainerBase*>(root);
        if (container)
        {
            for (const xit::Drawing::Visual* child : container->GetChildren())
            {
                PrintVisualTree(child, depth + 1);
            }
        }
    }
    
    void LayoutDiagnostics::PrintLayoutInfo(const xit::Drawing::VisualBase::LayoutManager* layout)
    {
        if (!layout) return;
        
        std::cout << "=== Layout Info for: " << layout->GetName() << " ===" << std::endl;
        std::cout << "  Actual Size: " << layout->GetActualWidth() << "x" << layout->GetActualHeight() << std::endl;
        std::cout << "  Desired Size: " << layout->GetDesiredSize().GetWidth() << "x" << layout->GetDesiredSize().GetHeight() << std::endl;
        std::cout << "  Position: (" << layout->GetLeft() << "," << layout->GetTop() << ")" << std::endl;
        std::cout << "  Bounds: (" << layout->GetBounds().GetLeft() << "," << layout->GetBounds().GetTop() 
                  << "," << layout->GetBounds().GetWidth() << "," << layout->GetBounds().GetHeight() << ")" << std::endl;
        std::cout << "  Visibility: " << (int)layout->GetVisibility() << std::endl;
        std::cout << "  Margin: (" << layout->GetMargin().GetLeft() << "," << layout->GetMargin().GetTop() 
                  << "," << layout->GetMargin().GetRight() << "," << layout->GetMargin().GetBottom() << ")" << std::endl;
        std::cout << "  Padding: (" << layout->GetPadding().GetLeft() << "," << layout->GetPadding().GetTop() 
                  << "," << layout->GetPadding().GetRight() << "," << layout->GetPadding().GetBottom() << ")" << std::endl;
        std::cout << "================================" << std::endl;
    }
    
    void LayoutDiagnostics::PrintInvalidationStatus(const xit::Drawing::VisualBase::LayoutManager* layout)
    {
        if (!layout) return;
        
        std::cout << "=== Invalidation Status for: " << layout->GetName() << " ===" << std::endl;
        std::cout << "  Invalidated: " << (layout->GetInvalidated() ? "true" : "false") << std::endl;
        std::cout << "  Need Width Recalc: " << (layout->GetNeedWidthRecalculation() ? "true" : "false") << std::endl;
        std::cout << "  Need Height Recalc: " << (layout->GetNeedHeightRecalculation() ? "true" : "false") << std::endl;
        std::cout << "  Need Left Recalc: " << (layout->GetNeedLeftRecalculation() ? "true" : "false") << std::endl;
        std::cout << "  Need Top Recalc: " << (layout->GetNeedTopRecalculation() ? "true" : "false") << std::endl;
        std::cout << "================================" << std::endl;
    }
    
    void LayoutDiagnostics::ForceInvalidateTree(xit::Drawing::Visual* root)
    {
        if (!root) return;
        
        std::cout << "Force invalidating: " << root->GetName() << std::endl;
        root->ForceInvalidate();
        
        // Try to invalidate children if this is a container
        xit::Drawing::ContainerBase* container = dynamic_cast<xit::Drawing::ContainerBase*>(root);
        if (container)
        {
            for (xit::Drawing::Visual* child : container->GetChildren())
            {
                ForceInvalidateTree(child);
            }
        }
    }
    
    void LayoutDiagnostics::DiagnoseWindowUpdateChain(xit::Drawing::Window* window)
    {
        if (!window) 
        {
            std::cout << "Window is null!" << std::endl;
            return;
        }
        
        std::cout << "=== Window Update Chain Diagnosis ===" << std::endl;
        std::cout << "Window Name: " << window->GetName() << std::endl;
        std::cout << "Window Size: " << window->GetActualWidth() << "x" << window->GetActualHeight() << std::endl;
        std::cout << "Window Invalidated: " << (window->GetInvalidated() ? "true" : "false") << std::endl;
        std::cout << "Window Needs Recalc: W=" << (window->GetNeedWidthRecalculation() ? "true" : "false") 
                  << " H=" << (window->GetNeedHeightRecalculation() ? "true" : "false")
                  << " L=" << (window->GetNeedLeftRecalculation() ? "true" : "false")
                  << " T=" << (window->GetNeedTopRecalculation() ? "true" : "false") << std::endl;
        
        // Check content
        xit::Drawing::Visual* content = window->GetContent();
        if (content)
        {
            std::cout << "Content found: " << content->GetName() << std::endl;
            std::cout << "Content Size: " << content->GetActualWidth() << "x" << content->GetActualHeight() << std::endl;
            std::cout << "Content Invalidated: " << (content->GetInvalidated() ? "true" : "false") << std::endl;
            PrintVisualTree(content, 1);
        }
        else
        {
            std::cout << "NO CONTENT SET!" << std::endl;
        }
        std::cout << "================================" << std::endl;
    }
    
    void LayoutDiagnostics::ForceWindowUpdate(xit::Drawing::Window* window)
    {
        if (!window) return;
        
        std::cout << "Force updating window: " << window->GetName() << std::endl;
        
        // Force invalidate the window itself
        window->ForceInvalidate();
        
        // Force invalidate the content if it exists
        xit::Drawing::Visual* content = window->GetContent();
        if (content)
        {
            std::cout << "Force updating window content: " << content->GetName() << std::endl;
            ForceInvalidateTree(content);
        }
        
        // Also manually trigger the render
        std::cout << "Triggering window render" << std::endl;
        // Note: DoRender is likely private, so we trigger through invalidation
    }
    
    std::vector<std::string> LayoutDiagnostics::CheckCommonIssues(const xit::Drawing::Visual* visual)
    {
        std::vector<std::string> issues;
        
        if (!visual) 
        {
            issues.push_back("Visual is null");
            return issues;
        }
        
        // Check visibility
        if (!visual->GetIsVisible())
        {
            issues.push_back("Visual is not visible");
        }
        
        // Check size
        if (visual->GetActualWidth() <= 0 || visual->GetActualHeight() <= 0)
        {
            issues.push_back("Visual has zero or negative size");
        }
        
        // Check for infinite size requests
        if (visual->GetWidth() < -1 || visual->GetHeight() < -1)
        {
            issues.push_back("Visual has invalid width/height values");
        }
        
        return issues;
    }
    
    void LayoutDiagnostics::TestWindowUpdates(Window* window)
    {
        if (!window) return;
        
        std::cout << "\n=== WINDOW UPDATE TEST ===" << std::endl;
        
        // Step 1: Check current state
        std::cout << "Step 1: Current window state" << std::endl;
        LayoutDiagnostics::DiagnoseWindowUpdateChain(window);
        
        // Step 2: Force invalidation
        std::cout << "\nStep 2: Forcing window invalidation" << std::endl;
        LayoutDiagnostics::ForceWindowUpdate(window);
        
        // Step 3: Check if update propagated
        std::cout << "\nStep 3: Post-invalidation state" << std::endl;
        LayoutDiagnostics::DiagnoseWindowUpdateChain(window);
        
        std::cout << "=== WINDOW TEST COMPLETE ===\n" << std::endl;
    }
}
