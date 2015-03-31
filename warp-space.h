#ifndef WARP_SPACE_H
#define WARP_SPACE_H 1.0

// Did I get the doxygen right?
/*****************************************************************************
 * @file warp-space.h
 * @author Andrew Beach
 * @date 2015-02-06
 * @verison 1.0
 *
 * @brief Modual that controls warp space and the ships.
 *
 * This modual renders all of warp space, as well as handling the warp space
 * fluxuation events and the player ships.
 *****************************************************************************/

void load(void);
// Loads items are prepares to start the game (more peramiters needed?)

void draw (const InputStateHANDLE is);
// Draw to the screen.

int step  (const InputStateHANDLE is);
// Not sure.

void onKeyDown(int key, const InputStateHANDLE is);
void onKeyUp(int key, const InputStateHANDLE is);
// Input Handlers.

void onQuit();
// Clean up.

void warpFlux(void);
// Allows other moduals to trigger a warp space fluxuation.

#endif//WARP_SPACE_H
