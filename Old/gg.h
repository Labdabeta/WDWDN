#ifndef GAME_GUI_H
#define GAME_GUI_H 1.0 // Version

typedef void *Sprite;
typedef unsigned int Colour;
//Drawing functions (SDL forwarded through gg.c):
void delay(int);
void delayUntil(int);
Sprite loadSprite(const char *);
void cleanSprite(Sprite);
void blitSprite(Sprite,int,int,int,int);



typedef struct {
    int mx,my;
    int keys[256];
    int ml,mr;
}GameState;
typedef struct {
    void (*load)();
    void (*draw)(const GameState*);
    int (*step)(const GameState*);
    void (*onKeyDown)(int,const GameState*);
    void (*onKeyUp)(int,const GameState*);
    void (*onQuit)();
}GameSystem;

void RunGame(GameSystem*,int,int,const char*);
#endif 
