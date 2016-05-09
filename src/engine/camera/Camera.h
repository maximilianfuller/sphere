#ifndef CAMERA_H
#define CAMERA_H

#include "util/CommonIncludes.h"

class Graphics;

const static float nearPlane = 0.00001;
const static float farPlane = 200.0;

class Camera
{
public:
    Camera(glm::vec2 size = glm::vec2(1.0, 1.0),
           glm::vec3 eye = glm::vec3(0, 1.0, 0), float yaw = 0,
           float pitch = 0, float fov = 45.f);
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
    void setLook(glm::vec3 look);

    glm::vec3 getUp();
    void setUp(glm::vec3 up);

    glm::mat4x4 getView();
    glm::mat4x4 getPerspective();

    bool getThirdPerson();

    void toggleThirdPerson();
    void translate(glm::vec3 vec);
    void rotate(float yaw, float pitch);

    void updateTransforms();
    void updateFrustumPlanes(Graphics *graphics);

    virtual void setTransforms(Graphics *graphics);
    virtual void setResolution(Graphics *graphics);

protected:
    float m_yaw, m_pitch;
    float m_fov;

    glm::vec2 m_ratio;
    glm::vec3 m_eye;

    glm::vec3 m_look, m_up;

    glm::mat4x4 m_view, m_proj, m_persp;

    bool m_update;
    bool m_thirdPerson;
};

#endif // CAMERA_H
