#include "gg.h"

int x=3200,y=2400;

void draw(const GameState *gs)
{
    if (gs->keys['x'])
        drawRect(0xFFFF00,0,0,gs->mx,gs->my);
    else
        drawRect(0xFF00FF,0,0,gs->mx,gs->my);

    drawRect(0x000000,(x/10)-5,(y/10)-5,(x/10)+5,(y/10)+5);
}

int step(const GameState *gs)
{
    if (gs->keys[','])
        y--;
    if (gs->keys['a'])
        x--;
    if (gs->keys['o'])
        y++;
    if (gs->keys['e'])
        x++;
    return !gs->keys[' '];
}

void onKeyDown(int key, const GameState *gs)
{
    return;
}
void onKeyUp(int key, const GameState *gs)
{
    return;
}
void onQuit()
{
    return;
}

int main(int argc, char *argv[])
{
    GameSystem gs;
    gs.draw=draw;
    gs.step=step;
    gs.onKeyDown=onKeyDown;
    gs.onKeyUp=onKeyUp;
    gs.onQuit=onQuit;

    RunGame(&gs,640,480,"test"); 
    return 0;
}
