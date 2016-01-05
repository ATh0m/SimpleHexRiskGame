#ifndef SIMPLEHEXRISKGAME_DEFS_H
#define SIMPLEHEXRISKGAME_DEFS_H

#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



enum State {
    CREATE,
    START,
    REINFORCEMENT,
    MOVE,
    WIN
};

#endif