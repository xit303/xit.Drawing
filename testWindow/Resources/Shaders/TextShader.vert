#version 330 core


uniform mat4 projection;

layout(location = 0) in vec3 iPosition;
layout(location = 1) in vec2 iTexCoord;

out vec2 TexCoord;

void main()
{
    gl_Position = projection * vec4(iPosition, 1.0);
    TexCoord = iTexCoord;
}
