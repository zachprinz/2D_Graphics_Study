uniform sampler2D texture;

void main()
{
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	pixel[3] = (1-pixel[3]);
	gl_FragColor = pixel;
}