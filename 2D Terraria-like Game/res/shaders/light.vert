#version 330 core
layout (location = 0) in vec2 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec2 TexCoord;
out vec3 Color;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
    gl_Position = projection * view * model * vec4(pos, 0.0f, 1.0f);
	TexCoord = texCoord;
	Color = color;
}