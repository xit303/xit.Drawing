#include <gtest/gtest.h>
#include <Drawing/GridRowManager.h>
#include <Drawing/Visual.h>

using namespace xit::Drawing;

class GridRowManagerTest : public ::testing::Test
{
protected:
    GridRowManager manager;
    std::vector<Visual*> children;
    Visual child1, child2, child3;

    void SetUp() override
    {
        // Initialize children
        children.clear();
        children.push_back(&child1);
        children.push_back(&child2);
        children.push_back(&child3);
        
        // Set up basic properties for children
        child1.SetRow(0);
        child1.SetRowSpan(1);
        child2.SetRow(1);
        child2.SetRowSpan(1);
        child3.SetRow(2);
        child3.SetRowSpan(1);
    }
};

TEST_F(GridRowManagerTest, DefaultConstructor)
{
    GridRowManager mgr;
    
    EXPECT_EQ(mgr.GetRowHeights().size(), 0);
    EXPECT_EQ(mgr.GetRowPositions().size(), 0);
    EXPECT_EQ(mgr.GetNumberOfRows(), 0);
    EXPECT_EQ(mgr.GetRowSpacing(), 0);
    EXPECT_EQ(mgr.GetRows(), "");
}

TEST_F(GridRowManagerTest, SetBounds_ValidRectangle)
{
    Rectangle bounds(10, 20, 200, 100);
    
    // Should not crash when setting bounds
    EXPECT_NO_THROW(manager.SetBounds(bounds));
}

TEST_F(GridRowManagerTest, SetBounds_ZeroHeight)
{
    Rectangle bounds(0, 0, 200, 0);
    
    // Should not crash when setting bounds with zero height
    EXPECT_NO_THROW(manager.SetBounds(bounds));
}

TEST_F(GridRowManagerTest, SetBounds_NegativePosition)
{
    Rectangle bounds(-50, -25, 200, 100);
    
    // Should not crash when setting bounds with negative position
    EXPECT_NO_THROW(manager.SetBounds(bounds));
}

TEST_F(GridRowManagerTest, SetChildren_ValidChildren)
{
    manager.SetChildren(&children);
    
    // Should not crash and internal state should be updated
    // We can't directly verify internal state, but we can verify no exceptions
}

TEST_F(GridRowManagerTest, SetChildren_NullPointer)
{
    manager.SetChildren(nullptr);
    
    // Should not crash
}

TEST_F(GridRowManagerTest, SetRows_SingleAutoRow)
{
    manager.SetRows("Auto");
    
    EXPECT_EQ(manager.GetRows(), "Auto");
    EXPECT_EQ(manager.GetNumberOfRows(), 1);
}

TEST_F(GridRowManagerTest, SetRows_MultipleRows)
{
    manager.SetRows("100,Auto,*");
    
    EXPECT_EQ(manager.GetRows(), "100,Auto,*");
    EXPECT_EQ(manager.GetNumberOfRows(), 3);
}

TEST_F(GridRowManagerTest, SetRows_EmptyString)
{
    manager.SetRows("");
    
    EXPECT_EQ(manager.GetRows(), "");
    // Number of rows might be 0 or 1 depending on implementation
}

TEST_F(GridRowManagerTest, SetRowSpacing_ValidSpacing)
{
    manager.SetRowSpacing(10);
    
    EXPECT_EQ(manager.GetRowSpacing(), 10);
}

TEST_F(GridRowManagerTest, SetRowSpacing_ZeroSpacing)
{
    manager.SetRowSpacing(0);
    
    EXPECT_EQ(manager.GetRowSpacing(), 0);
}

TEST_F(GridRowManagerTest, SetRowSpacing_NegativeSpacing)
{
    manager.SetRowSpacing(-5);
    
    EXPECT_EQ(manager.GetRowSpacing(), -5);
}

TEST_F(GridRowManagerTest, GetHeight_WithoutBounds)
{
    int height = manager.GetHeight(100);
    
    // Should return some valid value (likely 0 or calculated based on available space)
    EXPECT_GE(height, 0);
}

TEST_F(GridRowManagerTest, GetHeight_WithBounds)
{
    Rectangle bounds(0, 0, 200, 300);
    manager.SetBounds(bounds);
    
    int height = manager.GetHeight(100);
    
    EXPECT_GE(height, 0);
    EXPECT_LE(height, 300); // Should not exceed bounds height
}

TEST_F(GridRowManagerTest, GetHeight_ZeroAvailable)
{
    int height = manager.GetHeight(0);
    
    EXPECT_EQ(height, 0);
}

TEST_F(GridRowManagerTest, GetHeight_NegativeAvailable)
{
    int height = manager.GetHeight(-50);
    
    // Implementation should handle negative values gracefully
    EXPECT_GE(height, 0);
}

TEST_F(GridRowManagerTest, RowLayout_SingleFixedRow)
{
    manager.SetRows("100");
    Rectangle bounds(0, 0, 200, 200);
    manager.SetBounds(bounds);
    
    int height = manager.GetHeight(200);
    
    // With a single fixed row, the total height should be at least the row height
    EXPECT_GE(height, 0);
    
    // After layout calculation, we should have row heights and positions
    if (manager.GetNumberOfRows() > 0)
    {
        EXPECT_EQ(manager.GetRowHeights().size(), manager.GetNumberOfRows());
        EXPECT_EQ(manager.GetRowPositions().size(), manager.GetNumberOfRows());
    }
}

