#pragma once

#include <Drawing/InputContent.h>

namespace xit::Drawing
{
    class Border : public InputContent
    {
    private:
        Visual *content;

    public:
        Visual *GetContent() const { return content; }
        void SetContent(Visual *value)
        {
            if (content != nullptr)
            {
                content->SetParent(nullptr);
            }

            Visual *oldContent = content;
            content = value;

            if (content != nullptr)
            {
                content->SetDPIScale(GetScaleX(), GetScaleY());
                content->SetParent(this);
            }

            OnContentChanged(oldContent, content);
        }

        Border()
        {
            content = nullptr;
        }

    protected:
        virtual void OnContentChanged(Visual *oldContent, Visual *newContent)
        {
            // Invalidate();
        }

        int OnMeasureWidth(int available) override
        {
            if (content)
                return content->MeasureWidth(available);

            return InputContent::OnMeasureWidth(available);
        }

        int OnMeasureHeight(int availableSize) override
        {
            if (content)
                return content->MeasureHeight(availableSize);

            return InputContent::OnMeasureHeight(availableSize);
        }

        virtual void OnUpdate(const Rectangle &bounds) override
        {
            // even if we have no content we can update the border
            InputContent::OnUpdate(bounds);

            if (content)
            {
                // Use optimized BoxModel method for client bounds calculation
                Rectangle clientBounds = GetClientRectangle(GetLeft(), GetTop(), GetActualWidth(), GetActualHeight());
                content->UpdateLayout(clientBounds);
            }
        }

        virtual void OnRender() override
        {
            // even if we have no content we can draw the border
            InputContent::OnRender();

            if (content)
                content->Render();
        }

    public:
        virtual void SetDPIScale(float scaleX, float scaleY) override
        {
            InputContent::SetDPIScale(scaleX, scaleY);
            if (content)
                content->SetDPIScale(scaleX, scaleY);
        }
    };
}
