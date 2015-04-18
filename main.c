#include "gui.h"
#include <stdio.h>

#define WIN_WIDTH 1200
#define WIN_HEIGHT 700
#define WIN_FPS 30

void load(void)
{
    //todo: call all linked loads
}

void draw(const InputStateHANDLE is)
{
    //todo: call all linked draws
}

int step(const InputStateHANDLE is)
{
    //todo: call all linked steps

    // Quit on space is down?
    return !is->keys[' '];
}

void onKeyDown(int key, const InputStateHANDLE is)
{
    //todo: call all linked onKeyDowns
}

void onKeyUp(int key, const InputStateHANDLE is)
{
    //todo: call all linked onKeyUps
}

void onQuit()
{
    //todo: call all linked onQuits
}

int main(int argc, char *argv[])
{
    EventCallbacks ec;
    ec.load=load;
    ec.draw=draw;
    ec.step=step;
    ec.onKeyDown=onKeyDown;
    ec.onKeyUp=onKeyUp;
    ec.onQuit=onQuit;

    RunGame(&ec, WIN_WIDTH, WIN_HEIGHT, WIN_FPS, "Warp do we do now?!");
    return 0;
}
