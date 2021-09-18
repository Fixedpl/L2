#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aTex;

out vec3 v_TexCoord;

uniform mat4 u_MVP;

void main() {
	v_TexCoord = aTex;
	gl_Position = u_MVP * vec4(aPos.x, aPos.y, aPos.z, 1.0);
};