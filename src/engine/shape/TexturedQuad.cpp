#include "engine/shape/TexturedQuad.h"

#include "engine/graphics/Controller.h"

TexturedQuad::TexturedQuad(QString key, glm::mat4x4 model) :
    m_textureKey(key),
    Shape(model)
{
}

TexturedQuad::~TexturedQuad()
{
}

void TexturedQuad::draw(Graphics::Controller *graphics)
{
    Shape::draw(graphics);

    graphics->sendUseTextureUniform(1, "default");
    graphics->loadTexture(m_textureKey, GL_TEXTURE0);
    graphics->drawShape("quad");
    graphics->unloadTexture(GL_TEXTURE0);
}
