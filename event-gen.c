#include "event-gen.h"



/* A draft of some of the internal features.
 * To whom ever is incharge of implementing the generator:
 * Feel free to modify or even toss what I have writen here,
 * it was just a sketch of an idea I had in my head. It will probably
 * have to be changed to handle anything more robust than the "event type"
 * system used in the original proto-type.
 */
// An enum that groups diffrent types of events.
static enum EventClass
{
    NextTurnEvent,
    FluxEvent,
    VeryGoodEvent,
    GoodEvent,
    NeturalEvent,
    BadEvent,
    VeryBadEvent
};

// A structure that wraps up all the data about an event.
static typedef struct EventCardTAG
{
    // The image that is displayed on screen when an event occurs.
    Sprite image;
    // A pointer to the function that the computer uses to resolve internal
    // effects of the event.
    void (*resolve)(void);
} EventCard, * EventCardHANDLE;

// A holder for all the events [class][event];
EventCard ** allEvents;



// Loads items are prepares to start the game (more peramiters needed?)
void load(void)
{

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
