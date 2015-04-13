#ifndef GLOBAL_H
#define GLOBAL_H 1.0

// Check the doxygen some time.
/*****************************************************************************
 * @file global.h
 * @author Andrew Beach
 * @date 2015-02-14
 * @verison 1.0
 *
 * @brief provides storage for global game data
 *
 * This module is centered around the GameData structure which holds all of the
 * settings for a game. This is not complete data about the game, this is more
 * the games settings. That is those values which are decided at the start of
 * the game and are generally constaint until the game finishes.
 *****************************************************************************/

typedef struct GameDataTAB
{
  int players;
} GameData, * GameDataHANDLE;
/* Fields:
 * players: The number of players in the game.
 */

void load (int players);
// Loads items and prepares for the start of the game.

GameData GetGameData(void);
// Return a copy of the central GameData.

int GetNumPlayers(void);
// Return just the number of players in this game.

#endif//GLOBAL_H
