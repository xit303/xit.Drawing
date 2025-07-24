#pragma once

#include <Timers/Timer.h>
#include <Drawing/ScrollBar.h>
#include <Drawing/ScrollLogic.h>
#include <Drawing/ContentContainer.h>

namespace xit::Drawing
{
    class ScrollViewer : public ContentContainer, public ScrollLogic
    {
    private:
        // Container contentContainer;
        VScrollBar verticalScrollBar;
        HScrollBar horizontalScrollBar;

        Timer scrollBarTimer;
        bool isScrollBarAlwaysVisible;

        Rectangle clientBounds;

        void ScrollBarTimerTick(EventArgs &e);

        void ShowScrollBars();
        void HideScrollBars();

        bool ScrollHorizontal(int delta);
        bool ScrollVertical(int delta);

    protected:
        virtual void OnInputEnter(EventArgs &e) override;
        virtual void OnInputLeave(MouseEventArgs &e) override;

        virtual void OnInputMove(MouseEventArgs &e) override;
        virtual void OnInputScroll(MouseEventArgs &e) override;

        virtual void OnKeyDown(KeyEventArgs &e) override;

        virtual void OnVisibilityChanged(EventArgs &e) override;
        virtual void OnEnabledChanged(EventArgs &e) override;

        virtual void OnUpdate(const Rectangle &bounds) override;
        virtual void OnRender() override;

    public:
        inline bool IsScrollBarAlwaysVisible() { return isScrollBarAlwaysVisible; }
        inline void SetIsScrollBarAlwaysVisible(bool value)
        {
            if (isScrollBarAlwaysVisible != value)
            {
                isScrollBarAlwaysVisible = value;
            }
        }

        const Rectangle &ClientBounds = clientBounds;

        ScrollViewer();
        ~ScrollViewer();

        void ScrollToTop();
        void ScrollToLeft();
        void ScrollToBottom();
        void ScrollToRight();
        void ScrollToVerticalOffset(int offset);
        void ScrollToHorizontalOffset(int offset);

        virtual void SetDPIScale(float scaleX, float scaleY) override;
        virtual Size Measure(const Size &availableSize) override;
    };
}
