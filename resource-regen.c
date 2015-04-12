#include "resourse-regen.h"

// Reimplementing the old resourse regeneration system.
// (This is one that I do feel could use an upgrade.)
#define NUM_RESOURCES 5
Sprite resourceImages[NUM_RESOURCES];
int resourceWeights[NUM_RESOURCES] = {20, 10, 20, 30, 20};

#define ENUM_BIO 0 // BIO: Organic Material
#define ENUM_DE  1 // DE: Dark Energy
#define ENUM_EXM 2 // ExM: Exotic Matter
#define ENUM_ORE 3 // Ore: aka Coal aka Coar
#define ENUM_TEC 4 // Tech: Refined Goods



// Loads items are prepares to start the game (more peramiters needed?)
void load(void)
{
  // Load all sprites
  resourceImages[ENUM_ORE] = loadSprite("Old/WDWDN/Ore.png");
  resourceImages[ENUM_BIO] = loadSprite("Old/WDWDN/Bio.png");
  resourceImages[ENUM_TEC] = loadSprite("Old/WDWDN/Tech.png");
  resourceImages[ENUM_EXM] = loadSprite("Old/WDWDN/ExM.png");
  resourceImages[ENUM_DE]  = loadSprite("Old/WDWDN/DE.png");
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
  // Free Resource Images.
  for (int i = 0 ; i < NUM_RESOURCES ; ++i)
  {
    cleanSprite(resourceImages[i]);
  }
}
