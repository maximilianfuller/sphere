#include "engine/shape/FullscreenQuad.h"

#include "engine/graphics/Graphics.h"

FullscreenQuad::FullscreenQuad(QString key) :
    m_textureKey(key),
    Shape()
{
}

FullscreenQuad::~FullscreenQuad()
{
}

void FullscreenQuad::draw(Graphics *graphics)
{
    Shape::draw(graphics);

    graphics->sendUseTextureUniform(1);
    graphics->sendUseLightingUniform(0);

    graphics->loadTexture(m_textureKey, 0);
    graphics->drawShape("fullscreenQuad");
    graphics->unloadTexture(0);

    graphics->sendUseLightingUniform(1);
}
