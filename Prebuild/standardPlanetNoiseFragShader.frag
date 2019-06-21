
#define OCTAVES 10

float hash (in vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))*
        43758.5453123);
}

float noise (in vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);


    float a = hash(i);
    float b = hash(i + vec2(1.0, 0.0));
    float c = hash(i + vec2(0.0, 1.0));
    float d = hash(i + vec2(1.0, 1.0));

    vec2 u = f * f * (3.0 - 2.0 * f);

    return mix(a, b, u.x) +(c - a)* u.y * (1.0 - u.x) +(d - b) * u.x * u.y;
}

float fbm (in vec2 st) {
    // Initial values
    float value = 0.0;
    float amplitude = .5;
    float frequency = 0.;
    //
    // Loop of octaves
    for (int i = 0; i < OCTAVES; i++) {
        value += amplitude * abs(noise(st));
        st *= 3.;
        amplitude *= .6;
    }
    return value;
}

float KalisetTexture(vec3 p) {
	vec3 pos=p;
	float l=1.;
	float ln=0.;
	float lnprev=0.;
	float expsmooth=0.;
	for (int i=0; i<13; i++) {
		p.xyz=abs(p.xyz);
		p=p/dot(p,p);
		p=p*3.-vec3(1.);
			lnprev=ln;
			ln=length(p);
			expsmooth+=exp(-1./abs(lnprev-ln));
		
	}
	return (expsmooth-5.5)*0.1;
}

void main()
{
vec2 u_resolution=vec2(1920,1080);
vec2 st = gl_TexCoord[0].xy/vec2(2048,2048);
   // st.x *= u_resolution.x/u_resolution.y;
	
		vec4 col=gl_Color;
	vec3 color = vec3(0.0);
	vec3 kali=vec3(st,1.0);
    color += fbm(st*3.0)-clamp(KalisetTexture(kali),0,1);
    gl_FragColor = vec4(color,1.0);
	
	// vec2 P =(gl_TexCoord[0].xy-.5*vec2(2048,2048))/vec2(200,200);
	//gl_FragColor= mix(vec4(0.,0.,0.,0.),vec4(.4,.4,.4,1)/dot(P,P*.7),pow(1.-sqrt(max(1.-dot(P,P),0.)),2.));




	
}