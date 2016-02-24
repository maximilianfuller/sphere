#ifndef VOXELCUBE_H
#define VOXELCUBE_H

#include "engine/shape/Shape.h"

class VoxelCube : public Shape
{
public:
    VoxelCube(glm::vec2 ls, glm::vec2 le,
              glm::vec2 rs, glm::vec2 re,
              glm::vec2 bts, glm::vec2 bte,
              glm::vec2 ts, glm::vec2 te,
              glm::vec2 bas, glm::vec2 bae,
              glm::vec2 fs, glm::vec2 fe);
    ~VoxelCube();

    void setLeftTexture(glm::vec2 start, glm::vec2 end);
    void setRightTexture(glm::vec2 start, glm::vec2 end);
    void setBotTexture(glm::vec2 start, glm::vec2 end);
    void setTopTexture(glm::vec2 start, glm::vec2 end);
    void setBackTexture(glm::vec2 start, glm::vec2 end);
    void setFrontTexture(glm::vec2 start, glm::vec2 end);

    void drawLeftFace(float *vertexData, int &numVertices);
    void drawRightFace(float *vertexData, int &numVertices);
    void drawBotFace(float *vertexData, int &numVertices);
    void drawTopFace(float *vertexData, int &numVertices);
    void drawBackFace(float *vertexData, int &numVertices);
    void drawFrontFace(float *vertexData, int &numVertices);

    void draw(float *vertexData, int &numVertices,
              bool drawLeft, bool drawRight, bool drawBot,
              bool drawTop, bool drawBack, bool drawFront);

private:
    glm::vec2 leftStart, leftEnd;
    glm::vec2 rightStart, rightEnd;
    glm::vec2 botStart, botEnd;
    glm::vec2 topStart, topEnd;
    glm::vec2 backStart, backEnd;
    glm::vec2 frontStart, frontEnd;
};

#endif // VOXELCUBE_H
