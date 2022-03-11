/*
Original code by Ruud Helderman ("How to program a text adventure in C")
*/

#include <stdio.h>
#include "object.h"
#include "misc.h"
#include "match.h"
#include "noun.h"

int executeLookAround(void)
{
  if (isLit(player->location))
  {
    printf("\n* You are in %s.\n\n", player->location->description);
  }
  else
  {
    printf("\n* It is very dark in here.\n\n");
  }
  listObjectsAtLocation(player->location);
  return true;
}

int executeLook(void)
{
  OBJECT *obj = getVisible("what you want to look at", params[0]);
  switch (getDistance(player, obj))
  {
    case distHereContained:
    printf("Hard to see, try to get it first.\n");
    break;
    case distOverthere:
    printf("Too far away, move closer please.\n");
    break;
    case distNotHere:
    printf("You don't see any %s here.\n", params[0]);
    break;
    case distUnknownObject:
    // already handled by getVisible
    break;
    default:
    printf("%s", obj->details);
    listObjectsAtLocation(obj);
  }
  return true;
}

static void movePlayer(OBJECT *passage)
{
  printf("%s", passage->textGo);
  if (passage->destination != NULL)
  {
    player->location = passage->destination;
    printf("\n");
    executeLookAround();
  }
}

int executeGo(void)
{
  OBJECT *obj = getVisible("where you want to go", params[0]);
  switch (getDistance(player, obj))
  {
    case distOverthere:
    movePlayer(getPassage(player->location, obj));
    break;
    case distNotHere:
    printf("You don't see any %s here.\n", params[0]);
    break;
    case distUnknownObject:
    // already handled by getVisible
    break;
    default:
    movePlayer(obj);
  }
  return true;
}
