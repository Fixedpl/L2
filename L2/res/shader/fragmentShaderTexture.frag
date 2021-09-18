#version 330 core

in vec3 v_color;
in vec2 v_tex_coord;
in float v_tex_id;


out vec4 gl_FragColor;

uniform sampler2D u_texture[32];



void main() {
	vec4 texColor = vec4(1.0, 1.0, 1.0, 1.0);
	switch(int(v_tex_id)) {
		case 0: texColor = texture(u_texture[0], v_tex_coord); break;
		case 1: texColor = texture(u_texture[1], v_tex_coord); break;
		case 2: texColor = texture(u_texture[2], v_tex_coord); break;
		case 3: texColor = texture(u_texture[3], v_tex_coord); break;
		case 4: texColor = texture(u_texture[4], v_tex_coord); break;
		case 5: texColor = texture(u_texture[5], v_tex_coord); break;
		case 6: texColor = texture(u_texture[6], v_tex_coord); break;
		case 7: texColor = texture(u_texture[7], v_tex_coord); break;
		case 8: texColor = texture(u_texture[8], v_tex_coord); break;
		case 9: texColor = texture(u_texture[9], v_tex_coord); break;
		case 10: texColor = texture(u_texture[10], v_tex_coord); break;
		case 11: texColor = texture(u_texture[11], v_tex_coord); break;
		case 12: texColor = texture(u_texture[12], v_tex_coord); break;
		case 13: texColor = texture(u_texture[13], v_tex_coord); break;
		case 14: texColor = texture(u_texture[14], v_tex_coord); break;
		case 15: texColor = texture(u_texture[15], v_tex_coord); break;
		case 16: texColor = texture(u_texture[16], v_tex_coord); break;
		case 17: texColor = texture(u_texture[17], v_tex_coord); break;
		case 18: texColor = texture(u_texture[18], v_tex_coord); break;
		case 19: texColor = texture(u_texture[19], v_tex_coord); break;
		case 20: texColor = texture(u_texture[20], v_tex_coord); break;
		case 21: texColor = texture(u_texture[21], v_tex_coord); break;
		case 22: texColor = texture(u_texture[22], v_tex_coord); break;
		case 23: texColor = texture(u_texture[23], v_tex_coord); break;
		case 24: texColor = texture(u_texture[24], v_tex_coord); break;
		case 25: texColor = texture(u_texture[25], v_tex_coord); break;
		case 26: texColor = texture(u_texture[26], v_tex_coord); break;
		case 27: texColor = texture(u_texture[27], v_tex_coord); break;
		case 28: texColor = texture(u_texture[28], v_tex_coord); break;
		case 29: texColor = texture(u_texture[29], v_tex_coord); break;
		case 30: texColor = texture(u_texture[30], v_tex_coord); break;
		case 31: texColor = texture(u_texture[31], v_tex_coord); break;
	}
	gl_FragColor = texColor * vec4(v_color, 1.0);
};
