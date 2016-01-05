#ifndef MAIN_H
#define MAIN_H

#include "defs.h"
#include "utility.h"
#include "graphic.h"
#include "board.h"
#include "player.h"

void draw(SDL_Renderer *renderer, Board *board);

int main(int argc, char **argv);

#endif