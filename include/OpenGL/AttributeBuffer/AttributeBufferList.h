#pragma once

#include <list>
#include <OpenGL/AttributeBuffer/AttributeBuffer.h>
#include <OpenGL/VertexBuffers/VertexBufferArray.h>

namespace xit::OpenGL
{
    class AttributeBufferList
    {
    private:
        std::list<AttributeBuffer*> items;
        uint currentAttributeIndex;
        VertexBufferArray vertexBufferArray;

    public:
        VertexBufferArray GetVertexBufferArray() { return vertexBufferArray; }

        AttributeBufferList()
            : currentAttributeIndex(0)
        {
            vertexBufferArray.Create();
        }

        AttributeBuffer* CreateAttributeBuffer(const std::string& attributeName)
        {
            AttributeBuffer* attributeBuffer = new AttributeBuffer(attributeName, currentAttributeIndex++);
            items.push_back(attributeBuffer);
            return attributeBuffer;
        }

        void Bind()
        {
            vertexBufferArray.Bind();
        }

        void Unbind()
        {
            vertexBufferArray.Unbind();
        }
    };
}
using namespace xit::OpenGL;