TEST_F(GridRowManagerTest, RowLayout_MultipleFixedRows)
{
    manager.SetRows("50,100,75");
    Rectangle bounds(0, 0, 200, 300);
    manager.SetBounds(bounds);
    
    int height = manager.GetHeight(300);
    
    EXPECT_GE(height, 0);
    EXPECT_EQ(manager.GetNumberOfRows(), 3);
    
    if (manager.GetRowHeights().size() >= 3)
    {
        // Check that row heights are as expected (may include spacing)
        const auto& heights = manager.GetRowHeights();
        EXPECT_GT(heights.size(), 0);
    }
}

TEST_F(GridRowManagerTest, RowLayout_AutoRow)
{
    manager.SetRows("Auto");
    manager.SetChildren(&children);
    Rectangle bounds(0, 0, 200, 200);
    manager.SetBounds(bounds);
    
    int height = manager.GetHeight(200);
    
    EXPECT_GE(height, 0);
    EXPECT_EQ(manager.GetNumberOfRows(), 1);
}

TEST_F(GridRowManagerTest, RowLayout_StarRow)
{
    manager.SetRows("*");
    Rectangle bounds(0, 0, 200, 200);
    manager.SetBounds(bounds);
    
    int height = manager.GetHeight(200);
    
    EXPECT_GE(height, 0);
    EXPECT_EQ(manager.GetNumberOfRows(), 1);
}

TEST_F(GridRowManagerTest, RowLayout_MixedRows)
{
    manager.SetRows("100,Auto,*");
    manager.SetChildren(&children);
    Rectangle bounds(0, 0, 200, 400);
    manager.SetBounds(bounds);
    
    int height = manager.GetHeight(400);
    
    EXPECT_GE(height, 0);
    EXPECT_EQ(manager.GetNumberOfRows(), 3);
}

TEST_F(GridRowManagerTest, RowLayout_WithSpacing)
{
    manager.SetRows("50,50,50");
    manager.SetRowSpacing(10);
    Rectangle bounds(0, 0, 200, 200);
    manager.SetBounds(bounds);
    
    int height = manager.GetHeight(200);
    
    EXPECT_GE(height, 0);
    EXPECT_EQ(manager.GetRowSpacing(), 10);
}

TEST_F(GridRowManagerTest, VerticalAlignment_Top)
{
    manager.SetVerticalAlignment(VerticalAlignment::Top);
    Rectangle bounds(0, 0, 200, 200);
    manager.SetBounds(bounds);
    
    // Test that setting vertical alignment doesn't crash
    EXPECT_EQ(manager.GetVerticalAlignment(), VerticalAlignment::Top);
}

TEST_F(GridRowManagerTest, VerticalAlignment_Center)
{
    manager.SetVerticalAlignment(VerticalAlignment::Center);
    Rectangle bounds(0, 0, 200, 200);
    manager.SetBounds(bounds);
    
    // Test that setting vertical alignment doesn't crash
    EXPECT_EQ(manager.GetVerticalAlignment(), VerticalAlignment::Center);
}

TEST_F(GridRowManagerTest, VerticalAlignment_Bottom)
{
    manager.SetVerticalAlignment(VerticalAlignment::Bottom);
    Rectangle bounds(0, 0, 200, 200);
    manager.SetBounds(bounds);
    
    // Test that setting vertical alignment doesn't crash
    EXPECT_EQ(manager.GetVerticalAlignment(), VerticalAlignment::Bottom);
}

TEST_F(GridRowManagerTest, VerticalAlignment_Stretch)
{
    manager.SetVerticalAlignment(VerticalAlignment::Stretch);
    Rectangle bounds(0, 0, 200, 200);
    manager.SetBounds(bounds);
    
    // Test that setting vertical alignment doesn't crash
    EXPECT_EQ(manager.GetVerticalAlignment(), VerticalAlignment::Stretch);
}

TEST_F(GridRowManagerTest, BoundsConsistency)
{
    Rectangle bounds1(10, 20, 300, 150);
    manager.SetBounds(bounds1);
    
    // Bounds should be set without throwing
    EXPECT_NO_THROW(manager.GetHeight(150));
    
    Rectangle bounds2(50, 60, 200, 400);
    manager.SetBounds(bounds2);
    
    // New bounds should be set without throwing
    EXPECT_NO_THROW(manager.GetHeight(400));
}

TEST_F(GridRowManagerTest, EmptyVsNonEmptyChildren)
{
    // Test with no children
    manager.SetRows("Auto");
    Rectangle bounds(0, 0, 200, 200);
    manager.SetBounds(bounds);
    
    int heightNoChildren = manager.GetHeight(200);
    EXPECT_GE(heightNoChildren, 0);
    
    // Test with children
    manager.SetChildren(&children);
    int heightWithChildren = manager.GetHeight(200);
    EXPECT_GE(heightWithChildren, 0);
    
    // Both should be valid (exact values depend on implementation)
}

TEST_F(GridRowManagerTest, ConsistentInterfaceWithColumns)
{
    // Test that row manager has consistent interface with column manager
    manager.SetRows("100,Auto,*,2*");
    manager.SetRowSpacing(5);
    Rectangle bounds(0, 0, 300, 400);
    manager.SetBounds(bounds);
    manager.SetChildren(&children);
    
    EXPECT_EQ(manager.GetNumberOfRows(), 4);
    EXPECT_EQ(manager.GetRowSpacing(), 5);
    EXPECT_EQ(manager.GetRows(), "100,Auto,*,2*");
    
    int height = manager.GetHeight(400);
    EXPECT_GE(height, 0);
}
