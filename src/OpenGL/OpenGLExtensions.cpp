#include <OpenGL/OpenGLExtensions.h>

namespace xit::OpenGL
{
    const float OpenGLExtensions::RectangleTexCoords[] =
    {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,

        1.0f, 0.0f,
        0.0f, 0.0f,
        1.0f, 1.0f
    };

    const float OpenGLExtensions::InvalidBrush[] =
        {
            1, 0, 0, 1, // top left
            1, 0, 0, 1, // bottom left
            1, 0, 0, 1, // bottom right

            1, 0, 0, 1, // top right
            1, 0, 0, 1, // top left
            1, 0, 0, 1, // bottom right
    };

    const float OpenGLExtensions::TransparentBrush[] =
        {
            0, 0, 0, 0, // top left
            0, 0, 0, 0, // bottom left
            0, 0, 0, 0, // bottom right

            0, 0, 0, 0, // top right
            0, 0, 0, 0, // top left
            0, 0, 0, 0, // bottom right
    };

    // vec3 OpenGLExtensions::ColorToVec3(Color& color)
    // {
    //     return vec3(color.R / 255.0f, color.G / 255.0f, color.B / 255.0f);
    // }

    // float* OpenGLExtensions::ColorToFloat3(Color& color)
    // {
    //     return new float[] { color.R / 255.0f, color.G / 255.0f, color.B / 255.0f };
    // }

    // vec4 OpenGLExtensions::ColorToVec4(Color& color)
    // {
    //     return vec4(color.R / 255.0f, color.G / 255.0f, color.B / 255.0f, color.A / 255.0f);
    // }

    // vec4 OpenGLExtensions::ColorToVec4(Color& color, float opacity)
    // {
    //     return vec4(color.R / 255.0f, color.G / 255.0f, color.B / 255.0f, color.A / 255.0f * opacity);
    // }

    // Color* OpenGLExtensions::BrushToColor(SolidColorBrush& solidColorBrush)
    // {
    //     return new Color((byte)(solidColorBrush.Color()->A * (float)solidColorBrush.Opacity), solidColorBrush.Color()->R, solidColorBrush.Color()->G, solidColorBrush.Color()->B);
    // }

    // float* OpenGLExtensions::ColorToFloat4(Color& color)
    // {
    //     return new float[] { color.R / 255.0f, color.G / 255.0f, color.B / 255.0f, color.A / 255.0f };
    // }

    float *OpenGLExtensions::CreateSolidColorBrush(const SolidColorBrush *solidColorBrush)
    {
        glm::vec4 color = solidColorBrush->GetColor();
        return CreateSolidColorBrush(color.r, color.g, color.b, color.a, (float)solidColorBrush->GetOpacity());
    }

    glm::vec4 OpenGLExtensions::CreateSolidColorBrush(float r, float g, float b)
    {
        return vec4(r, g, b, 1);
    }

    // float* OpenGLExtensions::CreateSolidColorBrush(const Color& color, float opacity)
    // {
    //     float c1R = color.R / 255.0f;
    //     float c1G = color.G / 255.0f;
    //     float c1B = color.B / 255.0f;
    //     float c1A = color.A / 255.0f * opacity;

    //     //buffer[0] = buffer[4] = buffer[8] = buffer[12] = buffer[16] = buffer[20] = c1R;
    //     //buffer[1] = buffer[5] = buffer[9] = buffer[13] = buffer[17] = buffer[21] = c1G;
    //     //buffer[2] = buffer[6] = buffer[10] = buffer[14] = buffer[18] = buffer[22] = c1B;
    //     //buffer[3] = buffer[7] = buffer[11] = buffer[15] = buffer[19] = buffer[23] = c1A;

    //     return new float[]
    //     {
    //         c1R, c1G, c1B, c1A, // top left
    //         c1R, c1G, c1B, c1A, // bottom left
    //         c1R, c1G, c1B, c1A, // bottom right

    //         c1R, c1G, c1B, c1A, // top right
    //         c1R, c1G, c1B, c1A, // top left
    //         c1R, c1G, c1B, c1A, // bottom right
    //     };
    // }

    float *OpenGLExtensions::CreateSolidColorBrush(float r, float g, float b, float a, float opacity)
    {
        float c1R = r;
        float c1G = g;
        float c1B = b;
        float c1A = a * opacity;

        // buffer[0] = buffer[4] = buffer[8] = buffer[12] = buffer[16] = buffer[20] = c1R;
        // buffer[1] = buffer[5] = buffer[9] = buffer[13] = buffer[17] = buffer[21] = c1G;
        // buffer[2] = buffer[6] = buffer[10] = buffer[14] = buffer[18] = buffer[22] = c1B;
        // buffer[3] = buffer[7] = buffer[11] = buffer[15] = buffer[19] = buffer[23] = c1A;

        return new float[30]
        {
            c1R, c1G, c1B, c1A, // top left
            c1R, c1G, c1B, c1A, // bottom left
            c1R, c1G, c1B, c1A, // bottom right

            c1R, c1G, c1B, c1A, // top right
            c1R, c1G, c1B, c1A, // top left
            c1R, c1G, c1B, c1A, // bottom right
        };
    }

