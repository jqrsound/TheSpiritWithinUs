/*
Original code by Ruud Helderman ("How to program a text adventure in C")
For the game "THE SPIRIT WITHIN US" Alessandro Ielo added:
.executeDefense: increseas defenseCount from 1 to 2, halving the gravity of an attack (check damage.c)
.reachableObjectDefense: allows to use "yourself" as an object (check reach.c)
*/

#include <stdio.h>
#include "object.h"
#include "misc.h"
#include "match.h"
#include "noun.h"
#include "reach.h"
#include "damage.h"

static OBJECT *victimHere()
{
  OBJECT *victim = actorHere();
  if (victim == NULL)
  {
    printf("There is nobody here to attack.\n");
  }
  return victim;
}

static OBJECT *victimHereDefense()
{
  OBJECT *victim = actorHere();
  if (victim == NULL)
  {
    printf("There is nobody here to protect yourself from.\n");
  }
  return victim;
}

int executeAttack(void)
{
  OBJECT *victim =
  *params[0] == '\0' ? victimHere()
  : reachableObject("who to attack", params[0]);
  if (victim != NULL)
  {
    OBJECT *weapon =
    *params[1] == '\0' ? getOptimalWeapon(player)
                       : getPossession(player, "use", params[1]);
    if (weapon != NULL)
    {
      dealDamage(player, weapon, victim);
      return 1;
    }
  }
  return 0;
}

int executeDefense(void){
  OBJECT *victim =
  *params[0] == '\0' ? victimHereDefense()
                     : reachableObjectDefense("who you want to protect yourself from", params[0]);
  if (victim != NULL)
  {
    dealDefense();
    return 1;
  }
  return 0;
}
