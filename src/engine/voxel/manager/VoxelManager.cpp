#include "engine/voxel/manager/VoxelManager.h"

#include "engine/camera/Camera.h"
#include "engine/shape/Quad.h"
#include "engine/manager/CylinderCollisionManager.h"

#include "engine/voxel/entity/VoxelEntity.h"
#include "engine/voxel/block/Block.h"
#include "engine/voxel/terrain/Terrain.h"
#include "engine/voxel/manager/VoxelCollisionManager.h"

#include <QMutableListIterator>
#include <limits>

VoxelManager::VoxelManager(Camera *camera, Terrain *terrain) :
    m_terrain(terrain),
    World(camera)
{
    m_voxelManager = new VoxelCollisionManager(m_chunks, m_activeEntities, m_backgroundEntities);
    m_cylinderManager = new CylinderCollisionManager(m_activeEntities, m_backgroundEntities);
    m_face = new Quad(0, 0, "", glm::vec4(1, 0, 0, 0.5));
}

VoxelManager::~VoxelManager()
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
    delete m_voxelManager;
    delete m_cylinderManager;
    delete m_face;
}

Block *VoxelManager::getBlock(BlockPointer p)
{
    return m_blocks[p];
}

VoxelEntity *VoxelManager::getPlayer()
{
    return m_player;
}

void VoxelManager::purgeChunks()
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

void VoxelManager::loadChunks()
{
    glm::vec3 playerPos = m_player->getPosition();

    int startX = glm::round((playerPos.x / CHUNK_SIZE) - m_chunkRadius) * CHUNK_SIZE;
    int startY = glm::round((playerPos.y / CHUNK_SIZE) - m_chunkRadius) * CHUNK_SIZE;
    int startZ = glm::round((playerPos.z / CHUNK_SIZE) - m_chunkRadius) * CHUNK_SIZE;

    int endX = glm::round((playerPos.x / CHUNK_SIZE) + m_chunkRadius) * CHUNK_SIZE;
    int endY = glm::round((playerPos.y / CHUNK_SIZE) + m_chunkRadius) * CHUNK_SIZE;
    int endZ = glm::round((playerPos.z / CHUNK_SIZE) + m_chunkRadius) * CHUNK_SIZE;

    for(int x = startX; x <= endX; x += CHUNK_SIZE)
    {
        for(int y = startY; y <= endY; y += CHUNK_SIZE)
        {
            for(int z = startZ; z <= endZ; z += CHUNK_SIZE)
            {
                glm::vec3 chunkPos = glm::vec3(x, y, z);
                bool addChunk = true;

                foreach(Chunk *chunk, m_chunks)
                {
                    if(chunk->getPosition() == chunkPos)
                    {
                        addChunk = false;
                        break;
                    }
                }

                if(addChunk)
                {
                    foreach(Chunk *chunk, m_chunkQueue)
                    {
                        if(chunk->getPosition() == chunkPos)
                        {
                            addChunk = false;
                            break;
                        }
                    }
                }

                if(addChunk)
                {
                    m_chunkQueue.enqueue(new Chunk(this, chunkPos));
                }
            }
        }
    }
}

Chunk *VoxelManager::getChunk(float x, float y, float z)
{
    Chunk *ret = NULL;

    foreach(Chunk *chunk, m_chunks)
    {
        if(chunk->inChunk(x, y, z))
        {
            ret = chunk;
            break;
        }
    }

    if(!ret)
    {
        foreach(Chunk *chunk, m_chunkQueue)
        {
            if(chunk->inChunk(x, y, z))
            {
                ret = chunk;
                break;
            }
        }
    }

    return ret;
}

void VoxelManager::castRay(glm::vec3 p, glm::vec3 d)
{
    /* Initialize current position */
    int x = glm::round(p.x);
    int y = glm::round(p.y);
    int z = glm::round(p.z);

    /* Initialize steps */
    int stepX = d.x > 0 ? 1 : -1;
    int stepY = d.y > 0 ? 1 : -1;
    int stepZ = d.z > 0 ? 1 : -1;

    /* Initialize tMaxX, tMaxY, tMaxZ */
    float t = 0.0;
    float tMaxX = std::numeric_limits<float>::infinity();
    float tMaxY = std::numeric_limits<float>::infinity();
    float tMaxZ = std::numeric_limits<float>::infinity();

    if(d.x != 0)
    {
        if(stepX > 0)
        {
            tMaxX = (glm::round(p.x + stepX) - p.x - 0.5) / d.x;
        }
        else
        {
            tMaxX = (glm::round(p.x + stepX) - p.x + 0.5) / d.x;
        }
    }

    if(d.y != 0)
    {
        if(stepY > 0)
        {
            tMaxY = (glm::round(p.y + stepY) - p.y - 0.5) / d.y;
        }
        else
        {
            tMaxY = (glm::round(p.y + stepY) - p.y + 0.5) / d.y;
        }
    }

    if(d.z != 0)
    {
        if(stepZ > 0)
        {
            tMaxZ = (glm::round(p.z + stepZ) - p.z - 0.5) / d.z;
        }
        else
        {
            tMaxZ = (glm::round(p.z + stepZ) - p.z + 0.5) / d.z;
        }
    }

    /* Compute tDeltaX, tDeltaY, tDeltaZ */
    float tDeltaX = std::numeric_limits<float>::infinity();
    float tDeltaY = std::numeric_limits<float>::infinity();
    float tDeltaZ = std::numeric_limits<float>::infinity();

    if(d.x != 0)
    {
        tDeltaX = stepX / d.x;
    }

    if(d.y != 0)
    {
        tDeltaY = stepY / d.y;
    }

    if(d.z != 0)
    {
        tDeltaZ = stepZ / d.z;
    }

    /* Get intersection */
    Chunk *curChunk;

    while(true)
    {
        if(tMaxX < tMaxY)
        {
            if(tMaxX < tMaxZ)
            {
                t = tMaxX;
                x += stepX;
                tMaxX += tDeltaX;
            }
            else
            {
                t = tMaxZ;
                z += stepZ;
                tMaxZ += tDeltaZ;
            }
        }
        else
        {
            if(tMaxY < tMaxZ)
            {
                t = tMaxY;
                y += stepY;
                tMaxY += tDeltaY;
            }
            else
            {
                t = tMaxZ;
                z += stepZ;
                tMaxZ += tDeltaZ;
            }
        }

        if(!(curChunk = getChunk(x, y, z)))
        {
            break;
        }

        if(t > m_maxT)
        {
            break;
        }

        if(!curChunk->passable(x, y, z))
        {
            selectBlock(x, y, z, p, d, t);
            return;
        }
    }

    selectBlock(x, y, z, p, d, -1);
}

