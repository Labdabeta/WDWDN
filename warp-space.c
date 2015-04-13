#include "warp-space.h"

#include <stdlib.h>
#include <math.h>
#include "gui.h"
#include "global.h"



// Portal Data
#define NUM_PORTALS 6
// Should we give each portal its own radius? PORTAL_MAX_RADIUS, PORTAL_MIN_R?
#define PORTAL_RADIUS 75


typedef struct PortalTAB {
  Sprite image; // Picture of the portal.
  int x; // x coordinate of the portal's center.
  int y; // y coordinate of the portal's center.
} Portal, * PortalHANDLE;

Portal portals[NUM_PORTALS];



int links[NUM_PORTALS][NUM_PORTALS] = {0}; // 0 means yes link.
// This calculation should give the same dencity while only checking "half"
// the possible links. (20% + (20% of 80%)) = 36%
#define LINK_DENSITY 36

Sprite warpFuzz = NULL;
#define FUZZ_RADIUS 20
#define FUZZ_SKIP 5

/* Should we use a double array again? It cause some problems last time with
 * some portals being linked twice. With a bit of extra math we could store
 * everything once.
 */



// Ship Data
int numShips = -1;
// It took me a while to realize we treat the ship as a circle, not a box.
#define SHIP_RADIUS 40
#define SHIP_WIDTH  SHIP_RADIUS * 2
#define SHIP_HEIGHT SHIP_RADIUS * 2

typedef struct ShipDataTAB {
  Sprite waiting; // Picture of the unselected ship.
  Sprite active; // Picture of selected ship.
  int loc; // The location in warp-space, by portal number.
  int pOffSetX; // The x offset from the portal's center.
  int pOffSetY; // The y offset from the portal's center.
  int dockX; // The x location of the ship while docked (in real space).
  int dockY; // The y location of the ship while docked (in real space).
} ShipData, * ShipDataHANDLE

ShipDataHANDLE ships = NULL;



// Loads items are prepares to start the game (more peramiters needed?)
void load(void)
{
  int i;
  // General resorces:
  // The warp fuzz used for links between portals.
  warpFuzz = loadSprite("Old/WDWDN/WarpFuzz.png");

  // Read in portal map? (Not yet)
  portals[0].x = 300; portals[0].y = 200;
  portals[0].image = loadSprite("Old/WDWDN/Warps/Warp1.png");
  portals[1].x = 600; portals[1].y = 100;
  portals[1].image = loadSprite("Old/WDWDN/Warps/Warp2.png");
  portals[2].x = 900; portals[2].y = 200;
  portals[2].image = loadSprite("Old/WDWDN/Warps/Warp3.png");
  portals[3].x = 300; portals[3].y = 500;
  portals[3].image = loadSprite("Old/WDWDN/Warps/Warp4.png");
  portals[4].x = 600; portals[4].y = 600;
  portals[4].image = loadSprite("Old/WDWDN/Warps/Warp5.png");
  portals[5].x = 900; portals[5].y = 500;
  portals[5].image = loadSprite("Old/WDWDN/Warps/Warp6.png");

  // Get the number of players to get the number of ships.
  numShips = GetNumPlayers();
  ships = malloc(sizeof(ShipData) * numShips);
  // Load in the data for each ship.
  for (i = 0 ; i < numShips ; ++i)
  {
    ships[i].loc = -1;
    ships[i].dockX = SHIP_RADIUS;
    ships[i].dockY = SHIP_RADIUS * ((i * 2) + 1);
    switch (i)
    {
    case 0:
      ships[i].waiting = loadSprite("Old/WDWDN/Player1.png");
      ships[i].active = loadSprite("Old/WDWDN/Player1Grey.png");
      break;
    case 1:
      ships[i].waiting = loadSprite("Old/WDWDN/Player2.png");
      ships[i].active = loadSprite("Old/WDWDN/Player2Grey.png");
      break;
    case 2:
      ships[i].waiting = loadSprite("Old/WDWDN/Player3.png");
      ships[i].active = loadSprite("Old/WDWDN/Player3Grey.png");
      break;
    case 3:
      ships[i].waiting = loadSprite("Old/WDWDN/Player4.png");
      ships[i].active = loadSprite("Old/WDWDN/Player4Grey.png");
      break;
    case 4:
      ships[i].waiting = loadSprite("Old/WDWDN/Player5.png");
      ships[i].active = loadSprite("Old/WDWDN/Player5Grey.png");
      break;
    }
  }

  switch (numShips)
  {
  case 1:
    // X={0.00}
    // Y={0.00}
    break;
  case 2:
    // X={-1.00,+1.00}
    // Y={ 0.00, 0.00}
    break;
  case 3:
    // X={0.00,-0.866,+0.866}
    // Y={1.00,-0.500,-0.500}
    break;
  case 4:
    // X={-0.707,-0.707,+0.707,+0.707}
    // Y={+0.707,-0.707,-0.707,+0.707}
    break;
  case 5:
    //float shipXoff[MAX_PLAYERS]={0.00,+0.588,-0.951,+0.951,-0.588};
    //float shipYoff[MAX_PLAYERS]={1.00,-0.809,+0.309,+0.309,-0.809};
    break;
  }
  /* This is weird because there is a part that is the same for each ship,
   * a part that is calculated from the ship number, another part that is
   * different for each ship, and a part that is dependant on both the ship
   * and the total number of ships.
   */
}

