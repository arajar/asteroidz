
attribute vec4 vert; // vec2 pos, vec2 texcoords

uniform mat4 projection;
uniform mat4 model;
uniform vec4 color;

varying vec2 v_texCoords;
varying vec4 v_color;

void main()
{
	v_texCoords = vert.zw;
	v_color = color;
	gl_Position = projection * model * vec4(vert.xy, 0.0, 1.0);
}
