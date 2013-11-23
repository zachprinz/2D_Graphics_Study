uniform sampler2D texture;
uniform float centerX;
uniform float centerY;
uniform float radius;
uniform vec4 lightColor;

void main()
{
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	if(pixel[0] == 0 && pixel[1] > 0 && pixel[2] == 0){
		float x = gl_FragCoord.x;
		float y = gl_FragCoord.y;
		float distance = sqrt(pow((centerX - x),2.0) + pow((centerY - y),2));
		if(distance > radius)
			pixel[3] = 0.0;
		else
			pixel[3] = 1.0;
		gl_FragColor = pixel;
	}
	else{
		float x = gl_FragCoord.x;
		float y = gl_FragCoord.y;
		float distance = sqrt(pow((centerX - x),2.0) + pow((centerY - y),2));
		lightColor[3] = ((radius-distance)/radius);
		gl_FragColor = lightColor;
	}
}