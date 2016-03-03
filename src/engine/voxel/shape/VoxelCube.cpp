#include "engine/voxel/shape/VoxelCube.h"

#include "engine/graphics/Controller.h"

#include "engine/voxel/shape/CubeData.h"

VoxelCube::VoxelCube(glm::vec2 ls, glm::vec2 le,
                     glm::vec2 rs, glm::vec2 re,
                     glm::vec2 bts, glm::vec2 bte,
                     glm::vec2 ts, glm::vec2 te,
                     glm::vec2 bas, glm::vec2 bae,
                     glm::vec2 fs, glm::vec2 fe) :
    leftStart(ls),
    leftEnd(le),
    rightStart(rs),
    rightEnd(re),
    botStart(bts),
    botEnd(bte),
    topStart(ts),
    topEnd(te),
    backStart(bas),
    backEnd(bae),
    frontStart(fs),
    frontEnd(fe)
{
}

VoxelCube::~VoxelCube()
{
}

void VoxelCube::setLeftTexture(glm::vec2 start, glm::vec2 end)
{
    leftStart = start;
    leftEnd = end;
}

void VoxelCube::setRightTexture(glm::vec2 start, glm::vec2 end)
{
    rightStart = start;
    rightEnd = end;
}

void VoxelCube::setBotTexture(glm::vec2 start, glm::vec2 end)
{
    botStart = start;
    botEnd = end;
}

void VoxelCube::setTopTexture(glm::vec2 start, glm::vec2 end)
{
    topStart = start;
    topEnd = end;
}

void VoxelCube::setBackTexture(glm::vec2 start, glm::vec2 end)
{
    backStart = start;
    backEnd = end;
}

void VoxelCube::setFrontTexture(glm::vec2 start, glm::vec2 end)
{
    frontStart = start;
    frontEnd = end;
}

void VoxelCube::drawLeftFace(float *vertexData, int &numVertices)
{
    for(int index = 0; index < 48; index += 8)
    {
        vertexData[numVertices + index] = leftFaceData[index] + m_pos.x;
        vertexData[numVertices + index + 1] = leftFaceData[index + 1] + m_pos.y;
        vertexData[numVertices + index + 2] = leftFaceData[index + 2] + m_pos.z;

        vertexData[numVertices + index + 3] = leftFaceData[index + 3];
        vertexData[numVertices + index + 4] = leftFaceData[index + 4];
        vertexData[numVertices + index + 5] = leftFaceData[index + 5];

        vertexData[numVertices + index + 6] = leftFaceData[index + 6] * (leftEnd.x - leftStart.x);
        vertexData[numVertices + index + 6] += leftStart.x;
        vertexData[numVertices + index + 7] = leftFaceData[index + 7] * (leftEnd.y - leftStart.y);
        vertexData[numVertices + index + 7] += leftStart.y;
    }

    numVertices += 48;
}

void VoxelCube::drawRightFace(float *vertexData, int &numVertices)
{
    for(int index = 0; index < 48; index += 8)
    {
        vertexData[numVertices + index] = rightFaceData[index] + m_pos.x;
        vertexData[numVertices + index + 1] = rightFaceData[index + 1] + m_pos.y;
        vertexData[numVertices + index + 2] = rightFaceData[index + 2] + m_pos.z;

        vertexData[numVertices + index + 3] = rightFaceData[index + 3];
        vertexData[numVertices + index + 4] = rightFaceData[index + 4];
        vertexData[numVertices + index + 5] = rightFaceData[index + 5];

        vertexData[numVertices + index + 6] = rightFaceData[index + 6] * (rightEnd.x - rightStart.x);
        vertexData[numVertices + index + 6] += rightStart.x;
        vertexData[numVertices + index + 7] = rightFaceData[index + 7] * (rightEnd.y - rightStart.y);
        vertexData[numVertices + index + 7] += rightStart.y;
    }

    numVertices += 48;
}

