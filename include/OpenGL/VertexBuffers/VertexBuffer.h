#pragma once

#include <glm.hpp>
#include <OpenGL/VertexBuffers/VertexBufferBase.h>

namespace xit::OpenGL
{
    /// <summary>
    ///
    /// </summary>
    /// <remarks>
    /// Very useful reference for management of VBOs and VBAs:
    /// http://stackoverflow.com/questions/8704801/glvertexattribpointer-clarification
    /// </remarks>
    class VertexBuffer : public VertexBufferBase
    {
    public:
        void SetData(GLuint attributeIndex, int size, const float *data, bool isNormalised, int stride)
        {
            //  Set the data, specify its shape and assign it to a vertex attribute (so shaders can bind to it).
            glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, GL_STATIC_DRAW);
            glVertexAttribPointer(attributeIndex, stride, GL_FLOAT, isNormalised, stride * sizeof(float), nullptr);
            glEnableVertexAttribArray(attributeIndex);
        }

        void SetData(GLuint attributeIndex, int size, const int *data, int stride)
        {
            //  Set the data, specify its shape and assign it to a vertex attribute (so shaders can bind to it).
            glBufferData(GL_ARRAY_BUFFER, size * sizeof(int), data, GL_STATIC_DRAW);
            glVertexAttribPointer(attributeIndex, stride, GL_INT, false, stride * sizeof(int), nullptr);
            glEnableVertexAttribArray(attributeIndex);
        }

        void SetData(GLuint attributeIndex, int size, const glm::vec4 &data, int stride)
        {
            // float tmp[] = { data.a, data.r, data.g, data.b };
            float tmp[] =
            {
                data.r, data.g, data.b, data.a, // top left
                data.r, data.g, data.b, data.a, // bottom left
                data.r, data.g, data.b, data.a, // bottom right

                data.r, data.g, data.b, data.a, // top right
                data.r, data.g, data.b, data.a, // top left
                data.r, data.g, data.b, data.a, // bottom right
            };
            //  Set the data, specify its shape and assign it to a vertex attribute (so shaders can bind to it).
            glBufferData(GL_ARRAY_BUFFER, size * sizeof(int), tmp, GL_STATIC_DRAW);
            glVertexAttribPointer(attributeIndex, stride, GL_INT, false, stride * sizeof(int), nullptr);
            glEnableVertexAttribArray(attributeIndex);
        }

        __always_inline virtual void Bind() override
        {
            VertexBufferBase::Bind(GL_ARRAY_BUFFER);
        }

        __always_inline virtual void Unbind() override
        {
            VertexBufferBase::Unbind(GL_ARRAY_BUFFER);
        }
    };
}

using namespace xit::OpenGL;
