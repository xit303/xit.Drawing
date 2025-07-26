#version 330 core

uniform sampler2D text;
uniform vec4 textColor;

in vec2 TexCoord;

out vec4 fragColor;

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoord).r);
    fragColor = textColor * sampled;
}