    // float* OpenGLExtensions::CreateLinearGradientColorBrush(const Color& color1, const Color& color2, float angle) //LinearGradientBrush linearGradientBrush)
    // {
    //     //foreach(GradientStop gradientStop in linearGradientBrush.GradientStops)
    //     //{

    //     //}

    //     float c1R = color1.R / 255.0f;
    //     float c1G = color1.G / 255.0f;
    //     float c1B = color1.B / 255.0f;
    //     float c1A = color1.A / 255.0f;

    //     float c2R = color2.R / 255.0f;
    //     float c2G = color2.G / 255.0f;
    //     float c2B = color2.B / 255.0f;
    //     float c2A = color2.A / 255.0f;

    //     return new float[]
    //     {
    //         c1R, c1G, c1B, c1A, // top left
    //         c2R, c2G, c2B, c2A, // bottom left
    //         c2R, c2G, c2B, c2A, // bottom right

    //         c1R, c1G, c1B, c1A, // top right
    //         c1R, c1G, c1B, c1A, // top left
    //         c2R, c2G, c2B, c2A, // bottom right
    //     };

    //     //buffer[0] = buffer[12] = buffer[16] = c1R;
    //     //buffer[4] = buffer[8] = buffer[20] = c2R;

    //     //buffer[1] = buffer[13] = buffer[17] = c1G;
    //     //buffer[5] = buffer[9] = buffer[21] = c2G;

    //     //buffer[2] = buffer[14] = buffer[18] = c1B;
    //     //buffer[6] = buffer[10] = buffer[22] = c2B;

    //     //buffer[3] = buffer[15] = buffer[19] = c1A;
    //     //buffer[7] = buffer[11] = buffer[23] = c2A;
    // }

    float *OpenGLExtensions::CreateRectangle(float width, float height)
    {
        return CreateRectangle(0, 0, width, height);
    }

    float *OpenGLExtensions::CreateRectangle(float x, float y, float width, float height)
    {
        return new float[]
        {
            x, y + height, 0.0f, 0.0f, // bottom left
            x, y, 0.0f, 1.0f,          // top left
            x + width, y, 1.0f, 1.0f,  // top right

            x + width, y + height, 1.0f, 0.0f, // bottom right
            x, y + height, 0.0f, 0.0f,         // bottom left
            x + width, y, 1.0f, 1.0f,          // top right
        };
    }

    float *OpenGLExtensions::CreateRectangle(float x, float y, float z, float width, float height)
    {
        // z *= 0.001f;

        return new float[]
        {
            x, y + height, z,
            x, y, z,
            x + width, y, z,

            x + width, y + height, z,
            x, y + height, z,
            x + width, y, z,
        };
    }

    int *OpenGLExtensions::CreateRectangle(int x, int y, int z, int width, int height)
    {
        return new int[]
        {
            x, y + height, z,
            x, y, z,
            x + width, y, z,

            x + width, y + height, z,
            x, y + height, z,
            x + width, y, z,
        };
    }

    void OpenGLExtensions::UpdateRectangle(float *vertices, float x, float y, float z, float width, float height)
    {
        // z *= 0.001f;

        vertices[0] = vertices[3] = vertices[12] = x;
        vertices[4] = vertices[7] = vertices[16] = y;
        vertices[2] = vertices[5] = vertices[8] = vertices[11] = vertices[14] = vertices[17] = z;

        vertices[6] = vertices[9] = vertices[15] = x + width;
        vertices[1] = vertices[10] = vertices[13] = y + height;
    }

    void OpenGLExtensions::UpdateRectangle(int *vertices, int x, int y, int z, int width, int height)
    {
        // z *= 0.001f;

        vertices[0] = vertices[3] = vertices[12] = x;
        vertices[4] = vertices[7] = vertices[16] = y;
        vertices[2] = vertices[5] = vertices[8] = vertices[11] = vertices[14] = vertices[17] = z;

        vertices[6] = vertices[9] = vertices[15] = x + width;
        vertices[1] = vertices[10] = vertices[13] = y + height;
    }

    mat4 OpenGLExtensions::Initialize2D(Scene2D &scene)
    {
        return Initialize2D(scene.GetWidth(), scene.GetHeight());
    }

    mat4 OpenGLExtensions::Initialize2D(int width, int height)
    {
        glClearColor(0, 0, 0, 0);

        // glEnable(GL_DEPTH_TEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);

        return Resize2D(width, height);
    }

    mat4 OpenGLExtensions::Resize2D(Scene2D &scene)
    {
        return Resize2D(scene.GetWidth(), scene.GetHeight());
    }

    mat4 OpenGLExtensions::Resize2D(int width, int height, float zNear, float zFar)
    {
        glViewport(0, 0, width, height);

        return ortho<float>(0, (float)width, 0, (float)height, zNear, zFar);
    }

    void OpenGLExtensions::ClearScene2D()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // glEnable(GL_DEPTH_TEST);
        // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        // glEnable(GL_BLEND);
    }
}
