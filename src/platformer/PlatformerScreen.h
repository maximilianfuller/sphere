#ifndef PLATFORMERSCREEN_H
#define PLATFORMERSCREEN_H

#include "engine/Screen.h"

class Graphics;

class PlatformerScreen : public Screen
{
public:
    PlatformerScreen(Application *app, float opacity,
                     Graphics *graphics);
    ~PlatformerScreen();

    void setLevel(QString levelFile, QString levelKey);

    void keyPressEvent(QKeyEvent *event);

    void onTick(float seconds);

private:
    Graphics *m_graphics;
};

#endif
