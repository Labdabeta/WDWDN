#include "gg.h"
#include "turnCounter.h"
#include "events.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define WIN_WIDTH 1200
#define WIN_HEIGHT 700
#define SHIP_WIDTH 40
#define MAX_PLAYERS 5
#define NUM_PORTALS 6
#define PORTAL_DENSITY 20
#define FUZZ_WIDTH 20
#define FUZZ_SKIP 5
#define PORTAL_RADIUS 75

int portalXs[NUM_PORTALS+1]={300,600,900,300,600,900,0};
int portalYs[NUM_PORTALS+1]={200,100,200,500,600,500,0};
Sprite portalSs[NUM_PORTALS];
int portalLs[NUM_PORTALS][NUM_PORTALS]={0};//0 means YES link
int selectedPlayer=-1;
int darkPortal=1;
int shipLocs[MAX_PLAYERS]={-1,-1,-1,-1,-1};
int ishipXs[MAX_PLAYERS]={SHIP_WIDTH,SHIP_WIDTH,SHIP_WIDTH,SHIP_WIDTH,SHIP_WIDTH};
int shipXs[MAX_PLAYERS]={SHIP_WIDTH,SHIP_WIDTH,SHIP_WIDTH,SHIP_WIDTH,SHIP_WIDTH};
int ishipYs[MAX_PLAYERS]={SHIP_WIDTH,SHIP_WIDTH*3,SHIP_WIDTH*5,SHIP_WIDTH*7,SHIP_WIDTH*9};
int shipYs[MAX_PLAYERS]={SHIP_WIDTH,SHIP_WIDTH*3,SHIP_WIDTH*5,SHIP_WIDTH*7,SHIP_WIDTH*9};
float shipXoff[MAX_PLAYERS]={0.00,+0.588,-0.951,+0.951,-0.588};
float shipYoff[MAX_PLAYERS]={1.00,-0.809,+0.309,+0.309,-0.809};
Sprite shipsprites[MAX_PLAYERS];
Sprite selshipsprites[MAX_PLAYERS];
Sprite warpfuzz;
Sprite background;
int turnNum;
int eventMode;

void iteratePortals()
{
    int i,ii;
    for (i=0; i<NUM_PORTALS; ++i)
    {
        for (ii=0; ii<NUM_PORTALS; ++ii)
        {// PRAISE RNGESUS!!!
            portalLs[i][ii]=(rand()%100>PORTAL_DENSITY);
        }
    }
//    for (i=0; i<NUM_PORTALS; ++i)
//    {
//        for (ii=0; ii<NUM_PORTALS; ++ii)
//        {
//            portalLs[i][ii]=portalLs[ii][i];
//        }
//    }
}
void load(void)
{
    shipsprites[0]=loadSprite("WDWDN\\Player1.png");
    shipsprites[1]=loadSprite("WDWDN\\Player2.png");
    shipsprites[2]=loadSprite("WDWDN\\Player3.png");
    shipsprites[3]=loadSprite("WDWDN\\Player4.png");
    shipsprites[4]=loadSprite("WDWDN\\Player5.png");

    selshipsprites[0]=loadSprite("WDWDN\\Player1Grey.png");
    selshipsprites[1]=loadSprite("WDWDN\\Player2Grey.png");
    selshipsprites[2]=loadSprite("WDWDN\\Player3Grey.png");
    selshipsprites[3]=loadSprite("WDWDN\\Player4Grey.png");
    selshipsprites[4]=loadSprite("WDWDN\\Player5Grey.png");

    portalSs[0]=loadSprite("WDWDN\\Warps\\Warp1.png");
    portalSs[1]=loadSprite("WDWDN\\Warps\\Warp2.png");
    portalSs[2]=loadSprite("WDWDN\\Warps\\Warp3.png");
    portalSs[3]=loadSprite("WDWDN\\Warps\\Warp4.png");
    portalSs[4]=loadSprite("WDWDN\\Warps\\Warp5.png");
    portalSs[5]=loadSprite("WDWDN\\Warps\\Warp6.png");

    warpfuzz=loadSprite("WDWDN\\WarpFuzz.png");
    background=loadSprite("WDWDN\\Background.png");

    StartGame(MAX_PLAYERS-4,2,1); //TODO: update
    turnNum=0;
    loadEvents();
    iteratePortals();
    eventMode=0;

}
int distance(int ix, int iy, int fx, int fy)
{
    return sqrt((ix-fx)*(ix-fx)+(iy-fy)*(iy-fy));
}
//GUI///////////////////////////////////////////////////////////////////////////
void drawLine(int,int,int,int);
void draw(const GameState *gs)
{
    blitSprite(background,0,0,WIN_WIDTH,WIN_HEIGHT);
    int i,ii;
    for (i=0; i<NUM_PORTALS; ++i)
    {
        for (ii=0; ii<NUM_PORTALS; ++ii)
        {
            if (!portalLs[i][ii]||!portalLs[ii][i])
            {
                drawLine(portalXs[i],portalYs[i], 
                         portalXs[ii],portalYs[ii]);
            }
        }
    }
    for (i=0; portalXs[i]; ++i)
    {
        blitSprite(portalSs[i],portalXs[i]-PORTAL_RADIUS,
                          portalYs[i]-PORTAL_RADIUS,
                          portalXs[i]+PORTAL_RADIUS,
                          portalYs[i]+PORTAL_RADIUS);
    }
    for (i=0; i<MAX_PLAYERS; ++i)
    {
        blitSprite(selectedPlayer==i?selshipsprites[i]:shipsprites[i],
                                shipXs[i]-SHIP_WIDTH,shipYs[i]-SHIP_WIDTH,
                                shipXs[i]+SHIP_WIDTH,shipYs[i]+SHIP_WIDTH);
    }
    DrawButton();
    DrawPrice();
    DrawCounter();
    if (eventMode)drawEvents();
}

