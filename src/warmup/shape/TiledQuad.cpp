#include "warmup/shape/TiledQuad.h"

#include "engine/graphics/Controller.h"
#include "engine/shape/Shape.h"
#include "engine/shape/Quad.h"

TiledQuad::TiledQuad()
{
    glm::mat4x4 model;
    glm::vec3 pos;

    for(int i = -12; i < 12; i++)
    {
        for(int j = -12; j < 12; j++)
        {
            Quad *newTile = new Quad(1, 1, "grass", glm::vec4(1, 1, 1, 1),
                                     glm::vec3(i, 0, j));
            m_tiles.append(newTile);
        }
    }
}

TiledQuad::~TiledQuad()
{
    foreach(Quad *t, m_tiles)
    {
        delete(t);
    }
}

void TiledQuad::draw(Graphics::Controller *graphics)
{
    Shape::draw(graphics);

    foreach(Quad *t, m_tiles)
    {
        t->draw(graphics);
    }
}
