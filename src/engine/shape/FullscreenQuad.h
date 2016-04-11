#ifndef FULLSCREENQUAD_H
#define FULLSCREENQUAD_H

#include "engine/shape/Shape.h"
#include "engine/graphics/VertexData.h"

#include <QString>

class Graphics;

class FullscreenQuad : public Shape
{
public:
    FullscreenQuad(QString key);
    virtual ~FullscreenQuad();

    void draw(Graphics *graphics);

private:
    QString m_textureKey;
};

#endif // FULLSCREENQUAD_H
