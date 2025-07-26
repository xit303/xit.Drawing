#pragma once

#include <Event.h>
#include <glm.hpp>
#include <Drawing/Rectangle.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace glm;

namespace xit::OpenGL
{
    typedef void(*Action)();

    class Scene2D
    {
    private:
        Rectangle sceneRect;

        mat4 projectionMatrix;

        Action createBuffer;
        Action swapBuffers;

        static Scene2D* currentScene;

    public:
        const Rectangle& SceneRect = sceneRect;

        double GetFrameTime() const { return glfwGetTime(); }

        __always_inline int GetWidth() const { return sceneRect.GetWidth(); }
        __always_inline int GetHeight() const { return sceneRect.GetHeight(); }

        const mat4& ProjectionMatrix = projectionMatrix;

        static Scene2D& CurrentScene() { return *currentScene; }

        void CreateBuffer();
        void CreateBuffer(Action action);

        void SwapBuffers();
        void SwapBuffers(Action action);

        Scene2D();

        void Initialize(int width, int height);
        void Resize(int width, int height);

        static void MakeCurrent(Scene2D* scene);
    };
}

using namespace xit::OpenGL;