void drawLink (int sx, int sy, int fx, int fy);

// Draw to the screen.
void draw (const InputStateHANDLE is)
{
  // Draw Background

  // Draw Links
  int i, j;
  for (i = 0 ; i < NUM_PORTALS ; ++i)
  {
    for (j = i + 1 ; j < NUM_PORTALS ; ++j)
    {
      if (!links[i][j])
      {
         // Out sourced because it is complicated.
         drawLink(portals[i].x, portals[i].y, portals[j].x, portals[j].y);
      }
    }
  }

  // Draw Portals
  for (i = 0 ; i < NUM_PORTALS ; ++i)
  {
    blitSprite(portals[i].image,
               portals[i].x - PORTAL_RADIUS, portals[i].y - PORTAL_RADIUS,
               portals[i].x + PORTAL_RADIUS, portals[i].y + PORTAL_RADIUS);
  }

  // Draw Ships
  for (i = 0 ; i < numShips ; ++i)
  {
    // ShipDataHANDLE shipP = ships + i;
    if (-1 == ships[i].loc)
    {
      blitSprite(FALSE/*Is Selected*/ ? ships[i].active : ships[i].waiting,
                 ships[i].dockX - SHIP_RADIUS, ships[i].dockY - SHIP_RADIUS,
                 ships[i].dockX + SHIP_RADIUS, ships[i].dockY + SHIP_RADIUS);
    }
    else
    {
      blitSprite(FALSE/*Is Selected*/ ? ships[i].active : ships[i].waiting,
                 portals[ships[i].loc].x + ships[i].pOffSetx - SHIP_RADIUS,
                 portals[ships[i].loc].y + ships[i].pOffSety - SHIP_RADIUS,
                 portals[ships[i].loc].x + ships[i].pOffSetx + SHIP_RADIUS,
                 portals[ships[i].loc].y + ships[i].pOffSety + SHIP_RADIUS);
    }
  }
}

// Helper to the helper, find the distance between two points.
int distance (int x1, int y1, int x2, int y2)
{
  return sqrt( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) );
}

// Helper function to draw, draws links between portals.
void drawLink (int sx, int sy, int fx, int fy)
{
  int dx = fx > sx ? (fx-sx) : (sx-fx);
  int dy = fy > sx ? (fy-sy) : (sy-fy);
  int sgx = sx < fx ? FUZZ_SKIP : -FUZZ_SKIP;
  int sgy = sy < fy ? FUZZ_SKIP : -FUZZ_SKIP;
  int err = (dx > dy ? dx : -dy) / 2;
  int e2;

  while (TRUE)
  {
    blitSprite(warpFuzz, sx - FUZZ_RADIUS, sy - FUZZ_RADIUS,
                       sx + FUZZ_RADIUS, sy + FUZZ_RADIUS);
    if (distance(sx, sy, fx, fy) < (PORTAL_RADIUS/2)) break;

    e2 = err;
    if (e2 > -dx)
    {
      err -= dy;
      sx += sgx;
    }
    if (e2 < dy)
    {
      err += dx;
      sy += sgy;
    }
  }
}

// Not sure.
int step  (const InputStateHANDLE is)
{

}

// Input Handlers.
void onKeyDown(int key, const InputStateHANDLE is)
{

}

// Input Handlers.
void onKeyUp(int key, const InputStateHANDLE is)
{

}

// Clean up.
void onQuit()
{
  // General:
  cleanSprite(warpFuzz);

  // Free the ship storage.
  int i;
  for (i = 0 ; i < numShips ; ++i)
  {
    cleanSprite(ships[i].waiting);
    cleanSprite(ships[i].active);
  }
  free(ships);
}



// Allows other moduals to trigger a warp space fluxuation.
void warpFlux(void)
{
  int i, j;
  for (i = 0 ; i < NUM_PORTALS ; ++i)
  {
    for (j = i + 1 ; j < NUM_PORTALS ; ++j)
    {
      // "PRAISE RNGESUS!!!"
      links[i][j] = (rand()%100 > PORTAL_DENSITY);
    }
  }
}
