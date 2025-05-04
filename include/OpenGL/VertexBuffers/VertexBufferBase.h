#pragma once

#include <glad/glad.h>

namespace xit::OpenGL
{
    class VertexBufferBase
    {
    protected:
        GLuint id;

    public:
        /// <summary>
        /// Gets the vertex buffer id. (VBO or VBA)
        /// </summary>
        const GLuint& Id = id;

        bool IsCreated()
        {
            return id != 0;
        }

        VertexBufferBase() { id = 0; }

        /// <summary>
        /// 
        /// </summary>
        __always_inline virtual void Create()
        {
            //  Generate the vertex array.
            glGenBuffers(1, &id);
        }

        __always_inline virtual void Delete()
        {
            glDeleteBuffers(1, &id);
        }

        __always_inline void Bind(GLenum target)
        {
            glBindBuffer(target, id);
        }
        __always_inline void Unbind(GLenum target)
        {
            glBindBuffer(target, 0);
        }

        virtual void Bind() = 0;
        virtual void Unbind() = 0;
    };
}

using namespace xit::OpenGL;
