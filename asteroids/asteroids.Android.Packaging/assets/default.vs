attribute vec3 vert;
attribute vec3 color;
varying vec3 f_color;

void main()
{
	f_color = color;
	gl_Position = vec4(vert, 1);
}