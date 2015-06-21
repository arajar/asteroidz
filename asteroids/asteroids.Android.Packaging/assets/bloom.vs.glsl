attribute vec3 vert;

uniform mat4 camera;
uniform mat4 model;

varying sampler2D fboTexture;

void main()
{
	fboTexture = fbo;
	gl_Position = camera * model * vec4(vert, 1);
}