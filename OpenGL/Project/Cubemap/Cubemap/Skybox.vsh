#version 400
layout(location = 0) in vec3 aPos;

uniform mat4 Projection;
uniform mat4 View;

out vec3 texCoord;

void main(){
	vec4 pos = Projection * View * vec4(aPos, 1.0);

	texCoord = aPos;

	gl_Position = pos.xyww;
}