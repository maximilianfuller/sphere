#include "VoxelCollisionManager.h"

#include "engine/voxel/chunk/Chunk.h"
#include "engine/entity/ActiveEntity.h"
#include "engine/entity/BackgroundEntity.h"
#include "engine/voxel/block/Block.h"

/* TODO:
 * 1) Choose chunks to intersect with based on entity position
 * 2) Implement sweep for entity and chunk
 * 3) Move entity to correct position
 */
VoxelCollisionManager::VoxelCollisionManager(Chunk **chunks, int numChunks,
                           QList<ActiveEntity *> &activeEnts,
                           QList<BackgroundEntity *> &backgroundEnts) :
    m_chunks(chunks),
    m_numChunks(numChunks),
    CollisionManager(activeEnts, backgroundEnts)
{
}

bool VoxelCollisionManager::withinChunk(Chunk *chunk, ActiveEntity *ent)
{
    glm::vec3 entityPos = ent->getPosition();
    glm::vec3 chunkPos = chunk->getPosition();

    return (entityPos.y > chunkPos.y - 3 && entityPos.y < chunkPos.y + CHUNK_SIZE + 3)
            && (entityPos.x > chunkPos.x - 2 && entityPos.x < chunkPos.x + CHUNK_SIZE + 2)
            && (entityPos.z > chunkPos.z - 2 && entityPos.z < chunkPos.z + CHUNK_SIZE + 2);
}

void VoxelCollisionManager::xSweep(Chunk *chunk, ActiveEntity *ent, float seconds)
{
    glm::vec3 entPos = ent->getPosition();
    glm::vec3 entDims = ent->getDimensions();
    glm::vec3 entVel = ent->getVelocity();
    glm::vec3 chunkPos = chunk->getPosition();

    float entSpeed = ent->getSpeed();

    /* Get predicted position */
    float px = entPos.x + entVel.x * entSpeed * seconds;

    /* Get start and end x, z values */
    int startY = int(glm::round(entPos.y - entDims.y / 2 - chunkPos.y));
    int endY = int(glm::round(entPos.y + entDims.y / 2 - chunkPos.y));

    int startZ = int(glm::round(entPos.z - entDims.z / 2 - chunkPos.z));
    int endZ = int(glm::round(entPos.z + entDims.z / 2 - chunkPos.z));

    bool intersected = false;
    int x, y, z;

    if(entVel.x < 0)
    {
        /* Get target y value */
        int startX = int(glm::floor(entPos.x - entDims.x - chunkPos.x));
        int endX = int(glm::floor(entPos.x - entDims.x + entVel.x * entSpeed * seconds - chunkPos.x));

        /* Loop over x, z, y values until target value, checking intersections */
        for(x = startX; x >= endX; x--)
        {
            for(y = startY; y <= endY; y++)
            {
                for(z = startZ; z <= endZ; z++)
                {
                    BlockPointer block = chunk->getBlockPointer(x, y, z);

                    if(block != BLOCK_AIR)
                    {
                        intersected = true;
                        break;
                    }
                }

                if(intersected)
                    break;
            }

            if(intersected)
                break;
        }

        /* Update player position if there is an intersection */
        if(intersected)
        {
            float nx = x + (1 + entDims.x) / 2 + EPS + chunkPos.x;

            /*
            if(nx + EPS > px)
            {
                entPos.x = nx;
                entVel.x = 0;
            }
            else
            {
                entPos.x = px;
            }
            */
                entPos.x = nx;
                entVel.x = 0;

            ent->setPosition(entPos);
            ent->setVelocity(entVel);
        }
    }
    else
    {
        /* Get target y value */
        int startX = int(glm::ceil(entPos.x + entDims.x -chunkPos.x));
        int endX = int(glm::ceil(entPos.x + entDims.x + entVel.x * entSpeed * seconds - chunkPos.x));

        /* Loop over x, z, y values until target value, checking intersections */
        for(x = startX; x <= endX; x++)
        {
            for(y = startY; y <= endY; y++)
            {
                for(z = startZ; z <= endZ; z++)
                {
                    BlockPointer block = chunk->getBlockPointer(x, y, z);

                    if(block != BLOCK_AIR)
                    {
                        intersected = true;
                        break;
                    }
                }

                if(intersected)
                    break;
            }

            if(intersected)
                break;
        }

        /* Update player position if there is an intersection */
        if(intersected)
        {
            float nx = x - (1 + entDims.x) / 2 - EPS + chunkPos.x;

            /*
            if(nx - EPS < px)
            {
                entPos.x = nx;
                entVel.x = 0;
            }
            else
            {
                entPos.x = px;
            }
            */
                entPos.x = nx;
                entVel.x = 0;

            ent->setPosition(entPos);
            ent->setVelocity(entVel);
        }
    }
}

