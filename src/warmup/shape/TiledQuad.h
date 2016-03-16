#ifndef TILEDQUAD_H
#define TILEDQUAD_H

#include "engine/shape/Shape.h"

#include <QList>

namespace Graphics {
class Controller;
}
class Quad;

class TiledQuad : public Shape
{
public:
    TiledQuad();
    ~TiledQuad();

    void draw(Graphics::Controller *graphics);

private:
    QList<Quad *> m_tiles;
};

#endif // TILEDQUAD_H
