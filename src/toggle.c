/*
Original code by Ruud Helderman ("How to program a text adventure in C")
For the game "THE SPIRIT WITHIN US" Alessandro Ielo added:
.toggle to different objects (Toilet, BoxPhoto, BoxWoods, etc).
*/

#include <stdio.h>
#include "object.h"
#include "misc.h"
#include "location.h"

static void swapLocations(OBJECT *obj1, OBJECT *obj2)
{
  OBJECT *tmp = obj1->location;
  obj1->location = obj2->location;
  obj2->location = tmp;
}

const char *cannotBeOpened(void)    { return "That cannot be opened.\n";    }
const char *cannotBeClosed(void)    { return "That cannot be closed.\n";    }
const char *cannotBeLocked(void)    { return "That cannot be locked.\n";    }
const char *cannotBeUnlocked(void)  { return "That cannot be unlocked.\n";  }

const char *isAlreadyOpen(void)     { return "That is already open.\n";     }
const char *isAlreadyClosed(void)   { return "That is already closed.\n";   }
const char *isAlreadyLocked(void)   { return "That is already locked.\n";   }
const char *isAlreadyUnlocked(void) { return "That is already unlocked.\n"; }

const char *isStillOpen(void)       { return "That is still open.\n";       }
const char *isStillLocked(void)     { return "That is locked.\n";           }


const char *toggleToilet(void)
{
  swapLocations(openToilet, closedToilet);
  return "Done.\n";
}

const char *toggleFridge(void)
{
  swapLocations(openFridge, closedFridge);
  return "Done.\n";
}

const char *toggleBoxPhoto(void)
{
  swapLocations(openBoxPhoto, closedBoxPhoto);
  return "Done.\n";
}

const char *toggleAidKit(void)
{
  swapLocations(openAidKit, closedAidKit);
  return "Done.\n";
}

const char *toggleClosetDoor(void)
{
  swapLocations(openDoorToCloset, closedDoorToCloset);
  swapLocations(openDoorToLivingRoom, closedDoorToLivingRoom);
  return "Done.\n";
}

const char *toggleShedDoor(void)
{
  swapLocations(openDoorToShed, closedDoorToShed);
  swapLocations(openDoorToGardenNorth, closedDoorToGardenNorth);
  return "Done.\n";
}

const char *toggleGarageDoor(void)
{
  swapLocations(openDoorToGarage, closedDoorToGarage);
  swapLocations(openDoorToGroveSouth, closedDoorToGroveSouth);
  return "Done.\n";
}

const char *toggleGarageDoorLock(void)
{
  if (keyForGarage->location == player)
  {
    swapLocations(closedDoorToGarage, lockedDoorToGarage);
    keyForGarage->location = emptyRoom;
    return "Done.\n";
  }
  else
  {
    return "You don't have a key.\n";
  }
}

void toggleLamp(void)
{
  bool oldLit = isLit(player->location);
  swapLocations(lampOn, lampOff);
  printf("Done.\n");
  if (oldLit != isLit(player->location))
  {
    printf("\n");
    executeLookAround();
  }
}

void toggleCarEngine(void)
{
  swapLocations(carEngineOn, carEngineOff);
  printf("Done.\n");
}
