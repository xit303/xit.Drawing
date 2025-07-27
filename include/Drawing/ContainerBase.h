#pragma once

#include <Event.h>
#include <Drawing/VisualBase/GridContainerBase.h>
#include <Drawing/Grid.h>
#include <Drawing/InputContent.h>

namespace xit::Drawing
{
    struct FixedContentPosition
    {
    private:
        Visual *content;
        Point position;

    public:
        const Visual *GetContent() const { return content; }
        void SetContent(Visual *value)
        {
            if (content != value)
            {
                content = value;
            }
        }

        __always_inline const Point &GetPosition() const { return position; }
        void SetPosition(const Point &value)
        {
            if (position != value)
            {
                position = value;
            }
        }

        FixedContentPosition(Visual *content, int x, int y)
            : content(content)
        {
            position.X = x;
            position.Y = y;
        }
    };

    class ContainerBase : public GridContainerBase, public InputContent
    {
    private:
        mutable std::mutex contentWidthFixedPositionsMutex;
        std::list<FixedContentPosition *> contentWidthFixedPositions;

        /// <summary>
        /// Stores all hidde (IsVisible = false) content while this ContainerBase is Visible.
        /// This ensures that our content will remain invisible even if this ContainerBase changes its vislibility
        /// </summary>
        //std::list<Visual *> hiddenContent;

        /// <summary>
        /// Stores all disabled content while this ContainerBase is Enabled.
        /// This ensures that our content will remain disabled even if this ContainerBase changes its enabled state
        /// </summary>
        //std::list<Visual *> disabledContent;

        /// <summary>
        /// If we are in OnIsVisibleChanged, we dont want to trigger Invalidate() on this ContainerBase if a content is changing to Visible.
        /// </summary>
        bool isVisibleChanging;

        std::vector<Visual *> children;

        // void Children_CollectionChanged(NotifyCollectionChangedEventArgs<Visual *> &e);

        // void Content_EnabledChanged(EnabledProperty &sender, EventArgs &e);
        // void Content_VisibleChanged(VisibilityProperty &sender, EventArgs &e);

    protected:
        Grid grid;

        virtual void OnColumnsChanged(EventArgs &e) override;
        virtual void OnColumnSpacingChanged(EventArgs &e) override;
        virtual void OnRowsChanged(EventArgs &e) override;
        virtual void OnRowSpacingChanged(EventArgs &e) override;

        virtual void OnHorizontalContentAlignmentChanged(EventArgs &e) override;
        virtual void OnVerticalContentAlignmentChanged(EventArgs &e) override;

        // virtual void OnEnabledChanged(EventArgs &e) override;
        // virtual void OnVisibilityChanged(EventArgs &e) override;

        virtual void OnZIndexChanged(EventArgs &e) override;
        virtual void OnForegroundChanged(EventArgs &e) override;
        virtual void OnUpdateLayout(LayoutVisualState *value) override;

        virtual int OnMeasureWidth(int available) override;
        virtual int OnMeasureHeight(int available) override;

        virtual void OnUpdate(const Rectangle &bounds) override;
        virtual void OnRender() override;

        virtual void OnGotKeyboardFocus(EventArgs &e) override;
        virtual void OnLostKeyboardFocus(EventArgs &e) override;

        virtual void InvokeChildAdded(Visual &content);
        virtual void InvokeChildRemoved(Visual &content);

        virtual void OnChildAdded(Visual &content, EventArgs &e);
        virtual void OnChildRemoved(Visual &content, EventArgs &e);

    public:
        __always_inline const std::vector<Visual *> GetChildren() const { return children; }

        Event<Visual &, EventArgs &> ChildAdded;
        Event<Visual &, EventArgs &> ChildRemoved;

        ContainerBase();

        void AddChild(Visual *content);
        void InsertChild(size_t position, Visual *content);
        void RemoveChild(Visual *content);
        void RemoveChildAt(size_t index);
        bool ContainsChild(Visual *content);

        std::vector<Visual *> &GetChildren();
        Visual *GetChildAt(size_t index);
        size_t GetChildCount();
        int GetChildIndex(Visual *content);

        virtual void SetDPIScale(float scaleX, float scaleY) override;

        // virtual void ExecuteInputEnter(EventArgs& e) override;
        virtual void ExecuteInputLeave(MouseEventArgs &e) override;

        virtual void ExecuteInputPressed(MouseEventArgs &e) override;
        virtual void ExecuteInputReleased(MouseEventArgs &e) override;

        virtual void ExecuteInputMove(MouseEventArgs &e) override;
        virtual void ExecuteInputScroll(MouseEventArgs &e) override;
        virtual void ExecuteKeyDown(KeyEventArgs &e) override;
        virtual void ExecuteKeyUp(KeyEventArgs &e) override;

        /*static bool CheckInputEnter(Visual* content, MouseEventArgs& e)
        {
            if (!content)
                return false;

            if (IsHit(*content, e.Position))
            {
                ContainerBase* container = dynamic_cast<ContainerBase*>(content);
                if (container)
                {
                    container->ExecuteInputPressed(e);
                    return e.Handled;
                }

                InputContent* inputContent = dynamic_cast<InputContent*>(content);

                if (inputContent && inputContent->HandleMouse())
                {
                    inputContent->ExecuteInputPressed(e);
                    return e.Handled;
                }
            }
            return false;
        }*/

        void SetLeft(Visual &content, int value);
        void SetTop(Visual &content, int value);
    };
}
