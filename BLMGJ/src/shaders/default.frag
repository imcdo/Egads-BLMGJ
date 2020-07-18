#version 330 core

uniform sampler2D tex;

in vec4 dummy;
in vec2 vTexPos;
out vec4 color;

void main() {
	color = texture(tex, vTexPos);
	// color = vec4(dummy.xyz, 1) +.1f; 
}