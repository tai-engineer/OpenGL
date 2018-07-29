#version 430 core

in vec3 Color;
out vec4 FragColor;

void main()
{
	// FragColor = vec4(Color, 1.0);
	FragColor = vec4(0.5, 0.0, 0.0, 1.0);
}
