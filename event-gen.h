#ifndef EVENT_GEN_H
#define EVENT_GEN_H 1.0

// Did I get the doxygen right?
/*****************************************************************************
 * @file event-gen.h
 * @author Andrew Beach
 * @date 2015-02-06
 * @verison 1.0
 *
 * @brief Modual that handles the turn counter for the game.
 *
 * This modual generates events that occur between turns and as well as
 * displaying them.
 *****************************************************************************/

#include "gui.h"

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

#endif//EVENT_GEN_H

