#ifndef SIMPLEHEXRISKGAME_INPUT_H
#define SIMPLEHEXRISKGAME_INPUT_H

#include "defs.h"
#include "game.h"
#include "board.h"
#include "player.h"
#include "battle.h"

/**
 * Obsługa zdarzeń
 */
bool read_events(Game *game);

/**
 * Przesunięcie kursora
 */
void mouse_move_event(SDL_Event event, Game *game);

/**
 * Naciśnięcie przycisku na myszce
 */
void mouse_down_event(SDL_Event event, Game *game);

#endif