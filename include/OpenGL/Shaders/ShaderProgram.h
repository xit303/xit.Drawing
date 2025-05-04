#pragma once

#include <map>

#include <Exceptions.h>
#include <IO/IO.h>
#include <OpenGL/Shaders/Shader.h>

namespace xit::OpenGL
{
    class ShaderProgram
    {
    private:
        GLuint shaderProgramObject;

        Shader *vertexShader;
        Shader *fragmentShader;

        /// <summary>
        /// A mapping of uniform names to locations. This allows us to very easily specify
        /// uniform data by name, quickly looking up the location first if needed.
        /// </summary>
        std::map<std::string, int> uniformNamesToLocations;

        void CheckProgramObject()
        {
            if (shaderProgramObject == 0)
            {
                shaderProgramObject = glCreateProgram();
            }
        }

        Shader *CheckShader(Shader *shader)
        {
            if (shader == nullptr)
            {
                return new Shader();
            }
            if (shader->ShaderObject != 0)
            {
                glDetachShader(shaderProgramObject, shader->ShaderObject);
            }

            return shader;
        }

        bool CreateShader(GLuint shaderType, const std::string &shaderSource)
        {
            if (shaderSource.empty())
            {
                Logger::Log("ShaderProgram", ArgumentNullException("shaderSource"));
                return false;
            }

            CheckProgramObject();

            Shader *shader = nullptr;
            if (shaderType == GL_VERTEX_SHADER)
            {
                shader = vertexShader = CheckShader(vertexShader);
            }
            else if (shaderType == GL_FRAGMENT_SHADER)
            {
                shader = fragmentShader = CheckShader(fragmentShader);
            }
            else
            {
                throw NotImplementedException();
            }

            // try to create the shader.
            // if ShaderObject is not 0 it will be automatically deleted in the Create method
            if (shader->Create(shaderType, shaderSource))
            {
                glAttachShader(shaderProgramObject, shader->ShaderObject);
                return true;
            }

            return false;
        }

    public:
        /// <summary>
        /// Gets the shader program object.
        /// </summary>
        /// <value>
        /// The shader program object.
        /// </value>
        GLuint GetProgramId() { return shaderProgramObject; }

        ShaderProgram()
            : shaderProgramObject(0), vertexShader(nullptr), fragmentShader(nullptr)
        {
        }

        __always_inline bool CreateVertexShader(const std::string &shaderSource)
        {
            return CreateShader(GL_VERTEX_SHADER, shaderSource);
        }

        __always_inline bool CreateFragmentShader(const std::string &shaderSource)
        {
            return CreateShader(GL_FRAGMENT_SHADER, shaderSource);
        }

        bool Link()
        {
            //  Now we can link the program.
            glLinkProgram(shaderProgramObject);

            //  Now that we've compiled and linked the shader, check it's link status. If it's not linked properly, we're
            //  going to throw an exception.
            if (GetLinkStatus() == false)
            {
                Logger::Log(LogLevel::Error, "ShaderProgram", "Failed to link shader program with ID " + std::to_string(shaderProgramObject) + ".\n" + GetInfoLog());
                return false;
            }
            return true;
        }

        /// <summary>
        /// Creates the shader program.
        /// </summary>
        /// <param name="gl">The gl.</param>
        /// <param name="vertexShaderSource">The vertex shader source.</param>
        /// <param name="fragmentShaderSource">The fragment shader source.</param>
        /// <param name="attributeLocations">The attribute locations. This is an optional array of
        /// GLuint attribute locations to their names.</param>
        /// <exception cref="ShaderCompilationException"></exception>
        bool Create(const std::string &vertexShaderSource, const std::string &fragmentShaderSource,
                    std::map<GLuint, std::string> *attributeLocations)
        {
            //  Create the shaders.
            bool vertexShaderCreated = CreateVertexShader(vertexShaderSource);
            bool fragmentShaderCreated = CreateFragmentShader(fragmentShaderSource);

            if (!vertexShaderCreated && !fragmentShaderCreated)
            {
                return false;
            }

            //  Create the program, attach the shaders.
            shaderProgramObject = glCreateProgram();
            glAttachShader(shaderProgramObject, vertexShader->ShaderObject);
            glAttachShader(shaderProgramObject, fragmentShader->ShaderObject);

            //  Before we link, bind any vertex attribute locations.
            if (attributeLocations && !attributeLocations->empty())
            {
                for (std::pair<GLuint, std::string> pair : *attributeLocations)
                {
                    glBindAttribLocation(shaderProgramObject, pair.first, (GLchar *)pair.second.c_str());
                }
            }

            //  Now we can link the program.
            glLinkProgram(shaderProgramObject);

            //  Now that we've compiled and linked the shader, check it's link status. If it's not linked properly, we're
            //  going to throw an exception.
            if (GetLinkStatus() == false)
            {
                Logger::Log(LogLevel::Error, "ShaderProgram", "Failed to link shader program with ID " + std::to_string(shaderProgramObject) + ".\n" + GetInfoLog());
                return false;
            }
            return true;
        }

