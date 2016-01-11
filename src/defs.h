#ifndef SIMPLEHEXRISKGAME_DEFS_H
#define SIMPLEHEXRISKGAME_DEFS_H

#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

TTF_Font *font_default;
TTF_Font *font_header;
TTF_Font *font_small;
TTF_Font *font_field;
TTF_Font *font_description;

enum State {
    CREATE,
    START,
    REINFORCEMENT,
    MOVE,
    WIN
};

enum Race {
    NEUTRAL,
    ENEMY,
    ALLY
};

#endif