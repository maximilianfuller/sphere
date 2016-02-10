#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include "engine/Screen.h"

class Application;

class HomeScreen : public Screen
{
public:
    HomeScreen(Application *app, float opacity);
    ~HomeScreen();

    virtual void keyPressEvent(QKeyEvent *event);
};

#endif // HOMESCREEN_H
