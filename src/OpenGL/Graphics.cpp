#include <OpenGL/Graphics.h>
#include <OpenGL/OpenGLExtensions.h>
#include <OpenGL/Texture.h>
#include <Drawing/Brushes/SolidColorBrush.h>

#include <gtc/type_ptr.hpp>

#ifdef USE_AI_SUGGESTED_FIX
#include <algorithm>
#endif

namespace xit::OpenGL
{
    bool Graphics::isInitialized = false;
    ShaderProgram *Graphics::shaderProgram = nullptr;
    AttributeBufferList *Graphics::attributeBufferList = nullptr;
    AttributeBuffer *Graphics::vertexDataBuffer = nullptr;
    AttributeBuffer *Graphics::texCoordsDataBuffer = nullptr;
    AttributeBuffer *Graphics::colorDataBuffer = nullptr;
    AttributeBuffer *Graphics::foregroundColorDataBuffer = nullptr;
    AttributeBuffer *Graphics::borderColorDataBuffer = nullptr;

    void Graphics::InitShader()
    {
        if (!isInitialized)
        {
            isInitialized = true;

            shaderProgram = new ShaderProgram();
            attributeBufferList = new AttributeBufferList();

            std::string vertexShaderSource = File::ReadAllText("Resources/Shaders/Shader.vert");
            std::string fragmentShaderSource = File::ReadAllText("Resources/Shaders/Shader.frag");

            if (vertexShaderSource.empty() || !shaderProgram->CreateVertexShader(vertexShaderSource))
            {
                vertexShaderSource = "#version 330 core\nuniform mat4 projection;\nlayout(location = 0) in vec3 iPosition;\nlayout(location = 2) in vec4 iColor;out vec4 Color;void main(void){Color = iColor;gl_Position = projection * vec4(iPosition, 1.0);}";
                shaderProgram->CreateVertexShader(vertexShaderSource);
            }

            if (fragmentShaderSource.empty() || !shaderProgram->CreateFragmentShader(fragmentShaderSource))
            {
                fragmentShaderSource = "#version 330 core\nin vec4 Color;\nout vec4 fragColor;\nvoid main(void){fragColor = Color;}";
                shaderProgram->CreateFragmentShader(fragmentShaderSource);
            }

            if (shaderProgram->Link())
            {
                vertexDataBuffer = attributeBufferList->CreateAttributeBuffer("iPosition");
                vertexDataBuffer->BindShader(shaderProgram);

                texCoordsDataBuffer = attributeBufferList->CreateAttributeBuffer("iTexCoord");
                texCoordsDataBuffer->BindShader(shaderProgram);

                colorDataBuffer = attributeBufferList->CreateAttributeBuffer("iBackgroundColor");
                colorDataBuffer->BindShader(shaderProgram);

                borderColorDataBuffer = attributeBufferList->CreateAttributeBuffer("iBorderColor");
                borderColorDataBuffer->BindShader(shaderProgram);

                foregroundColorDataBuffer = attributeBufferList->CreateAttributeBuffer("iTextColor");
                foregroundColorDataBuffer->BindShader(shaderProgram);

                shaderProgram->AssertValid();
            }
        }
    }

    float *Graphics::GetBrushColor(const BrushBase *brush)
    {
        const SolidColorBrush *solidColorBrush = dynamic_cast<const SolidColorBrush *>(brush);

        if (solidColorBrush)
        {
            return OpenGLExtensions::CreateSolidColorBrush(solidColorBrush);
        }
        return nullptr;
    }

