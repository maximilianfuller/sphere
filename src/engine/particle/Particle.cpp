#include "Particle.h"

#include "engine/graphics/Graphics.h"

Particle::Particle(glm::vec3 pos, glm::vec3 vel, float noise1, float noise2,
                   QString textureKey) :
    pos(pos),
    vel(vel),
    u(noise1),
    v(noise2),
    age(0.f),
    textureKey(textureKey)
{
}

void Particle::tick(float seconds)
{
    pos += seconds * vel;
    age += seconds;
}

void Particle::draw(Graphics *graphics, glm::mat4x4 look, glm::mat4x4 model)
{
    glm::vec3 newPos = glm::vec3(model * glm::vec4(pos, 1.0));
    glm::mat4x4 rotate = look * glm::rotate(glm::mat4x4(), -float(M_PI) / 2.f, glm::vec3(1, 0, 0));
    glm::mat4x4 scale = glm::scale(glm::mat4x4(), glm::vec3(0.0001, 0.0001, 0.0001));
    glm::mat4x4 translate = glm::translate(glm::mat4x4(), newPos);

    graphics->sendModelUniform(translate * scale * rotate);
    graphics->sendParticleAgeUniform(age / MAX_AGE);
    graphics->loadTexture(textureKey, 1);
    graphics->sendTexturePosition("tex", 1);

    graphics->drawShape("quad");
}
