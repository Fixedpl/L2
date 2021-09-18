#version 330 core

in vec3 v_TexCoord;

out vec4 gl_FragColor;

uniform sampler2D u_Texture;

void main() {
	vec4 texColor = texture(u_Texture, v_TexCoord.xy);
	texColor = vec4(texColor.x, texColor.y, texColor.z, texture(u_Texture, v_TexCoord.xy).r);
	gl_FragColor = texColor;
};
