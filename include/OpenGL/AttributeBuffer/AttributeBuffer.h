#pragma once

#include <OpenGL/VertexBuffers/VertexBuffer.h>
#include <OpenGL/Shaders/ShaderProgram.h>

namespace xit::OpenGL
{
    class AttributeBuffer
    {
    private:
        std::string attributeName;
        VertexBuffer vertexBuffer;
        uint attributeIndex;

    public:
        std::string AttributeName() { return attributeName; }
        const VertexBuffer& GetVertexBuffer() { return vertexBuffer; }
        const uint& AttributeIndex = attributeIndex;

        /// <summary>
        /// Create a new AttributeBuffer storage.
        /// This will create an OpenGL VertexBuffer object and stores the 
        /// attribute name and the attribute index for further access
        /// by the BindShader and SetData Methods.
        /// </summary>
        /// <param name="gl">The OpenGL instance which should be used by this AttributeBuffer.</param>
        /// <param name="attributeName">The name of the attribute in the shader program. This would be "in_Position" if shader code contains -> layout(location = 0) in_Position;</param>
        /// <param name="attributeIndex">The index (or layout location) of the attribute in the shader program. This would be "0" if shader code contains -> layout(location = 0) in_Position;</param>
        /// <exception cref="ArgumentNullException"></exception>
        AttributeBuffer(const std::string& attributeName, uint attributeIndex)
        {
            if (attributeName.empty())
                throw ArgumentNullException("attributeName");

            this->attributeName = attributeName;
            this->attributeIndex = attributeIndex;

            vertexBuffer.Create();
        }

        /// <summary>
        /// Bind the Attribute to the ShaderProgram.
        /// shaderProgram.BindAttributeLocation(openGL, AttributeIndex, AttributeName);
        /// </summary>
        /// <param name="shaderProgram">The ShaderProgram with the compiled shader code, where the Attribute should be bound.</param>
        void BindShader(ShaderProgram* shaderProgram)
        {
            shaderProgram->BindAttributeLocation(attributeIndex, attributeName);
        }

        /// <summary>
        /// This method binds the VertexBuffer (VertexBuffer.Bind(OpenGL gl) to the stored OpenGL class (see constructor)
        /// and finally calls VertexBuffer.SetData(openGL, AttributeIndex, data, isNormalized, stride).
        /// This is just to create a better overview in the progam structure. 
        /// 
        /// Hopefully the compiler unwraps this to spped up calls.
        /// </summary>
        /// <param name="data">An array of float values with the data for the VerrtexBuffer</param>
        /// <param name="isNormalized">Set this to true if the data is already normalized (0-1)</param>
        /// <param name="stride">The number of floats, or the length of the data array</param>
        void SetData(int size, const float* data, bool isNormalized, int stride)
        {
            if (data != nullptr)
            {
                vertexBuffer.Bind();
                vertexBuffer.SetData(attributeIndex, size, data, isNormalized, stride);
                vertexBuffer.Unbind();
            }
        }

        void SetData(int size, const int* data, int stride)
        {
            if (data != nullptr)
            {
                vertexBuffer.Bind();
                vertexBuffer.SetData(attributeIndex, size, data, stride);
                vertexBuffer.Unbind();
            }
        }

        void SetData(int size, const glm::vec4 &data, int stride)
        {
            vertexBuffer.Bind();
            vertexBuffer.SetData(attributeIndex, size, data, stride);
            vertexBuffer.Unbind();
        }
    };
}

using namespace xit::OpenGL;
