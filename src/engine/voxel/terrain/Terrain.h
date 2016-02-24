#ifndef TERRAIN_H
#define TERRAIN_H

class Terrain
{
public:
    Terrain();
    virtual ~Terrain();

    virtual float getHeight(int x, int z) = 0;
};

#endif // TERRAIN_H
