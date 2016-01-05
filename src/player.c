#include "player.h"

Player *create_player(char *name, int id, bool active, bool ai, Color field_color, Color hover_color, Color action_color) {


    Player *new_player = malloc(sizeof(Player));

    new_player->name = strdup(name);
    new_player->id = id;
    new_player->active = active;
    new_player->ai = ai;
    new_player->field_color = field_color;
    new_player->hover_color = hover_color;
    new_player->action_color = action_color;

    return new_player;
}