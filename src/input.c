#include "input.h"

bool read_events(Game *game) {

    SDL_Event event;

    while (SDL_PollEvent(&event) != 0) {

        switch (event.type) {
            case SDL_QUIT:
                return true;
            case SDL_MOUSEMOTION:
                mouse_move_event(event, game);
                break;
            case SDL_MOUSEBUTTONDOWN:
                mouse_down_event(event, game);
                break;
            default:
                break;
        }
    }

    return false;
}

void mouse_move_event(SDL_Event event, Game *game) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    game->board->hover_field = point_to_field(x, y, game->board);
}

void mouse_down_event(SDL_Event event, Game *game) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    game->board->hover_field = point_to_field(x, y, game->board);

    Player *player = game->players[game->active_player_index];

    if (!is_actionable(game->board, game->board->hover_field.x, game->board->hover_field.y, player, game->state)) {
        return ;
    }

    Field *field = &game->board->fields[game->board->hover_field.x][game->board->hover_field.y];

    if (game->state == START) {
        field->owner = player->id;
        field->force = 3;
        push(player->fields_stack, game->board->hover_field);
        next_turn(game);
        return;
    } else if (game->state == REINFORCEMENT) {
//         TODO Add different buttons

        field->force++;
        player->reinforcements--;

        if (player->reinforcements <= 0) {
            game->state = MOVE;
        }
    } else if (game->state == MOVE) {
        if (field->owner == player->id) {
            field->force += 2;
            next_turn(game);
        }
        else if (field->owner == 0) {
            field->owner = player->id;

            int attack_power = 0;

            PairItem *pair_item = player->fields_stack->top;
            while (pair_item != NULL) {
                if (is_neighbour(game->board->hover_field.x, game->board->hover_field.y, pair_item->pair.x, pair_item->pair.y)) {
                    attack_power += game->board->fields[pair_item->pair.x][pair_item->pair.y].force;
                }
                pair_item = pair_item->prev;
            }

            push(player->fields_stack, game->board->hover_field);
            field->force = max(1, attack_power/2);

            next_turn(game);
        }
        else if (field->owner != player->id) {
            int attack_power = 0;

            PairItem *pair_item = player->fields_stack->top;
            while (pair_item != NULL) {
                if (is_neighbour(game->board->hover_field.x, game->board->hover_field.y, pair_item->pair.x, pair_item->pair.y)) {
                    attack_power += floor(game->board->fields[pair_item->pair.x][pair_item->pair.y].force / 2.0);
                    game->board->fields[pair_item->pair.x][pair_item->pair.y].force = ceil(game->board->fields[pair_item->pair.x][pair_item->pair.y].force / 2.0);
                }
                pair_item = pair_item->prev;
            }

            int defense_power = field->force;

//            TODO Simulate dices roll

            int temp_attack_power = attack_power;
            int temp_defense_power = defense_power;

            attack_power -= temp_defense_power;
            defense_power -= temp_attack_power;

            if (attack_power > 0) {
                Player *opponent = game->players[field->owner-1];

                erase(opponent->fields_stack, game->board->hover_field);

                field->owner = player->id;
                field->force = attack_power;
                push(player->fields_stack, game->board->hover_field);

                if (opponent->fields_stack->size <= 0) {
                    opponent->active = false;

                    int won = true;
                    for (int i = 0; i < game->players_size; i++) {
                        if (i != game->active_player_index && game->players[i]->active == true) {
                            won = false;
                        }
                    }

                    if (won) printf("WIN\n");
                }
            }
            else {
                field->force = defense_power;
            }

            next_turn(game);
        }
    }


}