#include "engine/camera/PerspectiveCamera.h"
#include "engine/graphics/Controller.h"

PerspectiveCamera::PerspectiveCamera(glm::vec2 size, glm::vec3 eye, float yaw, float pitch,
               float fov, bool thirdPerson) :
    Camera(size, eye, yaw, pitch, fov),
    m_thirdPerson(thirdPerson)
{
}

PerspectiveCamera::~PerspectiveCamera()
{
}

void PerspectiveCamera::toggleThirdPerson()
{
    m_thirdPerson = !m_thirdPerson;
}

void PerspectiveCamera::setTransforms(Graphics::Controller *graphics)
{
    glm::vec3 look, up, eye;
    glm::mat4x4 view, proj;

    // Orient look vector
    look = getLook();

    // Set up vector
    if(m_pitch < 0)
    {
        up = glm::normalize(glm::vec3(look.x, 1.f, look.z));
    }
    else
    {
        up = glm::vec3(0, 1.f, 0);
    }

    // Set eye
    if(m_thirdPerson)
    {
        eye = m_eye - 3.f * look;
    }
    else
    {
        eye = m_eye;
    }

    // Create transformation matrices
    view = glm::lookAt(eye, eye + look, up);
    proj = glm::perspective(glm::radians(m_fov), m_ratio.x / m_ratio.y,
                            nearPlane, farPlane);

    // Send matrices to the shader
    graphics->sendViewUniform(view, "default");
    graphics->sendProjectionUniform(proj, "default");
}
