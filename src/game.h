#ifndef SIMPLEHEXRISKGAME_GAME_H
#define SIMPLEHEXRISKGAME_GAME_H

#include "defs.h"
#include "utility.h"
#include "board.h"
#include "player.h"
#include "ai.h"
#include "graphic.h"

typedef struct Game {
    Board *board;

    Players *players;

    enum State state;

    Graphic *graphic;

    Color backgroun_color;
} Game;

Game *create_game(Graphic *graphic);

void draw_game(SDL_Renderer *renderer, Game *game);

void next_turn(Game *game) ;

#endif //SIMPLEHEXRISKGAME_GAME_H
