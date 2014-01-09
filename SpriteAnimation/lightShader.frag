uniform sampler2D texture;

void main(void)
{
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	float change = 0.4 * (1 - pixel[0]);
	pixel[3] += change;
	gl_FragColor = pixel;
}