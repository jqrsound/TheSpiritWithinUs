/*
Original code by Ruud Helderman ("How to program a text adventure in C")
For the game "THE SPIRIT WITHIN US" Alessandro Ielo added:
.obj->explanation instead of obj->description.
obj->description is used to describe the whole scene and obj->explanation to name individual objects
(check object.c).

in turn: in case of player's death, the function gameOverLose is recalled.
*/

#include <stdbool.h>
#include <stdio.h>
#include "object.h"
#include "location.h"
#include "misc.h"
#include "end.h"
#include "damage.h"

int moveCount, trigger = 0;

static OBJECT *findBestWeaponAround(OBJECT *actor, OBJECT *weapon)
{
  OBJECT *obj;
  forEachObject(obj)
  {
    if (getDistance(actor, obj) == distHere &&
    obj->impact > weapon->impact)
    {
      weapon = obj;
    }
  }
  return weapon;
}

static void actorTakingTurn(OBJECT *actor)
{
  if (getDistance(actor, player) == distHere && actor->trust < 0)
  {
    OBJECT *weapon = getOptimalWeapon(actor);
    OBJECT *best = findBestWeaponAround(actor, weapon);
    if (weapon == best)
    {
      dealDamage(actor, weapon, player);
    }
    else
    {
      best->location = actor;
      printf("You see the %s pick up the %s.\n",
      actor->explanation, best->explanation);
    }
  }
}

bool turn(int time)
{
  if (time > 0)
  {
    moveCount ++;
    trigger ++;
    OBJECT *obj;
    forEachObject(obj)
    {
      if (obj->health > 0) actorTakingTurn(obj);
    }
    if (player->health <= 0)
    {
      healthMove();
      gameOverLose();
      return 0;
    }
  }
  return time >= 0;
}