void VoxelCollisionManager::zSweep(Chunk *chunk, ActiveEntity *ent, float seconds)
{
    glm::vec3 entPos = ent->getPosition();
    glm::vec3 entDims = ent->getDimensions();
    glm::vec3 entVel = ent->getVelocity();
    glm::vec3 chunkPos = chunk->getPosition();

    float entSpeed = ent->getSpeed();

    /* Get predicted position */
    float pz = entPos.z + entVel.z * entSpeed * seconds;

    /* Get start and end x, z values */
    int startY = int(glm::round(entPos.y - entDims.y / 2 - chunkPos.y));
    int endY = int(glm::round(entPos.y + entDims.y / 2 - chunkPos.y));

    int startX = int(glm::round(entPos.x - entDims.x / 2 - chunkPos.x));
    int endX = int(glm::round(entPos.x + entDims.x / 2 - chunkPos.x));

    bool intersected = false;
    int x, y, z;

    if(entVel.z < 0)
    {
        /* Get target y value */
        int startZ = int(glm::floor(entPos.z - entDims.z - chunkPos.z));
        int endZ = int(glm::floor(entPos.z - entDims.z + entVel.z * entSpeed * seconds - chunkPos.z));

        /* Loop over x, z, y values until target value, checking intersections */
        for(z = startZ; z >= endZ; z--)
        {
            for(y = startY; y <= endY; y++)
            {
                for(x = startX; x <= endX; x++)
                {
                    BlockPointer block = chunk->getBlockPointer(x, y, z);

                    if(block != BLOCK_AIR)
                    {
                        intersected = true;
                        break;
                    }
                }

                if(intersected)
                    break;
            }

            if(intersected)
                break;
        }

        /* Update player position if there is an intersection */
        if(intersected)
        {
            float nz = z + (1 + entDims.z) / 2 + EPS + chunkPos.z;

            /*
            if(nz + EPS > pz)
            {
                entPos.z = nz;
                entVel.z = 0;
            }
            else
            {
                entPos.z = pz;
            }
            */

                entPos.z = nz;
                entVel.z = 0;

            ent->setPosition(entPos);
            ent->setVelocity(entVel);
        }
    }
    else
    {
        /* Get target y value */
        int startZ = int(glm::ceil(entPos.z + entDims.z - chunkPos.z));
        int endZ = int(glm::ceil(entPos.z + entDims.z + entVel.z * entSpeed * seconds - chunkPos.z));

        /* Loop over x, z, y values until target value, checking intersections */
        for(z = startZ; z <= endZ; z++)
        {
            for(y = startY; y <= endY; y++)
            {
                for(x = startX; x <= endX; x++)
                {
                    BlockPointer block = chunk->getBlockPointer(x, y, z);

                    if(block != BLOCK_AIR)
                    {
                        intersected = true;
                        break;
                    }
                }

                if(intersected)
                    break;
            }

            if(intersected)
                break;
        }

        /* Update player position if there is an intersection */
        if(intersected)
        {
            float nz = z - (1 + entDims.z) / 2 - EPS + chunkPos.z;

            /*
            if(nz - EPS < pz)
            {
                entPos.z = nz;
                entVel.z = 0;
            }
            else
            {
                entPos.z = pz;
            }
            */
                entPos.z = nz;
                entVel.z = 0;

            ent->setPosition(entPos);
            ent->setVelocity(entVel);
        }
    }
}

