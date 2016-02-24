#ifndef MINECRAFTAPPLICATION_H
#define MINECRAFTAPPLICATION_H

#include "engine/Application.h"

class MinecraftApplication : public Application
{
public:
    MinecraftApplication(QGLWidget *container);

    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
};

#endif // MINECRAFTAPPLICATION_H
