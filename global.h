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
 * the games settings.
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

#endif//GLOBAL_H
