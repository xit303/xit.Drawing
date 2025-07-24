#pragma once

#include <Drawing/Container.h>

namespace xit::Drawing
{
    class ContentContainer : public Container
    {
    private:
        Container contentContainer;
        Size desiredContentSize;

        void ContentContainer_ChildAdded(Visual &content, EventArgs &e)
        {
            int row = contentContainer.GetChildCount() - 1;
            content.SetRow(row);

            if (row == 0)
            {
                contentContainer.SetRows("Auto");
            }
            else
            {
                contentContainer.SetRows(contentContainer.GetRows() + ",Auto");
            }

            ChildAdded(content, e);
        }
        void ContentContainer_ChildRemoved(Visual &content, EventArgs &e)
        {
            size_t count = contentContainer.GetChildCount();
            std::string rows;

            // TODO this is not efficient
            for (size_t i = 0; i < count; i++)
            {
                rows += "Auto";
                if (i < (count - 1))
                    rows += ",";
            }

            contentContainer.SetRows(rows);
            ChildRemoved(content, e);
        }

    protected:
        void SetContentContainerVisibility(const Visibility &value)
        {
            contentContainer.SetVisibility(value);
        }

        void OnColumnsChanged(EventArgs &e) override
        {
            contentContainer.SetColumns(GetColumns());
            SetNumberOfColumns(contentContainer.GetNumberOfColumns());
        }

        void OnColumnSpacingChanged(EventArgs &e) override
        {
            contentContainer.SetColumnSpacing(GetColumnSpacing());
        }
        void OnRowsChanged(EventArgs &e) override
        {
            contentContainer.SetRows(GetRows());
            SetNumberOfRows(contentContainer.GetNumberOfColumns());
        }
        void OnRowSpacingChanged(EventArgs &e) override
        {
            contentContainer.SetRowSpacing(GetRowSpacing());
        }

        void OnHorizontalAlignmentChanged(EventArgs &e) override
        {
            contentContainer.SetHorizontalAlignment(GetHorizontalAlignment());
        }
        void OnVerticalAlignmentChanged(EventArgs &e) override
        {
            contentContainer.SetVerticalAlignment(GetVerticalAlignment());
        }

        void OnHorizontalContentAlignmentChanged(EventArgs &e) override
        {
            contentContainer.SetHorizontalContentAlignment(GetHorizontalContentAlignment());
        }
        void OnVerticalContentAlignmentChanged(EventArgs &e) override
        {
            contentContainer.SetVerticalContentAlignment(GetVerticalContentAlignment());
        }

        void OnColumnChanged(EventArgs &e) override
        {
            contentContainer.SetColumn(GetColumn());
        }
        void OnColumnSpanChanged(EventArgs &e) override
        {
            contentContainer.SetColumnSpan(GetColumnSpan());
        }

        void OnRowChanged(EventArgs &e) override
        {
            contentContainer.SetRow(GetRow());
        }
        void OnRowSpanChanged(EventArgs &e) override
        {
            contentContainer.SetRowSpan(GetRowSpan());
        }

        void OnInputEnter(EventArgs &e) override
        {
            InputContent::OnInputEnter(e);
            contentContainer.ExecuteInputEnter(e);
        }
        void OnInputLeave(MouseEventArgs &e) override
        {
            InputContent::OnInputLeave(e);
            contentContainer.ExecuteInputLeave(e);
        }

        void OnInputMove(MouseEventArgs &e) override
        {
            InputContent::OnInputMove(e);
            contentContainer.ExecuteInputMove(e);
        }
        void OnInputScroll(MouseEventArgs &e) override
        {
            contentContainer.ExecuteInputScroll(e);
        }

        void OnInputPressed(MouseEventArgs &e) override
        {
            InputContent::OnInputPressed(e);
            contentContainer.ExecuteInputPressed(e);
        }
        void OnInputReleased(MouseEventArgs &e) override
        {
            InputContent::OnInputReleased(e);
            contentContainer.ExecuteInputReleased(e);
        }

        void OnKeyDown(KeyEventArgs &e) override
        {
            InputContent::OnKeyDown(e);
            if (!e.Handled)
            {
                contentContainer.ExecuteKeyDown(e);
            }
        }

        void OnKeyUp(KeyEventArgs &e) override
        {
            InputContent::OnKeyUp(e);
            contentContainer.ExecuteKeyUp(e);
        }

        void OnVisibilityChanged(EventArgs &e) override
        {
            InputContent::OnVisibilityChanged(e);
            contentContainer.SetIsVisible(GetIsVisible());
        }
        void OnEnabledChanged(EventArgs &e) override
        {
            contentContainer.SetEnabled(GetEnabled());
        }
        void OnForegroundChanged(EventArgs &e) override
        {
            InputContent::OnForegroundChanged(e);
            contentContainer.SetForeground(GetForeground());
        }

