#ifndef SIMPLEHEXRISKGAME_GAME_H
#define SIMPLEHEXRISKGAME_GAME_H

#include "defs.h"
#include "utility.h"
#include "board.h"
#include "player.h"

typedef struct Game {
    Board *board;
    Player **players;

    int activ_player_index;

    enum State state;

    Color backgroun_color;
} Game;

Game *create_game();

void draw_game(SDL_Renderer *renderer, Game *game);

#endif //SIMPLEHEXRISKGAME_GAME_H
