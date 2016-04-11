#ifndef SIMPLECAMERA_H
#define SIMPLECAMERA_H

#include "engine/camera/Camera.h"

class Graphics;

class SimpleCamera : public Camera
{
public:
    SimpleCamera();
    ~SimpleCamera();

    void setTransforms(Graphics *graphics);
};

#endif // SIMPLECAMERA_H
