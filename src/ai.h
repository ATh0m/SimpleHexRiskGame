//
// Created by Tomasz Nanowski on 10.01.2016.
//
#ifndef SIMPLEHEXRISKGAME_AI_H
#define SIMPLEHEXRISKGAME_AI_H

#include "defs.h"
#include "utility.h"
#include "player.h"
#include "board.h"


bool ai_action(Player *player, Board *board, Players *players, enum State *state);

bool ai_start(Player *player, Board *board);

void ai_reinforcement(Player *player, Board *board, enum State *state, PairStack *fields_adjacent_enemies,
                      PairStack *fields_adjacent_neutrals);

bool ai_move(Player *player, Board *board, enum State *state, Players *players, PairStack *fields_adjacent_enemies,
             PairStack *fields_adjacent_neutrals);

void create_fields_adjacent(PairStack *fields_adjacent_enemies, PairStack *fields_adjacent_neutrals, Player *player,
                            Board *board);

#endif //SIMPLEHEXRISKGAME_AI_H
