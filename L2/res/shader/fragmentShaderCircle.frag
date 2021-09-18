#version 330 core

in vec3 vColor;
in vec3 center;

out vec4 gl_FragColor;

void main() {
	vec2 middle = vec2(center.x, center.y);
	float dist = distance(middle, gl_FragCoord.xy);
	if(dist > center.z) {
		discard;
	}
	gl_FragColor = vec4(vColor, 1.0);
};
