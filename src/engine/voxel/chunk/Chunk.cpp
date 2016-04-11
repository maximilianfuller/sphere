#include "engine/voxel/chunk/Chunk.h"

#include "engine/graphics/Graphics.h"
#include "engine/intersect/AABoundingBox.h"

#include "engine/voxel/manager/VoxelManager.h"
#include "engine/voxel/terrain/Terrain.h"
#include "engine/voxel/block/Block.h"
#include "engine/voxel/entity/VoxelEntity.h"

Chunk::Chunk(VoxelManager *manager, glm::vec3 pos) :
    m_manager(manager),
    m_pos(pos),
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
    m_passableMap[y * CHUNK_SIZE * CHUNK_SIZE + z * CHUNK_SIZE + x] = (p == BLOCK_AIR);
}

glm::vec3 Chunk::getPosition()
{
    return m_pos;
}

AABoundingBox *Chunk::getAABB()
{
    return m_aabb;
}

bool Chunk::passable(int x, int y, int z)
{
    int newX = x - m_pos.x;
    int newY = y - m_pos.y;
    int newZ = z - m_pos.z;

    return getBlockPointer(newX, newY, newZ) == BLOCK_AIR;
}

bool Chunk::inChunk(int x, int y, int z)
{
    return (x < m_pos.x + CHUNK_SIZE && x >= m_pos.x)
            && (y < m_pos.y + CHUNK_SIZE && y >= m_pos.y)
            && (z < m_pos.z + CHUNK_SIZE && z >= m_pos.z);
}

void Chunk::generateBlocks(Terrain *terrain)
{
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
                    m_passableMap[blockIndex] = true;
                }
                else if (int(y + m_pos.y) == height)
                {
                    m_blocks[blockIndex] = BLOCK_GRASS;
                    m_passableMap[blockIndex] = false;
                }
                else if(int(y + m_pos.y) >= DIRT_START)
                {
                    m_blocks[blockIndex] = BLOCK_DIRT;
                    m_passableMap[blockIndex] = false;
                }
                else
                {
                    m_blocks[blockIndex] = BLOCK_ROCK;
                    m_passableMap[blockIndex] = false;
                }

                blockIndex++;
            }
        }
    }
}

void Chunk::updateBlockVertexBuffer()
{
    m_vertexData = new float[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE * 16];
    int numVertices = 0;

    Block *block;
    int blockIndex = 0;
    int sizeSquared = CHUNK_SIZE * CHUNK_SIZE;

    for(int y = 0; y < CHUNK_SIZE; y++)
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

                    block->onDraw(m_vertexData, numVertices, blockPos,
                            x == 0 || m_passableMap[blockIndex - 1],
                            x == CHUNK_SIZE - 1 || m_passableMap[blockIndex + 1],
                            z == 0 || m_passableMap[blockIndex - CHUNK_SIZE],
                            z == CHUNK_SIZE - 1 || m_passableMap[blockIndex + CHUNK_SIZE],
                            y == 0 || m_passableMap[blockIndex - sizeSquared],
                            y == CHUNK_SIZE - 1 || m_passableMap[blockIndex + sizeSquared]);
                }

                blockIndex++;
            }
        }
    }

    /* Update VBO with new vertex data */
    m_vertexBuffer.setVertexData(m_vertexData,
                                 numVertices * sizeof(GLfloat) * 8,
                                 numVertices);
    m_vertexBuffer.setAttribute(POSITION_ATTR, 3, GL_FLOAT, GL_FALSE,
                                     sizeof(GLfloat) * 8, (void *) 0);
    m_vertexBuffer.setAttribute(NORMAL_ATTR, 3, GL_FLOAT, GL_TRUE,
                                     sizeof(GLfloat) * 8, (void *) (sizeof(GLfloat) * 3));
    m_vertexBuffer.setAttribute(TEXTURE_ATTR, 2, GL_FLOAT, GL_FALSE,
                       sizeof(GLfloat) * 8, (void *) (sizeof(GLfloat) * 6));

    /* Delete data array */
    delete[] m_vertexData;
}

void Chunk::onTick(float seconds)
{
}

void Chunk::onDraw(Graphics *graphics)
{
    if(graphics->inFrustum(m_aabb))
    {
        m_vertexBuffer.draw();
    }
}
