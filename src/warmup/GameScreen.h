#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "engine/Screen.h"

class Application;

class GameScreen : public Screen
{
public:
    GameScreen(Application *app, float opacity);
    ~GameScreen();

    void keyPressEvent(QKeyEvent *event);
};

#endif // GAMESCREEN_H
