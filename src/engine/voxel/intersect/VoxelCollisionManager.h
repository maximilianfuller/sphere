#ifndef VOXELCollisionMANAGER_H
#define VOXELCollisionMANAGER_H

#include "engine/intersect/CollisionManager.h"

const float EPS = 0.05;

class Chunk;

class VoxelCollisionManager : public CollisionManager
{
public:
    VoxelCollisionManager(Chunk **chunks, int numChunks,
                          QList<ActiveEntity *> &activeEnts,
                          QList<BackgroundEntity *> &backgroundEnts);

    bool withinChunk(Chunk *chunk, ActiveEntity *ent);

    void xSweep(Chunk *chunk, ActiveEntity *ent, float seconds);
    void zSweep(Chunk *chunk, ActiveEntity *ent, float seconds);
    void ySweep(Chunk *chunk, ActiveEntity *ent, float seconds);

    void onTick(float seconds);

protected:
    int m_numChunks;
    Chunk **m_chunks;
};

#endif // VOXELCollisionMANAGER_H
