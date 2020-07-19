#version 330 core
in vec2 vTexPos;
out vec4 color;

uniform float time;

void main() {
    vec2 uv = vTexPos;
    uv = floor(uv*vec2(160.0,90.0))/vec2(160.0,90.0);
    uv.y = (uv.y - 0.5) * -1.0 + 0.5;
    float dist = distance(uv - vec2(0.5,0.5),vec2(0.0,0.0));
    uv.x = uv.x + sin(uv.y);
	uv.x = uv.x + sin(sin(time*0.05+uv.y))/1.0;
	uv.y = uv.y + sin(sin(time*0.05+uv.x))/1.0;
    uv.x += dist;
    uv.y -= dist;
    // Time varying pixel color
    vec3 col = vec3(sin(uv.x*10.0));
    col = abs(col * vec3(sin(uv.y*10.0)));
	col = (-(col - vec3(0.5)))+0.5;
    // Output to screen
    color = vec4(col * vec3(0.5,0.5,1.0),1.0);
}