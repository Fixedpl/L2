#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aCenter;
layout(location = 2) in vec3 aColor;

out vec3 vColor;
out vec3 center;

uniform mat4 u_MVP;

void main() {
	vec4 norm = u_MVP * vec4(aPos, 1.0);
	vColor = aColor;
	center = aCenter;
	gl_Position = vec4(norm.x, norm.y, norm.z, 1.0);
};
