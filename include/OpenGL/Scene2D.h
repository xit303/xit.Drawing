#pragma once

#include <Event.h>
#include <Timers/Timer.h>
#include <Drawing/VisualBase/LayoutManager.h>
#include <glm.hpp>
#include <thread>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace glm;

namespace xit::OpenGL
{
    typedef void(*Action)();
    using namespace xit::Drawing::VisualBase;

    class Scene2D
    {
    private:
        Timer invalidationTimer;
        std::mutex invalidationTimerMutex;

        std::list<LayoutManager*> invalidatedVisuals;
       
        Rectangle sceneRect;

        mat4 projectionMatrix;

        mutable int updateCounter;
        mutable int invalidationCount;
        mutable int invalidationRaised;
        mutable bool isInvalidating;
        mutable std::string invalidatorName;
        mutable LayoutManager* invalidator;

        Action createBuffer;
        Action swapBuffers;

        void InvalidationTimerElapsed(EventArgs &e);

        static Scene2D* currentScene;

    public:
        const Rectangle& SceneRect = sceneRect;

        double GetFrameTime() const { return glfwGetTime(); }

        __always_inline int GetWidth() const { return sceneRect.GetWidth(); }
        __always_inline int GetHeight() const { return sceneRect.GetHeight(); }

        const mat4& ProjectionMatrix = projectionMatrix;

        const int& InvalidationCount = invalidationCount;
        const int& InvalidationRaised = invalidationRaised;

        std::string InvalidatorName() { return invalidatorName; }
        LayoutManager* Invalidator() { return invalidator; }

        static Scene2D& CurrentScene() { return *currentScene; }

        void CreateBuffer();
        void CreateBuffer(Action action);

        void SwapBuffers();
        void SwapBuffers(Action action);

        Event<EventArgs&> Invalidated;

        Scene2D();

        void Initialize(int width, int height);
        void Resize(int width, int height);
        void Invalidate(LayoutManager* visual);
        void SetInvalidationDone() { isInvalidating = false; }

        static void MakeCurrent(Scene2D* scene);
    };
}

using namespace xit::OpenGL;
