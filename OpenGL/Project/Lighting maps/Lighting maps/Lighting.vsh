#version 400
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

out vec3 Normal;
out vec3 fragPos;
out vec2 texCoord;

void main(){
	fragPos = vec3(Model * vec4(aPos, 1.0));
	Normal = aNormal;
	texCoord = aTexCoord;

	gl_Position = Projection * View * vec4(fragPos, 1.0);
}