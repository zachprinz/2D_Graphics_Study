uniform sampler2D texture;

void main(void)
{
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	pixel[3] = (1 - pixel[0] + 0.2);
	gl_FragColor = pixel;
}