    void Graphics::DrawRectangle(int x, int renderX, int y, int renderY, int z, int width, int height, glm::vec3 rotation, float *backgroundBrush, float *foregroundBrush, float *borderBrush, const Texture *backgroundTexture, const Texture *borderTexture, const Thickness &borderThickness, const CornerRadius &cornerRadius)
    {
        static int vertexRect[18] = {0};
        if (!isInitialized)
            InitShader();

        const Scene2D &currentScene = Scene2D::CurrentScene();

#ifdef USE_AI_SUGGESTED_FIX
        // Ensure we have valid scene dimensions to prevent rendering issues during resize
        int sceneWidth = currentScene.GetWidth();
        int sceneHeight = currentScene.GetHeight();

        if (sceneWidth <= 0 || sceneHeight <= 0)
            return; // Skip rendering if scene has invalid dimensions

        // Clamp rendering coordinates to scene bounds to prevent artifacts
        renderX = std::max(0, std::min(renderX, sceneWidth));
        renderY = std::max(0, std::min(renderY, sceneHeight));
        width = std::max(0, std::min(width, sceneWidth - renderX));
        height = std::max(0, std::min(height, sceneHeight - renderY));

        if (width <= 0 || height <= 0)
            return; // Skip rendering if rectangle has no area

#endif

        shaderProgram->Bind();
        shaderProgram->SetUniformMatrix4("projection", glm::value_ptr(currentScene.ProjectionMatrix));
        // TODO shaderProgram->SetUniformMatrix4(gl, "model", modelMatrix.to_array());

        shaderProgram->SetUniform4("iCornerRadius",
                                   (float)cornerRadius.TopLeft,
                                   (float)cornerRadius.TopRight,
                                   (float)cornerRadius.BottomRight,
                                   (float)cornerRadius.BottomLeft);
        shaderProgram->SetUniform4("iBorderThickness",
                                   (float)borderThickness.GetLeft(),
                                   (float)borderThickness.GetTop(),
                                   (float)borderThickness.GetRight(),
                                   (float)borderThickness.GetBottom());
        shaderProgram->SetUniform2("iLocation", (float)x, (float)y);
        shaderProgram->SetUniform3("iRotation", rotation.x, rotation.y, rotation.z);
        shaderProgram->SetUniform2("iSize", (float)width, (float)height);
#ifdef USE_AI_SUGGESTED_FIX
        shaderProgram->SetUniform2("iResolution", (float)sceneWidth, (float)sceneHeight);
#else
        shaderProgram->SetUniform2("iResolution", (float)currentScene.GetWidth(), (float)currentScene.GetHeight());
#endif
        shaderProgram->SetUniform1("iTime", (float)currentScene.GetFrameTime());

        attributeBufferList->Bind();

        OpenGLExtensions::UpdateRectangle(vertexRect, renderX, renderY, z, width, height);
        vertexDataBuffer->SetData(18, vertexRect, 3);
        texCoordsDataBuffer->SetData(12, OpenGLExtensions::RectangleTexCoords, false, 2);

        if (!backgroundTexture && !backgroundBrush)
        {
            shaderProgram->SetUniform1("iIsTexture", 0);
            colorDataBuffer->SetData(24, OpenGLExtensions::TransparentBrush, false, 4);
        }
        else
        {
            if (backgroundTexture && backgroundTexture->GetIsCreated())
            {
                shaderProgram->SetUniform1("iIsTexture", 1);
                shaderProgram->SetUniform1("iTextureChannels", static_cast<float>(backgroundTexture->GetChannels()));
                backgroundTexture->Bind();
            }
            else if (backgroundBrush)
            {
                shaderProgram->SetUniform1("iIsTexture", 0);
                colorDataBuffer->SetData(24, backgroundBrush, false, 4);
            }
            else
            {
                shaderProgram->SetUniform1("iIsTexture", 0);
            }
        }

        if (foregroundBrush)
        {
            shaderProgram->SetUniform1("iIsColoredTexture", 1);
            foregroundColorDataBuffer->SetData(24, foregroundBrush, false, 4);
        }
        else
        {
            shaderProgram->SetUniform1("iIsColoredTexture", 0);
        }

        if (borderTexture && borderTexture->GetIsCreated())
        {
            shaderProgram->SetUniform1("iIsBorderTexture", 1);
            shaderProgram->SetUniform1("iBorderTextureChannels", static_cast<float>(borderTexture->GetChannels()));
            borderTexture->Bind();
        }
        else if (borderBrush && borderBrush != OpenGLExtensions::TransparentBrush)
        {
            shaderProgram->SetUniform1("iIsBorderTexture", 0);
        }
        else if (borderBrush)
        {
            borderColorDataBuffer->SetData(24, borderBrush, false, 4);
            shaderProgram->SetUniform1("iIsBorderTexture", 0);
        }

        //  Draw the square.
        glDrawArrays(GL_TRIANGLES, 0, 6);

        attributeBufferList->Unbind();
        shaderProgram->Unbind();
    }
}
