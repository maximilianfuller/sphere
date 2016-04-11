#ifndef FINALAPPLICATION_H
#define FINALAPPLICATION_H

#include "engine/Application.h"

class FinalApp : public Application
{
public:
    FinalApp(QGLWidget *container);

    void mouseMoveEvent(QMouseEvent *event);
};

#endif // FINALAPPLICATION_H