        void Delete()
        {
            glDetachShader(shaderProgramObject, vertexShader->ShaderObject);
            glDetachShader(shaderProgramObject, fragmentShader->ShaderObject);

            vertexShader->Delete();
            fragmentShader->Delete();

            glDeleteProgram(shaderProgramObject);

            shaderProgramObject = 0;
        }

        __always_inline int GetAttributeLocation(const std::string &attributeName)
        {
            return glGetAttribLocation(shaderProgramObject, attributeName.c_str());
        }

        __always_inline void BindAttributeLocation(GLuint location, const std::string &attribute)
        {
            glBindAttribLocation(shaderProgramObject, location, attribute.c_str());
        }

        __always_inline void Bind()
        {
            glUseProgram(shaderProgramObject);
        }

        __always_inline void Unbind()
        {
            glUseProgram(0);
        }

        __always_inline bool GetLinkStatus()
        {
            int linkStatus = 0;
            glGetProgramiv(shaderProgramObject, GL_LINK_STATUS, &linkStatus);
            return linkStatus == GL_TRUE;
        }

        std::string GetInfoLog()
        {
            //  Get the info log length.
            int infoLogLength = 0;
            glGetProgramiv(shaderProgramObject, GL_INFO_LOG_LENGTH, &infoLogLength);

            //  Get the compile info.
            char *il = new char[infoLogLength];
            glGetProgramInfoLog(shaderProgramObject, infoLogLength, nullptr, il);

            return il;
        }

        void AssertValid()
        {
            if ((vertexShader != nullptr) && vertexShader->GetCompileStatus() == false)
            {
                throw Exception(vertexShader->GetInfoLog());
            }

            if ((fragmentShader != nullptr) && fragmentShader->GetCompileStatus() == false)
            {
                throw Exception(fragmentShader->GetInfoLog());
            }

            if (GetLinkStatus() == false)
            {
                throw Exception(GetInfoLog());
            }
        }

        __always_inline void SetUniform1(const std::string &uniformName, float v1)
        {
            glUniform1f(GetUniformLocation(uniformName), v1);
        }

        __always_inline void SetUniform2(const std::string &uniformName, float v1, float v2)
        {
            glUniform2f(GetUniformLocation(uniformName), v1, v2);
        }

        __always_inline void SetUniform2(const std::string &uniformName, int v1, int v2)
        {
            glUniform2i(GetUniformLocation(uniformName), v1, v2);
        }

        __always_inline void SetUniform2(const std::string &uniformName, int count, const float *values)
        {
            glUniform2fv(GetUniformLocation(uniformName), count, values);
        }

        __always_inline void SetUniform3(const std::string &uniformName, float v1, float v2, float v3)
        {
            glUniform3f(GetUniformLocation(uniformName), v1, v2, v3);
        }
        __always_inline void SetUniform3(const std::string &uniformName, int count, float *values)
        {
            glUniform3fv(GetUniformLocation(uniformName), count, values);
        }

        __always_inline void SetUniform4(const std::string &uniformName, float v1, float v2, float v3, float v4)
        {
            glUniform4f(GetUniformLocation(uniformName), v1, v2, v3, v4);
        }
        __always_inline void SetUniform4(const std::string &uniformName, int v1, int v2, int v3, int v4)
        {
            glUniform4i(GetUniformLocation(uniformName), v1, v2, v3, v4);
        }
        __always_inline void SetUniform4(const std::string &uniformName, int count, const float *values)
        {
            glUniform4fv(GetUniformLocation(uniformName), count, values);
        }

        __always_inline void SetUniformMatrix3(const std::string &uniformName, const float *m)
        {
            glUniformMatrix3fv(GetUniformLocation(uniformName), 1, false, m);
        }

        __always_inline void SetUniformMatrix4(const std::string &uniformName, const float *m)
        {
            glUniformMatrix4fv(GetUniformLocation(uniformName), 1, false, m);
        }

        __always_inline int GetUniformLocation(const std::string &uniformName)
        {
            //  If we don't have the uniform name in the dictionary, get it's
            //  location and add it.
            int &location = uniformNamesToLocations[uniformName];

            if (location == 0)
            {
                location = glGetUniformLocation(shaderProgramObject, uniformName.c_str());
                //uniformNamesToLocations.emplace(uniformName, location);
                //  TODO: if it's not found, we should probably throw an exception.
            }

            //  Return the uniform location.
            return location;
        }
    };
}
using namespace xit::OpenGL;
