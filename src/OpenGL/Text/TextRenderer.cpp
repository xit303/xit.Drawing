#include <OpenGL/Text/TextRenderer.h>
#include <OpenGL/Text/FontStorage.h>
#include <OpenGL/Scene2D.h>
#include <OpenGL/OpenGLExtensions.h>

#include <gtc/type_ptr.hpp>

namespace xit::OpenGL
{
    bool TextRenderer::isInitialized = false;
    ShaderProgram *TextRenderer::textShader = nullptr;
    AttributeBufferList *TextRenderer::attributeBufferList = nullptr;
    AttributeBuffer *TextRenderer::vertexDataBuffer = nullptr;
    AttributeBuffer *TextRenderer::texCoordsDataBuffer = nullptr;

    void TextRenderer::Initialize()
    {
        if (!isInitialized)
        {
            textShader = new ShaderProgram();
            attributeBufferList = new AttributeBufferList();

            //std::string vertexShaderSource = "#version 330 core\nuniform mat4 projection;layout(location = 0) in vec3 iPosition;layout(location = 1) in vec2 iTexCoord;out vec2 TexCoord;void main(){gl_Position = projection * vec4(iPosition, 1.0);TexCoord = iTexCoord;}";
            std::string vertexShaderSource = File::ReadAllText("Resources/Shaders/TextShader.vert");
            //std::string fragmentShaderSource = "#version 330 core\nuniform sampler2D text;uniform vec4 textColor;in vec2 TexCoord;out vec4 fragColor;void main(){vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoord).r);fragColor = textColor * sampled;}";
            std::string fragmentShaderSource = File::ReadAllText("Resources/Shaders/TextShader.frag");

            if (textShader->Create(vertexShaderSource, fragmentShaderSource, nullptr))
            {
                // configure VAO/VBO for texture quads
                // -----------------------------------
                vertexDataBuffer = attributeBufferList->CreateAttributeBuffer("iPosition");
                vertexDataBuffer->BindShader(textShader);

                texCoordsDataBuffer = attributeBufferList->CreateAttributeBuffer("iTexCoord");
                texCoordsDataBuffer->BindShader(textShader);

                textShader->AssertValid();
            }

            isInitialized = true;
        }
    }

    void TextRenderer::RenderText(const std::string &fontName, int fontSize, const std::string &text, int x, int y, int z, glm::vec4 &color)
    {
        Initialize();

        CharacterList &characterList = FontStorage::FindOrCreate(fontName, fontSize);
        if (characterList.empty())
            return;

        // activate corresponding render state
        textShader->Bind();
        textShader->SetUniformMatrix4("projection", glm::value_ptr(Scene2D::CurrentScene().ProjectionMatrix));
        textShader->SetUniform4("textColor", color.r, color.g, color.b, color.a);
        glActiveTexture(GL_TEXTURE0);
        attributeBufferList->Bind();

        const float *texCoords = OpenGLExtensions::RectangleTexCoords;

        // moved from loop below to avoid setting this value
        texCoordsDataBuffer->SetData(12, texCoords, false, 2);

        size_t textLength = text.length();

        int rows = 0;

        for (size_t i = 0; i < textLength; i++)
        {
            char c = text[i];
            if (c == '\n')
                rows++;
        }

        int xStart = x;
        y += rows * characterList.FontHeight;

        // iterate through all characters
        for (size_t i = 0; i < textLength; i++)
        {
            char c = text[i];

            if (c == '\n')
            {
                y -= characterList.FontHeight;
                x = xStart;
                continue;
            }

            Character character = characterList[c];

            // if (characterList.TryGetValue(c, character))
            {
                int left = x + character.Bearing.X;
                int top = y - (character.GlyphSize.GetHeight() - character.Bearing.Y);

                int width = character.GlyphSize.GetWidth();
                int height = character.GlyphSize.GetHeight();

                // update VBO for each character
                int vertices[] =
                    {
                    left, top + height, z,
                    left, top, z,
                    left + width, top, z,

                    left + width, top + height, z,
                    left, top + height, z,
                    left + width, top, z,
                    };
                // int* vertices = OpenGLExtensions::CreateRectangle(left, top, z, width, height);

                // render glyph texture over quad
                glBindTexture(GL_TEXTURE_2D, character.TextureID);

                // update content of VBO memory
                vertexDataBuffer->SetData(18, vertices, 3);

                // render quad
                glDrawArrays(GL_TRIANGLES, 0, 6);
                // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
                x += character.Advance;
            }
            // else
            // {
            //     Logger::Log(LogLevel::Error, "TextRenderer.RenderText", "Specified character not found %c", c);
            // }
        }

        attributeBufferList->Unbind();

        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
