uniform sampler2D texture;

void main(void)
{
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	pixel[3] = (pixel[0] + pixel[1] + pixel[2]) * 999;
	pixel[3] = pixel[3] / pixel[3];
	pixel[3] = pixel[3] * 0.3;
	gl_FragColor = pixel;
}