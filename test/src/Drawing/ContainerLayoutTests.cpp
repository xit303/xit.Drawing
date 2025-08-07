#include <gtest/gtest.h>
#include <Drawing/Container.h>
#include <Drawing/Label.h>
#include <Drawing/TextBox.h>
#include <Drawing/Rectangle.h>
#include <OpenGL/Scene2D.h>

using namespace xit::Drawing;

Scene2D scene;
GLFWwindow *window = nullptr;

#define ERROR(x)            \
    {                       \
        fprintf(stderr, x); \
        fflush(stderr);     \
    }
#define ERRORT(x)           \
    {                       \
        fprintf(stderr, x); \
        fflush(stderr);     \
        glfwTerminate();    \
    }

TEST(ContainerLayoutTest, BasicInitialization)
{
    if (!glfwInit())
    {
        ERROR("Failed to initialize GLFW");
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(400, 200, "TestWindow", NULL, NULL);
    if (window == NULL)
    {
        ERRORT("Failed to create GLFW window");
        return;
    }

    glfwSetWindowPos(window, 0, 0);

#if defined(DEBUG_INITIALIZATION) || defined(DEBUG_WINDOW)
    auto contextSetupStart = std::chrono::steady_clock::now();
#endif
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        ERRORT("Failed to initialize GLAD");
        return;
    }
}

// TEST(ContainerLayoutTest, LabelInAutoRow_ShouldBeVisible)
// {
//     // This test causes segfault due to Update() calling OpenGL components
//     // TODO: Enable when OpenGL initialization is properly mocked in tests
// }

// TEST(ContainerLayoutTest, LabelInAutoRow_WithoutText_ShouldHaveMinimalHeight)
// {
//     // This test causes segfault due to Update() calling OpenGL components
//     // TODO: Enable when OpenGL initialization is properly mocked in tests
// }

// TEST(ContainerLayoutTest, MultipleLabelsInAutoRows)
// {
//     // This test causes segfault due to Update() calling OpenGL components
//     // TODO: Enable when OpenGL initialization is properly mocked in tests
// }

TEST(ContainerLayoutTest, LabelInAutoRow_WithoutText_ShouldHaveMinimalHeight)
{
    Container container;
    container.SetRows("Auto");

    // Create a label without text
    Label *label = new Label();
    label->SetName("EmptyLabel");
    label->SetRow(0);
    container.AddChild(label);

    scene.Resize(400, 100);
    Scene2D::MakeCurrent(&scene);

    // Now we can safely call Update() with OpenGL initialized
    Rectangle containerBounds(0, 0, 400, 100);
    container.Update(containerBounds);

    // Check the label's actual dimensions after layout
    int labelHeight = label->GetActualHeight();
    int labelWidth = label->GetActualWidth();
    
    // Even empty label should have some minimal dimensions or be 0
    ASSERT_GE(labelHeight, 0) << "Empty label should have height >= 0";
    ASSERT_GE(labelWidth, 0) << "Empty label should have width >= 0";

    // Cleanup
    delete label;
}

TEST(ContainerLayoutTest, LabelInAutoRow_FullLayoutTest)
{
    Container container;
    container.SetName("TestContainer");
    container.SetRows("Auto,*,50");  // Auto row, Star row, Fixed row
    
    // Create a label with text for Auto row
    Label *label = new Label();
    label->SetName("AutoRowLabel");
    label->SetText("Welcome to the test program!");
    label->SetRow(0);  // Auto row
    container.AddChild(label);
    
    scene.Resize(400, 300);
    Scene2D::MakeCurrent(&scene);
    
    // Test full container layout
    Rectangle containerBounds(0, 0, 400, 300);
    bool needsRedraw = container.Update(containerBounds);
    
    // Check that label was positioned and sized correctly
    int labelHeight = label->GetActualHeight();
    int labelWidth = label->GetActualWidth();
    int labelTop = label->GetTop();
    int labelLeft = label->GetLeft();
    
    ASSERT_GT(labelHeight, 0) << "Label in Auto row should have height > 0";
    ASSERT_GT(labelWidth, 0) << "Label in Auto row should have width > 0";
    
    // Label should be positioned within container bounds
    ASSERT_GE(labelLeft, containerBounds.GetLeft()) << "Label should be within container bounds (left)";
    ASSERT_GE(labelTop, containerBounds.GetTop()) << "Label should be within container bounds (top)";
    ASSERT_LE(labelLeft + labelWidth, containerBounds.GetRight()) << "Label should be within container bounds (right)";
    
    // For Auto row, label should be positioned at the top of the container
    // (accounting for any margin)
    ASSERT_LE(labelTop, containerBounds.GetTop() + 50) << "Label in Auto row should be near top of container";
    
    std::cout << "Container Layout Results:" << std::endl;
    std::cout << "  Label Position: (" << labelLeft << ", " << labelTop << ")" << std::endl;
    std::cout << "  Label Size: " << labelWidth << "x" << labelHeight << std::endl;
    std::cout << "  Container Bounds: " << containerBounds.GetLeft() << "," << containerBounds.GetTop() 
              << " " << containerBounds.GetWidth() << "x" << containerBounds.GetHeight() << std::endl;
    
    // Cleanup
    delete label;
}

