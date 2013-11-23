uniform sampler2D texture;
uniform float centerX = 150.0;
uniform float centerY = 150.0;
uniform float radius = 150.0;
uniform vec4 lightColor;

void main()
{
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	if(pixel[3] > 0){
		float x = gl_FragCoord[0];
		float y = gl_FragCoord[1];
		float distance = sqrt(pow((centerX - x),2) + pow((centerY - y),2));
		float temp = radius - distance;
		float alpha = temp/radius;
		lightColor[3] = (alpha * 255.0);
		vec4 tempColor = lightColor;
		tempColor.a = (alpha * 255.0);
		vec4 tempColor2 = vec4{0,255,0,255 * alpha};
		gl_FragColor = tempColor2;
	}
}