uniform sampler2D texture;

void main(void)
{
	vec4 myColor = texture2D(texture, gl_TexCoord[0].xy);
	myColor[0] = myColor[3];
	myColor[1] = myColor[3];
	myColor[2] = myColor[3];
	gl_FragColor = myColor;
}