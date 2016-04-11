#ifndef BLOCKFACE_H
#define BLOCKFACE_H

#include "engine/shape/Shape.h"

#include <QString>

class BlockFace : public Shape
{
public:
    BlockFace(QString shapeKey, glm::vec4 color = glm::vec4(0.5, 0.5, 0.5, 1.0),
              glm::mat4x4 model = glm::mat4x4());
    ~BlockFace();

    void draw(Graphics *graphics, glm::vec3 blockPos);

private:
    QString m_shapeKey;
};

#endif // BLOCKFACE_H
