#ifndef SIMPLEHEXRISKGAME_BOARD_H
#define SIMPLEHEXRISKGAME_BOARD_H

#include "defs.h"
#include "utility.h"
#include "graphic.h"

typedef struct Field {
    int owner;
    int force;
    int x, y;
} Field;

typedef struct Board {
    Field **fields;
    int width, height;

    int field_size;
    int field_width;
    int field_height;

    int offset_x;
    int offset_y;

    Field *hover_field;
} Board;

Pair point_to_pair(int x, int y, Board *board);

Field *pair_to_field(Pair pair, Board *board);

Field *point_to_field(int x, int y, Board *board);

Pair field_to_point(int x, int y, Board *board);

Pair field_to_pair(Field *field);

Field *random_field(PairStack *pair_stack, Board *board);

Board *create_board(int cols, int rows, int tab[cols][rows]);

bool is_neighbour(int x1, int y1, int x2, int y2);

bool has_neighbour(int x, int y, enum Race race, Board *board);

void update_field_info(SDL_Renderer *renderer, Board *board);

#endif