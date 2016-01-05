#ifndef SIMPLEHEXRISKGAME_GAME_H
#define SIMPLEHEXRISKGAME_GAME_H

#include "defs.h"
#include "utility.h"
#include "board.h"
#include "player.h"

typedef struct Game {
    Board *board;
    Player **players;
    int players_size;

    int active_player_index;
    int active_players_amount;

    enum State state;

    Color backgroun_color;
} Game;

Game *create_game();

void draw_game(SDL_Renderer *renderer, Game *game);

void next_turn(Game *game) ;

#endif //SIMPLEHEXRISKGAME_GAME_H
