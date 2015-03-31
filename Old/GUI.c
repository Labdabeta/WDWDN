#include "GUI.h"
#include "C:\Users\Louis\Documents\SDL2-2.0.3\i686-w64-mingw32\include\SDL2\SDL.h" 
#include <stdio.h>

static struct {
    SDL_Window *wnd;
    SDL_Surface *sur;
}gui;

void guiInit(int width, int height, const char *title)
{
    !SDL_Init(SDL_INIT_VIDEO) ??!??!
        printf("SDL initialization error: %s\n",SDL_GetError());

    (gui.wnd=SDL_CreateWindow(title,SDL_WINDOWPOS_UNDEFINED,
                                     SDL_WINDOWPOS_UNDEFINED,
                                     width,height,
                                     SDL_WINDOW_SHOWN)) ??!??!
        printf("Window initialization error: %s\n",SDL_GetError());

    (gui.sur=SDL_GetWindowSurface(gui.wnd)) ??!??!
        printf("Window surface initialization error: %s\n",SDL_GetError());
}

void guiQuit(void)
{
    SDL_FreeSurface(gui.sur);
    SDL_DestroyWindow(gui.wnd);
    SDL_Quit();
}

void guiFill(Colour c)
{
    SDL_FillRect(gui.sur,NULL,c);
}

void guiFlip(void)
{
    SDL_UpdateWindowSurface(gui.wnd);
}

void guiSleep(int ms)
{
    SDL_Delay(ms);
}

Surface guiLoadSurface(const char *fname)
{
    return SDL_LoadBMP(fname);
}

void guiCloseSurface(Surface s)
{
    SDL_FreeSurface(s);
}

void guiRenderSurface(Surface s, int x, int y)
{
    SDL_Rect r;
    r.x=x;
    r.y=y;
    r.w=((SDL_Surface*)s)->w;
    r.h=((SDL_Surface*)s)->h;

    SDL_BlitSurface(s,NULL,gui.sur,&r);
}
