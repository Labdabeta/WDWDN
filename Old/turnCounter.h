#ifndef TURN_COUNTER_H
#define TURN_COUNTER_H 0.3

// Internals of the turn counter.

// Start the game for a number of players and a given difficulty level.
int StartGame (int players_, int objectives_, int difficulty_);
// Peramiters: players_ is the number of players in this game.
//             objectives_ is the number of objectives  the players would like to complete.
//             difficulty_ reperesents the difficulty setting of the game.

int GetRoundsLeft(void);

// Advance the turn counter by one.
void NextRound (void);

//Draw the "price" counter.
void DrawPrice(void);

//Draw the "round" counter.
void DrawCounter(void);

// Draw the button to buy time.
void DrawButton(void);

// Handle input (if button is pressed, buy time)
void handleClick(int mouse_x, int mouse_y);

// Ends game (cleans sprites?)
void EndGame(void);

#endif//TURN_COUNTER_H
