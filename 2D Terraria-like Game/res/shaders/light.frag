#version 330 core

in vec2 TexCoord;
in vec3 Color;
out vec4 FragColor;

uniform vec3 color;
uniform sampler2D texSampler;

void main()
{
    FragColor = texture(texSampler, TexCoord);
}