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

#define PLAYER1 "Red", 1, true, players_amount < 1, create_color(255, 204, 204, 255), create_color(255, 102, 102, 255), create_color(255, 51, 51, 255)
#define PLAYER2 "Blue", 2, true, players_amount < 2, create_color(51, 51, 255, 255), create_color(153, 153, 255, 255), create_color(0, 0, 204, 255)
#define PLAYER3 "Green", 3, true, players_amount < 3, create_color(122, 216, 138, 255), create_color(78, 174, 95, 255), create_color(19, 86, 31, 255)
#define PLAYER4 "Yellow", 4, true, players_amount < 4, create_color(255, 248, 144, 255), create_color(227, 220, 102, 255), create_color(113, 107, 24, 255)

#endif