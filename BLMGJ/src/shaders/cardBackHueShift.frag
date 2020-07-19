#version 330 core

uniform sampler2D tex;
uniform vec3 colorTint;

in vec2 vTexPos;
out vec4 color;

void main() {
	vec4 texCol = texture(tex, vTexPos);
	texCol.xyz = texCol.xyz * colorTint;
	color = texCol;
}