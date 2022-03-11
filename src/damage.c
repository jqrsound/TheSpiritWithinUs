/*
Original code by Ruud Helderman ("How to program a text adventure in C")
For the game "THE SPIRIT WITHIN US" Alessandro Ielo added:
.defenseCount: each attack is divided by defenseCount (default is by 1, in case of defense is by 2).
.weaponDamage: a weapon wears out with use, if it reaches a value of 3, it is thrown away because unusable.
The player has an impact of 1, the aggressor of 2 and the weapons from 3 and above.

in describeAttack, the defense is now taken into account and a health count is shown.
in dealDamage, if you do not have weapons, the weaponDescription is chosen randomly.
in dealDamage, the damage formula has been changed in a more aggressive way.
in dealDamage, it's now described if the opponent miss a hit (when damage = 0).
in getOptimalWeapon, when a weapon loses is power, the opponent trows it away.
*/

#include <stdlib.h>
#include <stdio.h>
#include "object.h"

int defenseCount = 1;
const char *weaponDescription;

void weaponDamage(OBJECT *weapon)
{
  if (weapon->health == 0)
  {
    weapon->impact--;
    if (weapon->impact == 3)
    {
      if (weapon->location == player) player->weapon--;
      printf("The %s breaks from the impact and falls on the ground, unusable\n", weapon->explanation);
      weapon->location = emptyRoom;
    }
  }
}

void dealDefense(void)
{
  defenseCount = 2;
}

static void describeAttack(OBJECT *attacker, OBJECT *victim, OBJECT *weapon, const char *weaponDescription)
{
  if (attacker == player)
  {
    printf("You attack the %s with a %s.\n", victim->explanation, weaponDescription);
    weaponDamage(weapon);
  }
  else if (victim == player)
  {
    printf("The %s attacks you with a %s.\n", attacker->explanation, weaponDescription);
    if (defenseCount == 2){
      printf("You defended yourself from the %s.\n", attacker->explanation);
      defenseCount = 1;
    }
    printf("\033[0;34m");
    printf("\nYour health is %d/100\n", player->health);
    printf("\033[0m");
    weaponDamage(weapon);
  }
  else
  {
    printf("You see the %s being attacked by the %s, with a %s.\n", victim->explanation, attacker->explanation, weaponDescription);
    weaponDamage(weapon);
  }
}

static void describeDeath(OBJECT *attacker, OBJECT *victim)
{
  if (attacker == player)
  {
    printf("You have killed the %s.\n", victim->explanation);
  }
  else if (victim == player)
  {
    printf("You have been killed by the %s.\n", attacker->explanation);
  }
  else
  {
    printf("You see the %s being killed by the %s.\n", victim->explanation, attacker->explanation);
  }
}

static void describeAlreadyDead(OBJECT *attacker, OBJECT *victim)
{
  if (victim == player)
  {
    printf("Even though you're dead, the %s continue to attack you with fury.\n", attacker->explanation);
  }
  else
  {
    printf("You need to calm down, the %s is already dead.\n", victim->explanation);
  }
}

void dealDamage(OBJECT *attacker, OBJECT *weapon, OBJECT *victim)
{
  if (weapon == attacker)
  {
    int noWeapon = rand() % 4;
    if (attacker->animal == 0)
    {
      switch(noWeapon)
      {
        case 1:
        weaponDescription = "raging fury";
        break;
        case 2:
        weaponDescription = "series of kicks";
        break;
        case 3:
        weaponDescription = "punch";
        break;
        default:
        weaponDescription = "violent lunge";
      }
    }
    else if (attacker->animal == 1)
    {
      switch(noWeapon)
      {
        case 1:
        weaponDescription = "savage brutality";
        break;
        case 2:
        weaponDescription = "wild ferocity";
        break;
        case 3:
        weaponDescription = "rapid movement";
        break;
        default:
        weaponDescription = "growl";
      }
    }
  }
  else
  {
    weaponDescription = weapon->explanation;
  }
  int damage = (rand() % 9) * weapon->impact / 6;
  if (damage > 0)
  {
    if (attacker == player)
    {
      victim->trust--;
    }
    if (victim->health <= 0)
    {
      describeAlreadyDead(attacker, victim);
    }
    else
    {
      victim->health = victim->health - (damage/defenseCount);
      describeAttack(attacker, victim, weapon, weaponDescription);
      if (victim->health <= 0)
      {
        victim->health = 0;
        describeDeath(attacker, victim);
      }
    }
  }
  else if (attacker == player)
  {
    printf("You try to attack the %s with a %s, but you miss.\n", victim->explanation, weaponDescription);
  }
  else if (attacker != player)
  {
    printf("The %s tries to attack you with a %s, but misses.\n", attacker->explanation, weaponDescription);
  }
}

OBJECT *getOptimalWeapon(OBJECT *attacker)
{
  OBJECT *obj, *weapon = attacker;
  forEachObject(obj)
  {
    if (obj->location == attacker && obj->impact > weapon->impact)
    {
      if (weapon->health == 0)
      {
        printf("The %s drops the %s to the ground.\n", attacker->explanation, weapon->explanation);
        weapon->location = attacker->location;
      }
      weapon = obj;
    }
  }
  return weapon;
}
