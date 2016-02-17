#ifndef BLOCK_H
#define BLOCK_H

#include "engine/entity/Entity.h"

#include "engine/graphics/Controller.h"
#include "engine/intersect/BoundingBox.h"

#include "engine/voxel/manager/Manager.h"
#include "engine/voxel/chunk/Chunk.h"
#include "engine/voxel/shape/BlockFace.h"

const BlockPointer BLOCK_AIR = 0;
const BlockPointer BLOCK_GRASS = 1;
const BlockPointer BLOCK_DIRT = 2;
const BlockPointer BLOCK_ROCK = 3;

struct Block
{
public:
    Block(BlockFace *lef, BlockFace *rif, BlockFace *tof, BlockFace *bof,
          BlockFace *frf, BlockFace *baf, char p) :
        leftFace(lef),
        rightFace(rif),
        topFace(tof),
        botFace(bof),
        frontFace(frf),
        backFace(baf),
        passable(p)
    {
        boundingBox = new BoundingBox();

        leftFace->rotateAbsolute(glm::vec3(0, 0, 1), 90);
        leftFace->translateRelative(glm::vec3(0, 0.5, 0.5));

        rightFace->rotateAbsolute(glm::vec3(0, 0, 1), -90);
        rightFace->translateRelative(glm::vec3(1, 0.5, 0.5));

        botFace->rotateAbsolute(glm::vec3(1, 0, 0), 180);
        botFace->translateRelative(glm::vec3(0.5, 0, 0.5));

        topFace->translateRelative(glm::vec3(0.5, 1, 0.5));

        backFace->rotateAbsolute(glm::vec3(1, 0, 0), -90);
        backFace->translateRelative(glm::vec3(0.5, 0.5, 0));

        frontFace->rotateAbsolute(glm::vec3(1, 0, 0), 90);
        frontFace->translateRelative(glm::vec3(0.5, 0.5, 1));
    }

    ~Block()
    {
        delete boundingBox;
        delete leftFace;
        delete rightFace;
        delete topFace;
        delete botFace;
        delete frontFace;
        delete backFace;
    }

    void onDraw(Graphics::Controller *graphics, Voxel::Manager *manager, Chunk *chunk,
                int chunkX, int chunkY, int chunkZ)
    {
        glm::vec3 blockPos = chunk->getPosition() + glm::vec3(chunkX, chunkY,
                                                              chunkZ);

        if(chunkX == 0 || manager->getBlock(
                    chunk->getBlockPointer(chunkX - 1, chunkY, chunkZ))->passable)
        {
            leftFace->draw(graphics, blockPos);
        }

        if(chunkX == CHUNK_SIZE || manager->getBlock(
                    chunk->getBlockPointer(chunkX + 0, chunkY, chunkZ))->passable)
        {
            rightFace->draw(graphics, blockPos);
        }

        if(chunkY == 0 || manager->getBlock(
                    chunk->getBlockPointer(chunkX, chunkY - 1, chunkZ))->passable)
        {
            botFace->draw(graphics, blockPos);
        }

        if(chunkY == CHUNK_SIZE || manager->getBlock(
                    chunk->getBlockPointer(chunkX, chunkY + 1, chunkZ))->passable)
        {
            topFace->draw(graphics, blockPos);
        }

        if(chunkZ == 0 || manager->getBlock(
                    chunk->getBlockPointer(chunkX, chunkY, chunkZ - 1))->passable)
        {
            backFace->draw(graphics, blockPos);
        }

        if(chunkZ == CHUNK_SIZE || manager->getBlock(
                    chunk->getBlockPointer(chunkX, chunkY, chunkZ) + 1)->passable)
        {
            frontFace->draw(graphics, blockPos);
        }
    }

    BoundingBox *getBoundingBox(glm::vec3 blockPos)
    {
        boundingBox->setPosition(blockPos);
        return boundingBox;
    }

    char passable;

private:
    BoundingBox *boundingBox;

    BlockFace *leftFace, *rightFace, *topFace, *botFace, *frontFace, *backFace;

} __attribute((packed));

#endif // BLOCK_H
