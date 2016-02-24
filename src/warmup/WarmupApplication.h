#ifndef WARMUPAPPLICATION_H
#define WARMUPAPPLICATION_H

#include "engine/Application.h"

class WarmupApplication : public Application
{
public:
    WarmupApplication(QGLWidget *container);

    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
};

#endif // WARMUPAPPLICATION_H
