#ifndef ENTITY_H
#define ENTITY_H

#include "util/CommonIncludes.h"
#include "engine/world/WorldConstants.h"

#include <queue>
#include <vector>

class Graphics;
class World;
class Shape;
class CompareDepth;
class PointLight;
class Light;

class Entity
{
public:
    Entity(World *world, glm::vec3 pos = glm::vec3(0, 0, 0),
           glm::vec3 dims = glm::vec3(1, 1, 1),
           float speed = 1,
           glm::vec3 vel = glm::vec3(0, 0, 0),
           glm::vec3 acc = glm::vec3(0, G, 0),
           glm::vec3 goal = glm::vec3(0, 0, 0),
           float friction = MU_GROUND);

    virtual ~Entity();

    Shape *getShape() const;

    glm::vec3 getPosition();
    void setPosition(glm::vec3 pos);

    glm::vec3 getDimensions();
    void setDimensions(glm::vec3 dims);

    virtual float getSpeed();
    void setSpeed(float speed);

    virtual glm::vec3 getVelocity();
    void setVelocity(glm::vec3 vel);

    virtual glm::vec3 getAcceleration();
    void setAcceleration(glm::vec3 acc);

    virtual glm::vec3 getGoalVelocity();
    void setGoalVelocity(glm::vec3 goal);

    virtual float getFriction();
    void setFriction(float friction);

    virtual bool getGrounded();
    void setGrounded(bool grounded);

    virtual bool getMoved();
    void setMoved(bool moved);

    virtual void updateFriction();
    virtual void updateGoalVelocity();
    virtual void updateAcceleration();
    virtual void updateVelocity(float seconds);
    virtual void updatePosition(float seconds);

    virtual void updateShape();

    virtual bool intersect(Entity *ent);
    virtual void onIntersect(Entity *ent, glm::vec3 mtv);
    virtual void onTick(float seconds);

    virtual void drawGeometry(Graphics *graphics);
    virtual void drawLights(Graphics *graphics);
    virtual void drawParticles(Graphics *graphics);
    virtual void drawLightGeometry(Graphics *graphics);

protected:
    World *m_world;
    Shape *m_shape;

    glm::vec3 m_pos;
    glm::vec3 m_dims;

    glm::vec3 m_vel;
    glm::vec3 m_acc;
    glm::vec3 m_goal;

    float m_speed;
    float m_friction;

    bool m_grounded;
    bool m_moved;
};

#endif // ENTITY_H
