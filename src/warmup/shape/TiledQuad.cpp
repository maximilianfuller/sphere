#include "warmup/shape/TiledQuad.h"

#include "engine/graphics/Controller.h"
#include "engine/shape/Shape.h"
#include "engine/shape/TexturedQuad.h"

TiledQuad::TiledQuad()
{
    glm::mat4x4 model;
    glm::vec3 pos;

    for(int i = -10; i < 10; i++)
    {
        for(int j = -10; j < 10; j++)
        {
            model = glm::mat4x4();
            pos = glm::vec3(i, 0, j);
            model = glm::translate(model, pos);

            TexturedQuad *new_tile = new TexturedQuad("grass", model);
            m_tiles.append(new_tile);
        }
    }
}

TiledQuad::~TiledQuad()
{
    QList<TexturedQuad *>::iterator t;

    for(t = m_tiles.begin(); t != m_tiles.end(); t++)
    {
        delete (*t);
    }
}

void TiledQuad::draw(Graphics::Controller *graphics)
{
    Shape::draw(graphics);

    graphics->sendUseTextureUniform(1, "default");

    QList<TexturedQuad *>::iterator t;

    for(t = m_tiles.begin(); t != m_tiles.end(); t++)
    {
        (*t)->draw(graphics);
    }
}
