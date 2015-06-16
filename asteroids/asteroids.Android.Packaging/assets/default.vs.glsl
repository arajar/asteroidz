attribute vec3 vert;
attribute vec3 color;

uniform mat4 camera;
uniform mat4 model;

varying vec3 f_color;

void main()
{
	f_color = color;
	//gl_Position = camera * model * vec4(vert, 1);
	//gl_Position = projection * vec4(vert, 1);
	//gl_Position = camera * vec4(vert, 1);
	gl_Position = camera * model * vec4(vert, 1);
}