#pragma once

#include <iostream>
#include <string>
#include <vector>

// Forward declarations
namespace xit::Drawing 
{
    class Visual;
    class Window;
    class TextBox;
    namespace VisualBase {
        class LayoutManager;
    }
}

namespace xit::Drawing::Debug
{
    // Debug flags for different subsystems
    enum class DebugFlags : uint32_t
    {
        None = 0,
        LayoutManager = 1 << 0,     // Layout invalidation and updates
        Window = 1 << 1,            // Window update cycles
        TextBox = 1 << 2,           // TextBox password functionality
        Visual = 1 << 3,            // Visual tree operations
        All = 0xFFFFFFFF
    };
    
    // Helper class to diagnose layout and rendering issues
    class LayoutDiagnostics
    {
    public:
        // Enable/disable specific debug output
        static void SetDebugFlags(DebugFlags flags);
        static void EnableDebugFlag(DebugFlags flag);
        static void DisableDebugFlag(DebugFlags flag);
        static bool IsDebugEnabled(DebugFlags flag);
        
        // Legacy compatibility
        static void SetDebugEnabled(bool enabled);
        
        // Convenience functions for common debug scenarios
        static void EnableTextBoxDebuggingOnly();
        static void DisableAllDebugging();
        
        // Test password TextBox functionality
        static void TestPasswordTextBox();
        
        // Test actual TextBox password functionality with real instance
        static void TestPasswordTextBoxInstance(xit::Drawing::TextBox* textBox);
        
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
        static uint32_t debugFlags;
    };
}
