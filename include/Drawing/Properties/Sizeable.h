#pragma once

#include <Event.h>
#include <MathHelper.h>
#include <IO/IO.h>
#include <cmath>

namespace xit::Drawing
{
    class Sizeable
    {
    private:
        int width;
        int height;

        int minWidth;
        int minHeight;

        int maxWidth;
        int maxHeight;

        int scaledWidth;
        int scaledHeight;

        int scaledMinWidth;
        int scaledMinHeight;

        int scaledMaxWidth;
        int scaledMaxHeight;

        float scaleX;
        float scaleY;

        bool SetWidthPrivate(int value)
        {
            if (width != value)
            {
                if (value != -1 && value < minWidth)
                    value = minWidth;
                if (maxWidth != -1 && value > maxWidth)
                    value = maxWidth;

                width = value;

                if (width != -1)
                    scaledWidth = (int)std::round((float)width * scaleX);
                else
                    scaledWidth = -1;

                HandleWidthChanged();
                return true;
            }
            return false;
        }
        bool SetHeightPrivate(int value)
        {
            if (height != value)
            {
                if (value != -1 && value < minHeight)
                    value = minHeight;
                if (maxHeight != -1 && value > maxHeight)
                    value = maxHeight;

                height = value;

                if (height != -1)
                    scaledHeight = (int)std::round((float)height * scaleY);
                else
                    scaledHeight = -1;

                HandleHeightChanged();
                return true;
            }
            return false;
        }

        void SetMinWidthPrivate(int value)
        {
            int minWidth = GetMinWidth();
            if (minWidth != value)
            {
                minWidth = value;

                scaledMinWidth = (int)std::round((float)minWidth * scaleX);

                // TODO is this correct. Does this cause any problems?
                if (minWidth != 0)
                {
                    if (width != -1 && width < minWidth)
                    {
                        SetWidth(minWidth);
                        HandleSizeChanged();
                    }
                    if (maxWidth != -1 && maxWidth <= minWidth)
                        SetMaxWidth(minWidth + 1);
                }

                HandleMinWidthChanged();
            }
        }
        void SetMinHeightPrivate(int value)
        {
            if (minHeight != value)
            {
                minHeight = value;

                scaledMinHeight = (int)std::round((float)minHeight * scaleY);

                // TODO is this correct. Does this cause any problems?
                if (minHeight != 0)
                {
                    if (height != -1 && height < minHeight)
                    {
                        SetHeight(minHeight);
                        HandleSizeChanged();
                    }
                    if (maxHeight != -1 && maxHeight <= minHeight)
                        SetMaxHeight(minHeight + 1);
                }

                HandleMinHeightChanged();
            }
        }

        void SetMaxWidthPrivate(int value)
        {
            if (maxWidth != value)
            {
                if (value < -1)
                {
                    Logger::Log(LogLevel::Warning, "Visual", "SetMaxWidth value was < -1 and has been corrected");
                    value = -1;
                }

                maxWidth = value;
                HandleMaxWidthChanged();

                if (maxWidth != -1)
                {
                    scaledMaxWidth = (int)std::round((float)maxWidth * scaleX);

                    if (width > maxWidth)
                    {
                        SetWidth(maxWidth);
                        HandleSizeChanged();
                    }
                    if (minWidth >= maxWidth && maxWidth >= 1)
                        SetMinWidth(maxWidth - 1);
                }
                else
                    scaledMaxWidth = -1;
            }
        }
        void SetMaxHeightPrivate(int value)
        {
            if (maxHeight != value)
            {
                if (value < -1)
                {
                    Logger::Log(LogLevel::Warning, "Visual", "SetMaxHeight value was < -1 and has been corrected");
                    value = -1;
                }

                maxHeight = value;
                HandleMaxHeightChanged();

                if (maxHeight != -1)
                {
                    scaledMaxHeight = (int)std::round((float)maxHeight * scaleY);

                    if (height > maxHeight)
                    {
                        SetHeight(maxHeight);
                        HandleSizeChanged();
                    }
                    if (minHeight >= maxHeight && maxHeight >= 1)
                        SetMinHeight(maxHeight - 1);
                }
                else
                    scaledMaxHeight = -1;
            }
        }

        void HandleWidthChanged()
        {
            EventArgs e;
            WidthChanged(*this, e);
            OnWidthChanged(e);
        }
        void HandleHeightChanged()
        {
            EventArgs e;
            HeightChanged(*this, e);
            OnHeightChanged(e);
        }

