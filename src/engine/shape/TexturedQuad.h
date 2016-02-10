#ifndef TEXTUREDQUAD_H
#define TEXTUREDQUAD_H

#include "engine/shape/Shape.h"
#include "engine/graphics/VertexData.h"

#include <QString>

namespace Graphics
{
class Controller;
}

class TexturedQuad : public Shape
{
public:
    TexturedQuad(QString key, glm::mat4x4 model = glm::mat4x4());
    virtual ~TexturedQuad();

    void draw(Graphics::Controller *graphics);

private:
    QString m_textureKey;
};

#endif // TEXTUREDQUAD_H
