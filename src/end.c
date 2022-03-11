/*
Original code by Alessandro Ielo for the game "THE SPIRIT WITHIN US"
.gameOverWin: the final message after the end of the game.
.gameOverLose: a message with random quotes about death is shown when the player loses.
.endNumber: being the ending of the game based on the death of your opponent,
man->health defines what kind of ending the player has reached.
.endGame: a different message for each final is shown at the end of the game (used by executeDrive in inventory2.c).
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "parsexec.h"
#include "object.h"

int ending = 0;

void gameOverWin(void)
{
  char buffer[10] = "0";
  printf("\nPress any key to continue\n");
  fgets(buffer, 10, stdin);
  if (buffer[0] != '\0'){
    printf("\nTHE SPIRIT WITHIN US has been developed with the idea of offering a story that could be both entertaining and morally challenging.\n");
    printf("I hope I have succeeded in my intention and that you have spent your time well, while playing my game.\n\n");
    printf("Much gratitude goes to Ruud Helderman for his \"How to program a text adventure in C\" tutorial.\n");
    printf("I would like to thank Susanna, Antje and Rebecca without whose contribution THE SPIRIT WITHIN US would be different from the way it is.\n\n");
    printf("My thanks also go to you, the player, without which it would make no sense to produce this game.\n\n");
    printf("Alessandro Ielo, Berlin 2021\n\n\n");
  }
  printf("\nPress any key to exit the game\n");
  fgets(buffer, 10, stdin);
}

void deathQuote(void)
{
  char buffer[10] = "0";
  int quoteNum = rand() % 3;
  switch(quoteNum)
  {
    case 1:
    printf("\"Death is not the greatest loss in life.\nThe greatest loss is what dies inside us while we live.\"\n");
    printf("-Norman Cousins \n\n");
    break;
    case 2:
    printf("\"The fear of death follows from the fear of life.\nA man who lives fully is prepared to die at any time.\"\n");
    printf("-Mark Twain\n\n");
    break;
    default:
    printf("\"You only live twice:\nOnce when you are born\nAnd once when you look death in the face\"\n");
    printf("-Ian Fleming\n\n");
  }
  printf("\nPress any key to exit the game\n");
  fgets(buffer, 10, stdin);
}

void gameOverLose(void)
{
  char buffer[10] = "0";
  printf("\nPress any key to continue\n");
  fgets(buffer, 10, stdin);
  if (buffer[0] != '\0'){
    printf("\nThe game is over, but remember:\n\n");
    deathQuote();
  }
}

void endNumber(void)
{
  if(player->location == man->location && man->health > 0) ending = 1;
  else if(man->health == 0) ending = 2;
  else if(man->health == -1) ending = 3;
}

void healthMove(void)
{
  extern int moveCount;
  printf("\nYour health is %d/100 ", player->health);
  printf("and you used %d moves.\n", moveCount - 1);
}

int endGame(void)
{
  char buffer[10] = "0";
  switch(ending){
    case 1:
    printf("\n\nYou found yourself face-to-face with your trauma and decided not to let your dark side win.\n\nYou have not surrendered to violence, you feel that you have been saved and that you can perhaps return to your old life.\n");
    printf("You'll have to work hard to become whole again, but you're not scared of the process. You feel you owe it to yourself to finally be happy.\n");
    printf("\nAs you drive through the night a single thought frightens you.\nThat there may be other victims in the future and you have not been strong enough to stop the evil.\n\n");
    healthMove();
    gameOverWin();
    return -1;
    break;
    case 2:
    printf("\n\nYou killed a man, and your blood is everywhere.\n\nWhat are you going to do now? You can never go back to your old life, to your work.\nThe process of becoming whole will take a long time but you feel almost well, as if revenge and violence have finally shown you a new way.\n");
    printf("\nAs you drive through the night you start thinking about a new life, maybe on the run but away from your past.\n\n");
    healthMove();
    gameOverWin();
    return -1;
    break;
    case 3:
    printf("\n\nYou have set everything on fire.\n\nYour violent and aggressive side has taken over but maybe you have always been that way.\nDespite everything you feel complete, as if an old wound can now begin to heal. Regaining control will not be easy but it is not impossible.\n");
    printf("All the evidence is burnt, maybe you can go back to your old life without any problems, but is that really what you want?\n\nAs you drive through the night, the glow of the fire gets more intense behind you, and you see yourself smiling in the rear-view mirror.\n\n");
    healthMove();
    gameOverWin();
    return -1;
    break;
    default:
    printf("\nDo you really want to go back to your life without knowing what really happened?\n");
    printf("[Y] [N]\n");
    fgets(buffer, 10, stdin);
    if (buffer[0] == 'y' || buffer[0] == 'Y')
    {
      healthMove();
      printf("\nThank you for playing.\n\n");
      return -1;
    }
    return 0;
  }
}
