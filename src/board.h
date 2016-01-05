#ifndef BOARD_H
#define BOARD_H

#include "defs.h"
#include "utility.h"
#include "player.h"
#include "graphic.h"

typedef struct Field {
    int owner;
    int force;
} Field;

typedef struct Board {
    Field **fields;
    int width, height;

    int field_size;
    int field_width;
    int field_height;

    int offset_x;
    int offset_y;

    enum Status status;

    Pair hover_field;
} Board;

Pair point_to_field(int x, int y, Board *board);

Pair field_to_point(int x, int y, Board *board);

Board *create_board(int cols, int rows, int tab[cols][rows]);

bool is_actionable(Board *board, int x, int y, Player *player);

void draw_board(SDL_Renderer *renderer, Board *board);

#endif