#include "SimpleCamera.h"

#include "engine/graphics/Graphics.h"

SimpleCamera::SimpleCamera()
{
}

SimpleCamera::~SimpleCamera()
{
}

void SimpleCamera::setTransforms(Graphics *graphics)
{
    /* Send matrices to the shader */
    graphics->sendModelUniform(glm::mat4x4());
    graphics->sendViewUniform(glm::mat4x4());
    graphics->sendProjectionUniform(glm::mat4x4());
}
