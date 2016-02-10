#ifndef CAMERA_H
#define CAMERA_H

#include "util/CommonIncludes.h"

namespace Graphics {
class Controller;
}

const static float nearPlane = 0.1;
const static float farPlane = 200.0;

class Camera
{
public:
    Camera(glm::vec2 size = glm::vec2(1.0, 1.0),
           glm::vec3 eye = glm::vec3(0, 1.0, 0), float yaw = 0,
           float pitch = 0, float fov = 60.f);
    virtual ~Camera();

    glm::vec3 getEye();
    void setEye(glm::vec3 eye);

    glm::vec2 getRatio();
    void setRatio(glm::vec2 size);

    float getYaw();
    void setYaw(float yaw);

    float getPitch();
    void setPitch(float pitch);

    float getFov();
    void setFov(float fov);

    glm::vec3 getLook();

    void translate(glm::vec3 vec);
    void rotate(float yaw, float pitch);

    virtual void setTransforms(Graphics::Controller *graphics) = 0;

protected:
    glm::vec2 m_ratio;
    glm::vec3 m_eye;

    float m_yaw;
    float m_pitch;
    float m_fov;
};

#endif // CAMERA_H
