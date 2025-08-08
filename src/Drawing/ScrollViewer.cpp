#include <Drawing/ScrollViewer.h>
#include <Drawing/UIDefaults.h>
#include <Input/InputHandler.h>

namespace xit::Drawing
{
    //******************************************************************************
    // Properties
    //******************************************************************************

    //******************************************************************************
    // Constructor
    //******************************************************************************

    ScrollViewer::ScrollViewer()
    {
        isScrollBarAlwaysVisible = false;

        SetName("ScrollViewer");

        SetHandleMouse(true);
        SetHandleKeyboard(true);
        SetClipToBounds(true);
        SetInheritForeground(true);

        SetColumns("*");
        SetRows("*");

        verticalScrollBar.SetVisibility(Visibility::Hidden);
        horizontalScrollBar.SetVisibility(Visibility::Hidden);

        scrollBarTimer.Elapsed.Add(&ScrollViewer::ScrollBarTimerTick, this);
        scrollBarTimer.SetInterval(2000);
    }

    ScrollViewer::~ScrollViewer()
    {
        scrollBarTimer.Stop();
        scrollBarTimer.Elapsed.Remove(&ScrollViewer::ScrollBarTimerTick, this);
    }

    //******************************************************************************
    // Public
    //******************************************************************************

    void ScrollViewer::ScrollToTop()
    {
        ScrollLogic::ScrollToTop();
        verticalScrollBar.SetValue(0);
        GetContentContainer().SetMargin(GetScrollMargin());
        Invalidate();
    }

    void ScrollViewer::ScrollToLeft()
    {
        ScrollLogic::ScrollToLeft();
        horizontalScrollBar.SetValue(0);
        GetContentContainer().SetMargin(GetScrollMargin());
        Invalidate();
    }

    void ScrollViewer::ScrollToBottom()
    {
        ScrollLogic::ScrollToBottom();
        verticalScrollBar.SetValue(verticalScrollBar.GetMaximum());
        GetContentContainer().SetMargin(GetScrollMargin());
        Invalidate();
    }

    void ScrollViewer::ScrollToRight()
    {
        ScrollLogic::ScrollToRight();
        horizontalScrollBar.SetValue(horizontalScrollBar.GetMaximum());
        GetContentContainer().SetMargin(GetScrollMargin());
        Invalidate();
    }

    void ScrollViewer::ScrollToVerticalOffset(int offset)
    {
        ScrollLogic::ScrollToVerticalOffset(offset);
        verticalScrollBar.SetValue(std::round((float)offset * GetScaleY()));
        GetContentContainer().SetMargin(GetScrollMargin());
        Invalidate();
    }

    void ScrollViewer::ScrollToHorizontalOffset(int offset)
    {
        ScrollLogic::ScrollToHorizontalOffset(offset);
        horizontalScrollBar.SetValue(std::round((float)offset * GetScaleX()));
        GetContentContainer().SetMargin(GetScrollMargin());
        Invalidate();
    }

    //******************************************************************************
    // Private
    //******************************************************************************

    void ScrollViewer::ScrollBarTimerTick(EventArgs &e)
    {
        HideScrollBars();
    }

    void ScrollViewer::ShowScrollBars()
    {
        bool start = false;

        if (GetExtentHeight() > GetActualHeight() || isScrollBarAlwaysVisible)
        {
            verticalScrollBar.SetVisibility(Visibility::Visible);
            start = true;
        }
        if (GetExtentWidth() > GetActualWidth() || isScrollBarAlwaysVisible)
        {
            horizontalScrollBar.SetVisibility(Visibility::Visible);
            start = true;
        }

        if (start)
        {
            bool invalidate = !scrollBarTimer.Enabled;
            scrollBarTimer.Stop();
            scrollBarTimer.Start();

            if (invalidate)
            {
                Invalidate();
            }
        }
        else
        {
            HideScrollBars();
        }
    }
    void ScrollViewer::HideScrollBars()
    {
        if (!isScrollBarAlwaysVisible)
        {
            verticalScrollBar.SetVisibility(Visibility::Hidden);
            horizontalScrollBar.SetVisibility(Visibility::Hidden);
        }

        if (GetExtentHeight() <= GetActualHeight())
        {
            return;
        }

        if (scrollBarTimer.Enabled)
        {
            scrollBarTimer.Stop();
            Invalidate();
        }
    }

