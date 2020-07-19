#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexPos;

uniform vec2 scale;
uniform vec2 pos;

out vec2 vTexPos;

void main()
{
	vTexPos = aTexPos;
	vec2 textPos = (aPos + vec2(1.0,1.0)) * 0.5;
	gl_Position = vec4(textPos * scale + pos, 0.0, 1.0);
}