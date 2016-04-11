#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "engine/Screen.h"

class Graphics;

class GameScreen : public Screen
{
public:
    GameScreen(Application *app, float opacity);
    ~GameScreen();

    void keyPressEvent(QKeyEvent *event);

private:
    Graphics *m_graphics;
};

#endif // GAMESCREEN_H
