/*
Original code by Ruud Helderman ("How to program a text adventure in C")
For the game "THE SPIRIT WITHIN US" Alessandro Ielo added:
.moveCount, trigger, foxCount, flashCountX, defenseCount: used to trigger various events during the game
(check damage.c, fire.c, flashback.c, fox.c).
.do...while loop: to control the menu when opening the executable.
.SPIRIT: generates a .txt file that will be used as save file.
It's the main loop, it also runs the functions flashback, fireEnd and healthCount.
.start: shows the welcome message when the game is selected from the menu .
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "object.h"
#include "expand.h"
#include "parsexec.h"
#include "turn.h"
#include "manual.h"
#include "clear.h"
#include "flashback.h"
#include "fire.h"
#include "health.h"

static char input[100] = "look around";
static int result;
int foxCount = 0;
int flashCountA, flashCountB, flashCountC = 0;

static bool getFromFP(FILE *fp)
{
  bool ok = fgets(input, sizeof input, fp) != NULL;
  if (ok) input[strcspn(input, "\n")] = '\0';
  return ok;
}

static bool getInput(const char *filename)
{
  static FILE *fp = NULL;
  bool ok;
  if (fp == NULL)
  {
    if (filename != NULL) fp = fopen(filename, "rt");
    if (fp == NULL) fp = stdin;
  }
  else if (fp == stdin && filename != NULL)
  {
    FILE *out = fopen(filename, "at");
    if (out != NULL)
    {
      fprintf(out, "%s\n", input);
      fclose(out);
    }
  }
  printf("\n--> ");
  ok = getFromFP(fp);
  if (fp != stdin)
  {
    if (ok)
    {
      printf("%s\n", input);
    }
    else
    {
      fclose(fp);
      ok = getFromFP(fp = stdin);
    }
  }
  foxCount ++;
  return ok;
}

char *string(char *dest, const char *src)
{
  size_t i,j;
  for (i = 0; dest[i] != '\n'; i++)
  ;
  for (j = 0; src[j] != '\0'; j++)
  dest[i+j] = src[j];
  dest[i+j] = '\0';
  return dest;
}

int start(void)
{
  printf("\n\nYou regain consciousness after an indefinite period of time. You don't feel well, something happened while you were out, but you don't remember what.\n");
  printf("You try to get up but the headache is terrible and your entire body hurts.\n");
  printf("Lying on the floor, you feel worried. It's been a very long time since your last blackout.\n\n");
  printf("With much effort you finally manage to stand up. The pain is strong but bearable.\n");
  printf("You touch your side and immediately withdraw your hand, it's covered in blood. You're injured.\n\n");
  printf("\033[0;34m");
  printf("Your health is %d/100\n\n", player->health);
  printf("\033[0m");
  return 1;
}

int SPIRIT(void)
{
  char name[30] = "0";
  char txt[] = {'.', 't', 'x', 't', '\0'};
  printf("Please enter the name of your save-game file (max 8 characters).\nIf the save file does not exist, it will be created automatically:\n");
  fgets(name, 30, stdin);
  string(name, txt);
  start();
  while (turn(parseAndExecute(expand(input, sizeof input))) &&
    flashback() &&
    fireEnd() &&
    healthCount() &&
    getInput(name));
  return 0;
}

int quit(void)
{
  char buffer[10] = "0";
  printf("Do you want to quit? [Y] [N]\n");
  fgets(buffer, 10, stdin);
  if (buffer[0] == 'y' ||buffer[0] == 'Y'){
    printf("\nThanks for playing!\n\n");
    return 0;
  }
  return 1;
}

int main(void)
{
  char buffer[10] = "0";
  int choice = 0;
  result = 1;

  do{
    clear();
    printf("THE SPIRIT WITHIN US, an interactive fiction.\n\n");
    printf("  [1] Play the Game\n\n");
    printf("  [2] Manual\n\n");
    printf("  [3] Quit\n");
    printf("\n\nPlease select [1-3] and enter fullscreen mode to better enjoy the game.\n");

    do{
      fgets(buffer, 10, stdin);
      choice = atoi (buffer);

      switch(choice){
        case 1:
        clear();
        result = SPIRIT();
        break;
        case 2:
        clear();
        result = manual();
        break;
        case 3:
        clear();
        result = quit();
        break;
        default:
        result = 1;
      }
    } while (!(choice = 3));
  } while(result == 1);

  return 0;
}
