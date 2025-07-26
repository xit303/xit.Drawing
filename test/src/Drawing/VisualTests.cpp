#include <gtest/gtest.h>
#include <Drawing/Visual.h>

using namespace xit::Drawing;

TEST(VisualTest, MeasureWidth_VerySmallAvailableSize)
{
    Visual visual;
    visual.SetWidth(-1); // Auto size
    visual.SetMargin(Thickness(5));
    visual.SetPadding(Thickness(2));
    visual.SetBorderThickness(Thickness(1));

    int availableSize = 1;
    int measuredWidth = visual.MeasureWidth(availableSize);

    // Expected: Padding + Border + available size = (2 * 2) + (2 * 1) + availableSize = 7
    ASSERT_EQ(measuredWidth, 7);
    ASSERT_EQ(visual.GetActualWidth(), 7);
    ASSERT_EQ(visual.GetDesiredSize().GetWidth(), 7);
    ASSERT_EQ(visual.GetTop(), 0);
    ASSERT_EQ(visual.GetLeft(), 0);
    ASSERT_EQ(availableSize + visual.GetPadding().GetWidth() + visual.GetBorderThickness().GetWidth(), 7);
}

TEST(VisualTest, MeasureWidth_VeryLargeAvailableSize)
{
    Visual visual;
    visual.SetWidth(-1); // Auto size
    visual.SetMargin(Thickness(5));
    visual.SetPadding(Thickness(2));
    visual.SetBorderThickness(Thickness(1));

    int availableSize = 1000;
    int measuredWidth = visual.MeasureWidth(availableSize);

    // Expected: available size minus margin = availableSize - (2 * 5) = 990
    ASSERT_EQ(measuredWidth, 990);
    ASSERT_EQ(visual.GetActualWidth(), 990);
    ASSERT_EQ(visual.GetDesiredSize().GetWidth(), 990);
    ASSERT_EQ(visual.GetTop(), 0);
    ASSERT_EQ(visual.GetLeft(), 0);
    // ASSERT_EQ(availableSize + visual.GetPadding().GetWidth() + visual.GetBorderThickness().GetWidth(), availableSize);
}

TEST(VisualTest, MeasureWidth_NegativeMarginPaddingBorder)
{
    Visual visual;
    visual.SetWidth(-1); // Auto size
    visual.SetMargin(Thickness(-5));
    visual.SetPadding(Thickness(-2));
    visual.SetBorderThickness(Thickness(-1));

    int availableSize = 100;
    int measuredWidth = visual.MeasureWidth(availableSize);

    // Expected: available size minus margin = availableSize - (2 * -5) = 110
    ASSERT_EQ(measuredWidth, 110);
    ASSERT_EQ(visual.GetActualWidth(), 110);
    ASSERT_EQ(visual.GetDesiredSize().GetWidth(), 110);
    ASSERT_EQ(visual.GetTop(), 0);
    ASSERT_EQ(visual.GetLeft(), 0);
    // ASSERT_EQ(availableSize + visual.GetPadding().GetWidth() + visual.GetBorderThickness().GetWidth(), availableSize);
}

TEST(VisualTest, MeasureWidth_ZeroMarginPaddingBorder)
{
    Visual visual;
    visual.SetWidth(-1); // Auto size
    visual.SetMargin(Thickness(0));
    visual.SetPadding(Thickness(0));
    visual.SetBorderThickness(Thickness(0));

    int availableSize = 100;
    int measuredWidth = visual.MeasureWidth(availableSize);

    // Expected: available size
    ASSERT_EQ(measuredWidth, availableSize);
    ASSERT_EQ(visual.GetActualWidth(), availableSize);
    ASSERT_EQ(visual.GetDesiredSize().GetWidth(), availableSize);
    ASSERT_EQ(visual.GetTop(), 0);
    ASSERT_EQ(visual.GetLeft(), 0);
    // ASSERT_EQ(availableSize + visual.GetPadding().GetWidth() + visual.GetBorderThickness().GetWidth(), availableSize);
}

