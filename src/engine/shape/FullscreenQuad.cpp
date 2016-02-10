#include "engine/shape/FullscreenQuad.h"

#include "engine/graphics/Controller.h"

FullscreenQuad::FullscreenQuad(QString key, glm::mat4x4 model) :
    m_textureKey(key),
    Shape(model)
{
}

FullscreenQuad::~FullscreenQuad()
{
}

void FullscreenQuad::draw(Graphics::Controller *graphics)
{
    Shape::draw(graphics);

    graphics->sendUseTextureUniform(1, "default");
    graphics->loadTexture(m_textureKey, GL_TEXTURE0);
    graphics->drawShape("fullscreenQuad");
    graphics->unloadTexture(GL_TEXTURE0);
}
