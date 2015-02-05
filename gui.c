/*******************************************************************************
 * @file gui.c
 * @author Louis Burke
 * @date 2014-02-05
 * @version 1.0
 *
 * @brief Implementation of the symbols in gui.h.
 *
 * This file implements a number of functions found in the gui.h file. It 
 * requires linkage with SDL2 and SDL2 image to compile. Thus compilation should
 * look something like this:
 *
 * <tt><C compiler> gui.c -I <SDL2\include location> 
 *                        -I <SDL2_image\include location> -c
 * </tt>
*******************************************************************************/

#include "gui.h"
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

static SDL_Window *wnd;
static SDL_Surface *sur;

void RunGame(EventCallbacks *callbacks, int width, 
                                        int height,
                                        int fps,
                                        const char *title)
{
    if (SDL_Init(SDL_INIT_VIDEO))
        printf("SDL initialization error: %s\n",SDL_GetError());
    if (!(wnd=SDL_CreateWindow(title,
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               width,height,SDL_WINDOW_SHOWN)))
        printf("Window initialization error: %s\n",SDL_GetError());
    if (!(sur=SDL_GetWindowSurface(wnd)))
        printf("Surface initialization error: %s\n",SDL_GetError());

    callbacks->load();

    SDL_Event e;
    int play=1;
    InputState is;
    int i;
    for (i=0; i<256; ++i) is.keys[i]=0;
    is.ml=is.mr=0;
    SDL_GetMouseState(&is.mx,&is.my);

    unsigned int lastTick=SDL_GetTicks();
    while (play&&callbacks->step(&is))
    {
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
                case SDL_QUIT:
                    play=0;
                    break;
                case SDL_KEYDOWN:
                    is.keys[e.key.keysym.sym]=1;
                    callbacks->onKeyDown(e.key.keysym.sym,&is);
                    break;
                case SDL_KEYUP:
                    is.keys[e.key.keysym.sym]=0;
                    callbacks->onKeyUp(e.key.keysym.sym,&is);
                    break;
                case SDL_MOUSEMOTION:
                    SDL_GetMouseState(&is.mx,&is.my);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (e.button.button==SDL_BUTTON_LEFT)
                    {
                        is.ml=1;
                        callbacks->onKeyDown(1,&is);
                    }
                    else
                    {
                        is.mr=1;
                        callbacks->onKeyDown(2,&is);
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (e.button.button==SDL_BUTTON_LEFT)
                    {
                        is.ml=0;
                        callbacks->onKeyUp(1,&is);
                    }
                    else
                    {
                        is.mr=0;
                        callbacks->onKeyUp(2,&is);
                    }
                    break;
            }
        }
        SDL_FillRect(sur,0,0xFFFFFF);
        callbacks->draw(&is);
        SDL_UpdateWindowSurface(wnd);
        
        unsigned int currTick=SDL_GetTick();
        if (currTick-lastTick<1000*fps)
            SDL_Delay((1000*fps)-(currTick-lastTick));
        lastTick=currTick;
    }

    callbacks->onQuit();

    SDL_DestroyWindow(wnd);
    SDL_Quit();
}

Sprite loadSprite(const char *fileName)
{
    SDL_Surface *tmp=IMG_Load(fileName);
    if (!tmp) printf("Unable to load %s: %s\n",fileName,SDL_GetError());

    return tmp;
}

void cleanSprite(Sprite spr)
{
    SDL_FreeSurface(spr);
}

void drawSprite(Sprite spr, int x, int y)
{
    SDL_Rect tmp;
    tmp.x=x; tmp.y=y;

    SDL_BlitSurface(spr,NULL,sur,&tmp);
}
