#include "VoxelCollisionManager.h"

#include "engine/entity/Entity.h"
#include "engine/world/World.h"
#include "engine/intersect/AABoundingBox.h"

#include "engine/voxel/entity/VoxelEntity.h"
#include "engine/voxel/chunk/Chunk.h"
#include "engine/voxel/block/Block.h"

VoxelCollisionManager::VoxelCollisionManager(World *world, QList<Chunk *> &chunks,
                                             QList<Entity *> &entities) :
    m_chunks(chunks),
    Manager(world, entities)
{
}

bool VoxelCollisionManager::withinChunk(Chunk *chunk, VoxelEntity *ent)
{
    glm::vec3 entityPos = ent->getPosition();
    glm::vec3 chunkPos = chunk->getPosition();

    return (entityPos.y > chunkPos.y - 3 && entityPos.y < chunkPos.y + CHUNK_SIZE + 3)
            && (entityPos.x > chunkPos.x - 2 && entityPos.x < chunkPos.x + CHUNK_SIZE + 2)
            && (entityPos.z > chunkPos.z - 2 && entityPos.z < chunkPos.z + CHUNK_SIZE + 2);
}

void VoxelCollisionManager::xSweep(Chunk *chunk, VoxelEntity *ent, float seconds)
{
    AABoundingBox *aabb = ent->getAABB();
    glm::vec3 pos = aabb->getPosition();
    glm::vec3 dims = aabb->getDimensions();
    glm::vec3 vel = ent->getVelocity();

    glm::vec3 chunkPos = chunk->getPosition();

    float entSpeed = ent->getSpeed();

    /* Get start and end x, z values */
    int startY = int(glm::round(pos.y - dims.y / 2 - chunkPos.y));
    int endY = int(glm::round(pos.y + dims.y / 2 - chunkPos.y));

    int startZ = int(glm::round(pos.z - dims.z / 2 - chunkPos.z));
    int endZ = int(glm::round(pos.z + dims.z / 2 - chunkPos.z));

    bool intersected = false;
    int x, y, z;

    if(vel.x < 0)
    {
        /* Get target y value */
        int startX = int(glm::floor(pos.x - dims.x - chunkPos.x));
        int endX = int(glm::round(pos.x - dims.x / 2 + vel.x * entSpeed * seconds - chunkPos.x));

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
            float nx = x + (1 + dims.x) / 2 + EPS + chunkPos.x;

            pos.x = nx;
            vel.x = 0;

            ent->setPosition(pos);
            ent->setVelocity(vel);
        }
    }
    else
    {
        /* Get target y value */
        int startX = int(glm::ceil(pos.x + dims.x -chunkPos.x));
        int endX = int(glm::round(pos.x + dims.x / 2 + vel.x * entSpeed * seconds - chunkPos.x));

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
            float nx = x - (1 + dims.x) / 2 - EPS + chunkPos.x;

            pos.x = nx;
            vel.x = 0;

            ent->setPosition(pos);
            ent->setVelocity(vel);
        }
    }
}

void VoxelCollisionManager::zSweep(Chunk *chunk, VoxelEntity *ent, float seconds)
{
    AABoundingBox *aabb = ent->getAABB();
    glm::vec3 pos = aabb->getPosition();
    glm::vec3 dims = aabb->getDimensions();
    glm::vec3 vel = ent->getVelocity();

    glm::vec3 chunkPos = chunk->getPosition();
 float entSpeed = ent->getSpeed();

    /* Get start and end x, z values */
    int startY = int(glm::round(pos.y - dims.y / 2 - chunkPos.y));
    int endY = int(glm::round(pos.y + dims.y / 2 - chunkPos.y));

    int startX = int(glm::round(pos.x - dims.x / 2 - chunkPos.x));
    int endX = int(glm::round(pos.x + dims.x / 2 - chunkPos.x));

    bool intersected = false;
    int x, y, z;

    if(vel.z < 0)
    {
        /* Get target y value */
        int startZ = int(glm::floor(pos.z - dims.z - chunkPos.z));
        int endZ = int(glm::round(pos.z - dims.z / 2 + vel.z * entSpeed * seconds - chunkPos.z));

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
            float nz = z + (1 + dims.z) / 2 + EPS + chunkPos.z;

            pos.z = nz;
            vel.z = 0;

            ent->setPosition(pos);
            ent->setVelocity(vel);
        }
    }
    else
    {
        /* Get target y value */
        int startZ = int(glm::ceil(pos.z + dims.z - chunkPos.z));
        int endZ = int(glm::round(pos.z + dims.z / 2 + vel.z * entSpeed * seconds - chunkPos.z));

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
            float nz = z - (1 + dims.z) / 2 - EPS + chunkPos.z;

            pos.z = nz;
            vel.z = 0;

            ent->setPosition(pos);
            ent->setVelocity(vel);
        }
    }
}

void VoxelCollisionManager::ySweep(Chunk *chunk, VoxelEntity *ent, float seconds)
{
    AABoundingBox *aabb = ent->getAABB();
    glm::vec3 pos = aabb->getPosition();
    glm::vec3 dims = aabb->getDimensions();
    glm::vec3 vel = ent->getVelocity();


    glm::vec3 chunkPos = chunk->getPosition();

    /* Get start and end x, z values */
    int startX = int(glm::round(pos.x - dims.x / 2 - chunkPos.x));
    int endX = int(glm::round(pos.x + dims.x / 2 - chunkPos.x));

    int startZ = int(glm::round(pos.z - dims.z / 2 - chunkPos.z));
    int endZ = int(glm::round(pos.z + dims.z / 2 - chunkPos.z));

    bool intersected = false;
    int x, y, z;


    if(vel.y < 0)
    {
        /* Get target y value */
        int startY = int(glm::floor(pos.y - dims.y - chunkPos.y));
        int endY = int(glm::round(pos.y - dims.y / 2 + vel.y * seconds - chunkPos.y));

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
            float ny = y + (1 + dims.y) / 2 + EPS + chunkPos.y;

            pos.y = ny;
            vel.y = 0;
            ent->setGrounded(true);

            ent->setPosition(pos);
            ent->setVelocity(vel);
            ent->setAcceleration(glm::vec3(0, 0, 0));
        }
        else
        {
            ent->setGrounded(false);
        }
    }
    else
    {
        /* Get target y value */
        int startY = int(glm::ceil(pos.y + dims.y - chunkPos.y));
        int endY = int(glm::round(pos.y + dims.y / 2 + vel.y * seconds - chunkPos.y));

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
            float ny = y - (1 + dims.y) / 2 - EPS + chunkPos.y;

            pos.y = ny;
            vel.y = 0;

            ent->setPosition(pos);
            ent->setVelocity(vel);
        }
    }
}

void VoxelCollisionManager::onTick(float seconds)
{
    foreach(Entity *aEnt, m_entities)
    {
        VoxelEntity *ent = dynamic_cast<VoxelEntity* >(aEnt);

        foreach(Chunk *chunk, m_chunks)
        {
            if(withinChunk(chunk, ent))
            {
                xSweep(chunk, ent, seconds);
                ySweep(chunk, ent, seconds);
                zSweep(chunk, ent, seconds);
            }
        }
    }

    Manager::onTick(seconds);
}
