#ifndef FULLSCREENQUAD_H
#define FULLSCREENQUAD_H

#include "engine/shape/Shape.h"
#include "engine/graphics/VertexData.h"

#include <QString>

namespace Graphics
{
class Controller;
}

class FullscreenQuad : public Shape
{
public:
    FullscreenQuad(QString key, glm::mat4x4 model = glm::mat4x4());
    virtual ~FullscreenQuad();

    void draw(Graphics::Controller *graphics);

private:
    QString m_textureKey;
};

#endif // FULLSCREENQUAD_H
