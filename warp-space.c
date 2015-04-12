#include "warp-space.h"

#include "gui.h"



// Portal Data
#define NUM_PORTALS 6;

typedef struct PortalTAB {
  Sprite image; // Picture of the portal.
  int x; // x coordinate of the portal's center.
  int y; // y coordinate of the portal's center.
} Portal, * PortalHANDLE;

Portal portals[NUM_PORTALS];



// int links[NUM_PORTALS][NUM_PORTALS] = ...
/* Should we use a double array again? It cause some problems last time with
 * some portals being linked twice. With a bit of extra math we could store
 * everything once.
 */



// Ship Data
int numShips = -1;

typedef struct ShipTAB {
  Sprite image; // Picture of the ship;
  int loc; // The location in warp-space, by portal number.
} Ship, * ShipHANDLE

ShipHANDLE ships = NULL;



// Loads items are prepares to start the game (more peramiters needed?)
void load(void)
{
  // Read in portal map?
  // Get the number of players to get the number of ships.
}

// Draw to the screen.
void draw (const InputStateHANDLE is)
{

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

}



// Allows other moduals to trigger a warp space fluxuation.
void warpFlux(void)
{

}
