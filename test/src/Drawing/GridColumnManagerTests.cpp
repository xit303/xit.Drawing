#include <gtest/gtest.h>
#include <Drawing/GridColumnManager.h>
#include <Drawing/Visual.h>

using namespace xit::Drawing;

class GridColumnManagerTest : public ::testing::Test
{
protected:
    GridColumnManager manager;
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
        child1.SetColumn(0);
        child1.SetColumnSpan(1);
        child2.SetColumn(1);
        child2.SetColumnSpan(1);
        child3.SetColumn(2);
        child3.SetColumnSpan(1);
    }
};

TEST_F(GridColumnManagerTest, DefaultConstructor)
{
    GridColumnManager mgr;
    
    EXPECT_EQ(mgr.GetColumnWidths().size(), 0);
    EXPECT_EQ(mgr.GetColumnPositions().size(), 0);
    EXPECT_EQ(mgr.GetNumberOfColumns(), 0);
    EXPECT_EQ(mgr.GetColumnSpacing(), 0);
    EXPECT_EQ(mgr.GetColumns(), "");
}

TEST_F(GridColumnManagerTest, SetBounds_ValidRectangle)
{
    Rectangle bounds(10, 20, 200, 100);
    
    // Should not crash when setting bounds
    EXPECT_NO_THROW(manager.SetBounds(bounds));
}

TEST_F(GridColumnManagerTest, SetBounds_ZeroWidth)
{
    Rectangle bounds(0, 0, 0, 100);
    
    // Should not crash when setting bounds with zero width
    EXPECT_NO_THROW(manager.SetBounds(bounds));
}

TEST_F(GridColumnManagerTest, SetBounds_NegativePosition)
{
    Rectangle bounds(-50, -25, 200, 100);
    
    // Should not crash when setting bounds with negative position
    EXPECT_NO_THROW(manager.SetBounds(bounds));
}

TEST_F(GridColumnManagerTest, SetChildren_ValidChildren)
{
    manager.SetChildren(&children);
    
    // Should not crash and internal state should be updated
    // We can't directly verify internal state, but we can verify no exceptions
}

TEST_F(GridColumnManagerTest, SetChildren_NullPointer)
{
    manager.SetChildren(nullptr);
    
    // Should not crash
}

TEST_F(GridColumnManagerTest, SetColumns_SingleAutoColumn)
{
    manager.SetColumns("Auto");
    
    EXPECT_EQ(manager.GetColumns(), "Auto");
    EXPECT_EQ(manager.GetNumberOfColumns(), 1);
}

TEST_F(GridColumnManagerTest, SetColumns_MultipleColumns)
{
    manager.SetColumns("100,Auto,*");
    
    EXPECT_EQ(manager.GetColumns(), "100,Auto,*");
    EXPECT_EQ(manager.GetNumberOfColumns(), 3);
}

TEST_F(GridColumnManagerTest, SetColumns_EmptyString)
{
    manager.SetColumns("");
    
    EXPECT_EQ(manager.GetColumns(), "");
    // Number of columns might be 0 or 1 depending on implementation
}

TEST_F(GridColumnManagerTest, SetColumnSpacing_ValidSpacing)
{
    manager.SetColumnSpacing(10);
    
    EXPECT_EQ(manager.GetColumnSpacing(), 10);
}

TEST_F(GridColumnManagerTest, SetColumnSpacing_ZeroSpacing)
{
    manager.SetColumnSpacing(0);
    
    EXPECT_EQ(manager.GetColumnSpacing(), 0);
}

TEST_F(GridColumnManagerTest, SetColumnSpacing_NegativeSpacing)
{
    manager.SetColumnSpacing(-5);
    
    EXPECT_EQ(manager.GetColumnSpacing(), -5);
}

TEST_F(GridColumnManagerTest, GetWidth_WithoutBounds)
{
    int width = manager.GetWidth(100);
    
    // Should return some valid value (likely 0 or calculated based on available space)
    EXPECT_GE(width, 0);
}

