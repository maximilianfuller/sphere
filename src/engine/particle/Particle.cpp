#include "Particle.h"

#include "engine/graphics/Graphics.h"

Particle::Particle(glm::vec3 pos, glm::vec3 vel, QString textureKey) :
    pos(pos),
    vel(vel),
    age(0.f),
    textureKey(textureKey)
{
}

void Particle::tick(float seconds)
{
    pos += seconds * vel;
    age += seconds;
}

void Particle::draw(Graphics *graphics, glm::mat4x4 model)
{
    glm::mat4x4 rotate = model * glm::rotate(glm::mat4x4(),
                                             -float(M_PI) / 2.f,
                                             glm::vec3(1, 0, 0));
    glm::mat4x4 scale = glm::scale(glm::mat4x4(), glm::vec3(0.2, 0.2, 0.2));
    glm::mat4x4 translate = glm::translate(glm::mat4x4(), pos);

    graphics->sendModelUniform(translate * scale * rotate);
    graphics->loadTexture(textureKey, 1);
    graphics->sendTexturePosition("tex", 1);

    graphics->drawShape("quad");
}
