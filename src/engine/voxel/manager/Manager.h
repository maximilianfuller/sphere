#ifndef MANAGER_H
#define MANAGER_H

#include "engine/world/World.h"

#include "engine/voxel/chunk/Chunk.h"

#include <QString>

const int CHUNKS_WIDTH = 10;
const int CHUNKS_HEIGHT = 2;
const int NUM_CHUNKS = CHUNKS_WIDTH * CHUNKS_WIDTH * CHUNKS_HEIGHT;

typedef unsigned char BlockPointer;

class Block;
class Terrain;
class VoxelCollisionManager;

class Manager : public World
{
public:
    Manager(Terrain *terrain, QString atlasKey = "atlas");
    virtual ~Manager();

    Block *getBlock(BlockPointer p);

    virtual void onTick(float seconds);
    virtual void onDraw(Graphics::Controller *graphics);

protected:
    QString m_atlasKey;

    Block *m_blockTypes[256];

    Chunk *m_chunks[NUM_CHUNKS];

    Terrain *m_terrain;

    VoxelCollisionManager *m_cmanager;
};

#endif // MANAGER_H
