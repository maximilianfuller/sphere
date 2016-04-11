#include "engine/voxel/shape//BlockFace.h"

BlockFace::BlockFace(QString shapeKey, glm::vec4 color,
                     glm::mat4x4 model) :
    m_shapeKey(shapeKey),
    Shape()
{
}

BlockFace::~BlockFace()
{
}

void BlockFace::draw(Graphics *graphics, glm::vec3 blockPos)
{
    glm::mat4x4 model;
    model = glm::translate(model, blockPos);
    model = model * m_model;

    graphics->sendModelUniform(model, "default");
    graphics->sendColorUniform(m_color, "default");

    graphics->sendUseTextureUniform(1, "default");
    graphics->drawShape(m_shapeKey);
}
