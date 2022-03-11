/*
Original code by StayPrivate (r/C_Programming)
*/

#include <stdio.h>
#include <stdlib.h>

void clear(void)
{
  #ifndef _WIN32
    system("clear");
  #else
    system("cls");
  #endif
}
