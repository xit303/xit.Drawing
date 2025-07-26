#include <OpenGL/Scene2D.h>
#include <OpenGL/OpenGLExtensions.h>

#ifdef DEBUG_SCENE2D
#include <iostream>
#endif

namespace xit::OpenGL
{
    Scene2D *Scene2D::currentScene = nullptr;

    Scene2D::Scene2D()
    {
        createBuffer = nullptr;
        swapBuffers = nullptr;
    }

    void Scene2D::CreateBuffer()
    {
        if (createBuffer != nullptr)
            createBuffer();
    }
    void Scene2D::CreateBuffer(Action action)
    {
        createBuffer = action;
    }
    void Scene2D::SwapBuffers()
    {
        if (swapBuffers != nullptr)
            swapBuffers();
    }
    void Scene2D::SwapBuffers(Action action)
    {
        swapBuffers = action;
    }

    void Scene2D::Initialize(int width, int height)
    {
        sceneRect.SetWidth(width);
        sceneRect.SetHeight(height);

        projectionMatrix = OpenGLExtensions::Initialize2D(*this);
    }

    void Scene2D::Resize(int width, int height)
    {
        sceneRect.SetWidth(width);
        sceneRect.SetHeight(height);

        projectionMatrix = OpenGLExtensions::Resize2D(*this);
    }

    void Scene2D::MakeCurrent(Scene2D *scene)
    {
        currentScene = scene;
    }
}
