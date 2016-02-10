#ifndef WARMUPAPPLICATION_H
#define WARMUPAPPLICATION_H

#include "util/CommonIncludes.h"

#include "engine/Application.h"
#include "engine/Screen.h"
#include "util/Settings.h"

class WarmupApplication : public Application
{
public:
    WarmupApplication(QGLWidget *container);

    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
};

#endif // WARMUPAPPLICATION_H
