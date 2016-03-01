#include "minecraft/terrain/ValueTerrain.h"

#include "util/CommonIncludes.h"

ValueTerrain::ValueTerrain()
{
}

ValueTerrain::~ValueTerrain()
{
}

float ValueTerrain::noise(int x, int z)
{
    return sin(x * 1000 + z * 94300);
}

float ValueTerrain::smoothNoise(int x, int z)
{
    float corners = (noise(x - 1, z - 1) + noise(x - 1, z + 1)
                     + noise(x + 1, z - 1) + noise(x + 1, z + 1)) / 16;
    float sides = (noise(x - 1, z) + noise(x, z + 1) + noise(x + 1, z)
                   + noise(x, z - 1)) / 8;
    float center = noise(x, z) / 4;

    return corners + sides + center;
}

float ValueTerrain::interpolate(float v1, float v2, float u)
{
    float f = (1.f - glm::cos(u * M_PI)) * 0.5;
    return v1 * (1.f - f) + v2 * f;
}

float ValueTerrain::terrain(float x, float z)
{
    int floorX = glm::floor(x);
    int floorZ = glm::floor(x);

    float fracX = x - floorX;
    float fracZ = z - floorZ;

    float noise0 = noise(floorX, floorZ);
    float noise1 = noise(floorX + 1, floorZ);
    float noise2 = noise(floorX, floorZ + 1);
    float noise3 = noise(floorX + 1, floorZ + 1);

    return glm::abs(interpolate(interpolate(noise0, noise1, fracX),
                                interpolate(noise2, noise3, fracX), fracZ));
}

float ValueTerrain::terrainOctave(float x, float z, float amplitude, float frequency)
{
    return amplitude * terrain(x * frequency, z * frequency);
}

float ValueTerrain::getHeight(int x, int z)
{
    float amplitude = 14.f;
    float persistence = 0.2f;
    float frequency = 0.04f;
    float height = 0.f;

    for(int i = 0; i < 5; i++)
    {
        height += terrainOctave(x, z, amplitude, frequency);

        amplitude *= persistence;
        frequency *= 2;
    }

    return height;
}