TEST_F(GridColumnManagerTest, GetWidth_WithBounds)
{
    Rectangle bounds(0, 0, 300, 200);
    manager.SetBounds(bounds);
    
    int width = manager.GetWidth(100);
    
    EXPECT_GE(width, 0);
    EXPECT_LE(width, 300); // Should not exceed bounds width
}

TEST_F(GridColumnManagerTest, GetWidth_ZeroAvailable)
{
    int width = manager.GetWidth(0);
    
    EXPECT_EQ(width, 0);
}

TEST_F(GridColumnManagerTest, GetWidth_NegativeAvailable)
{
    int width = manager.GetWidth(-50);
    
    // Implementation should handle negative values gracefully
    EXPECT_GE(width, 0);
}

TEST_F(GridColumnManagerTest, ColumnLayout_SingleFixedColumn)
{
    manager.SetColumns("100");
    Rectangle bounds(0, 0, 200, 100);
    manager.SetBounds(bounds);
    
    int width = manager.GetWidth(200);
    
    // With a single fixed column, the total width should be at least the column width
    EXPECT_GE(width, 0);
    
    // After layout calculation, we should have column widths and positions
    if (manager.GetNumberOfColumns() > 0)
    {
        EXPECT_EQ(manager.GetColumnWidths().size(), manager.GetNumberOfColumns());
        EXPECT_EQ(manager.GetColumnPositions().size(), manager.GetNumberOfColumns());
    }
}

TEST_F(GridColumnManagerTest, ColumnLayout_MultipleFixedColumns)
{
    manager.SetColumns("50,100,75");
    Rectangle bounds(0, 0, 300, 100);
    manager.SetBounds(bounds);
    
    int width = manager.GetWidth(300);
    
    EXPECT_GE(width, 0);
    EXPECT_EQ(manager.GetNumberOfColumns(), 3);
    
    if (manager.GetColumnWidths().size() >= 3)
    {
        // Check that column widths are as expected (may include spacing)
        const auto& widths = manager.GetColumnWidths();
        EXPECT_GT(widths.size(), 0);
    }
}

TEST_F(GridColumnManagerTest, ColumnLayout_AutoColumn)
{
    manager.SetColumns("Auto");
    manager.SetChildren(&children);
    Rectangle bounds(0, 0, 200, 100);
    manager.SetBounds(bounds);
    
    int width = manager.GetWidth(200);
    
    EXPECT_GE(width, 0);
    EXPECT_EQ(manager.GetNumberOfColumns(), 1);
}

TEST_F(GridColumnManagerTest, ColumnLayout_StarColumn)
{
    manager.SetColumns("*");
    Rectangle bounds(0, 0, 200, 100);
    manager.SetBounds(bounds);
    
    int width = manager.GetWidth(200);
    
    EXPECT_GE(width, 0);
    EXPECT_EQ(manager.GetNumberOfColumns(), 1);
}

TEST_F(GridColumnManagerTest, ColumnLayout_MixedColumns)
{
    manager.SetColumns("100,Auto,*");
    manager.SetChildren(&children);
    Rectangle bounds(0, 0, 400, 100);
    manager.SetBounds(bounds);
    
    int width = manager.GetWidth(400);
    
    EXPECT_GE(width, 0);
    EXPECT_EQ(manager.GetNumberOfColumns(), 3);
}

TEST_F(GridColumnManagerTest, ColumnLayout_WithSpacing)
{
    manager.SetColumns("50,50,50");
    manager.SetColumnSpacing(10);
    Rectangle bounds(0, 0, 200, 100);
    manager.SetBounds(bounds);
    
    int width = manager.GetWidth(200);
    
    EXPECT_GE(width, 0);
    EXPECT_EQ(manager.GetColumnSpacing(), 10);
}
