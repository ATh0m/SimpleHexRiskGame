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

    if (game->state != CREATE && game->state != WIN) {
        if (game->players->list[game->players->active_player_index]->ai) {
            if (ai_action(game->players->list[game->players->active_player_index], game->board, game->players,
                          &game->state))
                next_turn(game);
        }
    }

    return false;
}

void mouse_move_event(SDL_Event event, Game *game) {
    if (game->state != CREATE && game->state != WIN) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        game->board->hover_field = point_to_field(x, y, game->board);
    }
}

void mouse_down_event(SDL_Event event, Game *game) {
    int x, y;
    SDL_GetMouseState(&x, &y);

    if (game->state == CREATE) {
        int players_amount = -1;

        if (y >= game->graphic->height/2 + 130 - 40 && y <= game->graphic->height/2 + 130 + 40) {
            if (x >= game->graphic->width/2 - 150 - 40 && x <= game->graphic->width/2 - 150 + 40) {
                players_amount = 0;
            }
            else if (x >= game->graphic->width/2 - 75 - 40 && x <= game->graphic->width/2 - 75 + 40) {
                players_amount = 1;
            }
            else if (x >= game->graphic->width/2 - 40 && x <= game->graphic->width/2 + 40) {
                players_amount = 2;
            }
            else if (x >= game->graphic->width/2 + 75 - 40 && x <= game->graphic->width/2 + 75 + 40) {
                players_amount = 3;
            }
            else if (x >= game->graphic->width/2 + 150 - 40 && x <= game->graphic->width/2 + 150 + 40) {
                players_amount = 4;
            }
        }

        if (players_amount != -1) {
            game->players = create_players(players_amount);
            game->state = START;
        }


    }
    else if (game->state == WIN) {
        reset_game(game);
    }
    else {

        game->board->hover_field = point_to_field(x, y, game->board);

        Player *player = game->players->list[game->players->active_player_index];

        if (game->board->hover_field == NULL ||
            !is_actionable(game->board, game->board->hover_field->x, game->board->hover_field->y, player,
                           game->state)) {
            return;
        }

        Field *field = &game->board->fields[game->board->hover_field->x][game->board->hover_field->y];

        if (player_action(player, field, game->board, &game->state, game->players, event.button.button)) next_turn(game);

    }
}