#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include "engine/Screen.h"

class Application;

class WelcomeScreen : public Screen
{
public:
    WelcomeScreen(Application *app, float opacity = 1.f);
    ~WelcomeScreen();

    virtual void keyPressEvent(QKeyEvent *event);
};

#endif // HOMESCREEN_H
