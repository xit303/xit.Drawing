#version 330 core

uniform mat4 projection;
//uniform mat4 model;

uniform vec4 iCornerRadius;
uniform vec4 iBorderThickness;

layout(location = 0) in vec3 iPosition;
layout(location = 1) in vec2 iTexCoord;
layout(location = 2) in vec4 iBackgroundColor;
layout(location = 3) in vec4 iBorderColor;

out vec4 BackgroundColor;
out vec4 BorderColor;
out vec2 TexCoord;

void main(void)
{
    BackgroundColor = iBackgroundColor;
    BorderColor = iBorderColor;
    TexCoord = iTexCoord;

    gl_Position = projection * vec4(iPosition, 1.0);
}