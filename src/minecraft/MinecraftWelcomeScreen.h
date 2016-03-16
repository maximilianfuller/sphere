#ifndef MINECRAFTWELCOMESCREEN_H
#define MINECRAFTWELCOMESCREEN_H

#include "engine/Screen.h"

class Application;

class MinecraftWelcomeScreen : public Screen
{
public:
    MinecraftWelcomeScreen(Application *app, float opacity = 1.f);
    ~MinecraftWelcomeScreen();

    virtual void keyPressEvent(QKeyEvent *event);
};
#endif // MINECRAFTWELCOMESCREEN_H
