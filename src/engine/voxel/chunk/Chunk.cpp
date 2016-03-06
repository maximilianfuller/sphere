#include "engine/voxel/chunk/Chunk.h"

#include "engine/graphics/Controller.h"
#include "engine/intersect/AABoundingBox.h"

#include "engine/voxel/manager/Manager.h"
#include "engine/voxel/terrain/Terrain.h"
#include "engine/voxel/block/Block.h"
#include "engine/voxel/entity/VoxelEntity.h"

Chunk::Chunk(Manager *manager, glm::vec3 pos) :
    m_manager(manager),
    m_pos(pos),
    m_vertexUpdate(true),
    m_lastY(0),
    m_numVertices(0),
    m_generated(false),
    m_aabb(new AABoundingBox(pos,
                             glm::vec3(CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE)))
{
}

Chunk::~Chunk()
{
    delete m_aabb;
}

BlockPointer Chunk::getBlockPointer(int x, int y, int z)
{
    if(x < 0 || x > CHUNK_SIZE - 1 || y < 0 || y > CHUNK_SIZE - 1
            || z < 0 || z > CHUNK_SIZE - 1)
    {
        return BLOCK_AIR;
    }

    return m_blocks[y * CHUNK_SIZE * CHUNK_SIZE + z * CHUNK_SIZE + x];
}

void Chunk::setBlockPointer(int x, int y, int z, BlockPointer p)
{
    m_blocks[y * CHUNK_SIZE * CHUNK_SIZE + z * CHUNK_SIZE + x] = p;
}

glm::vec3 Chunk::getPosition()
{
    return m_pos;
}

AABoundingBox *Chunk::getAABB()
{
    return m_aabb;
}

void Chunk::generateBlocks(Terrain *terrain)
{
    if(m_generated)
        return;

    int height;
    int blockIndex = 0;

    for(int y = 0; y < CHUNK_SIZE; y++)
    {
        for(int z = 0; z < CHUNK_SIZE; z++)
        {
            for(int x = 0; x < CHUNK_SIZE; x++)
            {
                height = terrain->getHeight(m_pos.x + x, m_pos.z + z)
                        + BASE_HEIGHT;

                /* Choose block type */
                if(int(y + m_pos.y) > height)
                {
                    m_blocks[blockIndex] = BLOCK_AIR;
                    m_visibleMap[blockIndex] = true;
                }
                else if (int(y + m_pos.y) == height)
                {
                    m_blocks[blockIndex] = BLOCK_GRASS;
                    m_visibleMap[blockIndex] = false;
                }
                else if(int(y + m_pos.y) >= DIRT_START)
                {
                    m_blocks[blockIndex] = BLOCK_DIRT;
                    m_visibleMap[blockIndex] = false;
                }
                else
                {
                    m_blocks[blockIndex] = BLOCK_ROCK;
                    m_visibleMap[blockIndex] = false;
                }

                blockIndex++;
            }
        }
    }
}

bool Chunk::updateBlockVertexBuffer()
{
    if(m_numVertices == 0)
    {
        m_blockVertexData = new float[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE * 16];
    }

    Block *block;
    int sizeSquared = CHUNK_SIZE * CHUNK_SIZE;
    int blockIndex = m_lastY * sizeSquared;

    int numDrawn = 0;

    for(int y = m_lastY; y < CHUNK_SIZE; y++)
    {
        for(int z = 0; z < CHUNK_SIZE; z++)
        {
            for(int x = 0; x < CHUNK_SIZE; x++)
            {
                block = m_manager->getBlock(m_blocks[blockIndex]);

                /* Draw block if passable */
                if(block->passable)
                {
                    glm::vec3 blockPos = m_pos + glm::vec3(x, y, z);

                    block->onDraw(m_blockVertexData, m_numVertices, blockPos,
                            x == 0 || m_visibleMap[blockIndex - 1],
                            x == CHUNK_SIZE - 1 || m_visibleMap[blockIndex + 1],
                            z == 0 || m_visibleMap[blockIndex - CHUNK_SIZE],
                            z == CHUNK_SIZE - 1 || m_visibleMap[blockIndex + CHUNK_SIZE],
                            y == 0 || m_visibleMap[blockIndex - sizeSquared],
                            y == CHUNK_SIZE - 1 || m_visibleMap[blockIndex + sizeSquared]);
                }

                blockIndex++;
            }
        }

        numDrawn++;

        if(numDrawn > 10)
        {
            m_lastY = y++;
            return false;
        }
    }

    /* Update VBO with new vertex data */
    m_blockVertexBuffer.setVertexData(m_blockVertexData,
                                      m_numVertices * sizeof(GLfloat) * 8,
                                      m_numVertices);
    m_blockVertexBuffer.setAttribute(Graphics::POSITION_ATTR, 3, GL_FLOAT, GL_FALSE,
                                     sizeof(GLfloat) * 8, (void *) 0);
    m_blockVertexBuffer.setAttribute(Graphics::NORMAL_ATTR, 3, GL_FLOAT, GL_TRUE,
                                     sizeof(GLfloat) * 8, (void *) (sizeof(GLfloat) * 3));
    m_blockVertexBuffer.setAttribute(Graphics::TEXTURE_ATTR, 2, GL_FLOAT, GL_FALSE,
                       sizeof(GLfloat) * 8, (void *) (sizeof(GLfloat) * 6));

    /* Do not update chunks */
    m_vertexUpdate = false;

    /* Reset counts */
    m_lastY = 0;
    m_numVertices = 0;

    /* Delete data array */
    delete[] m_blockVertexData;

    /* Notify finished */
    return true;
}

void Chunk::onTick(float seconds)
{
}

void Chunk::onDraw(Graphics::Controller *graphics)
{
    if(graphics->inFrustum(m_aabb))
    {
        m_blockVertexBuffer.draw();
    }
}
