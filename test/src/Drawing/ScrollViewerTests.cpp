#include <gtest/gtest.h>
#include <Drawing/ScrollViewer.h>
#include <Drawing/Label.h>

using namespace xit::Drawing;

class ScrollViewerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Add any setup code here
    }

    void TearDown() override
    {
        // Add any cleanup code here
    }
};

TEST_F(ScrollViewerTest, BasicScrollViewerConstruction)
{
    ScrollViewer scrollViewer;

    // Test basic properties
    EXPECT_FALSE(scrollViewer.IsScrollBarAlwaysVisible());
    EXPECT_EQ(scrollViewer.GetExtentWidth(), 0);
    EXPECT_EQ(scrollViewer.GetExtentHeight(), 0);
    EXPECT_EQ(scrollViewer.GetScrollMarginLeft(), 0);
    EXPECT_EQ(scrollViewer.GetScrollMarginTop(), 0);
}

TEST_F(ScrollViewerTest, ScrollViewerWithContent)
{
    ScrollViewer scrollViewer;
    Label *label = new Label();
    label->SetText("Test Content");

    // Add content to ScrollViewer
    scrollViewer.AddChild(label);

    // Test that content was added
    EXPECT_EQ(scrollViewer.GetChildCount(), 1);
    EXPECT_EQ(scrollViewer.GetChildAt(0), label);
}

TEST_F(ScrollViewerTest, ExtentCalculation)
{
    ScrollViewer scrollViewer;

    // Set a viewport size for measurement
    Size availableSize(300, 200);
    scrollViewer.Measure(availableSize);

    // Debug output should show extent calculation
    // std::cout << "Test - Available Size: " << availableSize.GetWidth() << "x" << availableSize.GetHeight() << std::endl;
    // std::cout << "Test - Extent: " << scrollViewer.GetExtentWidth() << "x" << scrollViewer.GetExtentHeight() << std::endl;

    // Basic extent size check
    EXPECT_GE(scrollViewer.GetExtentWidth(), 0);
    EXPECT_GE(scrollViewer.GetExtentHeight(), 0);
}

TEST_F(ScrollViewerTest, ScrollLogicMethods)
{
    ScrollViewer scrollViewer;

    // Test scroll position methods
    scrollViewer.SetScrollMarginTop(-50);
    EXPECT_EQ(scrollViewer.GetScrollMarginTop(), -50);

    scrollViewer.SetScrollMarginLeft(-30);
    EXPECT_EQ(scrollViewer.GetScrollMarginLeft(), -30);

    // Test scroll to methods
    scrollViewer.ScrollToTop();
    EXPECT_EQ(scrollViewer.GetScrollMarginTop(), 0);

    scrollViewer.ScrollToLeft();
    EXPECT_EQ(scrollViewer.GetScrollMarginLeft(), 0);
}

TEST_F(ScrollViewerTest, ScrollBarVisibility)
{
    ScrollViewer scrollViewer;

    // Test always visible mode
    scrollViewer.SetIsScrollBarAlwaysVisible(true);
    EXPECT_TRUE(scrollViewer.IsScrollBarAlwaysVisible());

    scrollViewer.SetIsScrollBarAlwaysVisible(false);
    EXPECT_FALSE(scrollViewer.IsScrollBarAlwaysVisible());
}

TEST_F(ScrollViewerTest, ScrollWithLargeContent)
{
    ScrollViewer scrollViewer;

    // Add a few labels to create some content
    for (int i = 0; i < 3; i++)
    {
        Label *label = new Label();
        label->SetText("Content line " + std::to_string(i));
        scrollViewer.AddChild(label);
    }

    // Set a small viewport size
    Size availableSize(200, 150);

    // std::cout << "Large Content Test:" << std::endl;
    // std::cout << "  - Adding " << scrollViewer.GetChildCount() << " children" << std::endl;
    // std::cout << "  - Measuring with size: " << availableSize.GetWidth() << "x" << availableSize.GetHeight() << std::endl;

    scrollViewer.Measure(availableSize);

    // std::cout << "  - Extent after measure: " << scrollViewer.GetExtentWidth() << "x" << scrollViewer.GetExtentHeight() << std::endl;

    // Test basic scroll position methods (these don't require Update)
    // std::cout << "  - Testing scroll position methods..." << std::endl;

    scrollViewer.SetScrollMarginTop(-50);
    // std::cout << "  - Set margin top to -50, actual: " << scrollViewer.GetScrollMarginTop() << std::endl;

    scrollViewer.ScrollToTop();
    // std::cout << "  - After ScrollToTop, margin top: " << scrollViewer.GetScrollMarginTop() << std::endl;
    EXPECT_EQ(scrollViewer.GetScrollMarginTop(), 0);
}
