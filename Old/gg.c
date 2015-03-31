#include "gg.h"
#include <stdio.h>
#include "C:\Users\Louis\Documents\SDL2-2.0.3\i686-w64-mingw32\include\SDL2\SDL.h"
#include "C:\Users\Louis\Documents\SDL2_image-2.0.0\i686-w64-mingw32\include\SDL2\SDL_image.h"

SDL_Window *wnd;
SDL_Renderer *ren;
SDL_Surface *sur;
void RunGame(GameSystem *gs, int w, int h, const char *title)
{
    !SDL_Init(SDL_INIT_VIDEO)||
        printf("SDL initialization error: %s\n",SDL_GetError());

    (wnd=SDL_CreateWindow(title,
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         w,h,SDL_WINDOW_SHOWN)) ||
        printf("Window initialization error: %s\n",SDL_GetError());

    (sur=SDL_GetWindowSurface(wnd)) ||
        printf("Surface initialization error: %s\n",SDL_GetError());

    (ren=SDL_CreateRenderer(wnd,-1,SDL_RENDERER_SOFTWARE)) ||
        printf("Renderer creation error: %s\n",SDL_GetError());


    SDL_SetRenderDrawColor(ren,0xFF,0xFF,0xFF,0xFF);

    gs->load();

    SDL_Event e;
    int play=1;
    GameState s;
    int i;
    for (i=0; i<256; ++i)
        s.keys[i]=0;
    s.ml=s.mr=0;
    SDL_GetMouseState(&s.mx,&s.my);

    while (gs->step(&s))
    {
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
                case SDL_QUIT:
                    play=0;
                    break;
                case SDL_KEYDOWN:
                    s.keys[e.key.keysym.sym]=1;
                    gs->onKeyDown(e.key.keysym.sym,&s);
                    break;
                case SDL_KEYUP:
                    s.keys[e.key.keysym.sym]=0;
                    gs->onKeyUp(e.key.keysym.sym,&s);
                    break;
                case SDL_MOUSEMOTION:
                    SDL_GetMouseState(&s.mx,&s.my);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (e.button.button==SDL_BUTTON_LEFT)
                    {
                        s.ml=1;
                        gs->onKeyDown(1,&s);
                    }
                    else
                    {
                        s.mr=1;
                        gs->onKeyDown(2,&s);
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (e.button.button==SDL_BUTTON_LEFT)
                    {
                        s.ml=0;
                        gs->onKeyUp(1,&s);
                    }
                    else
                    {
                        s.mr=0;
                        gs->onKeyUp(2,&s);
                    }
                    break;
            }
        }
        SDL_FillRect(sur,NULL,0xFFFFFF);
        gs->draw(&s);
        SDL_UpdateWindowSurface(wnd);
    }

    gs->onQuit();
    
    SDL_DestroyWindow(wnd);
    SDL_Quit();
}

void delay(int ms)
{
    SDL_Delay(ms);
}
Sprite loadSprite(const char *fname)
{
    SDL_Surface *tmp=IMG_Load(fname);
    tmp||printf("Unable to load %s: %s\n",fname,SDL_GetError());

    return tmp;
}
void cleanSprite(Sprite spr)
{
    SDL_FreeSurface(spr);
}
void blitSprite(Sprite spr, int sx, int sy, int ex, int ey)
{
    SDL_Rect tmp;
    tmp.x=sx; tmp.y=sy;
    tmp.w=ex-sx; tmp.h=ey-sy;

    SDL_BlitSurface(spr,NULL,sur,&tmp);
}
