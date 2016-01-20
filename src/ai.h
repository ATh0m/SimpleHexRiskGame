//
// Created by Tomasz Nanowski on 10.01.2016.
//
#ifndef SIMPLEHEXRISKGAME_AI_H
#define SIMPLEHEXRISKGAME_AI_H

#include "defs.h"
#include "utility.h"
#include "player.h"
#include "board.h"

/**
 * Zarządzanie akcjami SI
 */
bool ai_action(Player *player, Board *board, Players *players, enum State *state);

/**
 * Akcja wyboru startowego pola przez SI
 */
bool ai_start(Player *player, Board *board);

/**
 * Akcja wzmocnienia pól przez SI
 */
void ai_reinforcement(Player *player, Board *board, enum State *state, PairStack *fields_adjacent_enemies,
                      PairStack *fields_adjacent_neutrals);

/**
 * Akcja ruchu SI
 */
bool ai_move(Player *player, Board *board, enum State *state, Players *players, PairStack *fields_adjacent_enemies,
             PairStack *fields_adjacent_neutrals);

/**
 * Tworzenie stosów {PairStack} z polami sąsiadującymi z przeciwnikami, neutralnymi
 */
void create_fields_adjacent(PairStack *fields_adjacent_enemies, PairStack *fields_adjacent_neutrals, Player *player,
                            Board *board);

#endif //SIMPLEHEXRISKGAME_AI_H
