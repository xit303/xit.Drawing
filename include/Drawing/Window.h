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

        std::vector<std::pair<Visual *, Rectangle>> invalidRegions;
        std::atomic<bool> redrawScheduled{false};
        std::mutex invalidRegionsMutex;
        std::binary_semaphore mainLoopSemaphore{0};

        // Double buffering for partial region rendering
        GLuint frontFramebuffer{0};
        GLuint backFramebuffer{0};
        GLuint frontColorTexture{0};
        GLuint backColorTexture{0};
        GLuint frontDepthTexture{0};
        GLuint backDepthTexture{0};
        bool framebuffersInitialized{false};

        // Debug timing for construction to first frame
        std::chrono::steady_clock::time_point constructionStartTime;
        std::chrono::steady_clock::time_point initializeStartTime;
        std::chrono::steady_clock::time_point showStartTime;
        std::chrono::steady_clock::time_point firstFrameCompleteTime;
        bool firstFrameCompleted{false};

        void App_Closing(EventArgs &e);
        void ScheduleRedraw();

        // Double buffering methods
        void InitializeFramebuffers();
        void CleanupFramebuffers();
        void SwapFramebuffers();
        void CopyRegionBetweenFramebuffers(const Rectangle& region);

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

        void InvalidateRegion(Visual *visual, Rectangle bounds);

        Window();

    protected:
        virtual void OnWindowStateChanged(EventArgs &e) override;

        virtual void OnUpdate(const Rectangle &bounds) override;
        virtual void OnRender() override;

        virtual bool OnClosing(bool canceled);
        virtual void OnInitializeComponent() = 0;

        virtual void OnContentChanged(Visual *oldContent, Visual *newContent) {}

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
    };
}
