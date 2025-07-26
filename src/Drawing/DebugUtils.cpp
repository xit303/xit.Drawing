#include <Drawing/DebugUtils.h>
#include <Drawing/Visual.h>
#include <Drawing/VisualBase/LayoutManager.h>
#include <Drawing/ContainerBase.h>
#include <Drawing/Properties/ParentProperty.h>
#include <Drawing/Window.h>
#include <Drawing/TextBox.h>

namespace xit::Drawing::Debug
{
    // Static debug flags
    uint32_t LayoutDiagnostics::debugFlags = 0;

    void LayoutDiagnostics::SetDebugFlags(DebugFlags flags)
    {
        debugFlags = static_cast<uint32_t>(flags);
    }

    void LayoutDiagnostics::EnableDebugFlag(DebugFlags flag)
    {
        debugFlags |= static_cast<uint32_t>(flag);
    }

    void LayoutDiagnostics::DisableDebugFlag(DebugFlags flag)
    {
        debugFlags &= ~static_cast<uint32_t>(flag);
    }

    bool LayoutDiagnostics::IsDebugEnabled(DebugFlags flag)
    {
        return (debugFlags & static_cast<uint32_t>(flag)) != 0;
    }

    void LayoutDiagnostics::SetDebugEnabled(bool enabled)
    {
        if (enabled)
        {
            debugFlags = static_cast<uint32_t>(DebugFlags::All);
        }
        else
        {
            debugFlags = static_cast<uint32_t>(DebugFlags::None);
        }
    }

    void LayoutDiagnostics::EnableTextBoxDebuggingOnly()
    {
        debugFlags = static_cast<uint32_t>(DebugFlags::TextBox);
    }

    void LayoutDiagnostics::DisableAllDebugging()
    {
        debugFlags = static_cast<uint32_t>(DebugFlags::None);
    }

    void LayoutDiagnostics::PrintVisualTree(const xit::Drawing::Visual *root, int depth)
    {
        // if (!IsDebugEnabled(DebugFlags::Visual)) return;
        if (!root)
        {
            std::cout << "Root visual is null!" << std::endl;
            return;
        }

        std::string indent(depth * 2, ' ');
        std::cout << indent << "Visual: " << root->GetName()
                  << " Type: " << typeid(*root).name()
                  << " Visible: " << (root->GetIsVisible() ? "true" : "false")
                  << " Size: " << root->GetActualWidth() << "x" << root->GetActualHeight()
                  << " Pos: (" << root->GetLeft() << "," << root->GetTop() << ")"
                  << std::endl;

        // Try to get children if this is a container
        const xit::Drawing::ContainerBase *container = dynamic_cast<const xit::Drawing::ContainerBase *>(root);
        if (container)
        {
            for (const xit::Drawing::Visual *child : container->GetChildren())
            {
                PrintVisualTree(child, depth + 1);
            }
        }
    }

    void LayoutDiagnostics::PrintLayoutInfo(const xit::Drawing::VisualBase::LayoutManager *layout)
    {
        if (!IsDebugEnabled(DebugFlags::LayoutManager))
            return;

        if (!layout)
        {
            std::cout << "LayoutManager is null!" << std::endl;
            return;
        }

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

    void LayoutDiagnostics::PrintInvalidationStatus(const xit::Drawing::VisualBase::LayoutManager *layout)
    {
        if (!IsDebugEnabled(DebugFlags::LayoutManager))
            return;

        if (!layout)
        {
            std::cout << "LayoutManager is null!" << std::endl;
            return;
        }

        std::cout << "=== Invalidation Status for: " << layout->GetName() << " ===" << std::endl;
        std::cout << "  Invalidated: " << (layout->GetInvalidated() ? "true" : "false") << std::endl;
        std::cout << "  Need Width Recalc: " << (layout->GetNeedWidthRecalculation() ? "true" : "false") << std::endl;
        std::cout << "  Need Height Recalc: " << (layout->GetNeedHeightRecalculation() ? "true" : "false") << std::endl;
        std::cout << "  Need Left Recalc: " << (layout->GetNeedLeftRecalculation() ? "true" : "false") << std::endl;
        std::cout << "  Need Top Recalc: " << (layout->GetNeedTopRecalculation() ? "true" : "false") << std::endl;
        std::cout << "================================" << std::endl;
    }

    void LayoutDiagnostics::DiagnoseWindowUpdateChain(xit::Drawing::Window *window)
    {
        // if (!IsDebugEnabled(DebugFlags::Window)) return;

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
        xit::Drawing::Visual *content = window->GetContent();
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

    std::vector<std::string> LayoutDiagnostics::CheckCommonIssues(const xit::Drawing::Visual *visual)
    {
        std::vector<std::string> issues;

        if (!IsDebugEnabled(DebugFlags::Visual))
        {
            return issues; // No issues to check if debugging is disabled
        }

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

    void LayoutDiagnostics::TestPasswordTextBox()
    {
        if (!IsDebugEnabled(DebugFlags::TextBox))
            return;

        std::cout << "=== PASSWORD TEXTBOX TEST ===" << std::endl;

        // Note: This test requires actual TextBox instance to work properly
        std::cout << "Password TextBox functionality test:" << std::endl;
        std::cout << "1. SetIsPassword(true) should:" << std::endl;
        std::cout << "   - Call UpdateVisibleText()" << std::endl;
        std::cout << "   - Call Invalidate() to trigger redraw" << std::endl;
        std::cout << "   - Show '*' characters instead of actual text" << std::endl;
        std::cout << "2. SetText() should:" << std::endl;
        std::cout << "   - Update internal text normally" << std::endl;
        std::cout << "   - Call UpdateVisibleText() which calls Invalidate()" << std::endl;
        std::cout << "   - Display asterisks in password mode" << std::endl;
        std::cout << "3. ShowPasswordButton toggle should:" << std::endl;
        std::cout << "   - Call UpdateVisibleText() which calls Invalidate()" << std::endl;
        std::cout << "   - Switch between actual text and asterisks" << std::endl;

        std::cout << "\nFixed invalidation issues in:" << std::endl;
        std::cout << "- SetIsPassword(): Now calls UpdateVisibleText() + Invalidate()" << std::endl;
        std::cout << "- UpdateVisibleText(): Now calls Invalidate() after SetText()" << std::endl;
        std::cout << "- ShowPasswordButton_ActiveChanged(): Calls UpdateVisibleText() (which invalidates)" << std::endl;

        std::cout << "=== PASSWORD TEST INFO COMPLETE ===\n"
                  << std::endl;
    }
}
