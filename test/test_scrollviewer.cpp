#include <iostream>
#include <Drawing/ScrollViewer.h>
#include <Drawing/Label.h>

using namespace xit::Drawing;

int main()
{
    std::cout << "=== ScrollViewer Direct Test ===" << std::endl;
    
    ScrollViewer scrollViewer;
    
    // Add some content
    for (int i = 0; i < 5; i++)
    {
        Label* label = new Label();
        label->SetText("Test content line " + std::to_string(i));
        scrollViewer.AddChild(label);
    }
    
    std::cout << "Added " << scrollViewer.GetChildCount() << " children" << std::endl;
    
    // Test measurement
    Size availableSize(200, 100); // Small viewport
    std::cout << "Measuring with available size: " << availableSize.GetWidth() << "x" << availableSize.GetHeight() << std::endl;
    
    Size measured = scrollViewer.Measure(availableSize);
    std::cout << "Measured size returned: " << measured.GetWidth() << "x" << measured.GetHeight() << std::endl;
    std::cout << "Extent size: " << scrollViewer.GetExtentWidth() << "x" << scrollViewer.GetExtentHeight() << std::endl;
    
    // Test scroll conditions
    bool canScrollV = scrollViewer.GetExtentHeight() > 100; // our viewport height
    bool canScrollH = scrollViewer.GetExtentWidth() > 200;  // our viewport width
    
    std::cout << "Can scroll vertically: " << (canScrollV ? "YES" : "NO") << std::endl;
    std::cout << "Can scroll horizontally: " << (canScrollH ? "YES" : "NO") << std::endl;
    
    // Test scroll logic methods
    std::cout << "\n=== Testing Scroll Methods ===" << std::endl;
    
    std::cout << "Initial scroll margin top: " << scrollViewer.GetScrollMarginTop() << std::endl;
    
    scrollViewer.SetScrollMarginTop(-30);
    std::cout << "After setting to -30: " << scrollViewer.GetScrollMarginTop() << std::endl;
    
    scrollViewer.ScrollToBottom();
    std::cout << "After ScrollToBottom: " << scrollViewer.GetScrollMarginTop() << std::endl;
    
    scrollViewer.ScrollToTop();
    std::cout << "After ScrollToTop: " << scrollViewer.GetScrollMarginTop() << std::endl;
    
    std::cout << "\n=== Test Complete ===" << std::endl;
    
    return 0;
}
