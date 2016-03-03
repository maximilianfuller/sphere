#ifndef PERSPECTIVECAMERA_H
#define PERSPECTIVECAMERA_H

#include "engine/camera/Camera.h"
#include "util/CommonIncludes.h"

namespace Graphics {
class Controller;
}

class PerspectiveCamera : public Camera
{
public:
    PerspectiveCamera(glm::vec2 size = glm::vec2(1.0, 1.0),
                      glm::vec3 eye = glm::vec3(0, 1.0, 0), float yaw = 0,
                      float pitch = 0, float fov = 60.f, bool thirdPerson = false);
    virtual ~PerspectiveCamera();

    void setTransforms(Graphics::Controller *graphics);
};

#endif // PERSPECTIVECAMERA_H