    bool ScrollViewer::ScrollHorizontal(int delta)
    {
        if (GetExtentWidth() != 0 && GetExtentWidth() > GetActualWidth())
        {
            int max = GetExtentWidth() - GetActualWidth();
            float factor = (float)GetActualWidth() / (float)max;

            ScrollLogic::ScrollHorizontal(delta, GetActualWidth());

            horizontalScrollBar.SetValue(std::round(factor * (float)std::abs(GetScrollMarginLeft())));

            GetContentContainer().SetMargin(GetScrollMargin());
            verticalScrollBar.SetMargin(-GetScrollMarginLeft(), 0, 0, 0);

            Invalidate();

            return true;
        }
        return false;
    }
    bool ScrollViewer::ScrollVertical(int delta)
    {
        if (GetExtentHeight() != 0 && GetExtentHeight() > GetActualHeight())
        {
            int realHeight = GetActualHeight() - GetBorderThickness().GetHeight() - GetPadding().GetHeight();
            int max = GetExtentHeight() - realHeight;
            float factor = (float)realHeight / (float)max;

            int lastValue = (int)((float)GetScrollMarginTop() * GetScaleY());

            if (delta < 0)
            {
                // scroll down (move content up)
                int result = lastValue - (int)((float)UIDefaults::DefaultItemHeight * GetScaleY());
                if (result > -max)
                    SetScrollMarginTop(GetScrollMarginTop() - UIDefaults::DefaultItemHeight);
                else
                    SetScrollMarginTop(-(int)((float)max / GetScaleY()));
            }
            else
            {
                // scroll up (move content down)
                int result = lastValue + (int)((float)UIDefaults::DefaultItemHeight * GetScaleY());
                if (result < 0)
                    SetScrollMarginTop(GetScrollMarginTop() + UIDefaults::DefaultItemHeight);
                else
                    SetScrollMarginTop(0);
            }

            verticalScrollBar.SetValue(std::round(factor * (float)std::abs(GetScrollMarginTop())));

            GetContentContainer().SetMargin(GetScrollMargin());
            horizontalScrollBar.SetMargin(0, -GetScrollMarginTop(), 0, 0);

            Invalidate();

            return true;
        }
        return false;
    }

    //******************************************************************************
    // Protecteds
    //******************************************************************************

    void ScrollViewer::OnInputEnter(EventArgs &e)
    {
        ContentContainer::OnInputEnter(e);
        ShowScrollBars();
    }
    void ScrollViewer::OnInputLeave(MouseEventArgs &e)
    {
        ContentContainer::OnInputLeave(e);
        HideScrollBars();
    }

    void ScrollViewer::OnInputMove(MouseEventArgs &e)
    {
        ContentContainer::OnInputMove(e);
        ShowScrollBars();
    }
    void ScrollViewer::OnInputScroll(MouseEventArgs &e)
    {
        // ShowScrollBars automatically handles if showing is needed or not
        ShowScrollBars();

        GetContentContainer().ExecuteInputScroll(e);

        if (e.Handled)
            return;

        if (InputHandler::IsShift())
        {
            e.Handled = ScrollHorizontal(e.WheelDelta);
        }
        else
        {
            e.Handled = ScrollVertical(e.WheelDelta);
        }
    }

    void ScrollViewer::OnKeyDown(KeyEventArgs &e)
    {
        if (e.Key == CKey::Down)
        {
            ShowScrollBars();
            e.Handled = ScrollVertical(-1);
        }
        else if (e.Key == CKey::Up)
        {
            ShowScrollBars();
            e.Handled = ScrollVertical(1);
        }
        else if (e.Key == CKey::Left)
        {
            ShowScrollBars();
            e.Handled = ScrollHorizontal(-1);
        }
        else if (e.Key == CKey::Right)
        {
            ShowScrollBars();
            e.Handled = ScrollHorizontal(1);
        }

        if (!e.Handled)
        {
            ContentContainer::OnKeyDown(e);
        }
    }

    void ScrollViewer::OnVisibilityChanged(EventArgs &e)
    {
        ContentContainer::OnVisibilityChanged(e);

        if (GetIsVisible())
            ShowScrollBars();
        else
            HideScrollBars();
    }
    void ScrollViewer::OnEnabledChanged(EventArgs &e)
    {
        ContentContainer::OnEnabledChanged(e);
        horizontalScrollBar.SetEnabled(GetEnabled());
        verticalScrollBar.SetEnabled(GetEnabled());
    }

