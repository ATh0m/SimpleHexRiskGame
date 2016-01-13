//
// Created by Tomasz Nanowski on 11.01.2016.
//

#ifndef SIMPLEHEXRISKGAME_GENERATOR_H
#define SIMPLEHEXRISKGAME_GENERATOR_H

#include "defs.h"

int **generate_fileds_tab(int width, int height);

void delete_generated_fields_tab(int **fields_tab, int width, int height);

#endif //SIMPLEHEXRISKGAME_GENERATOR_H
