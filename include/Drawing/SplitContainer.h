#pragma once

#include <Drawing/Grid.h>
#include <Drawing/InputContent.h>
#include <Drawing/Properties/Orientation.h>
#include <Drawing/Properties/OrientationDirection.h>

namespace xit::Drawing
{
    class SplitContainer : public InputContent
    {
    private:
        Grid grid;
        int panel1Index;
        int panel2Index;
        Visual* panel1;
        Visual* panel2;
        
        Rectangle clientBounds;

        Orientation orientation;
        OrientationDirection orientationDirection;
        std::vector<Visual *> children;

    public:
        Visual* GetPanel1() { return panel1; }
        void SetPanel1(Visual* value)
        {
            if (panel1 != value)
            {
                if (panel1 != nullptr)
                {
                    children.erase(std::remove(children.begin(), children.end(), panel1), children.end());
                }
                panel1 = value;

                if (panel1 != nullptr)
                {
                    panel1->SetDPIScale(GetScaleX(), GetScaleY());
                    children.push_back(panel1);
                    UpdateOrientation();
                }
                Invalidate();
            }
        }

        Visual* GetPanel2() { return panel2; }
        void SetPanel2(Visual* value)
        {
            if (panel2 != value)
            {
                if (panel2 != nullptr)
                {
                    panel2->SetParent(nullptr);
                    children.erase(std::remove(children.begin(), children.end(), panel2), children.end());
                }
                panel2 = value;

                if (panel2 != nullptr)
                {
                    panel2->SetDPIScale(GetScaleX(), GetScaleY());
                    children.push_back(panel2);
                    panel2->SetParent(this);
                    UpdateOrientation();
                }
                Invalidate();
            }
        }

        Orientation GetOrientation() const { return orientation; }
        void SetOrientation(Orientation value)
        {
            if (orientation != value)
            {
                orientation = value;
                UpdateOrientation();
            }
        }

        OrientationDirection GetOrientationDirection() const { return orientationDirection; }
        void SetOrientationDirection(OrientationDirection value)
        {
            if (orientationDirection != value)
            {
                orientationDirection = value;
                UpdateOrientation();
            }
        }

        Event<EventArgs&> OrientationChanged;

        SplitContainer();
        virtual ~SplitContainer() override = default;

    private:
        void UpdateOrientation();

    protected:
        void OnVisibilityChanged(EventArgs& e) override;
      
        int OnMeasureWidth(int available) override;
        int OnMeasureHeight(int available) override;

        void OnUpdate(const Rectangle& bounds) override;
        void OnRender() override;

        virtual void OnOrientationChanged();

    public:
        virtual void SetDPIScale(float scaleX, float scaleY) override;

        virtual Size Measure(const Size& availableSize) override;

        //virtual void ExecuteInputEnter(EventArgs& e) override;
        virtual void ExecuteInputLeave(EventArgs& e) override;

        virtual void ExecuteInputPressed(MouseEventArgs& e) override;
        virtual void ExecuteInputReleased(MouseEventArgs& e) override;

        virtual void ExecuteInputMove(MouseEventArgs& e) override;
        virtual void ExecuteInputScroll(MouseEventArgs& e) override;

        virtual void ExecuteKeyDown(KeyEventArgs& e) override;
        virtual void ExecuteKeyUp(KeyEventArgs& e) override;
    };
}
