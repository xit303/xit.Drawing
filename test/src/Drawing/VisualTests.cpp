#include <gtest/gtest.h>
#include <Drawing/Visual.h>
#include <Drawing/Rectangle.h>

using namespace xit::Drawing;

TEST(VisualTest, BasicVisualCreation)
{
    // Simple test to verify Visual can be created without crashing
    Visual visual;
    
    // Just check basic property access - no Update() call
    ASSERT_EQ(visual.GetActualWidth(), 0);  // Should be 0 initially
    ASSERT_EQ(visual.GetActualHeight(), 0); // Should be 0 initially
}

TEST(VisualTest, MeasureWidth_VerySmallAvailableSize)
{
    Visual visual;
    visual.SetWidth(-1); // Auto size
    visual.SetMargin(Thickness(5));
    visual.SetPadding(Thickness(2));
    visual.SetBorderThickness(Thickness(1));

    int availableSize = 1;
    
    // Test MeasureWidth directly (this sets desiredSize)
    int measuredWidth = visual.MeasureWidth(availableSize);

    // For Stretch alignment (default): finalSize = availableSize - margin.GetWidth()
    // Expected: 1 - (5 + 5) = -9
    int expectedWidth = availableSize - visual.GetMargin().GetWidth();
    ASSERT_EQ(measuredWidth, expectedWidth);
    ASSERT_EQ(visual.GetDesiredSize().GetWidth(), expectedWidth);
    
    // GetActualWidth() should still be 0 since Update() wasn't called
    ASSERT_EQ(visual.GetActualWidth(), 0);
}

TEST(VisualTest, MeasureWidth_VeryLargeAvailableSize)
{
    Visual visual;
    visual.SetWidth(-1); // Auto size
    visual.SetMargin(Thickness(5));
    visual.SetPadding(Thickness(2));
    visual.SetBorderThickness(Thickness(1));

    int availableSize = 1000;
    
    // Test MeasureWidth directly (this sets desiredSize)
    int measuredWidth = visual.MeasureWidth(availableSize);

    // For Stretch alignment (default): finalSize = availableSize - margin.GetWidth()
    // Expected: 1000 - (5 + 5) = 990
    int expectedWidth = availableSize - visual.GetMargin().GetWidth();
    ASSERT_EQ(measuredWidth, expectedWidth);
    ASSERT_EQ(visual.GetDesiredSize().GetWidth(), expectedWidth);
    
    // GetActualWidth() should still be 0 since Update() wasn't called
    ASSERT_EQ(visual.GetActualWidth(), 0);
}

TEST(VisualTest, MeasureWidth_NegativeMarginPaddingBorder)
{
    Visual visual;
    visual.SetWidth(-1); // Auto size
    visual.SetMargin(Thickness(-5));
    visual.SetPadding(Thickness(-2));
    visual.SetBorderThickness(Thickness(-1));

    int availableSize = 100;
    
    // Test MeasureWidth directly (this sets desiredSize)
    int measuredWidth = visual.MeasureWidth(availableSize);

    // For Stretch alignment (default): finalSize = availableSize - margin.GetWidth()
    // Expected: 100 - (-5 + -5) = 100 - (-10) = 110
    int expectedWidth = availableSize - visual.GetMargin().GetWidth();
    ASSERT_EQ(measuredWidth, expectedWidth);
    ASSERT_EQ(visual.GetDesiredSize().GetWidth(), expectedWidth);
    
    // GetActualWidth() should still be 0 since Update() wasn't called
    ASSERT_EQ(visual.GetActualWidth(), 0);
}

TEST(VisualTest, MeasureWidth_ZeroMarginPaddingBorder)
{
    Visual visual;
    visual.SetWidth(-1); // Auto size
    visual.SetMargin(Thickness(0));
    visual.SetPadding(Thickness(0));
    visual.SetBorderThickness(Thickness(0));

    int availableSize = 100;
    
    // Test MeasureWidth directly (this sets desiredSize)
    int measuredWidth = visual.MeasureWidth(availableSize);

    // For Stretch alignment (default): finalSize = availableSize - margin.GetWidth()
    // Expected: 100 - (0 + 0) = 100
    int expectedWidth = availableSize - visual.GetMargin().GetWidth();
    ASSERT_EQ(measuredWidth, expectedWidth);
    ASSERT_EQ(visual.GetDesiredSize().GetWidth(), expectedWidth);
    
    // GetActualWidth() should still be 0 since Update() wasn't called
    ASSERT_EQ(visual.GetActualWidth(), 0);
}

