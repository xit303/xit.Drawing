#pragma once

#include <OpenGL/Shaders/ShaderProgram.h>
#include <OpenGL/AttributeBuffer/AttributeBufferList.h>
#include <OpenGL/Texture.h>
#include <Drawing/Brushes/BrushBase.h>
#include <Drawing/Properties/Thickness.h>
#include <Drawing/Properties/CornerRadius.h>

namespace xit::OpenGL
{
    class Graphics
    {
    private:
        static bool isInitialized;
        static ShaderProgram* shaderProgram;
        static AttributeBufferList* attributeBufferList;
        static AttributeBuffer* vertexDataBuffer;
        static AttributeBuffer* texCoordsDataBuffer;
        static AttributeBuffer* colorDataBuffer;
        static AttributeBuffer* foregroundColorDataBuffer;
        static AttributeBuffer* borderColorDataBuffer;

    public:
        //static Graphics()
        //{
        //    InitShader();
        //}

    private:
        static void InitShader();

    public:
        static float* GetBrushColor(const BrushBase* brush);

        static void DrawRectangle(int x, int renderX, int y, int renderY, int z, int width, int height, glm::vec3 rotation, float* backgroundBrush, float* foregroundBrush, float* borderBrush, const Texture* backgroundTexture, const Texture* borderTexture, const Thickness& borderThickness, const CornerRadius& cornerRadius);
    };
}
