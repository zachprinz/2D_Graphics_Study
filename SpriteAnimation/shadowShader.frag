uniform sampler2D texture;
uniform vec4 color;

void main(void)
{
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	pixel[3] = pixel[3] * pixel[0];
	pixel[0] = color[0];
	pixel[1] = color[1];
	pixel[2] = color[2];
	gl_FragColor = pixel;
}