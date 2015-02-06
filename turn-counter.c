#include "turn-counter.h"



// Internal peramiter to decide game length (2 objectives).
static gameLengthBase = 120;

// Internal peramiter to store turns.
static TurnData td;



// Loads items are prepares to start the game (more peramiters needed?)
void load(void)
{
    // Prepare the turn data.
    td.gameLength = gameLengthBase / 4; // 4 = temp-num-of-players
    td.currant = 1; // or 0?
    td.remaining = td.gameLength;
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



// Getter for the information on turns the modal tracks.
TurnData/*HANDLE?*/ GetTurnData(void)
{
    return td;
}

/* const TurnDataHANDLE GetTurnData(void);
 * {
 *    return *td;
 * }
 *
 * Alternate method to do the turn data. Instead of a data structure, with a
 * copy of the currant data a read only pointer is given.
 * (Not completely safe but should be good enough for our purposes.)
 */
