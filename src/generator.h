//
// Created by Tomasz Nanowski on 11.01.2016.
//

#ifndef SIMPLEHEXRISKGAME_GENERATOR_H
#define SIMPLEHEXRISKGAME_GENERATOR_H

#include "defs.h"
#include "utility.h"
#include "board.h"

int **generate_fields_tab(int width, int height);

void fix_fields_tab(int **fields_tab, int width, int height);

void erase_another_colors(int **fields_tab, int width, int height, int color);

int count_fields_color(int **fields_tab, int width, int height, int color);

int normalize_fields_tab(int **fields_tab, int width, int height);

int count_different_fields(int **fields_tab, int width, int height, int x, int y);

int color_fields_tab(int **fields_tab, int width, int height);

void color_fields(int **fields_tab, int width, int height, int x, int y, int color);

void format_fields_tab(int **fields_tab, int width, int height);

void print_fields_tab(int **fields_tab, int width, int height);

void delete_generated_fields_tab(int **fields_tab, int width, int height);

#endif //SIMPLEHEXRISKGAME_GENERATOR_H
