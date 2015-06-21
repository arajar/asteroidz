varying sampler2D fboTexture;

void main()
{
	// Current texture coordinate
	vec2 texel = vec2(gl_TexCoord[0]);
	vec4 pixel = vec4(texture2D(fboTexture, texel));
	
	// Larger constant = bigger glow
	float glow = 4.0 * ((2.0 + 2.0) / 2.0);
	
	// The vector to contain the new, "bloomed" colour values
	vec4 bloom = vec4(0);
	
	// Loop over all the pixels on the texture in the area given by the constant in glow
	int count = 0;
	for(float x = texel.x - glow; x < texel.x + glow; x += 2.0)
	{
		for(float y = texel.y - glow; y < texel.y + glow; y += 2.0)
		{
			// Add that pixel's value to the bloom vector
			bloom += (texture2D(fboTexture, vec2(x, y)) - 0.4) * 30.0;
			// Add 1 to the number of pixels sampled
			count++;
		}
	}
	// Divide by the number of pixels sampled to average out the value
	// The constant being multiplied with count here will dim the bloom effect a bit, with higher values
	// Clamp the value between a 0.0 to 1.0 range
	bloom = clamp(bloom / (count * 30), 0.0, 1.0);
	
	// Set the current fragment to the original texture pixel, with our bloom value added on
	gl_FragColor = pixel + bloom;
}