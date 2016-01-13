#ifndef SIMPLEHEXRISKGAME_GAME_H
#define SIMPLEHEXRISKGAME_GAME_H

#include "defs.h"
#include "utility.h"
#include "board.h"
#include "player.h"
#include "ai.h"
#include "graphic.h"
#include "generator.h"

typedef struct Game {
    Board *board;

    Players *players;

    enum State state;

    Graphic *graphic;

    Color backgroun_color;
} Game;

Game *create_game(Graphic *graphic);

void delete_game(Game *game);

void reset_game(Game *game);

void draw_game(SDL_Renderer *renderer, Game *game);

void next_turn(Game *game);

void display_player_instructions(Game *game, SDL_Renderer *renderer);

void display_game_board(Game *game, SDL_Renderer *renderer);

void display_splash_screen(Game *game, SDL_Renderer *renderer);

#endif //SIMPLEHEXRISKGAME_GAME_H
