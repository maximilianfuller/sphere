#include "engine/camera/Camera.h"

Camera::Camera(glm::vec2 size, glm::vec3 eye, float yaw, float pitch, float fov) :
    m_ratio(size),
    m_eye(eye),
    m_yaw(yaw),
    m_pitch(pitch),
    m_fov(fov)
{
}

Camera::~Camera()
{
}

glm::vec2 Camera::getRatio()
{
    return m_ratio;
}

void Camera::setRatio(glm::vec2 size)
{
    m_ratio = size;
}

float Camera::getYaw()
{
    return m_yaw;
}

void Camera::setYaw(float yaw)
{
    m_yaw = yaw;
}

float Camera::getPitch()
{
    return m_pitch;
}

void Camera::setPitch(float pitch)
{
    m_pitch = pitch;
}

float Camera::getFov()
{
    return m_fov;
}

void Camera::setFov(float fov)
{
    m_fov = fov;
}

glm::vec3 Camera::getEye() {
    return m_eye;
}

void Camera::setEye(glm::vec3 eye)
{
    m_eye = eye;
}

glm::vec3 Camera::getLook()
{
    return glm::vec3(glm::cos(m_yaw) * glm::cos(m_pitch), glm::sin(m_pitch),
                     glm::sin(m_yaw) * glm::cos(m_pitch));
}

void Camera::translate(glm::vec3 vec)
{
    m_eye += vec;
}

void Camera::rotate(float yaw, float pitch)
{
    m_yaw += yaw;
    m_pitch += pitch;
    m_pitch = glm::clamp(static_cast<double>(m_pitch), -M_PI / 2.0 + 0.01, M_PI / 2.0 - 0.01);
}
