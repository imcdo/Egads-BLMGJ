#version 330 core

uniform sampler2D tex;

in vec2 vTexPos;
out vec4 color;

void main() {
	vec2 flipTexPos = vTexPos;
	flipTexPos.y = (flipTexPos.y - 0.5) * -1.0 + 0.5;
	vec4 outColor = vec4(1.0,1.0,1.0,texture(tex, flipTexPos).r);
	color = outColor;
}