void VoxelCube::drawBotFace(float *vertexData, int &numVertices)
{
    for(int index = 0; index < 48; index += 8)
    {
        vertexData[numVertices + index] = botFaceData[index] + m_pos.x;
        vertexData[numVertices + index + 1] = botFaceData[index + 1] + m_pos.y;
        vertexData[numVertices + index + 2] = botFaceData[index + 2] + m_pos.z;

        vertexData[numVertices + index + 3] = botFaceData[index + 3];
        vertexData[numVertices + index + 4] = botFaceData[index + 4];
        vertexData[numVertices + index + 5] = botFaceData[index + 5];

        vertexData[numVertices + index + 6] = botFaceData[index + 6] * (botEnd.x - botStart.x);
        vertexData[numVertices + index + 6] += botStart.x;
        vertexData[numVertices + index + 7] = botFaceData[index + 7] * (botEnd.y - botStart.y);
        vertexData[numVertices + index + 7] += botStart.y;
    }

    numVertices += 48;
}

void VoxelCube::drawTopFace(float *vertexData, int &numVertices)
{
    for(int index = 0; index < 48; index += 8)
    {
        vertexData[numVertices + index] = topFaceData[index] + m_pos.x;
        vertexData[numVertices + index + 1] = topFaceData[index + 1] + m_pos.y;
        vertexData[numVertices + index + 2] = topFaceData[index + 2] + m_pos.z;

        vertexData[numVertices + index + 3] = topFaceData[index + 3];
        vertexData[numVertices + index + 4] = topFaceData[index + 4];
        vertexData[numVertices + index + 5] = topFaceData[index + 5];

        vertexData[numVertices + index + 6] = topFaceData[index + 6] * (topEnd.x - topStart.x);
        vertexData[numVertices + index + 6] += topStart.x;
        vertexData[numVertices + index + 7] = topFaceData[index + 7] * (topEnd.y - topStart.y);
        vertexData[numVertices + index + 7] += topStart.y;
    }

    numVertices += 48;
}

void VoxelCube::drawBackFace(float *vertexData, int &numVertices)
{
    for(int index = 0; index < 48; index += 8)
    {
        vertexData[numVertices + index] = backFaceData[index] + m_pos.x;
        vertexData[numVertices + index + 1] = backFaceData[index + 1] + m_pos.y;
        vertexData[numVertices + index + 2] = backFaceData[index + 2] + m_pos.z;

        vertexData[numVertices + index + 3] = backFaceData[index + 3];
        vertexData[numVertices + index + 4] = backFaceData[index + 4];
        vertexData[numVertices + index + 5] = backFaceData[index + 5];

        vertexData[numVertices + index + 6] = backFaceData[index + 6] * (backEnd.x - backStart.x);
        vertexData[numVertices + index + 6] += backStart.x;
        vertexData[numVertices + index + 7] = backFaceData[index + 7] * (backEnd.y - backStart.y);
        vertexData[numVertices + index + 7] += backStart.y;
    }

    numVertices += 48;
}

void VoxelCube::drawFrontFace(float *vertexData, int &numVertices)
{
    for(int index = 0; index < 48; index += 8)
    {
        vertexData[numVertices + index] = frontFaceData[index] + m_pos.x;
        vertexData[numVertices + index + 1] = frontFaceData[index + 1] + m_pos.y;
        vertexData[numVertices + index + 2] = frontFaceData[index + 2] + m_pos.z;

        vertexData[numVertices + index + 3] = frontFaceData[index + 3];
        vertexData[numVertices + index + 4] = frontFaceData[index + 4];
        vertexData[numVertices + index + 5] = frontFaceData[index + 5];

        vertexData[numVertices + index + 6] = frontFaceData[index + 6] * (frontEnd.x - frontStart.x);
        vertexData[numVertices + index + 6] += frontStart.x;
        vertexData[numVertices + index + 7] = frontFaceData[index + 7] * (frontEnd.y - frontStart.y);
        vertexData[numVertices + index + 7] += frontStart.y;
    }

    numVertices += 48;
}

void VoxelCube::draw(float *vertexData, int &numVertices,
                     bool drawLeft, bool drawRight, bool drawBot,
                     bool drawTop, bool drawBack, bool drawFront)
{
    if(drawLeft)
        drawLeftFace(vertexData, numVertices);

    if(drawRight)
        drawRightFace(vertexData, numVertices);

    if(drawBack)
        drawBackFace(vertexData, numVertices);

    if(drawFront)
        drawFrontFace(vertexData, numVertices);

    if(drawBot)
        drawBotFace(vertexData, numVertices);

    if(drawTop)
        drawTopFace(vertexData, numVertices);
}
