#ifndef SIMPLEHEXRISKGAME_PLAYER_H
#define SIMPLEHEXRISKGAME_PLAYER_H

#include "defs.h"
#include "utility.h"

typedef struct Player {
	char* name;
	int id;

	bool active;
	bool ai;

	// TO DO List fields

	Color field_color;
	Color hover_color;
	Color action_color;
} Player;

Player *create_player(char *name, int id, bool active, bool ai, Color field_color, Color hover_color, Color action_color);

#endif