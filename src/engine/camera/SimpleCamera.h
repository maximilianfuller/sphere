#ifndef SIMPLECAMERA_H
#define SIMPLECAMERA_H

#include "engine/camera/Camera.h"

namespace Graphics {
class Controller;
}

class SimpleCamera : public Camera
{
public:
    SimpleCamera();
    ~SimpleCamera();

    void setTransforms(Graphics::Controller *graphics);
};

#endif // SIMPLECAMERA_H
