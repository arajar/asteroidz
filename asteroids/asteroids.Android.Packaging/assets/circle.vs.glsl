attribute vec3 vert;
attribute vec4 color;

uniform mat4 camera;
uniform mat4 model;
uniform vec4 finalColor;

varying vec4 v_finalColor;

void main()
{
	v_finalColor = finalColor;
	gl_Position = camera * model * vec4(vert, 1);
}