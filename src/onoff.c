/*
Original code by Ruud Helderman ("How to program a text adventure in C")
For the game "THE SPIRIT WITHIN US" Alessandro Ielo added:
.battery->location: without batteries, the lamp does not turn on.
.to executeDrive and finish the game, the car engine has to be on.
*/

#include <stdio.h>
#include "object.h"
#include "match.h"
#include "reach.h"
#include "toggle.h"

int executeTurnOn(void)
{
  OBJECT *obj = reachableObject("what you want to turn on", params[0]);
  if (obj != NULL)
  {
    if (obj == lampOff && battery->location == lampOff)
    {
      toggleLamp();
    }
    else if (obj == lampOff && battery->location != lampOff)
    {
      printf("You cannot turn the torch on without batteries.\n");
    }
    else if (obj == lampOn)
    {
      printf("The torch is already on.\n");
    }
    else if (obj == tvSet)
    {
      printf("With your severe headache you would not be able to watch television.\n");
    }
    else if (obj == carEngineOff)
    {
      toggleCarEngine();
    }
    else if (obj == carEngineOn)
    {
      printf("The engine is already on.\n");
    }
    else
    {
      printf("You cannot turn the %s on.\n", obj->explanation);
    }
  }
  return true;
}

int executeTurnOff(void)
{
  OBJECT *obj = reachableObject("what you want to turn off", params[0]);
  if (obj != NULL)
  {
    if (obj == lampOn)
    {
      toggleLamp();
    }
    else if (obj == lampOff)
    {
      printf("The torch is already off.\n");
    }
    else if (obj == tvSet)
    {
      printf("The television is already off.\n");
    }
    else if (obj == carEngineOn)
    {
      toggleCarEngine();
    }
    else if (obj == carEngineOff)
    {
      printf("The engine is already off.\n");
    }
    else
    {
      printf("You cannot turn the %s off.\n", obj->explanation);
    }
  }
  return true;
}
