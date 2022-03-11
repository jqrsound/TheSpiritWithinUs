/*
Original code by Ruud Helderman ("How to program a text adventure in C")
For the game "THE SPIRIT WITHIN US" Alessandro Ielo added:
.isLit: the light attribute in object.txt defines whether a location has light or not.
.listObjectsInventory: obj->explanation is read when calling inventory.
.originalLocation: if the dropped object is not in its original location a new line of text is shown,
so as not to ruin the narration of obj->description.
*/

#include <stdio.h>
#include "object.h"
#include "misc.h"

static OBJECT *getLocation(OBJECT *obj)
{
   while (obj->location != NULL) obj = obj->location;
   return obj;
}

bool isLit(OBJECT *location)
{
   return location == entryway ||
          location == kitchen ||
          location == corridor ||
          location == bedroom ||
          location == bathroom ||
          location == livingRoom ||
          location == closet ||
          location == guestRoom ||
          location == getLocation(lampOn);
}

OBJECT *getPassage(OBJECT *from, OBJECT *to)
{
  OBJECT *obj;
  forEachObject(obj)
  {
    if (from != NULL && obj->location == from && obj->prospect == to)
    {
      return obj;
    }
  }
  return NULL;
}

DISTANCE getDistance(OBJECT *from, OBJECT *to)
{
  return !validObject(to)                         ? distUnknownObject :
         to == from                               ? distSelf :
         to->location == from                     ? distHeld :
         !isLit(from->location) &&
         !isLit(to) && !isLit(to->prospect)       ? distNotHere :
         to == from->location                     ? distLocation :
         to->location == from->location           ? distHere :
         getPassage(from->location, to) != NULL   ? distOverthere :
         !validObject(to->location)               ? distNotHere :
         to->location->location == from           ? distHeldContained :
         to->location->location == from->location ? distHereContained :
         distNotHere;
}

OBJECT *actorHere(void)
{
  OBJECT *obj;
  forEachObject(obj)
  {
    if (getDistance(player, obj) == distHere && obj->health > 0)
    {
      return obj;
    }
  }
  return NULL;
}

int listObjectsAtLocation(OBJECT *location)
{
  int count = 0;
  int post = 0;
  OBJECT *obj;
  forEachObject(obj)
  {
    if (obj != player && obj->location == location &&
      (obj->location == obj->originalLocation || obj->originalLocation == emptyRoom) &&
      getDistance(player, obj) < distNotHere)
      {
        if (count++ == 0)
        {
          printf("%s ", location->contents);
        }
        printf("%s", obj->description);
      }
    }
    count = 0;
    forEachObject(obj)
    {
      if (obj != player && obj->location == location &&
        obj->location != obj->originalLocation && obj->originalLocation != emptyRoom &&
        getDistance(player, obj) < distNotHere)
        {
          if (count++ == 0)
          {
            if (player->location->sector == 4)
            {
              printf("On the floor you see ");
            }
            else
            {
              printf("On the ground you see ");
            }
          }
          printf("a %s, ", obj->explanation);
          post = 1;
        }
      }
      if(post == 1) printf("that you threw away.\n");
      return count;
    }

    int listObjectsInventory(OBJECT *location)
    {
      int count = 0;
      OBJECT *obj;
      forEachObject(obj)
      {
        if (obj != player && obj->location == location &&
          getDistance(player, obj) < distNotHere)
          {
            if (count++ == 0)
            {
              printf("%s:\n", location->contents);
            }
            printf(".%s\n", obj->explanation);
          }
        }
        return count;
      }

      int weightOfContents(OBJECT *container)
      {
        int sum = 0;
        OBJECT *obj;
        forEachObject(obj)
        {
          if (obj->location == container) sum += obj->weight;
        }
        return sum;
      }
