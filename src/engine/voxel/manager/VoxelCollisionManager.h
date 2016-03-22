#ifndef VOXELCOLLISIONMANAGER_H
#define VOXELCOLLISIONMANAGER_H

#include "engine/manager/Manager.h"

const float EPS = 0.001;

class Chunk;
class VoxelEntity;

class VoxelCollisionManager : public Manager
{
public:
    VoxelCollisionManager(QList<Chunk *> &chunks,
                          QList<Entity *> &entities);

    bool withinChunk(Chunk *chunk, VoxelEntity *ent);

    void xSweep(Chunk *chunk, VoxelEntity *ent, float seconds);
    void zSweep(Chunk *chunk, VoxelEntity *ent, float seconds);
    void ySweep(Chunk *chunk, VoxelEntity *ent, float seconds);

    void onTick(float seconds);

protected:
    QList<Chunk *> &m_chunks;
};

#endif // VOXELCollisionMANAGER_H