        void HandleMinWidthChanged()
        {
            EventArgs e;
            MinWidthChanged(*this, e);
            OnMinWidthChanged(e);
        }
        void HandleMinHeightChanged()
        {
            EventArgs e;
            MinHeightChanged(*this, e);
            OnMinHeightChanged(e);
        }

        void HandleMaxWidthChanged()
        {
            EventArgs e;
            MaxWidthChanged(*this, e);
            OnMaxWidthChanged(e);
        }
        void HandleMaxHeightChanged()
        {
            EventArgs e;
            MaxHeightChanged(*this, e);
            OnMaxHeightChanged(e);
        }

        void HandleSizeChanged()
        {
            EventArgs e;
            SizeChanged(*this, e);
            OnSizeChanged(e);
        }

    public:
        __always_inline int GetWidth() const { return scaledWidth; }
        void SetWidth(int value)
        {
            if (SetWidthPrivate(value))
                HandleSizeChanged();
        }
        __always_inline int GetHeight() const { return scaledHeight; }
        void SetHeight(int value)
        {
            if (SetHeightPrivate(value))
                HandleSizeChanged();
        }

        __always_inline int GetMinWidth() const { return scaledMinWidth; }
        void SetMinWidth(int value) { SetMinWidthPrivate(value); }
        __always_inline int GetMinHeight() const { return scaledMinHeight; }
        void SetMinHeight(int value) { SetMinHeightPrivate(value); }

        __always_inline int GetMaxWidth() const { return scaledMaxWidth; }
        void SetMaxWidth(int value) { SetMaxWidthPrivate(value); }
        __always_inline int GetMaxHeight() const { return scaledMaxHeight; }
        void SetMaxHeight(int value) { SetMaxHeightPrivate(value); }

        Event<Sizeable &, EventArgs &> WidthChanged;
        Event<Sizeable &, EventArgs &> HeightChanged;
        Event<Sizeable &, EventArgs &> MinWidthChanged;
        Event<Sizeable &, EventArgs &> MinHeightChanged;
        Event<Sizeable &, EventArgs &> MaxWidthChanged;
        Event<Sizeable &, EventArgs &> MaxHeightChanged;
        Event<Sizeable &, EventArgs &> SizeChanged;

        Sizeable()
        {
            width = height = -1;
            minWidth = minHeight = 0;
            maxWidth = maxHeight = -1;

            scaleX = scaleY = 1;
            Scale(scaleX, scaleY);
        }

        Sizeable(int uniformSize)
        {
            width = height = uniformSize;
            minWidth = minHeight = 0;
            maxWidth = maxHeight = -1;

            scaleX = scaleY = 1;
            Scale(scaleX, scaleY);
        }

        Sizeable(int width, int height)
        {
            this->width = width;
            this->height = height;

            minWidth = minHeight = 0;
            maxWidth = maxHeight = -1;

            scaleX = scaleY = 1;
            Scale(scaleX, scaleY);
        }

        ~Sizeable() = default;

        void SetSize(int width, int height)
        {
            bool set = SetWidthPrivate(width);
            set |= SetHeightPrivate(height);

            if (set)
                HandleSizeChanged();
        }

        void Scale(float factorX, float factorY)
        {
            scaleX = factorX;
            scaleY = factorY;

            if (width != -1)
                scaledWidth = (int)std::round((float)width * scaleX);
            else
                scaledWidth = -1;

            if (height != -1)
                scaledHeight = (int)std::round((float)height * scaleY);
            else
                scaledHeight = -1;

            scaledMinWidth = (int)std::round((float)minWidth * scaleX);
            scaledMinHeight = (int)std::round((float)minHeight * scaleY);

            if (maxWidth != -1)
                scaledMaxWidth = (int) std::round((float)maxWidth * scaleX);
            else
                scaledMaxWidth = -1;

            if (maxHeight != -1)
                scaledMaxHeight = (int)std::round((float)maxHeight * scaleY);
            else
                scaledMaxHeight = -1;
        }

        void ResetScale()
        {
            scaleX = scaleY = 1;
            Scale(scaleY, scaleY);
        }

    protected:
        virtual void OnWidthChanged(EventArgs &e) { (void)e; }
        virtual void OnHeightChanged(EventArgs &e) { (void)e; }

        virtual void OnMinWidthChanged(EventArgs &e) { (void)e; }
        virtual void OnMinHeightChanged(EventArgs &e) { (void)e; }

        virtual void OnMaxWidthChanged(EventArgs &e) { (void)e; }
        virtual void OnMaxHeightChanged(EventArgs &e) { (void)e; }

        virtual void OnSizeChanged(EventArgs &e) { (void)e; }
    };
}

using namespace xit::Drawing;