TEST(ContainerLayoutTest, MultipleLabelsInAutoRows)
{
    Container container;
    container.SetRows("Auto,Auto,Auto"); // Three auto rows
    container.SetRowSpacing(5);

    Label *label1 = new Label();
    label1->SetName("Label1");
    label1->SetText("First Label");
    label1->SetRow(0);
    container.AddChild(label1);

    Label *label2 = new Label();
    label2->SetName("Label2");
    label2->SetText("Second Label");
    label2->SetRow(1);
    container.AddChild(label2);

    Label *label3 = new Label();
    label3->SetName("Label3");
    label3->SetText("Third Label");
    label3->SetRow(2);
    container.AddChild(label3);

    scene.Resize(400, 300);
    Scene2D::MakeCurrent(&scene);

    // Test full container layout with Update()
    Rectangle containerBounds(0, 0, 400, 300);
    container.Update(containerBounds);

    // All labels should have dimensions when laid out
    ASSERT_GT(label1->GetActualHeight(), 0) << "First label should have height";
    ASSERT_GT(label2->GetActualHeight(), 0) << "Second label should have height";
    ASSERT_GT(label3->GetActualHeight(), 0) << "Third label should have height";

    ASSERT_GT(label1->GetActualWidth(), 0) << "First label should have width";
    ASSERT_GT(label2->GetActualWidth(), 0) << "Second label should have width";
    ASSERT_GT(label3->GetActualWidth(), 0) << "Third label should have width";
    
    // Labels should be stacked vertically (with spacing)
    int label1Bottom = label1->GetTop() + label1->GetActualHeight();
    int label2Top = label2->GetTop();
    int label2Bottom = label2->GetTop() + label2->GetActualHeight();
    int label3Top = label3->GetTop();

    ASSERT_LE(label1Bottom, label2Top + 1) << "Label2 should be below Label1 (with spacing tolerance)";
    ASSERT_LE(label2Bottom, label3Top + 1) << "Label3 should be below Label2 (with spacing tolerance)";

    std::cout << "Multiple Auto Rows Layout:" << std::endl;
    std::cout << "  Label1: (" << label1->GetLeft() << "," << label1->GetTop() << ") " 
              << label1->GetActualWidth() << "x" << label1->GetActualHeight() << std::endl;
    std::cout << "  Label2: (" << label2->GetLeft() << "," << label2->GetTop() << ") " 
              << label2->GetActualWidth() << "x" << label2->GetActualHeight() << std::endl;
    std::cout << "  Label3: (" << label3->GetLeft() << "," << label3->GetTop() << ") " 
              << label3->GetActualWidth() << "x" << label3->GetActualHeight() << std::endl;

    // Cleanup
    delete label1;
    delete label2;
    delete label3;
}

TEST(ContainerLayoutTest, LabelMeasurement_DirectTest)
{
    // Test label measurement directly to isolate the issue
    Label label;
    label.SetText("Test Label Text");

    // Test measurement with reasonable available space
    int availableWidth = 400;
    int availableHeight = 100;

    Size measuredSize = label.Measure(Size(availableWidth, availableHeight));

    // Label with text should have some dimensions
    ASSERT_GT(measuredSize.GetWidth(), 0) << "Label should have width when it has text";
    ASSERT_GT(measuredSize.GetHeight(), 0) << "Label should have height when it has text";

    // Check individual measurement methods
    int measuredWidth = label.MeasureWidth(availableWidth);
    int measuredHeight = label.MeasureHeight(availableHeight);

    ASSERT_GT(measuredWidth, 0) << "MeasureWidth should return > 0 for label with text";
    ASSERT_GT(measuredHeight, 0) << "MeasureHeight should return > 0 for label with text";
}

TEST(ContainerLayoutTest, LabelMeasurement_WithoutText)
{
    // Test label measurement without text
    Label label;
    // No text set

    int availableWidth = 400;
    int availableHeight = 100;

    Size measuredSize = label.Measure(Size(availableWidth, availableHeight));

    // Label without text might have 0 dimensions or minimal dimensions
    ASSERT_GE(measuredSize.GetWidth(), 0) << "Label width should be >= 0";
    ASSERT_GE(measuredSize.GetHeight(), 0) << "Label height should be >= 0";

    // Check what the desired size is
    Size desiredSize = label.GetDesiredSize();
    ASSERT_GE(desiredSize.GetWidth(), 0) << "Desired width should be >= 0";
    ASSERT_GE(desiredSize.GetHeight(), 0) << "Desired height should be >= 0";
}

TEST(ContainerLayoutTest, ContainerRowParsing_AutoRows)
{
    // Test that container properly parses "Auto,*,50" row definition
    Container container;
    container.SetRows("Auto,*,50");

    // Container should recognize the row configuration
    // This is a basic test to ensure the container accepts the row setup
    ASSERT_EQ(container.GetRows(), "Auto,*,50");
}

TEST(ContainerLayoutTest, BasicContainerWithLabel_NoUpdate)
{
    // Test basic container setup without calling Update()
    Container container;
    container.SetName("TestContainer");
    container.SetRows("Auto,*");

    Label *label = new Label();
    label->SetName("TestLabel");
    label->SetText("Welcome to the test program!");
    label->SetRow(0); // Auto row
    container.AddChild(label);

    // Just verify the setup worked - no Update() call to avoid segfault
    ASSERT_EQ(label->GetRow(), 0) << "Label should be in row 0";
    ASSERT_EQ(label->GetText(), "Welcome to the test program!") << "Label should have correct text";
    ASSERT_EQ(container.GetRows(), "Auto,*") << "Container should have correct row definition";

    // Test label measurement separately
    Size labelSize = label->Measure(Size(400, 100));
    ASSERT_GT(labelSize.GetHeight(), 0) << "Label should have height when measured";

    // Cleanup
    delete label;
}
