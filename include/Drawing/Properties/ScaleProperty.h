#pragma once

#include <Event.h>

namespace xit::Drawing
{
    class ScaleProperty
    {
    private:
        float scaleX;
        float scaleY;

        void HandleScaleChanged()
        {
            // Notify derived classes of scale change
            EventArgs e;
            ScaleChanged(e);
            OnScaleChanged(e);
        }

    protected:
        virtual void OnScaleChanged(EventArgs &e) {}

    public:
        virtual void SetDPIScale(float scaleX, float scaleY)
        {
            if (scaleX <= 0)
                scaleX = 1;
            if (scaleY <= 0)
                scaleY = 1;

            this->scaleX = scaleX;
            this->scaleY = scaleY;

            // Notify derived classes of scale change
            HandleScaleChanged();
        }
        __always_inline float GetScaleX() const { return scaleX; }
        __always_inline float GetScaleY() const { return scaleY; }

        Event<EventArgs &> ScaleChanged;

        ScaleProperty() : scaleX(1.0f), scaleY(1.0f) {}
    };
}