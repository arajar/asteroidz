attribute vec3 vert;

uniform mat4 camera;
uniform mat4 model;
uniform float radius;
uniform vec3 color;

varying float v_radius;
varying vec3 v_color;

void main()
{
	v_radius = radius;
	v_color = color;

	gl_Position = camera * model * vec4(vert, 1);
}

