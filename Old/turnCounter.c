#include "turnCounter.h"
#include "gg.h"

// Internal varibles:

// Turn Counter varibles
static int maxTurn = 0;
static int curTurn = 0;

static int players = 0;
static int objectives = 0;
static int difficulty = 0;

static int payments = 0;

/*
About game length:
Data:
- The original game took 26 rounds with 4 players for 2 objectives, 120 turns.
  However the first objective took 18 turns and the second another 8.

Using a turns/players=rounds formula will give a good base.
The game length might scale directly with the number of objectives, so I'm trying that.
*/
static int turnsForObjectivePerPlayer = 60;

// Draw Varibles (for drawing functions):
/// NOTE: The screen is 1200x700. The left 80 pixels store the ships, the right 80 are blank
/// See gg.h for drawing functions.

int screenHeight = 700;
int screenWidth = 1200;

int barOffset = 5;
Sprite barSprite;
int barHeight = 6;
int barWidth = 80;

Sprite coinSprite;
int coinWidth = 20; // Check
int coinHeight = 20; // Check
Sprite arrowSprite;
int arrowWidth = 20; // Check
int arrowHeight = 20; // Check

int buttonWidth = 80;
int buttonHeight = 100;
int buttonXPos = 0;
int buttonYPos = 600;

// Functions: ================================================================================

// Start the game for a number of players and a given difficulty level.
int StartGame (int players_, int objectives_, int difficulty_)
{
    // Load input.
    players = players_;
    objectives = objectives_;
    difficulty = difficulty_;

    // Calculate starting stats.
    maxTurn = (turnsForObjectivePerPlayer * objectives) / players;
    curTurn = 0;
    payments = 0;

    barSprite=loadSprite("WDWDN\\RoundBar.png");
    coinSprite=loadSprite("WDWDN\\Coin.png");
    arrowSprite=loadSprite("WDWDN\\Arrow.png");
}

// Advance the turn counter by one.
void NextRound(void)
{
    ++curTurn;
}

// The number of remaining turns.
int GetRoundsLeft (void)
{
    return maxTurn - curTurn;
}

// Get the number of rounds a purcuse will buy.
static int GetExtention(void)
{
    return 5;
}

// When extra time is bought, add some extra rounds.
static void BuyTime (void)
{
    // Changes the number of total rounds and
    maxTurn += GetExtention();
    ++payments;
}

// Get the price to buy more time.
static int GetPrice (void)
{
    return 3;
}

// Draw the "price" counter.
void DrawPrice(void)
{
    // Price included in button, please remove.
}

// Draw the "round" counter.
void DrawCounter()
{
    // How many bars to draw.
    int roundsleft = GetRoundsLeft();

    // The anchor points for drawning.
    int baseX = screenWidth - barWidth;
    int baseY = screenHeight - barHeight;

    //Draw all the bars to show the remaining turns.
    int n;
    for (n = 0 ; n < GetRoundsLeft() ; ++n)
        blitSprite(barSprite, baseX, baseY - (n * barOffset), screenWidth, screenHeight);
}

// Draw the button to buy time.
void DrawButton()
{
    // Draw the arrow.
    blitSprite(arrowSprite, (buttonXPos + buttonWidth / 2 - arrowWidth / 2),
                            (buttonYPos + buttonHeight/ 2 - arrowHeight/ 2), 0, 0);


    // Draw the bars for the payout.
    int toDraw = GetExtention();
    int baseX = buttonXPos /*+ buttonWidth / 2 - barWidth / 2*/;
    int baseY = buttonYPos + buttonHeight/ 2 + coinHeight + barHeight;
    int n;
    for (n = 0 ; n < toDraw ; ++n)
        blitSprite(barSprite, baseX, baseY + (barOffset * n), 0, 0);
    
    // Draw the coins for the price.
    toDraw = GetPrice();
    baseX = buttonXPos + buttonWidth / 2 - coinWidth * toDraw / 2;
    baseY = buttonYPos + buttonHeight/ 2 - coinHeight - arrowHeight;
    n;
    for (n = 0 ; n < toDraw ; ++n)
        blitSprite(coinSprite, baseX + (coinWidth * n), baseY, 0, 0);
}

// Handle input (if button is pressed, buy time)
void handleClick(int mouse_x, int mouse_y)
{
    //todo: if mouse is within button, call BuyTime
    if (buttonXPos <= mouse_x && mouse_x <= buttonXPos + buttonWidth &&
        buttonYPos <= mouse_y && mouse_y <= buttonYPos + buttonHeight)
        BuyTime();
}

// Ends game (cleans sprites?)
void EndGame(void)
{
    //todo: cleanSprites
}
