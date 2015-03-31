#ifndef TURN_COUNTER_H
#define TURN_COUNTER_H 1.0

// Did I get the doxygen right?
/*****************************************************************************
 * @file turn-counter.h
 * @author Andrew Beach
 * @date 2015-02-05
 * @verison 1.0
 *
 * @brief modual that handles the turn counter for the game.
 *
 * This modual has all the functions to draw the in game turn counter as well
 * as providing turn tracking to other files.
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

// Provided to other moduals:
typedef struct TurnDataTAG
{
    // The currant turn of the game.
    int currant;
    // How many more turns left before the end of the game.
    int remaining;
    // The original number of turns in the game.
    // Not this is not effected by any purchuses of extra time in game.
    int gameLength;
} TurnData, * TurnDataHANDLE;

TurnData GetTurnData(void);
// Getter for the information on turns the modal tracks.

#endif//TURN_COUNTER_H
