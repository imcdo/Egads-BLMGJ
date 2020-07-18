#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexPos;
uniform float depth;

out vec2 vTexPos;
out vec4 dummy;

uniform mat4 model;
uniform mat4 projection;

void main()
{
	vTexPos = aTexPos;
	gl_Position = projection * model * vec4(aPos, 0, 1.0);
	gl_Position = vec4(gl_Position.xy, depth, 1.0);

	dummy = model * vec4(aPos, depth, 1);
	// dummy = vec4(depth, depth, depth, 1);
}