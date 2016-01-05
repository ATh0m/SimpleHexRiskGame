#ifndef SIMPLEHEXRISKGAME_INPUT_H
#define SIMPLEHEXRISKGAME_INPUT_H

#include "defs.h"
#include "game.h"
#include "board.h"
#include "player.h"

bool read_events(Game *game);

void mouse_move_event(SDL_Event event, Game *game);

void mouse_down_event(SDL_Event event, Game *game);

#endif