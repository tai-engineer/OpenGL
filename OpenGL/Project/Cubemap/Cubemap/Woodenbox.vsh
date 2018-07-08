#version 400
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

out vec3 Normal;
out vec3 Position;

void main(){
	Normal = mat3(transpose(inverse(Model))) * aNormal;
	Position = vec3(Model * vec4(aPos, 1.0));
	gl_Position = Projection * View * Model * vec4(aPos, 1.0);
}