void VoxelManager::selectBlock(int x, int y, int z, glm::vec3 p, glm::vec3 d, float t)
{
    glm::vec3 pos = p + d * t;
    m_lastT = t;

    if(t == -1)
    {
        m_selectedFace = NoneFace;
    }
    else
    {
        m_selectedPos = glm::vec3(x, y, z);

        float diffX = x - pos.x;
        float diffY = y - pos.y;
        float diffZ = z - pos.z;

        if(glm::abs(diffX) > glm::abs(diffY))
        {
            if(glm::abs(diffX) > glm::abs(diffZ))
            {
                m_selectedFace = diffX > 0 ? LeftFace : RightFace;
            }
            else
            {
                m_selectedFace = diffZ > 0 ? BackFace : FrontFace;
            }
        }
        else
        {
            if(glm::abs(diffY) > glm::abs(diffZ))
            {
                m_selectedFace = diffY > 0 ? BottomFace : TopFace;
            }
            else
            {
                m_selectedFace = diffZ > 0 ? BackFace : FrontFace;
            }
        }
    }
}

void VoxelManager::renderSelectedBlock(Graphics::Controller *graphics)
{
    if(m_selectedFace == LeftFace)
    {
        m_face->rotate(glm::mat4x4(), glm::vec3(0, 0, 1), M_PI / 2);
        m_face->translate(m_face->getModelMatrix(), m_selectedPos + glm::vec3(-0.55, 0, 0));
    }
    else if(m_selectedFace == RightFace)
    {
        m_face->rotate(glm::mat4x4(), glm::vec3(0, 0, 1), -M_PI / 2);
        m_face->translate(m_face->getModelMatrix(), m_selectedPos + glm::vec3(0.55, 0, 0));
    }
    else if(m_selectedFace == BottomFace)
    {
        m_face->rotate(glm::mat4x4(), glm::vec3(1, 0, 0), M_PI);
        m_face->translate(m_face->getModelMatrix(), m_selectedPos + glm::vec3(0, -0.55, 0));
    }
    else if(m_selectedFace == TopFace)
    {
        m_face->translate(glm::mat4x4(), m_selectedPos + glm::vec3(0, 0.55, 0));
    }
    else if(m_selectedFace == BackFace)
    {
        m_face->rotate(glm::mat4x4(), glm::vec3(1, 0, 0), -M_PI / 2);
        m_face->translate(m_face->getModelMatrix(), m_selectedPos + glm::vec3(0, 0, -0.55));
    }
    else if(m_selectedFace == FrontFace)
    {
        m_face->rotate(glm::mat4x4(), glm::vec3(1, 0, 0), M_PI / 2);
        m_face->translate(m_face->getModelMatrix(), m_selectedPos + glm::vec3(0, 0, 0.55));
    }

    if(m_selectedFace != NoneFace)
    {
        m_face->draw(graphics);
    }
}

void VoxelManager::onTick(float seconds)
{
    /* Intersect entities */
    m_voxelManager->onTick(seconds);
    m_cylinderManager->onTick(seconds);

    /* Tick world */
    World::onTick(seconds);

    /* Draw chunks from queue */
    if(!m_chunkQueue.isEmpty())
    {
        Chunk *chunk = m_chunkQueue.head();

        chunk->generateBlocks(m_terrain);
        chunk->updateBlockVertexBuffer();

        m_chunkQueue.dequeue();
        m_chunks.append(chunk);
    }

    /* Cast ray */
    castRay(m_camera->getEye(), m_camera->getLook());
}

void VoxelManager::onDraw(Graphics::Controller *graphics)
{
    World::onDraw(graphics);

    graphics->sendColorUniform(glm::vec4(0.5, 0.5, 0.5, 1.0), "default");
    graphics->sendUseTextureUniform(1, "default");
    graphics->sendModelUniform(glm::mat4x4(), "default");

    /* Draw and load chunks */
    purgeChunks();
    loadChunks();

    foreach(Chunk *chunk, m_chunks)
    {
        chunk->onDraw(graphics);
    }

    /* Draw selected face */
    renderSelectedBlock(graphics);
}
