/*
Original code by Alessandro Ielo for the game "THE SPIRIT WITHIN US"
.flashback: the trigger shows various messages, based on its value.
Some messages have conditions that must be reached before they are shown.
.flashCountX allows messages to be shown only once.
*/

#include <stdio.h>
#include <stdlib.h>
#include "object.h"

int flashback(void)
{
  extern int trigger, flashCountA, flashCountB, flashCountC;
  if (trigger == 5)
  {
    printf("\033[0;31m");
    printf("\n\"My head hurts and I almost fell down, I don't like this feeling... I have almost regained control of myself after many years but now I feel full of doubt again.\"\n\n");
    printf("\033[0m");
  }
  else if(trigger == 15)
  {
    printf("\033[0;31m");
    printf("\n\"Since I no longer drink I have no more blackouts, I had finally managed to study and find a job, even the depression had eased. And now this...\"\n\n");
    printf("\033[0m");
  }
  else if(trigger == 45)
  {
    printf("\033[0;31m");
    printf("\n\"This is so- it's so confusing, I remember finding a photo when I was tidying up my closet at school... just look at my hands now, I'm trembling.\"\n\n");
    printf("\033[0m");
  }
  else if(trigger == 65)
  {
    printf("\033[0;31m");
    printf("\n\"The dean ordered me to throw the photo away and forget about it, but I couldn't. That's why I came here, to confront the old janitor.\"\n\n");
    printf("\033[0m");
  }
  else if(trigger == 70)
  {
    printf("\033[0;31m");
    printf("\n\"But the old janitor denied everything and attacked me, that's all I remember. How did I hurt myself?\"\n\n");
    printf("\033[0m");
  }
  else if(player->location == corridor && flashCountA == 0)
  {
    printf("\033[0;31m");
    printf("\n\"What happened here? There are signs of a fight and I'm afraid the blood on the floor could be mine.\"\n\n");
    printf("\033[0m");
    flashCountA = 1;
  }
  else if(player->location == gardenEast && flashCountA == 1)
  {
    printf("\033[0;31m");
    printf("\nYour memory comes back for an instant but you can't quite grasp the thought.\n");
    printf("\033[0m");
    flashCountA = 2;
  }
  else if(player->location == woodsWest && pictures->location == player && flashCountA == 2)
  {
    printf("\033[0;31m");
    printf("\n\"This picture is much worse than the one I found in the closet.\"\n");
    printf("\033[0m");
    flashCountA = 3;
  }
  else if(player->location == groveSouth && flashCountB == 0)
  {
    printf("\033[0;31m");
    printf("\nYou hear someone banging on the door and shouting.\n");
    printf("\033[0m");
    flashCountB = 1;
  }
  else if((meat->location == wildDog || oldFoxDead->location == wildDog) && flashCountC == 0)
  {
    printf("\033[0;31m");
    printf("\nThe dog eats the meat with eagerness and falls asleep.\n");
    printf("\033[0m");
    flashCountC = 1;
  }

  return 1;
}
