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

/**
 * Tworzy nową strukturę {Player}, alokuje pamięć i ustawia domyślne wartości
 */
Player *create_player(char *name, int id, bool active, bool ai, Color field_color, Color hover_color,
                      Color action_color);

/**
 * Czyści strukturę {Player} i zwalnia pamięć
 */
void delete_player(Player *player);

typedef struct Players {
    Player **list;

    int players_size;

    Player *active_player;
    int active_player_index;
    int active_players_amount;

} Players;

/**
 * Tworzy nową strukturę {Players}, alokuje pamięć i ustawia domyślne wartości
 */
Players *create_players(int players_amount);

/**
 * Czyści strukturę {Players} i zwalnia pamięć
 */
void delete_players(Players *players);

/**
 * Zarządza akcjami gracza
 */
bool player_action(Player *player, Field *field, Board *board, enum State *state, Players *players, Uint8 button);

/**
 * Akcja wyboru startowego pola przez gracza
 */
bool player_start(Player *player, Field *field);

/**
 * Akcja wzmocnienia pól przez gracza
 */
void player_reinforcement(Player *player, Field *field, enum State *state, Uint8 button);

/**
 * Akcja ruchu gracza
 */
bool player_move(Player *player, Field *field, Board *board, enum State *state, Players *players);

/**
 * Sprawdza czy gracz może wykonać dana akcję na wskazanym polu
 *
 * @return true, jeśli może wykonac akcje
 * @return false, jeśli nie może
 */
bool is_actionable(Board *board, int x, int y, Player *player, enum State state);

#endif