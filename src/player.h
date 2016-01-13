#ifndef SIMPLEHEXRISKGAME_PLAYER_H
#define SIMPLEHEXRISKGAME_PLAYER_H

#include "defs.h"
#include "utility.h"
#include "board.h"
#include "battle.h"

typedef struct Player {
    char *name;
    int id;

    bool active;
    bool ai;

    PairStack *fields_stack;

    Color field_color;
    Color hover_color;
    Color action_color;

    int reinforcements;
} Player;

Player *create_player(char *name, int id, bool active, bool ai, Color field_color, Color hover_color,
                      Color action_color);

void delete_player(Player *player);

typedef struct Players {
    Player **list;

    int players_size;

    Player *active_player;
    int active_player_index;
    int active_players_amount;

} Players;

Players *create_players(int players_amount);

void delete_players(Players *players);

bool player_action(Player *player, Field *field, Board *board, enum State *state, Players *players, Uint8 button);

bool player_start(Player *player, Field *field);

void player_reinforcement(Player *player, Field *field, enum State *state, Uint8 button);

bool player_move(Player *player, Field *field, Board *board, enum State *state, Players *players);

bool is_actionable(Board *board, int x, int y, Player *player, enum State state);

#endif