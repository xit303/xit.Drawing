#pragma once

#include <IO/IO.h>
#include <glad/glad.h>

namespace xit::OpenGL
{
    /// <summary>
    /// This is the base class for all shaders (vertex and fragment). It offers functionality
    /// which is core to all shaders, such as file loading and binding.
    /// </summary>
    class Shader
    {
    private:
        /// <summary>
        /// The OpenGL shader object.
        /// </summary>
        GLuint shaderObject;

    public:
        /// <summary>
        /// Gets the shader object.
        /// </summary>
        const GLuint& ShaderObject = shaderObject;

        Shader()
            : shaderObject(0)
        {
        }

        bool Create(GLenum shaderType, const std::string& source)
        {
            if (shaderObject != 0)
            {
                Delete();
            }

            //  Create the OpenGL shader object.
            shaderObject = glCreateShader(shaderType);

            //  Set the shader source.
            //(GLuint shader, GLsizei count, const GLchar* const* string, const GLint * length)
            GLint len = (GLint)source.length();
            GLchar *src = (GLchar*)source.c_str();

            glShaderSource(shaderObject, 1, &src, &len);

            //  Compile the shader object.
            glCompileShader(shaderObject);

            //  Now that we've compiled the shader, check it's compilation status. If it's not compiled properly, we're
            //  going to throw an exception.
            if (GetCompileStatus() == false)
            {
                Logger::Log(LogLevel::Error, "Shader", "Failed to compile shader with ID " + std::to_string(shaderObject) + "\n" + GetInfoLog());
                return false;
            }
            return true;
        }

        void Delete()
        {
            glDeleteShader(shaderObject);
            shaderObject = 0;
        }

        bool GetCompileStatus()
        {
            int compileStatus = 0;
            glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &compileStatus);
            return compileStatus == GL_TRUE;
        }

        std::string GetInfoLog()
        {
            //  Get the info log length.
            int infoLength = 0;
            glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &infoLength);

            //  Get the compile info.
            char* il = new char[infoLength];
            glGetShaderInfoLog(shaderObject, infoLength, nullptr, il);

            return il;
        }
    };
}

using namespace xit::OpenGL;
