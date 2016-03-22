#ifndef PLATFORMERSCREEN_H
#define PLATFORMERSCREEN_H

#include "engine/Screen.h"

namespace Graphics
{
class Controller;
}

class PlatformerScreen : public Screen
{
public:
    PlatformerScreen(Application *app, float opacity,
                     Graphics::Controller *graphics);
    ~PlatformerScreen();

    void setLevel(QString levelFile, QString levelKey);

    void keyPressEvent(QKeyEvent *event);

    void onTick(float seconds);

private:
    Graphics::Controller *m_graphics;
};

#endif