void VoxelCollisionManager::ySweep(Chunk *chunk, ActiveEntity *ent, float seconds)
{
    glm::vec3 entPos = ent->getPosition();
    glm::vec3 entDims = ent->getDimensions();
    glm::vec3 entVel = ent->getVelocity();
    glm::vec3 chunkPos = chunk->getPosition();

    float entSpeed = ent->getSpeed();

    /* Get predicted position */
    float py = entPos.y + entVel.y * entSpeed * seconds;

    /* Get start and end x, z values */
    int startX = int(glm::round(entPos.x - entDims.x / 2 - chunkPos.x));
    int endX = int(glm::round(entPos.x + entDims.x / 2 - chunkPos.x));

    int startZ = int(glm::round(entPos.z - entDims.z / 2 - chunkPos.z));
    int endZ = int(glm::round(entPos.z + entDims.z / 2 - chunkPos.z));

    bool intersected = false;
    int x, y, z;

    if(entVel.y < 0)
    {
        /* Get target y value */
        int startY = int(glm::floor(entPos.y - entDims.y - chunkPos.y));
        int endY = int(glm::floor(entPos.y - entDims.y + entVel.y * entSpeed * seconds - chunkPos.y));

        /* Loop over x, z, y values until target value, checking intersections */
        for(y = startY; y >= endY; y--)
        {
            for(x = startX; x <= endX; x++)
            {
                for(z = startZ; z <= endZ; z++)
                {
                    BlockPointer block = chunk->getBlockPointer(x, y, z);

                    if(block != BLOCK_AIR)
                    {
                        intersected = true;
                        break;
                    }
                }

                if(intersected)
                    break;
            }

            if(intersected)
                break;
        }

        /* Update player position if there is an intersection */
        if(intersected)
        {
            float ny = y + (1 + entDims.y) / 2 + EPS + chunkPos.y;

            /*
            if(ny + EPS > py)
            {
                entPos.y = ny;
                entVel.y = 0;
                ent->setGrounded(true);
            }
            else
            {
                entPos.y = py;
            }
            */
                entPos.y = ny;
                entVel.y = 0;
                ent->setGrounded(true);


            ent->setPosition(entPos);
            ent->setVelocity(entVel);
        }
    }
    else
    {
        /* Get target y value */
        int startY = int(glm::ceil(entPos.y + entDims.y - chunkPos.y));
        int endY = int(glm::ceil(entPos.y + entDims.y + entVel.y * entSpeed * seconds - chunkPos.y));

        /* Loop over x, z, y values until target value, checking intersections */
        for(y = startY; y <= endY; y++)
        {
            for(x = startX; x <= endX; x++)
            {
                for(z = startZ; z <= endZ; z++)
                {
                    BlockPointer block = chunk->getBlockPointer(x, y, z);

                    if(block != BLOCK_AIR)
                    {
                        intersected = true;
                        break;
                    }
                }

                if(intersected)
                    break;
            }

            if(intersected)
                break;
        }

        /* Update player position if there is an intersection */
        if(intersected)
        {
            float ny = y - (1 + entDims.y) / 2 - EPS + chunkPos.y;

            /*
            if(ny - EPS < py)
            {
                entPos.y = ny;
                entVel.y = 0;
            }
            else
            {
                entPos.y = py;
            }
            */
                entPos.y = ny;
                entVel.y = 0;

            ent->setPosition(entPos);
            ent->setVelocity(entVel);
        }
    }
}

void VoxelCollisionManager::onTick(float seconds)
{
    int numActiveEntities = m_activeEntities.size();

    for(int i = 0; i < numActiveEntities; i++)
    {
        ActiveEntity *ent = m_activeEntities[i];

        for(int j = 0; j < m_numChunks; j++)
        {
            if(withinChunk(m_chunks[j], ent))
            {
                xSweep(m_chunks[j], ent, seconds);
                ySweep(m_chunks[j], ent, seconds);
                zSweep(m_chunks[j], ent, seconds);
            }
        }
    }
}
