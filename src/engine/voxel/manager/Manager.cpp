#include "engine/voxel/manager/Manager.h"

#include "engine/camera/Camera.h"

#include "engine/voxel/entity/VoxelEntity.h"
#include "engine/voxel/block/Block.h"
#include "engine/voxel/terrain/Terrain.h"
#include "engine/voxel/intersect/VoxelCollisionManager.h"

#include <QMutableListIterator>

Manager::Manager(Terrain *terrain) :
    m_terrain(terrain),
    m_chunkRadius(1)
{
    m_collisionManager = new VoxelCollisionManager(m_chunks,
                                                   m_activeEntities,
                                                   m_backgroundEntities);
}

Manager::~Manager()
{
    Chunk *chunk;

    foreach(chunk, m_chunks)
    {
        delete chunk;
    }

    foreach(chunk, m_chunkQueue)
    {
        delete chunk;
    }

    delete m_terrain;
    delete m_collisionManager;
}

Block *Manager::getBlock(BlockPointer p)
{
    return m_blockTypes[p];
}

VoxelEntity *Manager::getPlayer()
{
    return m_player;
}

/* TODO:
 * 2) Fix speed of draws
 */
void Manager::purgeChunks()
{
    Chunk *chunk;
    QMutableListIterator<Chunk *> c(m_chunks);
    glm::vec3 playerPos = m_player->getPosition();

    int startX = glm::round((playerPos.x / CHUNK_SIZE) - m_chunkRadius) * CHUNK_SIZE;
    int startY = glm::round((playerPos.y / CHUNK_SIZE) - m_chunkRadius) * CHUNK_SIZE;
    int startZ = glm::round((playerPos.z / CHUNK_SIZE) - m_chunkRadius) * CHUNK_SIZE;

    int endX = glm::round((playerPos.x / CHUNK_SIZE) + m_chunkRadius) * CHUNK_SIZE;
    int endY = glm::round((playerPos.y / CHUNK_SIZE) + m_chunkRadius) * CHUNK_SIZE;
    int endZ = glm::round((playerPos.z / CHUNK_SIZE) + m_chunkRadius) * CHUNK_SIZE;

    while(c.hasNext())
    {
        chunk = c.next();
        glm::vec3 chunkPos = chunk->getPosition();

        if(chunkPos.x < startX - CHUNK_SIZE || chunkPos.x > endX + CHUNK_SIZE
                || chunkPos.y < startY - CHUNK_SIZE || chunkPos.y > endY + CHUNK_SIZE
                || chunkPos.z < startZ - CHUNK_SIZE || chunkPos.z > endZ + CHUNK_SIZE)
        {
            c.remove();
            delete chunk;
        }
    }

    QMutableListIterator<Chunk *> q(m_chunkQueue);

    while(q.hasNext())
    {
        chunk = q.next();
        glm::vec3 chunkPos = chunk->getPosition();

        if(chunkPos.x < startX - CHUNK_SIZE || chunkPos.x > endX + CHUNK_SIZE
                || chunkPos.y < startY - CHUNK_SIZE || chunkPos.y > endY + CHUNK_SIZE
                || chunkPos.z < startZ - CHUNK_SIZE || chunkPos.z > endZ + CHUNK_SIZE)
        {
            q.remove();
            delete chunk;
        }
    }
}

void Manager::loadChunks()
{
    glm::vec3 playerPos = m_player->getPosition();

    int startX = glm::round((playerPos.x / CHUNK_SIZE) - m_chunkRadius) * CHUNK_SIZE;
    int startY = glm::max(glm::round((playerPos.y / CHUNK_SIZE) - m_chunkRadius) * CHUNK_SIZE, -static_cast<float>(CHUNK_SIZE));
    int startZ = glm::round((playerPos.z / CHUNK_SIZE) - m_chunkRadius) * CHUNK_SIZE;

    int endX = glm::round((playerPos.x / CHUNK_SIZE) + m_chunkRadius) * CHUNK_SIZE;
    int endY = glm::min(glm::round((playerPos.y / CHUNK_SIZE) + m_chunkRadius) * CHUNK_SIZE, static_cast<float>(CHUNK_SIZE));
    int endZ = glm::round((playerPos.z / CHUNK_SIZE) + m_chunkRadius) * CHUNK_SIZE;

    for(int x = startX; x <= endX; x += CHUNK_SIZE)
    {
        for(int y = startY; y <= endY; y += CHUNK_SIZE)
        {
            for(int z = startZ; z <= endZ; z += CHUNK_SIZE)
            {
                Chunk *chunk;
                glm::vec3 chunkPos = glm::vec3(x, y, z);
                bool addChunk = true;

                foreach(chunk, m_chunks)
                {
                    if(chunk->getPosition() == chunkPos)
                    {
                        addChunk = false;
                        break;
                    }
                }

                foreach(chunk, m_chunkQueue)
                {
                    if(chunk->getPosition() == chunkPos)
                    {
                        addChunk = false;
                        break;
                    }
                }

                if(addChunk)
                {
                    chunk = new Chunk(this, chunkPos);

                    m_chunkQueue.enqueue(chunk);
                }
            }
        }
    }
}

void Manager::onTick(float seconds)
{
    m_collisionManager->onTick(seconds);

    int numActiveEntities = m_activeEntities.size();

    for(int i = 0; i < numActiveEntities; i++)
    {
        m_activeEntities[i]->onTick(seconds);
    }

    Chunk *chunk;
    bool drawn;

    if(!m_chunkQueue.isEmpty())
    {
        chunk = m_chunkQueue.head();
        chunk->generateBlocks(m_terrain);
        drawn = chunk->updateBlockVertexBuffer();

        if(drawn)
        {
            m_chunkQueue.dequeue();
            m_chunks.append(chunk);
        }
    }
}

void Manager::onDraw(Graphics::Controller *graphics)
{
    World::onDraw(graphics);

    graphics->sendColorUniform(glm::vec3(0.5, 0.5, 0.5), "default");
    graphics->sendUseTextureUniform(1, "default");
    graphics->sendModelUniform(glm::mat4x4(), "default");

    /* Draw and load chunks */
    purgeChunks();
    loadChunks();

    Chunk *chunk;

    foreach(chunk, m_chunks)
    {
        chunk->onDraw(graphics);
    }
}
