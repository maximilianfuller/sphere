#include "engine/voxel/chunk/Chunk.h"

#include "engine/graphics/Controller.h"

#include "engine/voxel/manager/Manager.h"
#include "engine/voxel/terrain/Terrain.h"
#include "engine/voxel/block/Block.h"
#include "engine/voxel/entity/VoxelEntity.h"

Chunk::Chunk(Voxel::Manager *manager, Terrain *terrain, glm::vec3 pos) :
    m_manager(manager),
    m_pos(pos),
    m_blockNumVertices(0),
    m_vertexUpdate(true),
    m_blockVertexData(new float[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE * 8])
{
    generateBlocks(terrain);
}

Chunk::~Chunk()
{
    delete[] m_blockVertexData;
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
                if(y > height)
                {
                    m_blocks[blockIndex] = BLOCK_AIR;
                    m_visibleMap[blockIndex] = true;
                }
                else if (y == height)
                {
                    m_blocks[blockIndex] = BLOCK_GRASS;
                    m_visibleMap[blockIndex] = false;
                }
                else if(y >= DIRT_START)
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

BlockPointer Chunk::getBlockPointer(int x, int y, int z)
{
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

bool Chunk::inFrustum(Graphics::Controller *graphics)
{
    glm::vec4 pos;

    bool allBehind;

    for(int i = 0; i < 6; i++)
    {
        allBehind = true;

        for(int x = 0; x <= 1; x++)
        {
            for(int y = 0; y <= 1; y++)
            {
                for(int z = 0; z <= 1; z++)
                {
                    pos = glm::vec4(m_pos.x, m_pos.y, m_pos.z, 1)
                            + glm::vec4(CHUNK_SIZE * x, CHUNK_SIZE * y, CHUNK_SIZE * z, 0);

                    allBehind = allBehind && (glm::dot(graphics->frustumPlanes[0], pos) < 0);
                }
            }
        }

        if(allBehind)
            return false;
    }

    return true;
}

void Chunk::updateBlockVertexBuffer()
{
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
                    block->onDraw(m_blockVertexData, m_blockNumVertices, blockPos,
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
    }

    /* Update VBO with new vertex data */
    m_blockVertexBuffer.setVertexData(m_blockVertexData,
                                      m_blockNumVertices * sizeof(GLfloat),
                                      m_blockNumVertices);
    m_blockVertexBuffer.setAttribute(Graphics::POSITION_ATTR, 3, GL_FLOAT, GL_FALSE,
                                     sizeof(GLfloat) * 8, (void *) 0);
    m_blockVertexBuffer.setAttribute(Graphics::NORMAL_ATTR, 3, GL_FLOAT, GL_TRUE,
                                     sizeof(GLfloat) * 8, (void *) (sizeof(GLfloat) * 3));
    m_blockVertexBuffer.setAttribute(Graphics::TEXTURE_ATTR, 2, GL_FLOAT, GL_FALSE,
                       sizeof(GLfloat) * 8, (void *) (sizeof(GLfloat) * 6));

    /* Do not update chunks */
    m_vertexUpdate = false;

    /* Reset the number of vertices */
    m_blockNumVertices = 0;
}

void Chunk::intersect(VoxelEntity *ent)
{
    Block *block;
    int blockIndex = 0;

    for(int y = 0; y < CHUNK_SIZE; y++)
    {
        for(int z = 0; z < CHUNK_SIZE; z++)
        {
            for(int x = 0; x < CHUNK_SIZE; x++)
            {
                block = m_manager->getBlock(m_blocks[blockIndex]);

                if(ent->intersect(block, m_pos + glm::vec3(x, y, z)))
                {
                    /* TODO (later): chunk callbacks, block pointer updating */
                }

                blockIndex++;
            }
        }
    }
}

void Chunk::onTick(float seconds)
{
}

void Chunk::onDraw(Graphics::Controller *graphics)
{
    if(inFrustum(graphics))
    {
        graphics->sendColorUniform(glm::vec3(0.5, 0.5, 0.5), "default");
        graphics->sendUseTextureUniform(1, "default");
        graphics->sendModelUniform(glm::mat4x4(), "default");

        if(m_vertexUpdate)
        {
            updateBlockVertexBuffer();
        }

        m_blockVertexBuffer.draw();
    }
}
