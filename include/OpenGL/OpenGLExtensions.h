#pragma once

#include <Drawing/Brushes/SolidColorBrush.h>
#include <OpenGL/Scene2D.h>

#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

using namespace glm;

namespace xit::OpenGL
{
    class OpenGLExtensions
    {
    public:
        static const float RectangleTexCoords[];

        // Retruns a red rectangle to indicate that no brush has been set
        static const float InvalidBrush[];

        static const float TransparentBrush[];

        // static vec3 ColorToVec3(Color& color);
        // static float* ColorToFloat3(Color& color);
        // static vec4 ColorToVec4(Color& color);
        // static vec4 ColorToVec4(Color& color, float opacity);

        // static Color* BrushToColor(SolidColorBrush& solidColorBrush);

        // static float* ColorToFloat4(Color& color);

        static float *CreateSolidColorBrush(const SolidColorBrush *solidColorBrush);
        // static float* CreateSolidColorBrush(const Color& color, float opacity = 1.0f);
        static float *CreateSolidColorBrush(float r, float g, float b, float a, float opacity = 1.0f);
        static glm::vec4 CreateSolidColorBrush(float r, float g, float b);

        // static float* CreateLinearGradientColorBrush(const Color& color1, const Color& color2, float angle);

        static float *CreateRectangle(float width, float height);
        static float *CreateRectangle(float x, float y, float width, float height);
        static float *CreateRectangle(float x, float y, float z, float width, float height);
        static int *CreateRectangle(int x, int y, int z, int width, int height);

        static void UpdateRectangle(float *vertices, float x, float y, float z, float width, float height);
        static void UpdateRectangle(int *vertices, int x, int y, int z, int width, int height);

        static mat4 Initialize2D(Scene2D &scene);
        static mat4 Initialize2D(int width, int height);

        static mat4 Resize2D(Scene2D &scene);
        static mat4 Resize2D(int width, int height, float zNear = -100.0f, float zFar = 100.0f);

        static void ClearScene2D();
    };
}