TEST(VisualTest, MeasureHeight_VerySmallAvailableSize)
{
    Visual visual;
    visual.SetHeight(-1); // Auto size
    visual.SetMargin(Thickness(5));
    visual.SetPadding(Thickness(2));
    visual.SetBorderThickness(Thickness(1));

    int availableSize = 1;
    int measuredHeight = visual.MeasureHeight(availableSize);

    // Expected: Padding + Border + available size = (2 * 2) + (2 * 1) + availableSize = 7
    ASSERT_EQ(measuredHeight, 7);
    ASSERT_EQ(visual.GetActualHeight(), 7);
    ASSERT_EQ(visual.GetDesiredSize().GetHeight(), 7);
    ASSERT_EQ(visual.GetTop(), 0);
    ASSERT_EQ(visual.GetLeft(), 0);
    ASSERT_EQ(availableSize + visual.GetPadding().GetHeight() + visual.GetBorderThickness().GetHeight(), 7);
}

TEST(VisualTest, MeasureHeight_VeryLargeAvailableSize)
{
    Visual visual;
    visual.SetHeight(-1); // Auto size
    visual.SetMargin(Thickness(5));
    visual.SetPadding(Thickness(2));
    visual.SetBorderThickness(Thickness(1));

    int availableSize = 1000;
    int measuredHeight = visual.MeasureHeight(availableSize);

    // Expected: available size minus margin = availableSize - (2 * 5) = 990
    ASSERT_EQ(measuredHeight, 990);
    ASSERT_EQ(visual.GetActualHeight(), 990);
    ASSERT_EQ(visual.GetDesiredSize().GetHeight(), 990);
    ASSERT_EQ(visual.GetTop(), 0);
    ASSERT_EQ(visual.GetLeft(), 0);
    // ASSERT_EQ(availableSize + visual.GetPadding().GetHeight() + visual.GetBorderThickness().GetHeight(), 990);
}

TEST(VisualTest, MeasureHeight_NegativeMarginPaddingBorder)
{
    Visual visual;
    visual.SetHeight(-1); // Auto size
    visual.SetMargin(Thickness(-5));
    visual.SetPadding(Thickness(-2));
    visual.SetBorderThickness(Thickness(-1));

    int availableSize = 100;
    int measuredHeight = visual.MeasureHeight(availableSize);

    // Expected: available size minus margin = availableSize - (2 * -5) = 110
    ASSERT_EQ(measuredHeight, 110);
    ASSERT_EQ(visual.GetActualHeight(), 110);
    ASSERT_EQ(visual.GetDesiredSize().GetHeight(), 110);
    ASSERT_EQ(visual.GetTop(), 0);
    ASSERT_EQ(visual.GetLeft(), 0);
    // ASSERT_EQ(availableSize + visual.GetPadding().GetHeight() + visual.GetBorderThickness().GetHeight(), 110);
}

TEST(VisualTest, MeasureHeight_ZeroMarginPaddingBorder)
{
    Visual visual;
    visual.SetHeight(-1); // Auto size
    visual.SetMargin(Thickness(0));
    visual.SetPadding(Thickness(0));
    visual.SetBorderThickness(Thickness(0));

    int availableSize = 100;
    int measuredHeight = visual.MeasureHeight(availableSize);

    ASSERT_EQ(measuredHeight, 100);
    ASSERT_EQ(visual.GetActualHeight(), 100);
    ASSERT_EQ(visual.GetDesiredSize().GetHeight(), 100);
    ASSERT_EQ(visual.GetTop(), 0);
    ASSERT_EQ(visual.GetLeft(), 0);
    // ASSERT_EQ(availableSize + visual.GetPadding().GetHeight() + visual.GetBorderThickness().GetHeight(), 100);
}
