#ifndef CAMERA_H
#define CAMERA_H

#include "util/CommonIncludes.h"

const static float nearPlane = 0.1;
const static float farPlane = 200.0;

class Camera
{
public:
    Camera(glm::vec2 size);
    virtual ~Camera() {}

    // Get camera angles
    float getYaw();
    float getPitch();

    // Set aspect ratio
    void setRatio(glm::vec2 size);

    // Change the position of the camera
    void translate(glm::vec3 vec);
    // Change the direction the camera is looking
    void rotate(float yaw, float pitch);

    // Camera transformations applied
    void sendTransforms(GLuint shader);

private:
    // Position of the eye
    glm::vec3 m_eye;

    // Rotation about the y-axis
    float m_yaw;
    // Angle with the horizontal plane (about theta unit vector)
    float m_pitch;
    // Field of view
    float m_fov;

    // Aspect ratio of the screen
    glm::vec2 m_ratio;
};

#endif // CAMERA_H