        int OnMeasureWidth(int available) override
        {
            return contentContainer.MeasureWidth(available);
        }
        int OnMeasureHeight(int available) override
        {
            return contentContainer.MeasureHeight(available);
        }

        void OnRender() override
        {
            InputContent::OnRender();
            contentContainer.Render();
        }

    public:
        Event<Visual &, EventArgs &> ChildAdded;
        Event<Visual &, EventArgs &> ChildRemoved;
        
        ContentContainer()
        {
            contentContainer.SetInheritForeground(true);
            contentContainer.SetRow(1);
            contentContainer.ChildAdded.Add(&ContentContainer::ContentContainer_ChildAdded, this);
            contentContainer.ChildRemoved.Add(&ContentContainer::ContentContainer_ChildRemoved, this);

            contentContainer.SetParent(this);
        }

        inline Container &GetContentContainer() { return contentContainer; }
        inline Size GetDesiredContentSize() const { return desiredContentSize; }

        inline std::string GetColumns() const { return contentContainer.GetColumns(); }
        inline void SetColumns(const std::string &value)
        {
            contentContainer.SetColumns(value);
        }

        inline int GetColumnSpacing() const { return contentContainer.GetColumnSpacing(); }
        inline void SetColumnSpacing(int value)
        {
            contentContainer.SetColumnSpacing(value);
        }

        inline std::string GetRows() const { return contentContainer.GetRows(); }
        inline void SetRows(const std::string &value)
        {
            contentContainer.SetRows(value);
        }

        inline int GetRowSpacing() const { return contentContainer.GetRowSpacing(); }
        inline void SetRowSpacing(int value)
        {
            contentContainer.SetRowSpacing(value);
        }

        inline size_t GetNumberOfColumns() const { return contentContainer.GetNumberOfColumns(); }
        inline size_t GetNumberOfRows() const { return contentContainer.GetNumberOfRows(); }

        inline const Thickness &GetPadding() const { return contentContainer.GetPadding(); }
        inline virtual void SetPadding(const Thickness &value) override
        {
            contentContainer.SetPadding(value);
        }

        inline HorizontalAlignment GetHorizontalContentAlignment() const { return contentContainer.GetHorizontalContentAlignment(); }
        virtual inline void SetHorizontalContentAlignment(const HorizontalAlignment &value) override { contentContainer.SetHorizontalContentAlignment(value); }

        inline VerticalAlignment GetVerticalContentAlignment() const { return contentContainer.GetVerticalContentAlignment(); }
        virtual inline void SetVerticalContentAlignment(const VerticalAlignment &value) override { contentContainer.SetVerticalContentAlignment(value); }

        void AddChild(Visual *content)
        {
            contentContainer.AddChild(content);
        }

        void InsertChild(size_t position, Visual *content)
        {
            contentContainer.InsertChild(position, content);
        }

        void RemoveChild(Visual *content)
        {
            contentContainer.RemoveChild(content);
        }

        bool ContainsChild(Visual *content)
        {
            return contentContainer.ContainsChild(content);
        }

        std::vector<Visual *> &GetChildren()
        {
            return contentContainer.GetChildren();
        }

        Visual *GetChildAt(size_t index)
        {
            return contentContainer.GetChildAt(index);
        }

        size_t GetChildCount()
        {
            return contentContainer.GetChildCount();
        }

        int GetChildIndex(Visual *content)
        {
            return contentContainer.GetChildIndex(content);
        }

        void SetDPIScale(float scaleX, float scaleY) override
        {
            InputContent::SetDPIScale(scaleX, scaleY);
            contentContainer.SetDPIScale(scaleX, scaleY);
        }

        Size Measure(const Size &availableSize) override
        {
            Size dSize = InputContent::Measure(availableSize);
    
            Size contentSize(dSize.GetWidth() - GetPadding().GetWidth() - GetBorderThickness().GetWidth(), dSize.GetHeight() - GetPadding().GetHeight() - GetBorderThickness().GetHeight());
            desiredContentSize = contentContainer.Measure(contentSize);
    
            if (desiredContentSize.GetWidth() > 0 && 
                desiredContentSize.GetWidth() < availableSize.GetWidth() && 
                GetHorizontalAlignment() != HorizontalAlignment::Stretch)
            {
                dSize.SetWidth(desiredContentSize.GetWidth());
            }
            if (desiredContentSize.GetHeight() > 0 && 
                desiredContentSize.GetHeight() < availableSize.GetHeight() && 
                GetVerticalAlignment() != VerticalAlignment::Stretch)
            {
                dSize.SetHeight(desiredContentSize.GetHeight());
            }
            return dSize;
        }

        Size GetDesiredContentSize()
        {
            return desiredContentSize;
        }
    };
} // namespace xit::Drawing
