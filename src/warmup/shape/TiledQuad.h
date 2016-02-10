#ifndef TILEDQUAD_H
#define TILEDQUAD_H

#include "engine/shape/Shape.h"

#include <QList>

namespace Graphics {
class Controller;
}
class TexturedQuad;

class TiledQuad : public Shape
{
public:
    TiledQuad();
    ~TiledQuad();

    void draw(Graphics::Controller *graphics);

private:
    QList<TexturedQuad *> m_tiles;
};

#endif // TILEDQUAD_H
