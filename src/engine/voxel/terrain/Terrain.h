#ifndef TERRAIN_H
#define TERRAIN_H

class Terrain
{
public:
    Terrain();
    ~Terrain();

    virtual float getHeight(float x, float z) = 0;
};

#endif // TERRAIN_H
