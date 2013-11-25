uniform sampler2D texture;

void main(void)
{
	vec2 offx = vec2(0.00097, 0.0);
	vec2 offy = vec2(0.0, 0.0012);
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	float alpha = (pixel[3]);
	alpha += 2*texture2D(texture, gl_TexCoord[0].xy + offx)[3];
	alpha += 2*texture2D(texture, gl_TexCoord[0].xy - offx)[3];
	alpha += 2*texture2D(texture, gl_TexCoord[0].xy + offy)[3];
	alpha += 2*texture2D(texture, gl_TexCoord[0].xy - offy)[3];
	pixel[3] = 1- (alpha / 7.0);
	gl_FragColor = pixel;
}