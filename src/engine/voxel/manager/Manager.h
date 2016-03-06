#ifndef MANAGER_H
#define MANAGER_H

#include "engine/world/World.h"

#include "engine/voxel/chunk/Chunk.h"

#include <QList>
#include <QQueue>

typedef unsigned char BlockPointer;

class Block;
class Terrain;
class VoxelCollisionManager;
class VoxelEntity;

class Manager : public World
{
public:
    Manager(Terrain *terrain);
    virtual ~Manager();

    Block *getBlock(BlockPointer p);
    VoxelEntity *getPlayer();

    void purgeChunks();
    void loadChunks();

    virtual void onTick(float seconds);
    virtual void onDraw(Graphics::Controller *graphics);

protected:
    Terrain *m_terrain;
    Block *m_blockTypes[256];

    QList<Chunk *> m_chunks;
    QQueue<Chunk *> m_chunkQueue;
    int m_chunkRadius;

    VoxelEntity *m_player;

    VoxelCollisionManager *m_collisionManager;

};

#endif // MANAGER_H
