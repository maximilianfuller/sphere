#include "engine/camera/Camera.h"

Camera::Camera(glm::vec2 size) :
    m_yaw(0),
    m_pitch(0),
    m_fov(60.f),
    m_eye(glm::vec3(0, 1.f, 0)),
    m_ratio(size)
{
}

float Camera::getYaw()
{
    return m_yaw;
}

float Camera::getPitch()
{
    return m_pitch;
}

void Camera::setYaw(float yaw)
{
    m_yaw = yaw;
}

void Camera::setPitch(float pitch)
{
    m_pitch = pitch;
}

void Camera::setFov(float fov)
{
    m_fov = fov;
}

void Camera::setEye(glm::vec3 eye)
{
    m_eye = eye;
}

void Camera::setRatio(glm::vec2 size)
{
    m_ratio = size;
}

void Camera::translate(glm::vec3 vec)
{
    m_eye += vec;
}

void Camera::rotate(float yaw, float pitch)
{
    m_yaw += yaw;
    m_pitch += pitch;
    m_pitch = glm::clamp(static_cast<double>(m_pitch), -M_PI / 2.0, M_PI / 2.0);
}

void Camera::sendToShader(GLuint shader)
{
    glm::vec3 look, up;
    glm::mat4x4 view, proj;

    // Orient look vector
    look = glm::vec3(glm::cos(m_yaw) * glm::cos(m_pitch), glm::sin(m_pitch), glm::sin(m_yaw) * glm::cos(m_pitch));

    // Set up vector
    if(m_pitch < 0)
    {
        up = glm::normalize(glm::vec3(look.x, 1.f, look.z));
    }
    else
    {
        up = glm::vec3(0, 1.f, 0);
    }

    // Create transformation matrices
    view = glm::lookAt(m_eye, m_eye + look, up);
    proj = glm::perspective(glm::radians(m_fov), m_ratio.x / m_ratio.y, nearPlane, farPlane);

    // Send matrices to the shader
    glUniformMatrix4fv(glGetUniformLocation(shader, "v"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader, "p"), 1, GL_FALSE, glm::value_ptr(proj));
}
