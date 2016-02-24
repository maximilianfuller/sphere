#ifndef MINECRAFTSCREEN_H
#define MINECRAFTSCREEN_H

#include "engine/Screen.h"

class MinecraftScreen : public Screen
{
public:
    MinecraftScreen(Application *app, float opacity = 1.f);
    ~MinecraftScreen();

    void keyPressEvent(QKeyEvent *event);

    void onTick(float seconds);
};

#endif // MINECRAFTSCREEN_H
