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
    new_player->reinforcements = 0;

    new_player->fields_stack = create_pair_stack();

    return new_player;
}

void delete_player(Player *player) {
    free(player->name);
    delete_pair_stack(player->fields_stack);
    free(player);
}

Players *create_players(int players_amount) {
    Players *new_players = malloc(sizeof(Players));

    new_players->list = malloc(4 * sizeof(Player*));
    new_players->players_size = 4;

    new_players->list[0] = create_player("Red", 1, true, players_amount < 1, create_color(255, 204, 204, 255), create_color(255, 102, 102, 255), create_color(255, 51, 51, 255));
    new_players->list[1] = create_player("Blue", 2, true, players_amount < 2, create_color(51, 51, 255, 255), create_color(153, 153, 255, 255), create_color(0, 0, 204, 255));
    new_players->list[2] = create_player("Green", 3, true, players_amount < 3, create_color(122, 216, 138, 255), create_color(78, 174, 95, 255), create_color(19, 86, 31, 255));
    new_players->list[3] = create_player("Yellow", 4, true, players_amount < 4, create_color(255, 248, 144, 255), create_color(227, 220, 102, 255), create_color(113, 107, 24, 255));

    new_players->active_player_index = rand() % new_players->players_size;
    new_players->active_players_amount = new_players->players_size;

    return new_players;
}

void delete_players(Players *players) {
    for(int i = 0; i < players->players_size; i++) {
        delete_player(players->list[i]);
    }

    free(players);
}

bool player_action(Player *player, Field *field, Board *board, enum State *state, Players *players) {
    bool end_turn = false;

    switch (*state) {
        case START:
            end_turn = player_start(player, field);
            break;
        case REINFORCEMENT:
            player_reinforcement(player, field, state);
            break;
        case MOVE:
            end_turn = player_move(player, field, board, state, players);
            break;
        default:
            break;
    }

    return end_turn;
}

bool player_start(Player *player, Field *field) {
    field->owner = player->id;
    field->force = 3;
    push(player->fields_stack, field_to_pair(field));
    return true;
}

void player_reinforcement(Player *player, Field *field, enum State *state) {
    field->force++;
    player->reinforcements--;

    if (player->reinforcements <= 0) {
        *state = MOVE;
    }
}

bool player_move(Player *player, Field *field, Board *board, enum State *state, Players *players) {
    if (field->owner == player->id) {
        field->force += 2;
        return true;
    }
    else if (field->owner == 0) {
        field->owner = player->id;

        int attack_power = 0;
        PairItem *pair_item = player->fields_stack->top;
        while (pair_item != NULL) {
            if (is_neighbour(field->x, field->y, pair_item->pair.x, pair_item->pair.y)) {
                attack_power += board->fields[pair_item->pair.x][pair_item->pair.y].force;
            }
            pair_item = pair_item->prev;
        }

        push(player->fields_stack, field_to_pair(field));
        field->force = max(1, attack_power/2);

        return true;
    }
    else if (field->owner != player->id) {
        int attack_power = 0;

        PairItem *pair_item = player->fields_stack->top;
        while (pair_item != NULL) {
            if (is_neighbour(field->x, field->y, pair_item->pair.x, pair_item->pair.y)) {
                attack_power += floor(board->fields[pair_item->pair.x][pair_item->pair.y].force / 2.0);
                board->fields[pair_item->pair.x][pair_item->pair.y].force = ceil(board->fields[pair_item->pair.x][pair_item->pair.y].force / 2.0);
            }
            pair_item = pair_item->prev;
        }

        int defense_power = field->force;

        Pair result = battle(attack_power, defense_power);

        attack_power = result.x;
        defense_power = result.y;

        if (attack_power > 0) {
            Player *opponent = players->list[field->owner-1];

            erase(opponent->fields_stack, field_to_pair(field));

            field->owner = player->id;
            field->force = attack_power;
            push(player->fields_stack, field_to_pair(field));

            if (opponent->fields_stack->size <= 0) {
                opponent->active = false;

                int won = true;
                for (int i = 0; i < players->players_size; i++) {
                    if (i != players->active_player_index && players->list[i]->active == true) {
                        won = false;
                    }
                }

                if (won) {
                    *state = WIN;
                }
            }
        }
        else {
            field->force = defense_power;
        }

        return *state != WIN;
    }

    return false;
}

bool is_actionable(Board *board, int x, int y, Player *player, enum State state) {
    if (x >= 0 && x < board->width && y >= 0 && y < board->height && board->fields[x][y].owner >= 0) {
        if (state == START) {
            if (board->fields[x][y].owner == 0) {
                return true;
            }
        }
        if (state == REINFORCEMENT || state == MOVE) {
            if (board->fields[x][y].owner == player->id) {
                return true;
            }
        }
        if (state == MOVE) {
            PairItem *pair_item = player->fields_stack->top;

            while (pair_item != NULL) {

                if (is_neighbour(x, y, pair_item->pair.x, pair_item->pair.y)) {
                    return true;
                }

                pair_item = pair_item->prev;
            }
        }
    }

    return false;
}


