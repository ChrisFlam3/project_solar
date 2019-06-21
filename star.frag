uniform sampler2D texture;


void main()
{
vec2 texCenter=vec2(1024,1024);
		double d=distance(texCenter,gl_TexCoord[0].xy)/1024;
		
	
		vec4 col=gl_Color;
		vec2 wh=gl_FragCoord;
		wh.x=wh.x/1920;
		wh.y=wh.y/1080;
		vec4 sample=texture2D(texture,wh)/255;
		col.rgb=(-(d-0.999)/(1-0.999));


			gl_FragColor = col+sample;
	
}