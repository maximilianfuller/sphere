#version 330 core



layout(location = 0) in vec3 position; // Position of the vertex
layout(location = 1) in vec2 texCoord; // UV texture coordinates
uniform mat4 m;
uniform mat4 v;
uniform mat4 p;
uniform mat4 cube_m; //model that maps quad to cube
uniform int collisionDetection;

out vec4 position_worldSpace;
out vec4 eye_worldSpace;
out vec2 texc;
flat out int cd;


///////////////////////////////
//VALUE NOISE
///////////////////////////////

float PI = 3.141592;
int seed = 0;
int octaves = 14;
float alpha = .50;
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

    if(collisionDetection != 0) {
        //RENDER QUAD FOR COLLISION DETECTION
        vec3 loc = vec3(m*vec4(0,0,0,1));
        float h = noise(loc.x, loc.y, loc.z);

        //set uniforms
        gl_Position = m*vec4(position,1);


    } else {
        //RENDER PLANET
        //calculate sphere position
        vec3 pos = vec3(cube_m * m * vec4(position, 1.0));  //position on spherified cube
        pos = normalize(pos);
        pos = sNoise(pos); //with noise added

        //adjust normalDelta
        vec3 eyeLoc = vec3(inverse(v)*vec4(0,0,0,1));
//        normalDelta *= max(length(pos-(eyeLoc)),.005);//multiply eyeloc by small scalar to avoid this coming out to zero with floating point errors

        //set uniforms
        position_worldSpace = vec4(pos, 1.0);
        gl_Position = p * v * position_worldSpace;
        eye_worldSpace = vec4(eyeLoc, 1.0);
        texc = texCoord;
    }

    cd = collisionDetection;
}




