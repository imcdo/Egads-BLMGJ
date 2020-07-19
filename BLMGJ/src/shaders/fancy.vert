#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexPos;

out vec2 vTexPos;

uniform float scale;

void main()
{
	vTexPos = aTexPos;
	gl_Position = vec4(aPos * scale, 0.0, 1.0);
}