    void ScrollViewer::OnUpdate(const Rectangle &bounds)
    {
        ContentContainer::OnUpdate(bounds);

        // Use cached client bounds from LayoutManager for optimal performance
        Rectangle clientBounds = GetClientBounds();

#ifdef DEBUG_SCROLL_VIEWER
        Rectangle manualClientBounds = GetClientRectangle(GetLeft(), GetTop(), GetActualWidth(), GetActualHeight());
        std::cout << "ScrollViewer::OnUpdate - Manual: ("
                  << manualClientBounds.GetLeft() << "," << manualClientBounds.GetTop()
                  << "," << manualClientBounds.GetWidth() << "," << manualClientBounds.GetHeight() << ")" << std::endl;
        std::cout << "ScrollViewer::OnUpdate - Cached: ("
                  << clientBounds.GetLeft() << "," << clientBounds.GetTop()
                  << "," << clientBounds.GetWidth() << "," << clientBounds.GetHeight() << ")" << std::endl;
        std::cout << "ScrollViewer values: GetLeft()=" << GetLeft() << " GetTop()=" << GetTop()
                  << " GetActualWidth()=" << GetActualWidth() << " GetActualHeight()=" << GetActualHeight() << std::endl;
#endif

        GetContentContainer().UpdateLayout(clientBounds);

        // Calculate scroll bar bounds - still using border thickness directly for scroll bars
        const Thickness &borderThickness = GetBorderThickness();
        Rectangle scrollBarBounds(
            GetLeft() + borderThickness.GetLeft(),
            GetTop() + borderThickness.GetTop(),
            GetActualWidth() - borderThickness.GetWidth(),
            GetActualHeight() - borderThickness.GetHeight());

        int availableWidth = scrollBarBounds.GetWidth();
        int availableHeight = scrollBarBounds.GetHeight();

        float overshotWidth = static_cast<float>(GetExtentWidth() - GetActualWidth());
        float overshotHeight = static_cast<float>(GetExtentHeight() - GetActualHeight());

        // Adjust available dimensions if scrollbars are visible
        if (overshotHeight > 0)
            availableWidth -= verticalScrollBar.GetWidth();

        if (overshotWidth > 0)
            availableHeight -= horizontalScrollBar.GetHeight();

        // Update horizontal scrollbar
        horizontalScrollBar.SetWidth(availableWidth);
        horizontalScrollBar.SetMaximum(static_cast<float>(GetExtentWidth()));

        float horizontalFactor = (overshotWidth > 0) ? (float)availableWidth / overshotWidth : 0.0f;

        if (horizontalFactor == 0.0f)
            SetScrollMarginLeft(0);

        horizontalScrollBar.SetValue(std::round(horizontalFactor * (float)std::abs(GetScrollMarginLeft())));

        // Update vertical scrollbar
        verticalScrollBar.SetHeight(availableHeight);
        verticalScrollBar.SetMaximum(static_cast<float>(GetExtentHeight()));

        float verticalFactor = (overshotHeight > 0) ? (float)availableHeight / overshotHeight : 0.0f;

        if (verticalFactor == 0.0f)
            SetScrollMarginTop(0);

        verticalScrollBar.SetValue(std::round(verticalFactor * (float)std::abs(GetScrollMarginTop())));

        // Update margins and bounds
        GetContentContainer().SetMargin(GetScrollMargin());
        horizontalScrollBar.SetMargin(0, -GetScrollMarginTop(), 0, 0);
        verticalScrollBar.SetMargin(-GetScrollMarginLeft(), 0, 0, 0);

        horizontalScrollBar.UpdateLayout(scrollBarBounds);
        verticalScrollBar.UpdateLayout(scrollBarBounds);
    }
    void ScrollViewer::OnRender()
    {
        ContentContainer::OnRender();
        horizontalScrollBar.Render();
        verticalScrollBar.Render();
    }

    //******************************************************************************
    // Publics
    //******************************************************************************

    void ScrollViewer::SetDPIScale(float scaleX, float scaleY)
    {
        ContentContainer::SetDPIScale(scaleX, scaleY);
        horizontalScrollBar.SetDPIScale(scaleX, scaleY);
        verticalScrollBar.SetDPIScale(scaleX, scaleY);
    }

    Size ScrollViewer::Measure(const Size &availableSize)
    {
        Size dSize = ContentContainer::Measure(availableSize);
        Size desiredContentSize = GetDesiredContentSize();

        SetExtentWidth(desiredContentSize.GetWidth());
        SetExtentHeight(desiredContentSize.GetHeight());

        return dSize;
    }
}
