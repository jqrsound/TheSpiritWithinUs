/*
Original code by Ruud Helderman ("How to program a text adventure in C")
*/

#include <stdio.h>
#include "object.h"
#include "match.h"
#include "reach.h"

int executeOpen(void)
{
  OBJECT *obj = reachableObject("what you want to open", params[0]);
  if (obj != NULL) printf("%s", (*obj->open)());
  return true;
}

int executeClose(void)
{
  OBJECT *obj = reachableObject("what you want to close", params[0]);
  if (obj != NULL) printf("%s", (*obj->close)());
  return true;
}

int executeLock(void)
{
  OBJECT *obj = reachableObject("what you want to lock", params[0]);
  if (obj != NULL) printf("%s", (*obj->lock)());
  return true;
}

int executeUnlock(void)
{
  OBJECT *obj = reachableObject("what you want to unlock", params[0]);
  if (obj != NULL) printf("%s", (*obj->unlock)());
  return true;
}
