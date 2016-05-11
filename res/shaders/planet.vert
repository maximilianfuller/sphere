#version 330 core



layout(location = 0) in vec3 position; // Position of the vertex
layout(location = 1) in vec2 texCoord; // UV texture coordinates
uniform mat4 m;
uniform mat4 v;
uniform mat4 p;
uniform mat4 cube_m; //model that maps quad to cube
uniform sampler2D tex;

//collision uniforms
uniform int collisionDetection;
uniform vec3 collisionLoc;

out vec4 position_worldSpace;
out vec4 normal_worldSpace;
out vec4 eye_worldSpace;
out vec2 texc;
flat out int cd;


///////////////////////////////
//VALUE NOISE
///////////////////////////////

float PI = 3.141592;
int seed = 0;
int octaves = 12;
float alpha = .50;
float normalDelta = .0001;
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

//    vec3 p = floor(x);
//    vec3 f = fract(x);
//    f = f*f*(3.0-2.0*f);

//    vec2 uv = (p.xy+vec2(37.0,17.0)*p.z)+ f.xy;
//    uv = (uv+0.5)/256.0;
//    uv.y = -uv.y;
//    vec2 rg = texture2D( tex, uv).yx;
//    return mix( rg.x, rg.y, f.z);
}

float noise(float x, float y, float z) {
    float noise = 0.0;
    float frequency = freq;
    for(int i = 0; i < octaves; i++) {
        float amplitude = pow(alpha, i);
        noise += amplitude*noiseF(vec3(x*frequency, y*frequency, z*frequency));
        frequency *= 2.0;
    }
    return amp*clamp(1.0-noise,0.0, 1.0);
}

vec3 sNoise(vec3 sphereLoc) {
    vec3 s = normalize(sphereLoc);
    float h = noise(s.x, s.y, s.z);
    return  s*(h+1.0);
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
        //        octaves = octaves -4;
        float h = noise(collisionLoc.x, collisionLoc.y, collisionLoc.z);

        //set uniforms
        gl_Position = m*vec4(position,1);
        eye_worldSpace = vec4(h,0,0,0);




    } else {
        //RENDER PLANET
        //calculate sphere position
        vec3 pos = vec3(cube_m * m * vec4(position, 1.0));  //position on spherified cube
        pos = normalize(pos);
        pos = sNoise(pos); //with noise added

        for(int i = 0; i < 10; i++) {
            pos = sNoise(pos);
        }

        vec3 polar = cartesianToPolar(pos);
        vec3 p1 = sNoise(polarToCartesian(vec3(polar.x + normalDelta, polar.y, polar.z)));
//        vec3 p2 = sNoise(polarToCartesian(vec3(polar.x - normalDelta, polar.y, polar.z)));
        vec3 p3 = sNoise(polarToCartesian(vec3(polar.x, polar.y + normalDelta, polar.z)));
//        vec3 p4 = sNoise(polarToCartesian(vec3(polar.x, polar.y - normalDelta, polar.z)));
//        vec4 normal = vec4(normalize(cross(p1-p2, p3-p4)), 0.0);
        vec4 normal = vec4(normalize(cross(p1-pos, p3-pos)), 0.0);


        //adjust normalDelta
        vec3 eyeLoc = vec3(inverse(v)*vec4(0,0,0,1));

        //set uniforms
        position_worldSpace = vec4(pos, 1.0);
        normal_worldSpace = normal;
        gl_Position = p * v * position_worldSpace;
        eye_worldSpace = vec4(eyeLoc, 1.0);
        texc = texCoord;
    }

    cd = collisionDetection;
}





