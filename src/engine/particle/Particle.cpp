#include "Particle.h"

#include "engine/graphics/Graphics.h"

Particle::Particle(glm::vec3 pos, glm::vec3 vel, QString textureKey) :
    m_pos(pos),
    m_vel(vel),
    m_age(0.f),
    m_textureKey(textureKey)
{
}

void Particle::setPos(glm::vec3 pos)
{
    m_pos = pos;
}

void Particle::setVel(glm::vec3 vel)
{
    m_vel = vel;
}

void Particle::setTextureKey(QString textureKey)
{
    m_textureKey = textureKey;
}

float Particle::getAge()
{
    return m_age;
}

void Particle::tick(float seconds)
{
    m_pos += seconds * m_vel;
    m_age += seconds;
}

void Particle::draw(Graphics *graphics)
{
    glm::mat4x4 rotate = glm::rotate(glm::mat4x4(), -float(M_PI) / 2.f, glm::vec3(1, 0, 0));
    glm::mat4x4 scale = glm::scale(glm::mat4x4(), glm::vec3(0.1, 0.1, 0.1));
    glm::mat4x4 translate = glm::translate(glm::mat4x4(), m_pos);

    graphics->sendModelUniform(translate * scale * rotate);
    graphics->sendColorUniform(glm::vec4(1));
    graphics->sendUseTextureUniform(1);
    graphics->loadTexture(m_textureKey, 0);

    graphics->drawShape("quad");
}
