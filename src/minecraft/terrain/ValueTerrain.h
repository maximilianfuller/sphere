#ifndef VALUETERRAIN_H
#define VALUETERRAIN_H

#include "engine/voxel/terrain/Terrain.h"

class ValueTerrain : public Terrain
{
public:
    ValueTerrain();
    ~ValueTerrain();

    float noise(int x, int z);
    float smoothNoise(int x, int z);
    float interpolate(float v1, float v2, float u);

    float terrain(float x, float z);
    float terrainOctave(float x, float z, float amplitude, float frequency);

    float getHeight(int x, int z);

private:
    int m_randArray[100 * 100];
};

#endif // VALUETERRAIN_H
