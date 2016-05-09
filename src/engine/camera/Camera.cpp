#include "engine/camera/Camera.h"

#include "engine/graphics/Graphics.h"

Camera::Camera(glm::vec2 size, glm::vec3 eye, float yaw, float pitch, float fov) :
    m_ratio(size),
    m_eye(eye),
    m_look(glm::vec3(0, 0, -1)),
    m_up(glm::vec3(0, 1, 0)),
    m_yaw(yaw),
    m_pitch(pitch),
    m_fov(fov),
    m_update(true),
    m_thirdPerson(false)
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

glm::vec3 Camera::getEye()
{
    if(m_thirdPerson)
    {
        return m_eye - .006f * m_look;
    }
    else
    {
        return m_eye;
    }
}

void Camera::setEye(glm::vec3 eye)
{
    m_eye = eye;
}

glm::vec3 Camera::getLook()
{
    return m_look;
}

void Camera::setLook(glm::vec3 look)
{
    m_look = look;
}

glm::vec3 Camera::getUp()
{
    return m_up;
}

void Camera::setUp(glm::vec3 up)
{
    m_up = up;
}

glm::mat4x4 Camera::getView()
{
    return m_view;
}

glm::mat4x4 Camera::getPerspective()
{
    return m_persp;
}

bool Camera::getThirdPerson()
{
    return m_thirdPerson;
}

void Camera::toggleThirdPerson()
{
    m_thirdPerson = !m_thirdPerson;
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

void Camera::updateTransforms()
{
    /* Set eye */
    glm::vec3 eye = getEye();

    /* Update transforms */
    m_view = glm::lookAt(eye, eye + m_look, m_up);
    m_proj = glm::perspective(glm::radians(m_fov), m_ratio.x / m_ratio.y,
                              nearPlane, farPlane);
    m_persp = m_proj * m_view;

    /* Do not update until flag is set */
    m_update = false;
}

void Camera::updateFrustumPlanes(Graphics *controller)
{
    glm::vec4 nx = glm::vec4(m_persp[0][3] - m_persp[0][0],
            m_persp[1][3] - m_persp[1][0],
            m_persp[2][3] - m_persp[2][0],
            m_persp[3][3] - m_persp[3][0]);

    glm::vec4 x = glm::vec4(m_persp[0][3] + m_persp[0][0],
            m_persp[1][3] + m_persp[1][0],
            m_persp[2][3] + m_persp[2][0],
            m_persp[3][3] + m_persp[3][0]);

    glm::vec4 ny = glm::vec4(m_persp[0][3] - m_persp[0][1],
            m_persp[1][3] - m_persp[1][1],
            m_persp[2][3] - m_persp[2][1],
            m_persp[3][3] - m_persp[3][1]);

    glm::vec4 y = glm::vec4(m_persp[0][3] + m_persp[0][1],
            m_persp[1][3] + m_persp[1][1],
            m_persp[2][3] + m_persp[2][1],
            m_persp[3][3] + m_persp[3][1]);

    glm::vec4 nz = glm::vec4(m_persp[0][3] - m_persp[0][2],
            m_persp[1][3] - m_persp[1][2],
            m_persp[2][3] - m_persp[2][2],
            m_persp[3][3] - m_persp[3][2]);

    glm::vec4 z = glm::vec4(m_persp[0][3] + m_persp[0][2],
            m_persp[1][3] + m_persp[1][2],
            m_persp[2][3] + m_persp[2][2],
            m_persp[3][3] + m_persp[3][2]);

    controller->setFrustumPlanes(nx, x, ny, y, nz, z);
}

void Camera::setTransforms(Graphics *graphics)
{
    /* Update transforms if necessary */
    updateTransforms();
    updateFrustumPlanes(graphics);

    /* Send matrices to the shader */
    graphics->sendViewUniform(m_view);
    graphics->sendProjectionUniform(m_proj);
}

void Camera::setResolution(Graphics *graphics)
{
    graphics->sendResolutionUniform(m_ratio);
}