int step(const GameState *gs)
{
    return !gs->keys['q'];
}

void onKeyDown(int key, const GameState *gs)
{
    if (key==1)//LMB
    {
        if (selectedPlayer<0)
        {
            int i;
            for (i=0; i<MAX_PLAYERS; ++i)
            {
                if (distance(gs->mx,gs->my,shipXs[i],shipYs[i])<SHIP_WIDTH)
                    selectedPlayer=i;
            }
        }
        else
        {
            int i;
            for (i=0; portalXs[i]; ++i)
            {
                if (distance(gs->mx,gs->my,portalXs[i],portalYs[i])<PORTAL_RADIUS)
                {
                    if (shipLocs[selectedPlayer]==i)
                    {
                        shipXs[selectedPlayer]=ishipXs[selectedPlayer];
                        shipYs[selectedPlayer]=ishipYs[selectedPlayer];
                        shipLocs[selectedPlayer]=-1;
                    }
                    else
                    {
                        shipXs[selectedPlayer]=portalXs[i]+(int)(shipXoff[selectedPlayer]*(float)PORTAL_RADIUS);
                        shipYs[selectedPlayer]=portalYs[i]+(int)(shipYoff[selectedPlayer]*(float)PORTAL_RADIUS);
                        shipLocs[selectedPlayer]=i;
                    }
                    selectedPlayer=-1;
                }
            }

            if (selectedPlayer>=0&&gs->mx<2*SHIP_WIDTH)
            {
                shipXs[selectedPlayer]=ishipXs[selectedPlayer];
                shipYs[selectedPlayer]=ishipYs[selectedPlayer];
                shipLocs[selectedPlayer]=-1;
                selectedPlayer=-1;
            }
        }
        handleClick(gs->mx,gs->my);
    }
    if (key==2)//RMB
        selectedPlayer=-1;
    if (key==' ')
    {
        if (eventMode) eventMode=0;
        else
        {
            if (loadNextEvent(2,turnNum++,GetRoundsLeft()))
                iteratePortals();
            NextRound();
            eventMode=1;
        }
    }
}

void onKeyUp(int key, const GameState *gs)
{

}

void onQuit(void)
{
    int i;
    for (i=0; i<MAX_PLAYERS; ++i)
    {
        cleanSprite(shipsprites[i]);
        cleanSprite(selshipsprites[i]);
    }
    for (i=0; i<NUM_PORTALS; ++i)
        cleanSprite(portalSs[i]);
    cleanSprite(warpfuzz);
    EndGame();
    cleanEvents();
}

void drawLine(int sx, int sy, int fx, int fy)
{
    int dx=(fx-sx)>0?(fx-sx):(sx-fx);
    int dy=(fy-sy)>0?(fy-sy):(sy-fy);
    int sgx=sx<fx?FUZZ_SKIP:-FUZZ_SKIP;
    int sgy=sy<fy?FUZZ_SKIP:-FUZZ_SKIP;
    int err=(dx>dy?dx:-dy)/2;
    int e2;

    for (;;) {
        blitSprite(warpfuzz,sx-FUZZ_WIDTH,sy-FUZZ_WIDTH,
                            sx+FUZZ_WIDTH,sy+FUZZ_WIDTH);
        if (distance(sx,sy,fx,fy)<(PORTAL_RADIUS/2)) break;

        e2=err;
        if (e2 > -dx)
        {
            err-=dy;
            sx+=sgx;
        }
        if (e2 < dy)
        {
            err+=dx;
            sy+=sgy;
        }
    }
}

int main(int argc, char *argv[])
{
    int i;
    for (i=0; i<NUM_PORTALS; ++i)
    {
        portalSs[i]=loadSprite("portal.bmp");
    }
    srand(time(NULL));
    GameSystem gs;
    gs.load=load;
    gs.draw=draw;
    gs.step=step;
    gs.onKeyDown=onKeyDown;
    gs.onKeyUp=onKeyUp;
    gs.onQuit=onQuit;

    RunGame(&gs,WIN_WIDTH,WIN_HEIGHT,"Warp do we do now?!");

    return 0;
}
