/*
Original code by Ruud Helderman ("How to program a text adventure in C")
For the game "THE SPIRIT WITHIN US" Alessandro Ielo added:
.executeKill: based on the health of the enemy, and whether or not the enemy is an animal.
.executeDrive: being the car the way to end the game in case of victory,
the drive command recalls the relative ending (check end.c)
.executeRead: to read objects with read attribute.
.executeBurn: depending on different conditions you can burn or not burn some objects.
In case you burn the corpse of your enemy, the function fireContdown is recalled (check fire.c).
.executeEat: to eat objects with power attribute. In case power is negative, the player's health is reduced.
After eating it, the object is moved to emptyRoom and disappears from the map.
*/

#include <stdio.h>
#include "object.h"
#include "misc.h"
#include "match.h"
#include "noun.h"
#include "move.h"
#include "reach.h"
#include "end.h"
#include "fire.h"

int executeGetFrom(void)
{
  OBJECT *from = reachableObject("where to get that from", params[1]);
  if (from != NULL && getVisible("what you want to get", params[0]) != NULL)
  {
    if (from->health > 0)
    {
      printf("You should take it from the %s by force.\n", from->explanation);
    }
    else
    {
      moveObject(getPossession(from, "get", params[0]), player);
    }
  }
  return true;
}

int executePutIn(void)
{
  OBJECT *obj = getPossession(player, "put", params[0]);
  if (obj != NULL)
  {
    OBJECT *to = reachableObject("where to put that in", params[1]);
    if (to != NULL)
    {
      if (to->health > 0)
      {
        printf("You should offer that nicely to the %s.\n", to->explanation);
      }
      else
      {
        moveObject(obj, to);
      }
    }
  }
  return true;
}

int executeGiveTo(void)
{
  OBJECT *obj = getPossession(player, "give", params[0]);
  if (obj != NULL)
  {
    OBJECT *to = reachableObject("who to give that to", params[1]);
    if (to != NULL)
    {
      if (to->health > 0)
      {
        moveObject(obj, to);
      }
      else
      {
        printf("No eagerness is shown by the %s.\n", to->explanation);
      }
    }
  }
  return true;
}

int executeKill(void)
{
  OBJECT *obj = getVisible("who you want to kill", params[0]);
  switch (getDistance(player, obj))
  {
    case distSelf:
    printf("You should not be doing that to %s.\n", obj->explanation);
    break;
    case distOverthere:
    printf("There's no one to kill here.\n");
    break;
    case distUnknownObject:
    // already handled by getVisible
    break;
    default:
    if (player->location == man->location && (man->health > 0 && man->health <= 5))
    {
      man->health = 0;
      printf("With one quick move you put your hands on the old janitor's neck and start squeezing, first with fear and then with more rage.\n");
      printf("His eyes start to cry and you can feel his throat give out. He tries to hit you but his fists are weak.\nYou just killed a man.\n");
    }
    else if (player->location == man->location && man->health > 5)
    {
      printf("You try to choke the old janitor but he is too strong and keeps on fighting.\n");
    }
    else if (player->location == man->location && man->health == 0)
    {
      printf("You already killed him.\n");
    }
    else if (player->location == obj->location && obj->animal == 1)
    {
      printf("The %s is too fast for your to catch and chocke. You attack but miss.\n", obj->explanation);
      obj->trust = -1;
    }
    else if (player->location == obj->location && obj->health == 0)
    {
      printf("You can't kill an object.\n");
    }
  }
  return true;
}

int executeDrive(void)
{
  OBJECT *obj = getVisible("what you want to drive", params[0]);
  int a = 1;
  switch (getDistance(player, obj))
  {
    case distSelf:
    printf("You can't drive the %s.\n", obj->explanation);
    break;
    case distOverthere:
    printf("There's nothing to drive here.\n");
    break;
    case distUnknownObject:
    // already handled by getVisible
    break;
    default:
    if (player->location == car && carEngineOn->location == car)
    {
      a = endGame();
    }
    else if (player->location == car && carEngineOff->location == car)
    {
      printf("You have to start the engine before you can drive.\n");
    }
  }
  return a;
}

int executeRead(void)
{
  OBJECT *obj = getVisible("what you want to read", params[0]);
  switch (getDistance(player, obj))
  {
    case distSelf:
    printf("You can't read the %s.\n", obj->explanation);
    break;
    case distOverthere:
    printf("There's nothing to read here.\n");
    break;
    case distUnknownObject:
    // already handled by getVisible
    break;
    default:
    if (obj->read != NULL && obj->location == player)
    {
      printf("%s\n", obj->read);
    }
    else if (obj->read != NULL && obj->location != player)
    {
      printf("You'd hold the %s first.\n", obj->explanation);
    }
    else
    {
      printf("You can't read it.\n");
    }
  }
  return true;
}

int executeBurn(void)
{
  OBJECT *obj = getVisible("what you want to burn", params[0]);
  switch (getDistance(player, obj))
  {
    case distSelf:
    printf("You should not be doing that to %s.\n", obj->explanation);
    break;
    case distOverthere:
    printf("There's nothing important to burn here.\n");
    break;
    case distUnknownObject:
    // already handled by getVisible
    break;
    default:
    if (gas->location == player && matches->location == player)
    {
      if (player->location == obj->location && obj->health > 0)
      {
        printf("You can't burn the %s alive.\n", obj->explanation);
      }
      else if (player->location == man->location && man->health == 0)
      {
        printf("You set fire to everything, you don't have much time to escape before the fire spreads.\n");
        man->health = -1;
        fireCountdown();
      }
      else if (player->location == obj->location && obj->health == 0)
      {
        printf("You better use the little gas you have to burn the real evidence.\n");
      }
    }
    else
    {
      printf("You have nothing to burn it with.\n");
    }
  }
  return true;
}

int executeEat(void){
  OBJECT *obj = getVisible("what you want to eat", params[0]);
  switch (getDistance(player, obj))
  {
    case distSelf:
    printf("You can't eat %s.\n", obj->explanation);
    break;
    case distOverthere:
    printf("There's nothing to eat here.\n");
    break;
    case distUnknownObject:
    // already handled by getVisible
    break;
    default:
    if (obj->power != 0 && obj->location == player)
    {
      player->health = player->health + obj->power;
      if (obj->power > 0)
      {
        printf("You ate the %s.\n", obj->explanation);
      }
      else if (obj->power < 0)
      {
        printf("The food you just ate makes you feel bad, the %s was toxic.\n", obj->explanation);
      }
      printf("\033[0;34m");
      printf("\nYour health is %d/100\n", player->health);
      printf("\033[0m");
      obj->power = 0;
      obj->location = emptyRoom;
    }
    else if (obj->power != 0 && obj->location != player)
    {
      printf("You'd hold the %s first.\n", obj->explanation);
    }
    else
    {
      printf("You can't eat it.\n");
    }
  }
  return true;
}
