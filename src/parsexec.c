/*
Original code by Ruud Helderman ("How to program a text adventure in C")
For the game "THE SPIRIT WITHIN US" Alessandro Ielo added:
.executeQuit: the player can now select Yes or No. It shows the number of moves and remaining health.
.attack, defense, kill, drive, read, burn and eat added to the parser.
.endNumber and fox are controlled within the loop (check end.c and fox.c).
*/

#include <ctype.h>
#include <stdio.h>
#include "object.h"
#include "misc.h"
#include "match.h"
#include "location.h"
#include "inventory.h"
#include "inventory2.h"
#include "openclose.h"
#include "onoff.h"
#include "attack.h"
#include "end.h"
#include "fox.h"

typedef struct
{
  const char *pattern;
  int (*function)(void);
} COMMAND;

static int executeQuit(void)
{
  extern int moveCount;
  char buffer[4] = "0";

  printf("Are you sure? [Y] [N]\n");
  fgets(buffer, 4, stdin);

  if (buffer[0] == 'y' ||buffer[0] == 'Y')
  {
    printf("\nYour health is %d/100 ", player->health);
    printf("and you used %d moves.\n", moveCount - 1);
    printf("\nThank you for playing.\n\n");
    return -1;
  }
  printf("You resumed the game.\n");
  return 0;
}

static int executeWait(void)
{
  printf("Some time has passed.\n");
  return 1;
}

static int executeNoMatch(void)
{
  const char *src = *params;
  if (*src != '\0')
  {
    printf("I don't know how to '");
    while (*src != '\0' && !isspace(*src)) putchar(*src++);
    printf("'.\n");
  }
  return 0;
}

int parseAndExecute(const char *input)
{
  static const COMMAND commands[] =
  {
    { "quit"        , executeQuit       },
    { "die"         , executeQuit       },
    { "suicide"     , executeQuit       },
    { "look"        , executeLookAround },
    { "look around" , executeLookAround },
    { "look at A"   , executeLook       },
    { "look A"      , executeLook       },
    { "examine A"   , executeLook       },
    { "go to A"     , executeGo         },
    { "go A"        , executeGo         },
    { "follow A"    , executeGo         },
    { "exit A"      , executeGo         },
    { "run to A"    , executeGo         },
    { "run A"       , executeGo         },
    { "leave A"     , executeGo         },
    { "escape A"    , executeGo         },
    { "get A from B", executeGetFrom    },
    { "get A"       , executeGet        },
    { "hold A"      , executeGet        },
    { "take A from B", executeGetFrom   },
    { "take A"      , executeGet        },
    { "put A in B"  , executePutIn      },
    { "drop A in B" , executePutIn      },
    { "drop A"      , executeDrop       },
    { "give A to B" , executeGiveTo     },
    { "give A"      , executeGive       },
    { "inventory"   , executeInventory  },
    { "open A"      , executeOpen       },
    { "close A"     , executeClose      },
    { "lock A"      , executeLock       },
    { "unlock A"    , executeUnlock     },
    { "turn on A"   , executeTurnOn     },
    { "light A"     , executeTurnOn     },
    { "turn off A"  , executeTurnOff    },
    { "turn A on"   , executeTurnOn     },
    { "turn A off"  , executeTurnOff    },
    { "hit with B"  , executeAttack     },
    { "hit A with B", executeAttack     },
    { "hit A"       , executeAttack     },
    { "attack with B", executeAttack    },
    { "attack A with B", executeAttack  },
    { "attack A"    , executeAttack     },
    { "beat with B"  , executeAttack    },
    { "beat A with B", executeAttack    },
    { "beat A"      , executeAttack     },
    { "defend"      , executeDefense    },
    { "protect"     , executeDefense    },
    { "parry"       , executeDefense    },
    { "defend A"    , executeDefense    },
    { "protect A"   , executeDefense    },
    { "parry A"     , executeDefense    },
    { "kill A"      , executeKill       },
    { "murder A"    , executeKill       },
    { "terminate A" , executeKill       },
    { "assassinate A" , executeKill       },
    { "drive A"     , executeDrive      },
    { "read A"      , executeRead       },
    { "burn A"      , executeBurn       },
    { "eat A"       , executeEat        },
    { "drink A"     , executeEat        },
    { "swallow A"   , executeEat        },
    { "ingest A"    , executeEat        },
    { "wait"        , executeWait       },
    { "stay"        , executeWait       },
    { "use"         , executeUse        },
    { "use A"       , executeUse        },
    { "hi"          , executeGreets     },
    { "hello"       , executeGreets     },
    { "fuck"        , executeGreets     },
    { "fuck A"      , executeGreets     },
    { "wear"        , executeWear       },
    { "wear A"      , executeWear       },
    { "put on A"    , executeWear       },
    { "put A on"    , executeWear       },
    { "why"         , executeQuestion   },
    { "why A"       , executeQuestion   },
    { "help"        , executeManual     },
    { "manual"      , executeManual     },
    { "please"      , executeManual     },
    { "shout"       , executeVoice      },
    { "call"        , executeVoice      },
    { "call A"      , executeVoice      },
    { "scream"      , executeVoice      },
    { "yell"        , executeVoice      },
    { "say"         , executeVoice      },
    { "say A"       , executeVoice      },
    { "status"      , executeStatus     },
    { "information" , executeStatus     },
    { "life"        , executeStatus     },
    { "diagnostic"  , executeStatus     },
    { "score"       , executeStatus     },
    { "fullscore"   , executeStatus     },
    { "rest"        , executeRest       },
    { "sleep"       , executeRest       },
    { "relax"       , executeRest       },
    { "pause"       , executeRest       },
    { "pray"        , executeRest       },
    { "climb"       , executeNoEnergy   },
    { "climb A"     , executeNoEnergy   },
    { "jump"        , executeNoEnergy   },
    { "swim"        , executeNoEnergy   },
    { "jump A"      , executeNoEnergy   },
    { "throw"       , executeNoEnergy   },
    { "throw A"     , executeNoEnergy   },
    { "break A"     , executeNoEnergy   },
    { "play A"      , executeNoEnergy   },
    { "play with A" , executeNoEnergy   },
    { "listen"      , executeListen     },
    { "listen A"    , executeListen     },
    { "brief"       , executeVerbose    },
    { "superbrief"  , executeVerbose    },
    { "oops A"      , executeUndo       },
    { "undo A"      , executeUndo       },
    { "undo"        , executeUndo       },
    { "\0"          , executeWait       },
    { "A"           , executeNoMatch    }
  };
  endNumber();
  fox();
  const COMMAND *cmd;
  for (cmd = commands; !matchCommand(input, cmd->pattern); cmd++);
  return (*cmd->function)();
}
