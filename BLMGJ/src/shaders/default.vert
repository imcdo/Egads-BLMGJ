#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexPos;

uniform float depth;

out vec2 vTexPos;
uniform vec2 model;

void main()
{
	vTexPos = aTexPos;
	gl_Position = vec4(aPos, depth, 1.0);
}