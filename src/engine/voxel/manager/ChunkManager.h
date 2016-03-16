#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H

#include "engine/manager/ModuleManager.h"

#include <QList>
#include <QQueue>

class Terrain;
class Chunk;

class ChunkManager : public ModuleManager
{
public:
    ChunkManager(Terrain *terrain);

    /* Chunk streaming */
    void purgeChunks();
    void loadChunks();

    /* Raycasting */
    Chunk *getChunk(float x, float y, float z);

    /* Game loop */
    virtual void onTick(float seconds);
    virtual void onDraw(Graphics::Controller *graphics);

protected:
    Terrain *m_terrain;
    QList<Chunk *> m_chunks;
    QQueue<Chunk *> m_chunkQueue;
    int m_chunkRadius = 2;
};

#endif // CHUNKMANAGER_H
