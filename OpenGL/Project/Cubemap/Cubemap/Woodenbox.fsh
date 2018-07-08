#version 400

in vec3 Normal;
in vec3 Position;

uniform samplerCube skyBox;
uniform vec3 cameraPos;

out vec4 color;

void main()
{
	vec3 I = normalize(Position - cameraPos);
	vec3 R = reflect(I , normalize(Normal));
	color = vec4(texture(skyBox, R).rgb, 1.0);
}
