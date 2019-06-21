uniform float hashNum;
#define OCTAVES 10

float hash (in vec2 st) {
    return fract(sin(dot(st.xy,vec2(12.9898,78.233)))*(13758.5453123+hashNum));
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

float fbm (in vec2 st,float oct) {
 mat2 rot = mat2(cos(0.5), sin(0.5),
                    -sin(0.5), cos(0.50));
    // Initial values
    float value = 0.0;
    float amplitude = .5;
    float frequency = 0.;
    //
    // Loop of octaves
    for (int i = 0; i < oct; i++) {
        value += amplitude * abs(noise(st));
        st *= 3.;
        amplitude *= .6;
		st*=rot;
    }
    return value;
}

float KalisetTexture(vec3 p,float iter) {
	float a=0.;
	float pa=0.;
	p = abs(vec3(0.85)-mod(p,vec3(0.85*2.)));
	for (int i=0; i<iter; i++) {
		p=abs(p)/dot(p,p)-0.53; // the magic formula
			a+=abs(length(p)-pa); // absolute sum of average change
			pa=length(p);
		
	}
	a*=a*a;
	a=a*0.0015*0.01;
	return a;
	
}


void main()
{
vec2 st = gl_FragCoord.xy/vec2(2048,2048);



	vec3 color = vec3(0.0);
	vec3 kali=vec3(st,1.0);
	float a1=.5;
	float a2=.8;
	mat2 rot1=mat2(cos(a1),sin(a1),-sin(a1),cos(a1));
	mat2 rot2=mat2(cos(a2),sin(a2),-sin(a2),cos(a2));
	kali.xz*=rot1;
	kali.xy*=rot2;

	
	kali.z-=hashNum/1000;
	color=fbm(st+fbm(st,10),10)*0.5;
    color += fbm(st*3.0,10)*0.5-(clamp(KalisetTexture(kali,12),0,0.8)*0.5);

	kali.z-=hashNum/1000;
	color -=clamp(KalisetTexture(kali,17),0,1)*0.25;
	
	color-=fbm(st*0.1,10);
	color-=clamp(KalisetTexture(clamp(KalisetTexture(clamp(KalisetTexture(kali,12),0,1),12),0,1),12),0,1)*0.1;//fractal warp
	//st*=7;
	//color=fbm(st+fbm(st+fbm(st,5),5),5);
    gl_FragColor = vec4(color,1.0);
	





	
}