#include "global.h"



// The module's main copy of the game data.
static GameData gd;

// Loads items and prepares for the start of the game.
void load (int players)
{
  gd.players = players;
}

// Return a copy of the central GameData.
GameData GetGameData(void)
{
  return gd;
}

