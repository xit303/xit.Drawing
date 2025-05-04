#include <OpenGL/Scene2D.h>
#include <OpenGL/OpenGLExtensions.h>

namespace xit::OpenGL
{
    Scene2D *Scene2D::currentScene = nullptr;

    Scene2D::Scene2D()
    {
        createBuffer = nullptr;
        swapBuffers = nullptr;
        invalidator = nullptr;
        invalidationCount = 0;
        invalidationRaised = 0;
        updateCounter = 0;
        isInvalidating = false;
        invalidationTimer.SetInterval(10);
        invalidationTimer.Elapsed.Add(&Scene2D::InvalidationTimerElapsed, this);
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

    void Scene2D::InvalidationTimerElapsed(EventArgs &e)
    {
        if (isInvalidating)
        {
            if (currentScene)
            {
                EventArgs e;
                currentScene->Invalidated(e);
            }

            invalidationTimer.Stop();
            isInvalidating = false;
        }
    }

    void Scene2D::Invalidate(LayoutManager *visual)
    {
        if (currentScene)
        {
            if (!isInvalidating)
            {
                isInvalidating = true;

                currentScene->invalidator = visual;
                currentScene->invalidatorName = visual->GetName(); // TODO visual->Type().Name;
    
                currentScene->invalidationCount++;
                currentScene->updateCounter++;
            }

            currentScene->invalidationTimer.Restart();
        }
    }

    void Scene2D::MakeCurrent(Scene2D *scene)
    {
        currentScene = scene;
    }
}
