varying vec2 v_texCoords;
varying vec4 v_color;

uniform sampler2D image;

void main()
{
	gl_FragColor = v_color * texture2D(image, vec2(-v_texCoords.x, v_texCoords.y));
}