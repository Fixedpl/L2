#version 330 core

in vec3 v_color;
in vec2 v_tex_coord;
in float v_tex_id;


out vec4 gl_FragColor;

uniform sampler2D u_texture;

uniform float width[7];
uniform float edge[7];


void main() {
	vec3 msd = texture(u_texture, v_tex_coord).rgb;
	msd = vec3(1.0) - msd;
	if(msd.r > width[int(v_tex_id)]) {
		if(msd.r < edge[int(v_tex_id)]) {
			msd.r = 1.0 - smoothstep(width[int(v_tex_id)], edge[int(v_tex_id)], msd.r);
		} else {
			discard;
		}
	} else {
		msd.r = 1.0;
	}

	gl_FragColor = vec4(v_color, msd.r);
};
