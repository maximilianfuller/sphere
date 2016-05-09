#version 330 core
out vec4 fragColor;

layout (location = 0) out vec4 fragPosition;
layout (location = 1) out vec4 fragNormal;
layout (location = 2) out vec4 fragColorSpecular;

in vec4 position_worldSpace;
in vec4 eye_worldSpace;
flat in int cd;

///////////////////////////////
//VALUE NOISE
///////////////////////////////

float PI = 3.141592;
int seed = 0;
int octaves = 14;
float alpha = .50;
float normalDelta = .00005;
float amp = .03;
float freq = 10.0;

float hash( float n ) { return fract(sin(n)*753.5453123); }
float noiseF( in vec3 x )
{
    vec3 p = floor(x);
    vec3 f = fract(x);
    f = f*f*(3.0-2.0*f);

    float n = p.x + p.y*157.0 + 113.0*p.z;
    return mix(mix(mix( hash(n+  0.0), hash(n+  1.0),f.x),
                   mix( hash(n+157.0), hash(n+158.0),f.x),f.y),
               mix(mix( hash(n+113.0), hash(n+114.0),f.x),
                   mix( hash(n+270.0), hash(n+271.0),f.x),f.y),f.z);
}

float noise(float x, float y, float z) {
    float noise = 0.0;
    float frequency = 1.0;
    for(int i = 0; i < octaves; i++) {
        float amplitude = pow(alpha, i);
        noise += amplitude*noiseF(vec3(x*frequency, y*frequency, z*frequency));
        frequency *= 2.0;
    }
    return noise;
}

vec3 sNoise(vec3 sphereLoc) {
    vec3 s = normalize(sphereLoc);
    float h = noise(freq*s.x, freq*s.y, freq*s.z)-1.0;
    h = clamp(h, 0.0, 1.0);
    return  s + s*(h*amp);
}

///////////////////////////////
//COORDINATE SWITCHING
///////////////////////////////
vec3 polarToCartesian(vec3 v) {
    return vec3(cos(v.x)*sin(v.y)*v.z, cos(v.y)*v.z, sin(v.x)*sin(v.y)*v.z);
}

vec3 cartesianToPolar(vec3 v){
    float radius = sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
    return vec3(atan(v.z,v.x), acos(v.y/radius), radius);
}




void main(){

    //outColor = vec3(.5, .5, .5);

    if(cd != 0) {
        //collision detection TODO
    } else {
        //rendering planet
        fragColor = vec4(0);
        vec3 base_color = vec3(0,0,0);
        vec3 pos = vec3(position_worldSpace);

        float h = (length(vec3(position_worldSpace))-1.0)/.03;

        vec3 blue = vec3(28/255.0, 107/255.0, 160/255.0);
        vec3 tan = vec3(194/255.0, 178/255.0, 128/255.0);
        vec3 green = vec3(0/255.0, 123/255.0, 12/255.0);
        vec3 gray = vec3(139/255.0, 140/255.0, 122/255.0);
        vec3 white = vec3(1.0,1.0,1.0);


        vec3 polar = cartesianToPolar(pos);
        vec3 p1 = sNoise(polarToCartesian(vec3(polar.x + normalDelta, polar.y, polar.z)));
        vec3 p2 = sNoise(polarToCartesian(vec3(polar.x - normalDelta, polar.y, polar.z)));
        vec3 p3 = sNoise(polarToCartesian(vec3(polar.x, polar.y + normalDelta, polar.z)));
        vec3 p4 = sNoise(polarToCartesian(vec3(polar.x, polar.y - normalDelta, polar.z)));
        vec4 normal = vec4(normalize(cross(p1-p2, p3-p4)), 0.0);


        if (dot(vec3(normal), normalize(pos)) > .850) {
            base_color = white;
        } else {
            base_color = tan;
        }


        //add diffuse component
        vec4 vertexToLight = normalize(vec4(1,1,1,0));
        float diffuseIntensity = max(0.0, dot(vertexToLight, normal));
        fragColor += vec4(max(vec3(0), vec3(1,1,1) * base_color * diffuseIntensity),0.f);

        // Add specular component
        vec4 lightReflection = normalize(-reflect(vertexToLight, normal));
        vec4 eyeDirection = normalize(eye_worldSpace - position_worldSpace);
        float specIntensity = pow(max(0.0, dot(eyeDirection, lightReflection)), 150);
        fragColor += vec4(max(vec3(0), vec3(1,1,1) * base_color * specIntensity),0.f);

        //addambient component
        fragColor += vec4(base_color*.5,0.f);

        //set out uniforms
        fragPosition = position_worldSpace/position_worldSpace.w;
        fragNormal = normal;
        fragColorSpecular = vec4(vec3(fragColor), .1);

    }
}
