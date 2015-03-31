#include "events.h"
#include "gg.h"
#include <math.h>
#include <stdlib.h>

#define OFF_X 405 //600-width/2
#define OFF_Y 220 //350-width/2

#define NUM_RESOURCES 5
#define ROFF_X 568 //600-width/2
#define ROFF_Y 490

#define NUM_RNEGS 5
#define NUM_NEGS 11
#define NUM_NEUTRALS 4
#define NUM_POSITIVES 9
static Sprite RNegs[NUM_RNEGS];
static Sprite Negs[NUM_NEGS];
static Sprite Neutrals[NUM_NEUTRALS];
static Sprite Positives[NUM_POSITIVES];
static Sprite WSC;
static Sprite s;
Sprite resources[NUM_RESOURCES];
int resWeights[NUM_RESOURCES]={20,10,20,30,20};
int selRes;
void loadEvents(void)
{
    RNegs[0]=loadSprite("WDWDN\\Events\\RNeg1.png");
    RNegs[1]=loadSprite("WDWDN\\Events\\RNeg2.png");
    RNegs[2]=loadSprite("WDWDN\\Events\\RNeg3.png");
    RNegs[3]=loadSprite("WDWDN\\Events\\RNeg4.png");
    RNegs[4]=loadSprite("WDWDN\\Events\\RNeg5.png");

    Negs[0]=loadSprite("WDWDN\\Events\\Neg1.png");
    Negs[1]=loadSprite("WDWDN\\Events\\Neg01.png");
    Negs[2]=loadSprite("WDWDN\\Events\\Neg02.png");
    Negs[3]=loadSprite("WDWDN\\Events\\Neg03.png");
    Negs[4]=loadSprite("WDWDN\\Events\\Neg04.png");
    Negs[5]=loadSprite("WDWDN\\Events\\Neg05.png");
    Negs[6]=loadSprite("WDWDN\\Events\\Neg06.png");
    Negs[7]=loadSprite("WDWDN\\Events\\Neg07.png");
    Negs[8]=loadSprite("WDWDN\\Events\\Neg08.png");
    Negs[9]=loadSprite("WDWDN\\Events\\Neg09.png");
    Negs[10]=loadSprite("WDWDN\\Events\\Neg10.png");

    Neutrals[0]=loadSprite("WDWDN\\Events\\Neu1.png");
    Neutrals[1]=loadSprite("WDWDN\\Events\\Neu2.png");
    Neutrals[2]=loadSprite("WDWDN\\Events\\Neu3.png");
    Neutrals[3]=loadSprite("WDWDN\\Events\\Neu4.png");

    Positives[0]=loadSprite("WDWDN\\Events\\Pos1.png");
    Positives[1]=loadSprite("WDWDN\\Events\\Pos2.png");
    Positives[2]=loadSprite("WDWDN\\Events\\Pos3.png");
    Positives[3]=loadSprite("WDWDN\\Events\\Pos4.png");
    Positives[4]=loadSprite("WDWDN\\Events\\Pos5.png");
    Positives[5]=loadSprite("WDWDN\\Events\\Pos6.png");
    Positives[6]=loadSprite("WDWDN\\Events\\Pos7.png");
    Positives[7]=loadSprite("WDWDN\\Events\\Pos8.png");
    Positives[8]=loadSprite("WDWDN\\Events\\Pos9.png");

    WSC=loadSprite("WDWDN\\Events\\WSC.png");
    
    selRes=0;

    resources[0]=loadSprite("WDWDN\\Bio.png");
    resources[1]=loadSprite("WDWDN\\DE.png");
    resources[2]=loadSprite("WDWDN\\ExM.png");
    resources[3]=loadSprite("WDWDN\\Ore.png");
    resources[4]=loadSprite("WDWDN\\Tech.png");
}
static int displayRNeg(void)
{
    s=RNegs[rand()%NUM_RNEGS];
    return 0;
}
static int displayNeg(void)
{
    s=Negs[rand()%NUM_NEGS];
    return 0;
}
static int displayNeutral(void)
{
    s=Neutrals[rand()%NUM_NEUTRALS];
    return 0;
}
static int displayPositive(void)
{
    s=Positives[rand()%NUM_POSITIVES];
    return 0;
}
static int displayWarpChange(void)
{
    s=WSC;
    return 1;
}
int loadNextEvent(int difficulty, int turn, int max_turns)
{
    int ret;
    if (rand()%100<(0.03*cos((double)turn)+0.0003*max_turns+0.1)*100)
        ret=displayRNeg();
    else if (rand()%100<(0.1*sin((double)turn)+0.001*max_turns+0.1)*100)
        ret=displayNeg();
    else if (rand()%100<(0.2+0.1*(1.0/(double)turn)+0.0001*(1.0/(double)max_turns))*100)
        ret=displayNeutral();
    else if (rand()%100<(0.05*pow(sin((double)turn),(double)turn)+0.00003*max_turns+0.1)*100)
        ret=displayPositive();
    else
        ret=displayWarpChange();
    
    int i;
    selRes=3;//coar
    for (i=0; i<NUM_RESOURCES; ++i)
    {
        if (rand()%100<resWeights[i])
        {
            selRes=i;
            break;
        }
    }

    return ret;
}
void drawEvents(void)
{
    blitSprite(s,OFF_X,OFF_Y,0,0);
    blitSprite(resources[selRes],ROFF_X,ROFF_Y,0,0);
}
    


void cleanEvents(void)
{
    //TODO
}
