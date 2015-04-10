#include "turn-counter.h"

#include <stdbool.h>



// Internal peramiter to decide game length, divide out the number of players
// and multiply by the number of objectives to get the actual game length.
static playerTurnsPerObjective = 60;

// Internal peramiter to store turns.
static TurnData td;



// "Tick" the turn counter.
// Return 0/false if the game is over (zero turns left).
static bool nextTurn(void)
{
  ++td.currant;
  --td.remaining;

  // 0 turns marks the last turn
  if (0 < td.remaining)
    return TRUE;
  else
    return FALSE;
}



// Loads items are prepares to start the game (more peramiters needed?)
void load(void)
{
  // Prepare the turn data.
  td.gameLength = gameLengthBase * 2 / 4; // 2 objectives and 4 players.
  td.currant = 1;
  td.remaining = td.gameLength - 1;
  // Depending on how we count, the 1s in the preivous lines might be replaced
  // with 0s. (Also ajust the end of game condition in nextTurn.)
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
TurnData GetTurnData(void)
{
    return td;
}
