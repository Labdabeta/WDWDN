#ifndef RESOURE_REGEN_H
#define RESOURE_REGEN_H 1.0

// Did I get the doxygen right?
/*****************************************************************************
 * @file resourse-regen.h
 * @author Andrew Beach
 * @date 2015-02-06
 * @verison 1.0
 *
 * @brief Modual that controls when resources regenerate in game.
 *
 * The modual controls the turns resource regeneration that occurse between
 * turns, including desplaying the results of the regeneration to the player.
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

#endif//RESOURE_REGEN_H

