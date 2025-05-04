#pragma once

#include <Drawing/VertexBuffers/VertexBufferBase.h>

namespace xit::OpenGL
{
    class IndexBuffer : public VertexBufferBase
    {
    public:
        __always_inline void SetData(int size, const void* rawData)
        {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, rawData, GL_STATIC_DRAW);
        }

        __always_inline virtual void Bind() override
        {
            VertexBufferBase::Bind(GL_ELEMENT_ARRAY_BUFFER);
        }

        __always_inline virtual void Unbind() override
        {
            VertexBufferBase::Unbind(GL_ELEMENT_ARRAY_BUFFER);
        }
    };
}

using namespace xit::OpenGL;
