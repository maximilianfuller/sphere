#ifndef NOISE_H
#define NOISE_H

#include "util/CommonIncludes.h"

#endif // NOISE_H

using namespace glm;


class Noise {

public:

    float PI = 3.141592;

    int seed = 0;
    int octaves = 8;
    float alpha = .50;
    float normalDelta = .01;
    float amp = .03;
    float freq = 5.0;

    vec3 sNoise(vec3 sphereLoc) {
        vec3 s = normalize(sphereLoc);
        float h = noiseVal(freq*s.x, freq*s.y, freq*s.z);
        h = clamp(h, -.1f, 1.f);
        return  s + s*(h*amp);
    }

    float noiseVal(float x, float y, float z) {
        float noise = 0.0;
        float frequency = 1.0;
        for(int i = 0; i < octaves; i++) {
            float amplitude = glm::pow(alpha, i);
            noise += amplitude*interpolatedGradientNoise(x*frequency, y*frequency, z*frequency);
            frequency *= 2.0;
        }
        return noise;
    }

    float interpolatedGradientNoise(float x, float y, float z) {
        int x0 = int(floor(x));
        int x1 = x0 + 1;
        int y0 = int(floor(y));
        int y1 = y0 + 1;
        int z0 = int(floor(z));
        int z1 = z0 + 1;

        float dx0 = x - x0;
        float dx1 = x - x1;
        float dy0 = y - y0;
        float dy1 = y - y1;
        float dz0 = z - z0;
        float dz1 = z - z1;


        float v0 = dot(vec3(dx0,dy0,dz0),noiseVector(x0,y0,z0));
        float v1 = dot(vec3(dx1,dy0,dz0),noiseVector(x1,y0,z0));
        float v2 = dot(vec3(dx0,dy1,dz0),noiseVector(x0,y1,z0));
        float v3 = dot(vec3(dx1,dy1,dz0),noiseVector(x1,y1,z0));
        float v4 = dot(vec3(dx0,dy0,dz1),noiseVector(x0,y0,z1));
        float v5 = dot(vec3(dx1,dy0,dz1),noiseVector(x1,y0,z1));
        float v6 = dot(vec3(dx0,dy1,dz1),noiseVector(x0,y1,z1));
        float v7 = dot(vec3(dx1,dy1,dz1),noiseVector(x1,y1,z1));

        float cx1 = polyinterp(v0,v1,dx0);
        float cx2 = polyinterp(v2,v3,dx0);
        float cx3 = polyinterp(v4,v5,dx0);
        float cx4 = polyinterp(v6,v7,dx0);
        float cy1 = polyinterp(cx1, cx2, dy0);
        float cy2 = polyinterp(cx3, cx4, dy0);
        return polyinterp(cy1, cy2, dz0);

    }


    ///interpolation
    float polyinterp(float x1, float x2, float c) {
        float f = c*c*c*(6*c*c - 15*c + 10);
        return (1-f)*x1 + f*x2;
    }

    float cubicinterp(float x1, float x2, float c) {
        float f =  c*c*(3-2*c);
        return (1-f)*x1 + f*x2;
    }



    vec3 noiseVector(int x, int y, int z) {
        int a = x*59*53*61 + y*53*61 + z*61 + 13*seed;
        int b = x*67*71*73 + y*71*73 + z*73 + 17*seed;
        int c = x*79*83*89 + y*83*89 + z*89 + 19*seed;

        return normalize(vec3(scramble(a),scramble(b),scramble(c)));

    }

    float scramble(int n) {
        n = (n<<13) ^ n;
        return 1.0 - ( (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0;
    }
};
