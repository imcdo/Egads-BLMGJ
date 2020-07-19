#version 330 core

uniform sampler2D tex;
uniform int active;

in vec4 dummy;
in vec2 vTexPos;
layout (location = 0) out vec4 color;

void main() {
	if(active == 0)
		discard;
	vec4 outCol = vec4(1.0,0.0,0.0,1.0);
	outCol.a = (distance(vTexPos,vec2(1.0,0.5))) * 1.5;
	outCol.a = (((outCol.a - 0.5) * -1.0) + 0.5);
	color = outCol;
}