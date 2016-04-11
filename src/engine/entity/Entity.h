#ifndef ENTITY_H
#define ENTITY_H

#include "util/CommonIncludes.h"
#include "engine/world/WorldConstants.h"

class Graphics;
class World;
class BoundingShape;
class Shape;

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
    BoundingShape *getBoundingShape() const;

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

    virtual void updateFriction();
    virtual void updateGoalVelocity();
    virtual void updateAcceleration();
    virtual void updateVelocity(float seconds);
    virtual void updatePosition(float seconds);

    virtual void updateShape();
    virtual void updateBoundingShape();

    virtual bool intersect(Entity *ent);
    virtual void onIntersect(Entity *ent, glm::vec3 mtv);
    virtual void onTick(float seconds);
    virtual void onDraw(Graphics *graphics);

protected:
    World *m_world;
    BoundingShape *m_boundingShape;
    Shape *m_shape;

    glm::vec3 m_pos;
    glm::vec3 m_dims;

    glm::vec3 m_vel;
    glm::vec3 m_acc;
    glm::vec3 m_goal;

    float m_speed;
    float m_friction;

    bool m_grounded;
};

#endif // ENTITY_H
