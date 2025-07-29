#include <Drawing/SplitContainer.h>
#include <Drawing/ContainerBase.h>
#include <Input/InputHandler.h>

namespace xit::Drawing
{
    SplitContainer::SplitContainer()
        : panel1(nullptr)
        , panel2(nullptr) 
        , panel1Index(0)
        , panel2Index(2)
        , orientation(Orientation::Vertical)
        , orientationDirection(OrientationDirection::Normal)
    {
        SetName("SplitContainer");
        SetInheritForeground(true);

        grid.SetChildren(&children);

        UpdateOrientation();
    }

    //******************************************************************************

    //******************************************************************************

    void SplitContainer::UpdateOrientation()
    {
        std::string columnsOrRows;

        switch (orientationDirection)
        {
        default:
        case OrientationDirection::Normal:
            columnsOrRows = "Auto,*";

            panel1Index = 0;
            panel2Index = 1;
            break;

        case OrientationDirection::Inverted:
            columnsOrRows = "*,Auto";

            panel1Index = 1;
            panel2Index = 0;
            break;
        }

        switch (orientation)
        {
        case Orientation::Horizontal:
            grid.SetColumns(columnsOrRows);
            grid.SetRows("*");

            if (panel1)
                panel1->SetGrid(panel1Index, 0);
            if (panel2)
                panel2->SetGrid(panel2Index, 0);
            break;

        case Orientation::Vertical:
            grid.SetColumns("*");
            grid.SetRows(columnsOrRows);

            if (panel1)
                panel1->SetGrid(0, panel1Index);
            if (panel2)
                panel2->SetGrid(0, panel2Index);

            break;
        }

        OnOrientationChanged();
    }

    //******************************************************************************
    // Protected override
    //******************************************************************************

    void SplitContainer::OnVisibilityChanged(EventArgs &e)
    {
        InputContent::OnVisibilityChanged(e);

        if (panel1 != nullptr)
        {
            panel1->SetVisibility(GetVisibility());
        }

        if (panel2 != nullptr)
        {
            panel2->SetVisibility(GetVisibility());
        }
    }

    int SplitContainer::OnMeasureWidth(int available)
    {
        return grid.GetWidth(available);
    }
    int SplitContainer::OnMeasureHeight(int available)
    {
        return grid.GetHeight(available);
    }

    void SplitContainer::OnUpdate(const Rectangle &bounds)
    {
        bool updateSize = GetNeedWidthRecalculation() || GetNeedHeightRecalculation();
        bool updateLocations = GetNeedLeftRecalculation() || GetNeedTopRecalculation();

        InputContent::OnUpdate(bounds);

        // Use optimized BoxModel method for client bounds calculation
        Rectangle stored = GetClientRectangle(GetLeft(), GetTop(), GetActualWidth(), GetActualHeight());

        // Handle negative margin (special case for SplitContainer)
        int left = stored.GetLeft();
        int top = stored.GetTop();
        int width = stored.GetWidth();
        int height = stored.GetHeight();
        
        if (GetMargin().GetTop() < 0)
            top -= GetMargin().GetTop();
        // if (Margin.Left < 0)
        //     left += Margin.Left;

        clientBounds.Set(left, top, width, height);

        grid.SetBounds(stored);

        if (updateSize || updateLocations)
        {
            if (orientation == Drawing::Orientation::Horizontal)
            {
                // for all same
                top += grid.GetRowPositions()[0];
                height = grid.GetRowHeights()[0];

                Rectangle r(left + grid.GetColumnPositions()[panel1Index], top, grid.GetColumnWidths()[panel1Index], height);

                if (panel1)
                    panel1->Update(r);

                if (panel2)
                {
                    r.SetLeft(left + grid.GetColumnPositions()[panel2Index]);
                    r.SetWidth(grid.GetColumnWidths()[panel2Index]);
                    panel2->Update(r);
                }
            }
            else
            {
                // for all same
                left += grid.GetColumnPositions()[0];
                width = grid.GetColumnWidths()[0];

                Rectangle r(left, top + grid.GetRowPositions()[panel1Index], width, grid.GetRowHeights()[panel1Index]);

                if (panel1)
                    panel1->Update(r);

                if (panel2)
                {
                    r.SetTop(top + grid.GetRowPositions()[panel2Index]);
                    r.SetHeight(grid.GetRowHeights()[panel2Index]);
                    panel2->Update(r);
                }
            }
        }
    }
    void SplitContainer::OnRender()
    {
        InputContent::OnRender();

        if (panel1)
            panel1->Render();
        if (panel2)
            panel2->Render();
    }

