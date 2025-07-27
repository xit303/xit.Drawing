#include <OpenGL/Text/TextRenderer.h>
#include <OpenGL/Text/FontStorage.h>
#include <OpenGL/Scene2D.h>
#include <OpenGL/OpenGLExtensions.h>

#include <gtc/type_ptr.hpp>

#ifdef DEBUG_TEXT_RENDERER_PERFORMANCE
#include <chrono>
#include <iostream>
#endif

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
#ifdef DEBUG_TEXT_RENDERER_PERFORMANCE
        auto totalStart = std::chrono::high_resolution_clock::now();
        std::cout << "TextRenderer::RenderText - Rendering text '" << text << "' at (" << x << "," << y << ")" << std::endl;
#endif

        Initialize();

#ifdef DEBUG_TEXT_RENDERER_PERFORMANCE
        auto initEnd = std::chrono::high_resolution_clock::now();
        auto initDuration = std::chrono::duration_cast<std::chrono::microseconds>(initEnd - totalStart);
        std::cout << "TextRenderer::RenderText - Initialize() took " << initDuration.count() << "μs" << std::endl;
#endif

        CharacterList &characterList = FontStorage::FindOrCreate(fontName, fontSize);
        if (characterList.empty())
            return;

#ifdef DEBUG_TEXT_RENDERER_PERFORMANCE
        auto fontEnd = std::chrono::high_resolution_clock::now();
        auto fontDuration = std::chrono::duration_cast<std::chrono::microseconds>(fontEnd - initEnd);
        std::cout << "TextRenderer::RenderText - FontStorage::FindOrCreate() took " << fontDuration.count() << "μs" << std::endl;
#endif

        // activate corresponding render state
        textShader->Bind();
        textShader->SetUniformMatrix4("projection", glm::value_ptr(Scene2D::CurrentScene().ProjectionMatrix));
        textShader->SetUniform4("textColor", color.r, color.g, color.b, color.a);
        glActiveTexture(GL_TEXTURE0);
        attributeBufferList->Bind();

#ifdef DEBUG_TEXT_RENDERER_PERFORMANCE
        auto setupEnd = std::chrono::high_resolution_clock::now();
        auto setupDuration = std::chrono::duration_cast<std::chrono::microseconds>(setupEnd - fontEnd);
        std::cout << "TextRenderer::RenderText - OpenGL setup took " << setupDuration.count() << "μs" << std::endl;
#endif

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

#ifdef DEBUG_TEXT_RENDERER_PERFORMANCE
        auto preprocessEnd = std::chrono::high_resolution_clock::now();
        auto preprocessDuration = std::chrono::duration_cast<std::chrono::microseconds>(preprocessEnd - setupEnd);
        std::cout << "TextRenderer::RenderText - Text preprocessing took " << preprocessDuration.count() << "μs for " << textLength << " characters" << std::endl;
        auto renderStart = std::chrono::high_resolution_clock::now();
        int drawCalls = 0;
#endif

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

                // render glyph texture over quad
                glBindTexture(GL_TEXTURE_2D, character.TextureID);

                // update content of VBO memory
                vertexDataBuffer->SetData(18, vertices, 3);

                // render quad
                glDrawArrays(GL_TRIANGLES, 0, 6);

#ifdef DEBUG_TEXT_RENDERER_PERFORMANCE
                drawCalls++;
#endif

                // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
                x += character.Advance;
            }
            // else
            // {
            //     Logger::Log(LogLevel::Error, "TextRenderer.RenderText", "Specified character not found %c", c);
            // }
        }

#ifdef DEBUG_TEXT_RENDERER_PERFORMANCE
        auto renderEnd = std::chrono::high_resolution_clock::now();
        auto renderDuration = std::chrono::duration_cast<std::chrono::microseconds>(renderEnd - renderStart);
        std::cout << "TextRenderer::RenderText - Character rendering took " << renderDuration.count() << "μs for " << drawCalls << " draw calls" << std::endl;
#endif

        attributeBufferList->Unbind();

        glBindTexture(GL_TEXTURE_2D, 0);

#ifdef DEBUG_TEXT_RENDERER_PERFORMANCE
        auto totalEnd = std::chrono::high_resolution_clock::now();
        auto totalDuration = std::chrono::duration_cast<std::chrono::microseconds>(totalEnd - totalStart);
        std::cout << "TextRenderer::RenderText - Total rendering took " << totalDuration.count() << "μs" << std::endl;
#endif
    }
}
