#version 330 core
layout (location = 0) in vec2 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec2 TexCoord;
out vec3 Color;
out vec2 Pos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    gl_Position = projection * view * model * vec4(pos, 0.0, 1.0);
	TexCoord = texCoord;
	Color = color;
	Pos = vec2(model * vec4(pos, 1.0, 1.0));
}