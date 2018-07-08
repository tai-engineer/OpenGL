#version 400
layout(location = 0) in vec3 aPos;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

out vec2 texCoord;
void main(){
	gl_Position = (Projection * View * Model) * vec4(aPos, 1.0);
}
