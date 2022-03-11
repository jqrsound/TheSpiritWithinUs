/*
Original code by Alessandro Ielo for the game "THE SPIRIT WITHIN US"
.healthCount: being the player injured, the energy will go down with every 10 or 5 moves.
A message will be shown every 15 moves.
*/

#include <stdio.h>
#include "object.h"

extern int moveCount;

int healthCount(void)
{
  if(moveCount != 0)
  {
    if(player->health > 29 && moveCount%10 == 0)
    {
      player->health = player->health - 1;
    }
    else if(player->health <= 29 && moveCount%5 == 0)
    {
      player->health = player->health - 1;
    }
  }
  if(moveCount != 0)
  {
    if(moveCount%15 == 0)
    {
      printf("\033[0;34m");
      printf("\nDue to injuries, your health is now %d/100\n", player->health);
      printf("\033[0m");
    }
  }
  return 1;
}
