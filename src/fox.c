/*
Original code by Alessandro Ielo for the game "THE SPIRIT WITHIN US"
.foxBehaviour: the fox attacks if the health of the player is < 40
.foxLocation: foxCount determines where the fox will be on the map.
.fox: if the fox is alive and not in the same location as the player, it will keep moving.
*/

#include <stdio.h>
#include <stdbool.h>
#include "object.h"
#include "health.h"

extern int foxCount;
int foxSwap = 0;

void foxBehaviour(void)
{
  if (player->location == oldFox->location && player->health < 50 )
  {
    oldFox->trust--;
  }
  if (rawMeat->location == oldFox)
  {
    oldFox->trust++;
    printf("The fox eats the meat quickly but still seems to be hungry.\n");
    rawMeat->location = emptyRoom;
  }
}

void foxLocation(void)
{
  switch(foxCount)
  {
    case 1:
    case 2:
    case 3:
    oldFox->location = woodsWest;
    break;
    case 4:
    case 5:
    case 6:
    oldFox->location = woodsNorth;
    break;
    case 7:
    case 8:
    case 9:
    oldFox->location = woodsEast;
    break;
    case 10:
    case 11:
    case 12:
    oldFox->location = emptyRoom;
    break;
    default:
    oldFox->location = emptyRoom;
  }
}

static void swapLocations(OBJECT *obj1, OBJECT *obj2)
{
  OBJECT *tmp = obj1->location;
  obj1->location = obj2->location;
  obj2->location = tmp;
}

void fox(void)
{
  if (oldFox->location != player->location && oldFox->health > 0 && oldFoxDead->location == emptyRoom)
  {
    if (foxCount > 12) foxCount = 0;
    foxLocation();
  }
  if (oldFox->health <= 0 && foxSwap == 0)
  {
    swapLocations(oldFox, oldFoxDead);
    foxSwap++;
  }
  foxBehaviour();
}
