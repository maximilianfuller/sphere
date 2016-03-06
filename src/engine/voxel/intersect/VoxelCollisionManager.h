#ifndef VOXELCollisionMANAGER_H
#define VOXELCollisionMANAGER_H

#include "engine/intersect/CollisionManager.h"

const float EPS = 0.001;

class Chunk;
class VoxelEntity;

class VoxelCollisionManager : public CollisionManager
{
public:
    VoxelCollisionManager(QList<Chunk *> &chunks,
                          QList<ActiveEntity *> &activeEnts,
                          QList<BackgroundEntity *> &backgroundEnts);

    bool withinChunk(Chunk *chunk, VoxelEntity *ent);

    void xSweep(Chunk *chunk, VoxelEntity *ent, float seconds);
    void zSweep(Chunk *chunk, VoxelEntity *ent, float seconds);
    void ySweep(Chunk *chunk, VoxelEntity *ent, float seconds);

    void onTick(float seconds);

protected:
    QList<Chunk *> &m_chunks;
};

#endif // VOXELCollisionMANAGER_H
