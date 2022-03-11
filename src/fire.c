/*
Original code by Alessandro Ielo for the game "THE SPIRIT WITHIN US"
.fireCountdown: when the burn command is executed, trigger is set at 100000 and increases by 1 with every move of the player.
(check executeBurn in inventory2.c)
.fireDestroy: each location on the map is destroyed by the spreading fire, based on the trigger and their sector.
Each object with attribute burn=1 is moved to emptyRoom and disappears from the map. (check object.txt)
.fireEnd: the trigger shows various messages, based on its value.
It also acts as a countdown, and when trigger reaches 100020, the player dies.
*/

#include <stdio.h>
#include "parsexec.h"
#include "object.h"
#include "location.h"
#include "turn.h"
#include "end.h"

void fireCountdown(void)
{
  extern int trigger;
  if (man->health == -1) trigger = 100000;
}

int fireHealth(void)
{
  printf("The fire has reached the %s, everything is burning.\n", player->location->explanation);
  player->health--;
  printf("\033[0;34m");
  printf("\nThe heat is unbearable, you get too close and get burned.\n");
  printf("Your health is %d/100\n", player->health);
  printf("\033[0m");
  if(player->health <= 0)
  {
    printf("\033[0;34m");
    printf("You die from the injuries.\n");
    printf("\033[0m");
    return -1;
  }
  return 1;
}

int fireDestroy(void)
{
  OBJECT *obj;
  extern int trigger;
  if (trigger >= 100001)
  {
    forEachObject(obj)
    {
      if (obj->burn == 1 && obj->location != NULL)
      {
        if (obj->location->sector == 1)
        {
          obj->location = emptyRoom;
        }
      }
    }
    if (player->location->sector == 1)
    {
      fireHealth();
    }
  }
  if (trigger >= 100004)
  {
    forEachObject(obj)
    {
      if (obj->burn == 1 && obj->location != NULL)
      {
        if (obj->location->sector == 2)
        {
          obj->location = emptyRoom;
        }
      }
    }
    if (player->location->sector == 2)
    {
      fireHealth();
    }
  }
  if (trigger >= 100008)
  {
    forEachObject(obj)
    {
      if (obj->burn == 1 && obj->location != NULL)
      {
        if (obj->location->sector == 3)
        {
          obj->location = emptyRoom;
        }
      }
    }
    if (player->location->sector == 3)
    {
      fireHealth();
    }
  }
  if (trigger >= 100012)
  {
    forEachObject(obj)
    {
      if (obj->burn == 1 && obj->location != NULL)
      {
        if (obj->location->sector == 4)
        {
          obj->location = emptyRoom;
        }
      }
    }
    if (player->location->sector == 4)
    {
      fireHealth();
    }
  }
  if (trigger >= 100016)
  {
    forEachObject(obj)
    {
      if (obj->burn == 1 && obj->location != NULL)
      {
        if (obj->location->sector == 5)
        {
          obj->location = emptyRoom;
        }
      }
    }
    if (player->location->sector == 5)
    {
      fireHealth();
    }
  }
  if (trigger >= 100018)
  {
    forEachObject(obj)
    {
      if (obj->burn == 1 && obj->location != NULL)
      {
        if (obj->location->sector == 6)
        {
          obj->location = emptyRoom;
        }
      }
    }
    if (player->location->sector == 6)
    {
      fireHealth();
    }
  }
  return 1;
}

int fireEnd(void)
{
  extern int trigger;
  fireDestroy();
  if (trigger == 100003)
  {
    printf("\033[0;31m");
    printf("\nDry grass and the rest of the gasoline help the fire spread faster than you thought it would.\n");
    printf("\033[0m");
  }
  else if (trigger == 100005)
  {
    printf("\033[0;31m");
    printf("\nRun, the fire's spreading and will soon catch up with you!\n");
    printf("\033[0m");
  }
  else if (trigger == 100012)
  {
    printf("\033[0;31m");
    printf("\nThe house is completely engulfed in flames and it's about to collapse on itself.\n");
    printf("\033[0m");
  }
  else if (trigger == 100015)
  {
    printf("\033[0;31m");
    printf("\nYou don't have much time, hurry up and get out of this hell!\n");
    printf("\033[0m");
  }
  else if (trigger == 100020)
  {
    printf("\033[0;31m");
    printf("\nThe fire has spread too fast for you to escape. You are caught in the flames and burned alive.\n");
    printf("\033[0m");

    player->health = 0;

    printf("\033[0;34m");
    printf("\nYour health is %d/100\n", player->health);
    printf("\033[0m");
    printf("\nYou die from the injuries.\n");

    gameOverLose();
    return 0;
  }
  return 1;
}