TEST(VisualTest, MeasureHeight_VerySmallAvailableSize)
{
    Visual visual;
    visual.SetHeight(-1); // Auto size
    visual.SetMargin(Thickness(5));
    visual.SetPadding(Thickness(2));
    visual.SetBorderThickness(Thickness(1));

    int availableSize = 1;
    
    // Test MeasureHeight directly (this sets desiredSize)
    int measuredHeight = visual.MeasureHeight(availableSize);

    // For Stretch alignment (default): finalSize = availableSize - margin.GetHeight()
    // Expected: 1 - (5 + 5) = -9
    int expectedHeight = availableSize - visual.GetMargin().GetHeight();
    ASSERT_EQ(measuredHeight, expectedHeight);
    ASSERT_EQ(visual.GetDesiredSize().GetHeight(), expectedHeight);
    
    // GetActualHeight() should still be 0 since Update() wasn't called
    ASSERT_EQ(visual.GetActualHeight(), 0);
}

TEST(VisualTest, MeasureHeight_VeryLargeAvailableSize)
{
    Visual visual;
    visual.SetHeight(-1); // Auto size
    visual.SetMargin(Thickness(5));
    visual.SetPadding(Thickness(2));
    visual.SetBorderThickness(Thickness(1));

    int availableSize = 1000;
    
    // Test MeasureHeight directly (this sets desiredSize)
    int measuredHeight = visual.MeasureHeight(availableSize);

    // For Stretch alignment (default): finalSize = availableSize - margin.GetHeight()
    // Expected: 1000 - (5 + 5) = 990
    int expectedHeight = availableSize - visual.GetMargin().GetHeight();
    ASSERT_EQ(measuredHeight, expectedHeight);
    ASSERT_EQ(visual.GetDesiredSize().GetHeight(), expectedHeight);
    
    // GetActualHeight() should still be 0 since Update() wasn't called
    ASSERT_EQ(visual.GetActualHeight(), 0);
}

TEST(VisualTest, MeasureHeight_NegativeMarginPaddingBorder)
{
    Visual visual;
    visual.SetHeight(-1); // Auto size
    visual.SetMargin(Thickness(-5));
    visual.SetPadding(Thickness(-2));
    visual.SetBorderThickness(Thickness(-1));

    int availableSize = 100;
    
    // Test MeasureHeight directly (this sets desiredSize)
    int measuredHeight = visual.MeasureHeight(availableSize);

    // For Stretch alignment (default): finalSize = availableSize - margin.GetHeight()
    // Expected: 100 - (-5 + -5) = 100 - (-10) = 110
    int expectedHeight = availableSize - visual.GetMargin().GetHeight();
    ASSERT_EQ(measuredHeight, expectedHeight);
    ASSERT_EQ(visual.GetDesiredSize().GetHeight(), expectedHeight);
    
    // GetActualHeight() should still be 0 since Update() wasn't called
    ASSERT_EQ(visual.GetActualHeight(), 0);
}

TEST(VisualTest, MeasureHeight_ZeroMarginPaddingBorder)
{
    Visual visual;
    visual.SetHeight(-1); // Auto size
    visual.SetMargin(Thickness(0));
    visual.SetPadding(Thickness(0));
    visual.SetBorderThickness(Thickness(0));

    int availableSize = 100;
    
    // Test MeasureHeight directly (this sets desiredSize)
    int measuredHeight = visual.MeasureHeight(availableSize);

    // For Stretch alignment (default): finalSize = availableSize - margin.GetHeight()
    // Expected: 100 - (0 + 0) = 100
    int expectedHeight = availableSize - visual.GetMargin().GetHeight();
    ASSERT_EQ(measuredHeight, expectedHeight);
    ASSERT_EQ(visual.GetDesiredSize().GetHeight(), expectedHeight);
    
    // GetActualHeight() should still be 0 since Update() wasn't called
    ASSERT_EQ(visual.GetActualHeight(), 0);
}
