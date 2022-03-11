/*
Original code by Ruud Helderman ("How to program a text adventure in C")
For the game "THE SPIRIT WITHIN US" Alessandro Ielo added:
.reachableObjectDefense: allows to use "yourself" as an object (used by executeDefense in attack.c)
*/

#include <stdio.h>
#include "object.h"
#include "misc.h"
#include "noun.h"

OBJECT *reachableObject(const char *intention, const char *noun)
{
  OBJECT *obj = getVisible(intention, noun);
  switch (getDistance(player, obj))
  {
    case distSelf:
    printf("You should not be doing that to %s.\n", obj->explanation);
    break;
    case distHeldContained:
    case distHereContained:
    printf("You would have to get it from the %s first.\n",
    obj->location->explanation);
    break;
    case distOverthere:
    printf("Too far away, move closer please.\n");
    break;
    case distNotHere:
    case distUnknownObject:
    // already handled by getVisible
    break;
    default:
    return obj;
  }
  return NULL;
}

OBJECT *reachableObjectDefense(const char *intention, const char *noun)
{
  OBJECT *obj = getVisible(intention, noun);
  switch (getDistance(player, obj))
  {
    case distSelf:
    printf("You are preparing to parry the attack.\n");
    return obj;
    break;
    case distHeldContained:
    case distHereContained:
    printf("You don't need to parry from the %s.\n",
    obj->location->explanation);
    break;
    case distOverthere:
    printf("Too far away, you don't need to parry.\n");
    break;
    case distNotHere:
    case distUnknownObject:
    // already handled by getVisible
    break;
    default:
    return obj;
  }
  return NULL;
}
