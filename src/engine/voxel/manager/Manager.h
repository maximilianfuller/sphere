#ifndef MANAGER_H
#define MANAGER_H

#include "engine/world/World.h"

#include "engine/voxel/chunk/Chunk.h"

typedef unsigned char BlockPointer;

class Block;

namespace Voxel
{

class Manager : public World
{
public:
    Manager();
    virtual ~Manager();

    Block *getBlock(BlockPointer p);

    virtual void onTick(float seconds);
    virtual void onDraw(Graphics::Controller *graphics);

protected:
    Block *m_blockTypes[256];

    Chunk *m_chunks[4];
};

}

#endif // MANAGER_H