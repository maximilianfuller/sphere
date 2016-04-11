#include "engine/shape/Quad.h"

#include "engine/graphics/Graphics.h"

Quad::Quad(bool useTexture, bool useLighting, QString key, glm::vec4 color,
           glm::vec3 pos, glm::vec3 dims) :
    m_useTexture(useTexture),
    m_useLighting(useLighting),
    m_textureKey(key),
    Shape(pos, dims, color)
{
}

Quad::~Quad()
{
}

void Quad::draw(Graphics *graphics)
{
    Shape::draw(graphics);

    graphics->sendUseTextureUniform(m_useTexture);
    graphics->sendUseLightingUniform(m_useLighting);

    if(m_useTexture)
    {
        graphics->loadTexture(m_textureKey, 0);
    }

    graphics->drawShape("quad");

    if(m_useTexture)
    {
        graphics->unloadTexture(0);
    }

    if(!m_useLighting)
    {
        graphics->sendUseLightingUniform(1);
    }
}
