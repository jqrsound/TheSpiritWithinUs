/*
Original code by Ruud Helderman ("How to program a text adventure in C")
For the game "THE SPIRIT WITHIN US" Alessandro Ielo added:
.obj->explanation instead of obj->description.
obj->description is used to describe the whole scene and obj->explanation to name individual objects
(check object.txt)
.player->weapon: the player can carry only 2 weapons (check object.txt).
.player->capacity: the player can carry a limited amount of objects, based on capacity.
.objects with a capacity of 100 have a special message on why they cannot be carried.
*/

#include <stdio.h>
#include "object.h"
#include "misc.h"

int moveObject(OBJECT *obj, OBJECT *to)
{
  if (obj == NULL)
  {
    // already handled by getVisible or getPossession
    return 0;
  }
  else if (to == NULL)
  {
    printf("There is nobody here to give that to.\n");
    return 0;
  }
  else if (to->capacity == 0)
  {
    printf(obj == keyForGarage && (to == closedDoorToGarage || to == lockedDoorToGarage) ?
    "The key seems to fit the padlock.\n" :
    "It doesn't seem to fit in.\n");
    return 1;
  }
  else if (obj->weight > to->capacity)
  {
    if (obj->weight == 100)
    {
      printf("You feel too weak, better not to waste energy carrying objects that you do not need.\n");
      return 1;
    }
    if (to->animal == 1)
    {
      printf("The %s doesn't show interest in the %s.\n", to->explanation, obj->explanation);
      return 1;
    }
    else
    {
      printf("That is way too heavy for you to carry.\n");
    }
    return 1;
  }
  else if (obj->weight + weightOfContents(to) > to->capacity)
  {
    if (to == player)
    {
      printf("You can't carry too many items.\n");
    }
    else
    {
      printf("That would become too heavy.\n");
    }
    return 1;
  }
  else
  {
    if (to == player->location)
    {
      printf("You drop the %s.\n", obj->explanation);
      if (obj->impact > 0) player->weapon--;
    }
    else if (to != player)
    {
      printf(to->health > 0 ? "You give the %s to the %s.\n"
                            : "You put the %s in the %s.\n",
      obj->explanation, to->explanation);
      if (obj->impact > 0) player->weapon--;
    }
    else if (obj->location == player->location)
    {
      if (obj->impact > 0 && player->weapon >= 2)
      {
        printf("You can only carry two weapons.\n");
        return 0;
      }
      else
      {
        printf("You pick up the %s.\n", obj->explanation);
        if (obj->impact > 0) player->weapon++;
      }
    }
    else
    {
      if (obj->impact > 0 && player->weapon >= 2)
      {
        printf("You can only carry two weapons.\n");
        return 0;
      }
      else
      {
        printf("You get the %s from the %s.\n", obj->explanation,
        obj->location->explanation);
        if (obj->impact > 0) player->weapon++;
      }
    }
    obj->location = to;
    return 1;
  }
}
