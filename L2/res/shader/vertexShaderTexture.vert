#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 tex_coord;
layout (location = 3) in float tex_id;

out vec3 v_color;
out vec2 v_tex_coord;
out float v_tex_id;

uniform mat4 u_MVP;

void main() {
	v_color = color;
	v_tex_coord = tex_coord;
	v_tex_id = tex_id;
	gl_Position = u_MVP * vec4(pos.x, pos.y, pos.z, 1.0);
};