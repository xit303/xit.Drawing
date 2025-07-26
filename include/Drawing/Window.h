#pragma once

#include "Drawing/WindowSettings.h"
#include "Drawing/Properties/WindowStyleProperty.h"
#include "Drawing/Properties/WindowStateProperty.h"
#include <Drawing/InputContent.h>
#include <OpenGL/Scene2D.h>
#include <semaphore>

namespace xit::Drawing
{
    class Window : public InputContent,
                   public WindowStyleProperty,
                   public WindowStateProperty
    {
    private:
        // Screen screen;
        std::string title;

        GLFWwindow *window;

        Visual *content;

        WindowSettings windowSettings;

        bool topmost;
        bool handleMouse;
        bool isInputPressed;
        bool isMouseOver;
        bool canFocus;
        bool isFocused;
        bool isDestroyed;

        float contentScaleX;
        float contentScaleY;

        Rectangle clientBounds;
        Scene2D scene;

        std::binary_semaphore mainLoopSemaphore{0};

        // Background buffer for partial redraws
        GLuint backgroundFramebuffer;
        GLuint backgroundTexture;
        GLuint backgroundDepthBuffer;
        std::vector<Rectangle> dirtyRegions;
        bool useBackgroundBuffer;
        bool backgroundBufferInitialized;

        void App_Closing(EventArgs &e);

    protected:
        bool isClosing;

        virtual void OnInvalidated(EventArgs &e) override;

    public:
        inline bool GetTopmost() { return topmost; }
        void SetTopmost(bool value) { topmost = value; }

        Visual *GetContent() { return content; }
        void SetContent(Visual *value);

        inline bool IsClosing() { return isClosing; }
        void SetIsClosing(bool value) { isClosing = value; }

        const WindowSettings &GetWindowSettings() const { return windowSettings; }

        inline bool IsInputPressed() { return isInputPressed; }
        inline bool IsMouseOver() { return isMouseOver; }

        const Rectangle &GetClientBounds() { return clientBounds; }

        __always_inline const std::string &GetTitle() { return title; }
        void SetTitle(const std::string &value);

        Window();

    protected:
        virtual void OnWindowStateChanged(EventArgs &e) override;

        virtual void OnUpdate(const Rectangle &bounds) override;
        virtual void OnRender() override;

        virtual bool OnClosing(bool canceled);
        virtual void OnInitializeComponent() = 0;

        virtual void OnContentChanged(Visual *oldContent, Visual *newContent) {}
        virtual void OnContentInvalidated(Visual* childVisual);
        virtual void OnChildInvalidated(LayoutManager* childLayout) override;

    public:
        void ExecuteInputEnter(EventArgs &e);
        void ExecuteInputLeave(MouseEventArgs &e) override;

        void ExecuteInputPressed(MouseEventArgs &e) override;
        void ExecuteInputReleased(MouseEventArgs &e) override;

        void ExecuteInputScroll(MouseEventArgs &e) override;
        void ExecuteInputMove(MouseEventArgs &e) override;

        void ExecuteKeyDown(KeyEventArgs &e) override;
        void ExecuteKeyUp(KeyEventArgs &e) override;

        bool Initialize(const WindowSettings &windowSettings, const std::string &title);
        void Show();
        void Close();

        virtual void SaveState();

        virtual int MeasureWidth(int availableSize) override;
        virtual int MeasureHeight(int availableSize) override;

        virtual void SetDPIScale(float scaleX, float scaleY) override;

        void SetWindowPos(int left, int top);
        void SetWindowSize(int width, int height);
        void DoRender();

        // Background buffer methods
        void InitializeBackgroundBuffer();
        void ResizeBackgroundBuffer(int width, int height);
        void DestroyBackgroundBuffer();
        void AddDirtyRegion(const Rectangle& region);
        void OptimizeDirtyRegions();
        void ClearDirtyRegions();
        void CopyFromBackgroundBuffer(const Rectangle& region);
        void CopyToBackgroundBuffer(const Rectangle& region);
        bool HasDirtyRegions() const;
        
        // Public methods for background buffer control
        void SetBackgroundBufferEnabled(bool enabled);
        bool IsBackgroundBufferEnabled() const;
        void InvalidateRegion(const Rectangle& region);
    };
}
