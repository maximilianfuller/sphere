#ifndef PLATFORMERAPPLICATION_H
#define PLATFORMERAPPLICATION_H

#include "engine/Application.h"

class PlatformerApplication : public Application
{
public:
    PlatformerApplication(QGLWidget *container);

    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
};

#endif
