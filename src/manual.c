/*
Original code by Alessandro Ielo for the game "THE SPIRIT WITHIN US"
.do...while loop: to control the menu when opening the manual.
*/

#include <stdio.h>
#include <stdlib.h>
#include "clear.h"

int anyKeyManual(void)
{
  char buffer[10] = "0";
  printf("\n\n\n\nPress any key to return to the manual, [r] to return to the main window.\n");
  fgets (buffer, 10, stdin);
  if (buffer[0] == 'r' || buffer[0] == 'R')
  {
    return 0;
  }
  return 1;
}

int intro(void)
{
  int a = 1;
  printf("Interactive fiction is a story in which you are the main character.\n");
  printf("Your own thinking and imagination determine the actions of a character and guide the story from start to finish.\n\n");
  printf("To move from place to place, type the direction you want to go.\n\n");
  printf("When you begin your adventure, it's a good idea to become familiar with your surroundings by exploring every location and reading each description carefully.\n");
  printf("As you explore, it is helpful to draw a map of the geography.\n\n");
  printf("In addition to exploring you will have to make choices that will lead to one of the possible endings.\n");
  a = anyKeyManual();
  return a;
}

int listParser(void)
{
  char buffer[10] = "0";
  clear();
  printf("Here is a partial list of commands recognized by the parser:\n\n");
  printf("   .look / look around / look X / look at X / examine X\n   .go to X / go X\n   .take X / get X / hold X\n");
  printf("   .drop X / put X in Y\n   .give X to Y\n   .open X / close X / lock X / unlock X\n   .turn on X / turn off X\n");
  printf("   .hit X / attack X / hit X with Y / attack X with Y / kill X\n   .defend / protect / parry\n");
  printf("   .eat X / read X / drive X / burn X\n   .inventory / help / info\n   .wait / quit\n\n");
  printf("\n\n\n\nPress any key to return to the manual.\n");
  fgets (buffer, 10, stdin);
  return 1;
}

int parser(void)
{
  char buffer[10] = "0";
  printf("When you see the prompt (-->) on your screen, the game is waiting for your command. Type the command after the prompt and hit the ENTER key.\n\n");
  printf("  1. To move from place to place, just type the direction you want to go: north (or \"n\"), east (\"e\"), south (\"s\"), west (\"w\").\n");
  printf("  2. The game understands many different kinds of sentences, mainly in the \"verb-noun\" form, however combinations like \"turn X on\" or \"put X in Y\" are also possible.\n");
  printf("  3. One-word commands, such as \"inventory\", give you specific information.\n");
  printf("  4. Some commands have abbreviations to make the game run more smoothly, as \"g\" for get/take, \"l\" for look or \"x\" for examine.\n");
  printf("  5. Traditional commands are \"look\", \"go\", \"get/take\", \"put\", \"open\", \"unlock\", but the game recognizes many more that the player will have to discover.\n");
  printf("\nFor a list of commands press [x]");
  printf("\n\n\n\nPress any key to return to the manual, [r] to return to the main window.\n");
  fgets (buffer, 10, stdin);
  if (buffer[0] == 'r' ||buffer[0] == 'R')
  {
    return 0;
  }
  else if (buffer[0] == 'x' ||buffer[0] == 'X')
  {
    listParser();
  }
  return 1;
}

int save(void)
{
  int a = 1;
  printf("THE SPIRIT WITHIN US follows natural rules. The player has only one life, and if the energy level reaches zero the player dies and the game ends.\n");
  printf("The game can be interrupted and resumed as many times as you want, thanks to the save file.\n\n");
  printf("To save and recall the game:\n\n");
  printf("  1. At the beginning of the game you will be asked to enter a name for your save-game file.\n");
  printf("  2. If the save file does not exist, it will be created automatically.\n");
  printf("  3. To resume your game, enter the save-game file name the next time you access the program.\n");
  printf("  4. If you want to play the game again from the beginning, simply create a new save file.\n");
  a = anyKeyManual();
  return a;
}

int feedback(void)
{
  int a = 1;
  printf("If you have technical problems or find that something isn't working, please get in touch at:\n\n");
  printf("hi@jqrsound.com\n");
  a = anyKeyManual();
  return a;
}

int credits(void)
{
  int a = 1;
  printf("THE SPIRIT WITHIN US is written and programmed in the C Language by Alessandro Ielo.\n");
  printf("It is based on the tutorial \"How to program a text adventure in C\" by Ruud Helderman.\n\n");
  printf("Language consultant: Rebecca Pedinoff\n\n");
  printf("v0.35 - 2021 MIT License\n\n\n");
  printf("If you like my game, feel free to support my music at:\n");
  printf("  effter.bandcamp.com\n  apwnm.bandcamp.com\n");
  a = anyKeyManual();
  return a;
}

int mainWindow(void)
{
  return 0;
}

int manual(void)
{
  int choice = 0;
  int result = 1;
  char buffer[10] = "0";

  do{
    clear();
    printf("THE SPIRIT WITHIN US, the manual.\n");
    printf("  [1] Introduction\n");
    printf("  [2] The Parser\n");
    printf("  [3] Save and Recall\n");
    printf("  [4] Feedback\n");
    printf("  [5] Credits\n\n");
    printf("  [6] Return to the main window\n");
    printf("\nPlease select\n");

    do{
      fgets (buffer, 10, stdin);
      choice = atoi (buffer);

      switch(choice){
        case 1:
        clear();
        result = intro();
        break;
        case 2:
        clear();
        result = parser();
        break;
        case 3:
        clear();
        result = save();
        break;
        case 4:
        clear();
        result = feedback();
        break;
        case 5:
        clear();
        result = credits();
        break;
        case 6:
        clear();
        result = mainWindow();
        break;
        default:
        result = 1;
        break;
      }
    } while (!(choice = 6));
  } while(result == 1);

  return 1;
}
