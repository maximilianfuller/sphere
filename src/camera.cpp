#include "camera.h"

Camera::Camera(glm::vec2 size) :
    m_eye(glm::vec3(0, 2, 0)),
    m_yaw(0),
    m_pitch(0),
    m_fov(60),
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

void Camera::sendTransforms(GLuint shader)
{
    glm::vec3 look, up;
    glm::mat4x4 view, proj;

    // Orient look based on rotation about y, and horizontal rotation
    look = glm::vec3(glm::cos(m_yaw) * glm::cos(m_pitch), glm::sin(m_pitch), glm::sin(m_yaw) * glm::cos(m_pitch));

    // Set up vector
    if(m_pitch < 0)
    {
        up = glm::normalize(glm::vec3(look.x, 1, look.z));
    }
    else
    {
        up = glm::vec3(0, 1, 0);
    }

    // Create transformation matrices
    view = glm::lookAt(m_eye, m_eye + look, up);
    proj = glm::perspective(glm::radians(m_fov), m_ratio.x / m_ratio.y, nearPlane, farPlane);

    // Send matrices to the shader
    glUniformMatrix4fv(glGetUniformLocation(shader, "v"),1,GL_FALSE,glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader, "p"),1,GL_FALSE,glm::value_ptr(proj));
}
