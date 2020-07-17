#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexPos;

uniform vec2 model;
uniform float depth;

out vec2 vTexPos;

void main()
{
	vTexPos = aTexPos;
	gl_Position = vec4(aPos, depth, 1.0);
}