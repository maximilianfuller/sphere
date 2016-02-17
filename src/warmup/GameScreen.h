#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "engine/Screen.h"

class GameScreen : public Screen
{
public:
    GameScreen(Application *app, float opacity = 1.f);
    ~GameScreen();

    void keyPressEvent(QKeyEvent *event);

    void onTick(float seconds);
};

#endif // GAMESCREEN_H
