#pragma once

#include <OpenGL/VertexBuffers/VertexBufferBase.h>

namespace xit::OpenGL
{
    /// <summary>
    /// A VertexBufferArray is a logical grouping of VertexBuffers. Vertex Buffer Arrays
    /// allow us to use a set of vertex buffers for vertices, indicies, normals and so on,
    /// without having to use more complicated interleaved arrays.
    /// </summary>
    class VertexBufferArray : public VertexBufferBase
    {
    public:
        __always_inline virtual void Create() override
        {
            GLuint id0 = 0;
            //  Generate the vertex array.
            glGenVertexArrays(1, &id0);

            id = id0;
        }

        __always_inline virtual void Delete() override
        {
            glDeleteVertexArrays(1, &id);
        }

        __always_inline virtual void Bind() override
        {
            glBindVertexArray(id);
        }

        __always_inline virtual void Unbind() override
        {
            glBindVertexArray(0);
        }
    };
}

using namespace xit::OpenGL;
