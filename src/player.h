#ifndef PLAYER_H
#define PLAYER_H

#include "defs.h"

typedef struct Player {
    char *name;
    int id;

    bool active;
    bool ai;

    // TO DO List fields

    Color field_color;
    Color hover_color;
    Color action_color;
} Player;

#endif