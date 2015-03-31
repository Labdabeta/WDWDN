#include "planets.h"

#define NUM_PLANETS

static Sprite planetSs[NUM_PLANETS];
static int planetRs[NUM_PLANETS]={0};

void loadPlanets(void)
{
    planetSs[0]=loadSprite("WDWDN\\....png");
    //more...
}

int getPlanetSprite(int index)
{
    return planetSs[index];
}

int getPlanetResources(int index)
{
    return planetRs[index];
}

int numPlanets(void)
{
    return NUM_PLANETS;
}