    //******************************************************************************
    // Protected
    //******************************************************************************

    void SplitContainer::OnOrientationChanged()
    {
        EventArgs e;
        OrientationChanged(e);
    }

    //******************************************************************************

    //******************************************************************************

    void SplitContainer::SetDPIScale(float scaleX, float scaleY)
    {
        InputContent::SetDPIScale(scaleX, scaleY);
        if (panel1)
            panel1->SetDPIScale(scaleX, scaleY);
        if (panel2)
            panel2->SetDPIScale(scaleX, scaleY);
    }

    Size SplitContainer::Measure(const Size &availableSize)
    {
        return InputContent::Measure(availableSize);
    }

    // void SplitContainer::ExecuteInputEnter(EventArgs& e)
    //{
    //     if (ContainerBase::CheckInputEnter(panel1, e))
    //         return;

    //    if (ContainerBase::CheckInputEnter(panel2, e))
    //        return;

    //    InputContent::ExecuteInputEnter(e);
    //}
    void SplitContainer::ExecuteInputLeave(MouseEventArgs &e)
    {
        if (InputHandler::CheckInputLeave(dynamic_cast<IFocus *>(panel1), e))
            return;
        if (InputHandler::CheckInputLeave(dynamic_cast<IFocus *>(panel2), e))
            return;
        InputContent::ExecuteInputLeave(e);
    }

    void SplitContainer::ExecuteInputPressed(MouseEventArgs &e)
    {
        if (InputHandler::CheckInputPressed(dynamic_cast<IFocus *>(panel1), e))
            return;

        if (InputHandler::CheckInputPressed(dynamic_cast<IFocus *>(panel2), e))
            return;

        InputContent::ExecuteInputPressed(e);
    }
    void SplitContainer::ExecuteInputReleased(MouseEventArgs &e)
    {
        if (InputHandler::CheckInputReleased(dynamic_cast<IFocus *>(panel1), e))
            return;
        if (InputHandler::CheckInputReleased(dynamic_cast<IFocus *>(panel2), e))
            return;
        InputContent::ExecuteInputReleased(e);
    }

    void SplitContainer::ExecuteInputMove(MouseEventArgs &e)
    {
        if (InputHandler::CheckInputMove(dynamic_cast<IFocus *>(panel1), e))
            return;
        if (InputHandler::CheckInputMove(dynamic_cast<IFocus *>(panel2), e))
            return;

        InputContent::ExecuteInputMove(e);
    }

    void SplitContainer::ExecuteInputScroll(MouseEventArgs &e)
    {
        if (InputHandler::CheckInputScroll(dynamic_cast<IFocus *>(panel1), e))
            return;
        if (InputHandler::CheckInputScroll(dynamic_cast<IFocus *>(panel2), e))
            return;

        InputContent::ExecuteInputScroll(e);
    }

    void SplitContainer::ExecuteKeyDown(KeyEventArgs &e)
    {
        if (InputHandler::CheckKeyDown(dynamic_cast<IFocus *>(panel1), e))
            return;
        if (InputHandler::CheckKeyDown(dynamic_cast<IFocus *>(panel2), e))
            return;

        if (!e.Handled)
            InputContent::ExecuteKeyDown(e);
    }

    void SplitContainer::ExecuteKeyUp(KeyEventArgs &e)
    {
        if (InputHandler::CheckKeyUp(dynamic_cast<IFocus *>(panel1), e))
            return;
        if (InputHandler::CheckKeyUp(dynamic_cast<IFocus *>(panel2), e))
            return;

        if (!e.Handled)
            InputContent::ExecuteKeyUp(e);
    }
}
