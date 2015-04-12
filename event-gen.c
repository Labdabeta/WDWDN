#include "event-gen.h"

/* A draft of some of the internal features.
 * To whom ever is incharge of implementing the generator:
 * Feel free to modify or even toss what I have writen here,
 * it was just a sketch of an idea I had in my head. It will probably
 * have to be changed to handle anything more robust than the "event type"
 * system used in the original proto-type.
 */

#include <stdlib.h>



// An enum that groups diffrent types of events.
enum EventClass
{
    NextTurnEvent,
    FluxEvent,
    VeryGoodEvent,
    GoodEvent,
    NeturalEvent,
    BadEvent,
    VeryBadEvent,

    EventClassNumber
};

// A structure that wraps up all the data about an event.
typedef struct EventCardTAG
{
    // The image that is displayed on screen when an event occurs.
    Sprite image;
    // A pointer to the function that the computer uses to resolve internal
    // effects of the event.
    void (*resolve)(void);
} EventCard, * EventCardHANDLE;

// A holder for all the events [class][event].
static EventCard ** allEvents;

// A counter for all the events [class].
static int const numEvents[EventClassNumber] = {1, 1, 0, 0, 0, 0, 0};



// Initialize an EventCard.
/* Params:
 *     spriteFile is the name of the file the image for the event is
 *   stored in.
 *     reslove is a pointer to a function that is called when the event
 *   occures (for any computer, side effects of the event)
 */
static EventCard initEventCard (const char * spriteFile, void (*resolve)(void))
{
  EventCard tmp;
  tmp->image = loadSprite(spriteFile);
  tmp->resolve = resolve;
  return tmp;
}

// Free all the memory for an EventCard, the EventCard's deconstructor.
static void cleanEventCard (EventCardHANDLE event)
{
  cleanSprite(event->image);
}



// Loads items are prepares to start the game (more peramiters needed?)
void load(void)
{
  // Create the list of event classes.
  allEvents = malloc(sizeof(EventCardHANDLE) * EventClassNumber);

  /* DO NOT UNCOMMENT WITHOUT COMPLETING

  // Load all event cards into the events regester.
  // NextTurnEvent
  allEvents[NextTurnEvent] =
      malloc(sizeof(EventCard) * numEvents[NextTurnEvent]);
  allEvents[NextTurnEvent][0] = initEventCard("~NextTurn.imagefile", nothing);

  // FluxEvent
  allEvents[FluxEvent] = malloc(sizeof(EventCard) * numEvents[FluxEvent]);
  allEvents[FluxEvent][0] = initEventCard("~Warp.imagefile", warpFlux);

  // VeryGoodEvent(s)
  allEvents[VeryGoodEvent] =
      malloc(sizeof(EventCard) * numEvents[VeryGoodEvent]);
  allEvents[VeryGoodEvent][0] ... init ...
  // ...
  allEvents[VeryGoodEvent][n] ... init ...

  // GoodEvent(s)
  allEvents[GoodEvent] = malloc(sizeof(EventCard) * numEvents[GoodEvent]);
  allEvents[GoodEvent][0] ... init ...
  // ...
  allEvents[GoodEvent][n] ... init ...

  // NeturalEvent(s)
  allEvents[NeturalEvent] = malloc(sizeof(EventCard) * numEvents[NeturalEvent);
  allEvents[NeturalEvent][0] ... init ...
  // ...
  allEvents[NeturalEvent][n] ... init ...

  // BadEvent(s)
  allEvents[BadEvent] = malloc(sizeof(EventCard) * numEvents[BadEvent]);
  allEvents[BadEvent][0] ... init ...
  // ...
  allEvents[BadEvent][n] ... init ...

  // VeryBadEvent(s)
  allEvents[VeryBadEvent] = malloc(sizeof(EventCard) * numEvents[VeryBadEvent]);
  allEvents[VeryBadEvent][0] ... init ...
  // ...
  allEvents[VeryBadEvent][n] ... init ...
  */
}

// Draw to the screen.
void draw (const InputStateHANDLE is)
{

}

// Not sure.
int step  (const InputStateHANDLE is)
{
  return 0;
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
  /*
  // Clear all of the Event Cards from memory.
  for (int i = 0 ; i < EventCardNumber ; ++i)
  {
    // Go through each class.
    for (int j = 0 ; j < numEvents[i] ; ++j)
    {
      // Clean up each event card.
      cleanEventCard(&allEvents[i][j]);
    }
    free(allEvents[i]);
    allEvents[i] = NULL;
  }
  */
  free(allEvents);
  allEvents = NULL;
}
