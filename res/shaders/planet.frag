#version 330 core
layout (location = 0) out vec4 fragPosition;
layout (location = 1) out vec4 fragNormal;
layout (location = 2) out vec4 fragColorSpecular;

in vec4 position_worldSpace;
in vec4 normal_worldSpace;
in vec4 position_normal;
in vec4 eye_worldSpace;
flat in int cd;

vec3 tan = vec3(194/255.0, 178/255.0, 128/255.0);
vec3 white = vec3(1.0,1.0,1.0);


///////////////////////////////
//VALUE NOISE
///////////////////////////////

float PI = 3.141592;
int seed = 0;
int octaves = 10;
float alpha = .50;
float normalDelta = .0003;
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
    return clamp(1.0-noise,0.0, 1.0);
}

vec3 sNoise(vec3 sphereLoc) {
    vec3 s = normalize(sphereLoc);
    float h = noise(freq*s.x, freq*s.y, freq*s.z);
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

    if(cd != 0) {
        //collision
        fragPosition = eye_worldSpace;
    } else {
        //rendering planet
        vec3 base_color = white;
        float spec;
        vec3 pos = vec3(position_worldSpace);
//        pos = sNoise(pos);



        vec3 polar = cartesianToPolar(pos);
        vec3 p1 = sNoise(polarToCartesian(vec3(polar.x + normalDelta, polar.y, polar.z)));
//        vec3 p2 = sNoise(polarToCartesian(vec3(polar.x - normalDelta, polar.y, polar.z)));
        vec3 p3 = sNoise(polarToCartesian(vec3(polar.x, polar.y + normalDelta, polar.z)));
//        vec3 p4 = sNoise(polarToCartesian(vec3(polar.x, polar.y - normalDelta, polar.z)));
//        vec4 normal = vec4(normalize(cross(p1-p2, p3-p4)), 0.0);
      vec4 normal = vec4(normalize(cross(p1-pos, p3-pos)), 0.0);


//      vec4 normal = normal_worldSpace;
//      vec4 normal = vec4(pos, 0);


        if (dot(vec3(normal), normalize(pos)) > .900) {
            base_color = white;
            spec = .3;
        } else {
            base_color = tan;
            spec = .15;
        }

        //set out uniforms
        fragPosition = position_worldSpace/position_worldSpace.w;
        fragNormal = normal;
        fragColorSpecular = vec4(vec3(base_color * spec), .1);
    }
}
