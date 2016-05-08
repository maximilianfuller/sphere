#ifndef PLATFORMERSCREEN_H
#define PLATFORMERSCREEN_H

#include "engine/Screen.h"

class Graphics;

class PlatformerScreen : public Screen
{
public:
    PlatformerScreen(Application *app, int width, int height, float opacity,
                     Graphics *graphics);
    ~PlatformerScreen();

    void keyPressEvent(QKeyEvent *event);

    void onTick(float seconds);

private:
    Graphics *m_graphics;
};

#endif
