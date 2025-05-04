#pragma once

#include <Exceptions.h>
#include <string>

namespace xit::OpenGL
{
    class ShaderCompilationException : public Exception
    {
    private:
        std::string compilerOutput;

    protected:
        /*ShaderCompilationException(SerializationInfo info, StreamingContext context)
            : base(info, context)
        {
        }*/

    public:
        std::string CompilerOutput() { return compilerOutput; }

        // ShaderCompilationException(const std::string& compilerOutput)
        //     : Exception("")
        // {
        //     this->compilerOutput = compilerOutput;
        // }
        ShaderCompilationException(const std::string& message, const std::string& compilerOutput)
            : Exception(message)
        {
            this->compilerOutput = compilerOutput;
        }

        //ShaderCompilationException(const std::string& message, std::exception inner, const std::string& compilerOutput)
        //    : std::exception(message, inner)
        //{
        //    compilerOutput = compilerOutput;
        //}
    };
}
using namespace xit::OpenGL;
