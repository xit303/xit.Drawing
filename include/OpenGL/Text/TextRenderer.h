#pragma once

#include <IO/IO.h>

#include <glad/glad.h>
#include <glm.hpp>

#include <OpenGL/Shaders/ShaderProgram.h>
#include <OpenGL/AttributeBuffer/AttributeBufferList.h>

namespace xit::OpenGL
{
    class TextRenderer
    {
    private:
        static bool isInitialized;
        static ShaderProgram* textShader;
        static AttributeBufferList* attributeBufferList;
        static AttributeBuffer* vertexDataBuffer;
        static AttributeBuffer* texCoordsDataBuffer;

    public:
        static void Initialize();
        static void RenderText(const std::string& fontName, int fontSize, const std::string& text, int x, int y, int z, glm::vec4& color);
    };
}
