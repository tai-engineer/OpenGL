#version 430 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

out vec3 Color;
out vec4 Position;

void main()
{
	Color = aColor;
	Position = vec4(aPos, 1.0);
	//gl_Position = vec4(aPos, 1.0f);
}
