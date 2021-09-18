#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 color;

out vec4 vColor;

uniform mat4 u_MVP;

void main() {
	vColor = vec4(color, 1.0);
	gl_Position = u_MVP * vec4(aPos, 1.0);
};
