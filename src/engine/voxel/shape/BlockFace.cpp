#include "engine/voxel/shape//BlockFace.h"

BlockFace::BlockFace(QString shapeKey, glm::mat4x4 model) :
    m_shapeKey(shapeKey),
    Shape(model)
{
}

BlockFace::~BlockFace()
{
}

void BlockFace::draw(Graphics::Controller *graphics, glm::vec3 blockPos)
{
    Shape::draw(graphics);

    glm::mat4x4 model = glm::mat4x4();
    m_model = glm::translate(model, blockPos);

    graphics->sendUseTextureUniform(1, "default");
    graphics->drawShape(m_shapeKey);
}
