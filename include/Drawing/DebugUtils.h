#pragma once

#include <iostream>
#include <string>
#include <vector>

// Forward declarations
namespace xit::Drawing 
{
    class Visual;
    class Window;
    namespace VisualBase {
        class LayoutManager;
    }
}

namespace xit::Drawing::Debug
{
    // Helper class to diagnose layout and rendering issues
    class LayoutDiagnostics
    {
    public:
        // Enable/disable debug output
        static void SetDebugEnabled(bool enabled);
        static bool IsDebugEnabled();
        
        // Print visual tree hierarchy
        static void PrintVisualTree(const xit::Drawing::Visual* root, int depth = 0);
        
        // Print layout information for a visual
        static void PrintLayoutInfo(const xit::Drawing::VisualBase::LayoutManager* layout);
        
        // Print invalidation status
        static void PrintInvalidationStatus(const xit::Drawing::VisualBase::LayoutManager* layout);
        
        // Force all child visuals to invalidate (nuclear option)
        static void ForceInvalidateTree(xit::Drawing::Visual* root);
        
        // Check for common layout problems
        static std::vector<std::string> CheckCommonIssues(const xit::Drawing::Visual* visual);
        
        // Diagnose window update chain specifically
        static void DiagnoseWindowUpdateChain(xit::Drawing::Window* window);
        
        // Force window and all its content to update
        static void ForceWindowUpdate(xit::Drawing::Window* window);
        
        // Test window update chain functionality
        static void TestWindowUpdates(xit::Drawing::Window* window);
        
    private:
        static bool debugEnabled;
    };
}
