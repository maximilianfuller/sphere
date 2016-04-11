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
    /* Create transformation matrices */
    glm::mat4x4 view = glm::mat4x4();
    glm::mat4x4 proj = glm::mat4x4();

    /* Send matrices to the shader */
    graphics->sendViewUniform(view);
    graphics->sendProjectionUniform(proj);
}
