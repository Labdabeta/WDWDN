#include "GUI.h"
#include <stdio.h>

const int SCREEN_WIDTH = 640; const int SCREEN_HEIGHT = 480;

int main(int argc, char *argv[])
{
    guiInit(SCREEN_WIDTH,
            SCREEN_HEIGHT,
            "Test");

    guiFill(0xFF00FF);
    guiFlip();
    guiSleep(2000);
    
    guiQuit();
    return 0;
}

//#include <SDL.h>
//#include <stdio.h>
//
//const int scrw=640,scrh=480;
//
//int main(int argc, char *argv[])
//{
//    SDL_Init(SDL_INIT_VIDEO);
//
//    SDL_Window *wnd=SDL_CreateWindow("Test",SDL_WINDOWPOS_UNDEFINED,
//                                            SDL_WINDOWPOS_UNDEFINED,
//                                            scrw,scrh,SDL_WINDOW_SHOWN);
//
//    SDL_Surface *sur=SDL_GetWindowSurface(wnd);
//
//    SDL_FillRect(sur,NULL,0xFF00FF);
//    SDL_UpdateWindowSurface(wnd);
//
//    SDL_Delay(2000);
//
//    SDL_DestroyWindow(wnd);
//    SDL_Quit();
//    return 0;
//}
