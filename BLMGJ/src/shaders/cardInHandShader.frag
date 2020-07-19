#version 330 core

uniform sampler2D tex;
uniform float time;
uniform int rarity;

in vec4 dummy;
in vec2 vTexPos;
layout (location = 0) out vec4 color;

void main() {
	float shiny = max(inversesqrt((abs(sin((time + vTexPos.x + vTexPos.y)/3.0))+0.3)),1.0);
	vec4 colorDup = texture(tex, vTexPos);
	if (rarity < 4) shiny = 1.0f; 
	colorDup.xyz = shiny * colorDup.xyz;
	color = colorDup;
}