/*
Original code by Ruud Helderman ("How to program a text adventure in C")
*/

#include <stdio.h>
#include "object.h"
#include "misc.h"
#include "match.h"
#include "noun.h"
#include "move.h"
#include "manual.h"

int executeGet(void)
{
  OBJECT *obj = getVisible("what you want to get", params[0]);
  switch (getDistance(player, obj))
  {
    case distSelf:
    printf("You should not be doing that to %s.\n", obj->explanation);
    break;
    case distHeld:
    printf("You already have the %s.\n", obj->explanation);
    break;
    case distOverthere:
    printf("Too far away, move closer please.\n");
    break;
    case distUnknownObject:
    // already handled by getVisible
    break;
    default:
    if (obj->location != NULL && obj->location->health > 0)
    {
      printf("You should ask the %s nicely.\n", obj->location->explanation);
    }
    else
    {
      moveObject(obj, player);
    }
  }
  return true;
}

int executeDrop(void)
{
  moveObject(getPossession(player, "drop", params[0]), player->location);
  return true;
}

int executeAsk(void)
{
  moveObject(getPossession(actorHere(), "ask", params[0]), player);
  return true;
}

int executeGive(void)
{
  moveObject(getPossession(player, "give", params[0]), actorHere());
  return true;
}

int executeInventory(void)
{
  if (listObjectsInventory(player) == 0)
  {
    printf("You are empty-handed.\n");
  }
  return true;
}

int executeUse(void)
{
  printf("Please be more specific.\n");
  return true;
}

int executeGreets(void)
{
  printf("Hi yourself.\n");
  return true;
}

int executeWear(void)
{
  OBJECT *obj = getVisible("what you want to wear", params[0]);
  switch (getDistance(player, obj))
  {
    case distSelf:
    printf("You can't wear the %s.\n", obj->explanation);
    break;
    case distOverthere:
    printf("There's nothing to wear here.\n");
    break;
    case distUnknownObject:
    // already handled by getVisible
    break;
    default:
      printf("The clothes you wear are fine as they are.\n");
  }
  return true;
}

int executeQuestion(void)
{
  printf("I am just a computer game, I have no real answer to your questions.\n");
  return true;
}

int executeManual(void)
{
  char buffer[10] = "0";
  printf("Do you want to read the manual? [Y] [N]\n");
  fgets(buffer, 10, stdin);
  if (buffer[0] == 'y' ||buffer[0] == 'Y'){
    manual();
  }
  return true;
}

int executeVoice(void)
{
  printf("Your throat hurts, and you can't make any sound other than a wheeze.\n");
  return true;
}

int executeStatus(void)
{
  printf("Your health is %d.\n", player->health);
  executeInventory();
  return true;
}

int executeRest(void)
{
  printf("The temptation is great but there is no time to lose.\n");
  return true;
}

int executeNoEnergy(void)
{
  printf("You don't have enough energy to do it.\n");
  return true;
}

int executeListen(void)
{
  if (player->location->sector == 4)
  {
    printf("The rooms are silent. You hear the ticking of a clock but you can't tell where it's coming from.\n");
  }
  else if (player->location->sector == 1 && player->location != garage)
  {
    printf("You hear a calm sound of water.\n");
  }
  else if (player->location->sector == 1 && player->location == garage)
  {
    printf("You are too shaken to hear anything other than your own heartbeat.\n");
  }
  else
  {
    printf("Outdoor night sounds bring you back to calmness.\n");
  }
  return true;
}

int executeVerbose(void)
{
  printf("Sorry, this game gives full description after each command.\n");
  return true;
}

int executeUndo(void)
{
  printf("You can't change the past.\n");
  return true;
}
