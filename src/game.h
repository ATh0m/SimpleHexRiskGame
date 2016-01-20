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

/**
 * Tworzy nową strukturę {Game}, alokuje pamięć i ustawia domyślne wartości
 */
Game *create_game(Graphic *graphic);

/**
 * Czyści strukturę {Game} i zwalnia pamięć
 */
void delete_game(Game *game);

/**
 * Ustawia domyślne wartości w strukturze {Game}
 */
void reset_game(Game *game);

/**
 * Tworzy nową plansze {Board}
 */
Board *generate_new_game_board();

/**
 * Główna funkcja rysująca
 */
void draw_game(SDL_Renderer *renderer, Game *game);

/**
 * Następna tura
 */
void next_turn(Game *game);

/**
 * Wypisywanie instrukcji dla gracza
 */
void display_player_instructions(Game *game, SDL_Renderer *renderer);

/**
 * Rysowanie planszy {Board}
 */
void display_game_board(Game *game, SDL_Renderer *renderer);

/**
 * Wyświetlanie powitalnej wiadomości
 */
void display_splash_screen(Game *game, SDL_Renderer *renderer);

#endif //SIMPLEHEXRISKGAME_GAME_H
