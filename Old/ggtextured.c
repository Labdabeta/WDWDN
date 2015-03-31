#include "gg.h"
#include <stdio.h>
#include "C:\Users\Louis\Documents\SDL2-2.0.3\i686-w64-mingw32\include\SDL2\SDL.h"

static SDL_Window *wnd;
static SDL_Renderer *ren;
void RunGame(GameSystem *gs, int w, int h, const char *title)
{
    !SDL_Init(SDL_INIT_VIDEO)||
        printf("SDL initialization error: %s\n",SDL_GetError());

    (wnd=SDL_CreateWindow(title,
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         w,h,SDL_WINDOW_SHOWN)) ||
        printf("Window initialization error: %s\n",SDL_GetError());

    (ren=SDL_CreateRenderer(wnd,-1,SDL_RENDERER_SOFTWARE)) ||
        printf("Renderer creation error: %s\n",SDL_GetError());

    SDL_SetRenderDrawColor(ren,0xFF,0xFF,0xFF,0xFF);

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
        SDL_RenderClear(ren);
        gs->draw(&s);
        SDL_RenderPresent(ren);
    }

    gs->onQuit();
    
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(wnd);
    SDL_Quit();
}

void delay(int ms)
{
    SDL_Delay(ms);
}
Sprite loadBKG(const char *fname)
{
    SDL_Surface *tmp=SDL_LoadBMP(fname);
    tmp||printf("Unable to load %s: %s\n",fname,SDL_GetError());

    SDL_Texture *ret=SDL_CreateTextureFromSurface(ren,tmp);
    ret||printf("Unable to create texture: %s\n",SDL_GetError());

    SDL_FreeSurface(tmp);
    return ret;
}
Sprite loadSprite(const char *fname, Colour key)
{
    SDL_Surface *tmp=SDL_LoadBMP(fname);
    tmp||printf("Unable to load %s: %s\n",fname,SDL_GetError());

    SDL_SetColorKey(tmp,SDL_TRUE,key);

    SDL_Texture *ret=SDL_CreateTextureFromSurface(ren,tmp);
    ret||printf("Unable to create texture: %s\n",SDL_GetError());

    SDL_FreeSurface(tmp);
    return ret;
}
void cleanSprite(Sprite spr)
{
    SDL_DestroyTexture(spr);
}
void blitSprite(Sprite spr, int sx, int sy, int ex, int ey)
{
    SDL_Rect tmp;
    tmp.x=sx; tmp.y=sy;
    tmp.w=ex-sx; tmp.h=ey-sy;

    SDL_RenderCopy(ren,spr,NULL,&tmp);
}
void blitSpriteEx(Sprite spr, int sx, int sy, int ex, int ey, double rot, 
                              int cx, int cy, int hf, int vf)
{
    SDL_Rect tmp;
    tmp.x=sx; tmp.y=sy;
    tmp.w=ex-sx; tmp.h=ey-sy;

    SDL_Point pnt;
    pnt.x=cx;pnt.y=cy;

    SDL_RenderCopyEx(ren,spr,NULL,&tmp,rot,&pnt,(hf?SDL_FLIP_HORIZONTAL:0)|
                                                (vf?SDL_FLIP_VERTICAL:0));
}
void drawLine(Colour c, int sx, int sy, int ex, int ey)
{
    SDL_SetRenderDrawColor(ren,(c>>16)&0xFF,(c>>8)&0xFF,c&0xFF,0xFF);
    SDL_RenderDrawLine(ren,sx,sy,ex,ey);
    SDL_SetRenderDrawColor(ren,0xFF,0xFF,0xFF,0xFF);
}
void drawDot(Colour c, int x, int y)
{
    SDL_SetRenderDrawColor(ren,(c>>16)&0xFF,(c>>8)&0xFF,c&0xFF,0xFF);
    SDL_RenderDrawPoint(ren,x,y);
    SDL_SetRenderDrawColor(ren,0xFF,0xFF,0xFF,0xFF);
}

void drawRect(Colour c, int sx, int sy, int ex, int ey)
{
    SDL_Rect tmp;
    tmp.x=sx;tmp.y=sy;
    tmp.w=ex-sx;tmp.h=ey-sy;

    SDL_SetRenderDrawColor(ren,(c>>16)&0xFF,(c>>8)&0xFF,c&0xFF,0xFF);
    SDL_RenderFillRect(ren,&tmp);
    SDL_SetRenderDrawColor(ren,0xFF,0xFF,0xFF,0xFF);
}

