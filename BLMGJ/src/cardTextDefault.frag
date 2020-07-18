#version 330 core

uniform sampler2D tex;

in vec2 vTexPos;
out vec4 color;

void main() {
	color = vec4(1.0,1.0,1.0,texture(tex, vTexPos).r);
}