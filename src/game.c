#include "game.h"

Game *create_game(Graphic *graphic) {

    Game *new_game = malloc(sizeof(Game));
    new_game->graphic = graphic;

    int tab[10][11] = { {0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0},
                      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                      {0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0},
                      {0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1},
                      {1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1},
                      {1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0},
                      {1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1},
                      {0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0},
                      {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0},
                      {0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1} };

    new_game->board = create_board(10, 11, tab);
    update_field_info(new_game->graphic->renderer, new_game->board);

    new_game->players = create_players();

    new_game->backgroun_color = create_color(0, 0, 0, 255);

    new_game->players->active_player_index = rand() % new_game->players->players_size;
    new_game->players->active_players_amount = new_game->players->players_size;

    new_game->state = CREATE;

    return new_game;
}

void draw_game(SDL_Renderer *renderer, Game *game) {
    SDL_SetRenderDrawColor(renderer, game->backgroun_color.r, game->backgroun_color.g, game->backgroun_color.b, game->backgroun_color.a);
    SDL_RenderClear(renderer);

    update_field_info(renderer, game->board);
    Player *player = game->players->list[game->players->active_player_index];

    for (int x = 0; x < game->board->width; x++) {
        for (int y = 0; y < game->board->height; y++) {
            if (game->board->fields[x][y].owner >= 0) {

                Color filed_color = game->board->fields[x][y].owner == 0 ? create_color(128, 128, 128, 255) : game->players->list[game->board->fields[x][y].owner-1]->field_color;

                Pair point = field_to_point(x, y, game->board);
                draw_filled_hex(renderer, point.x, point.y, game->board->field_size - 2, filed_color);

                Color hover_color = player->hover_color;
                Color action_color = player->action_color;

                if (is_actionable(game->board, x, y, player, game->state)) {
                    if (game->board->hover_field != NULL) {
//                        printf("%d %d\n", game->board->hover_field->x, game->board->hover_field->y);
                        if (x == game->board->hover_field->x && y == game->board->hover_field->y) {
                            draw_filled_hex(renderer, point.x, point.y, game->board->field_size - 2, hover_color);
                        }
                    }
                    draw_hex(renderer, point.x, point.y, game->board->field_size, action_color);
                }

                if (game->board->fields[x][y].owner > 0) {
                    char force[10];
                    sprintf(force, "%d", game->board->fields[x][y].force);
                    display_text(renderer, force, create_color(255, 255, 255, 255), point.x, point.y);
                }
            }
        }
    }

    char message[200];

    switch (game->state) {
        case START:
            sprintf(message, "Gracz %s wybiersz swoje startowe pole", player->name);
            display_text(renderer, message, player->action_color, 480, 860);
            break;
        case REINFORCEMENT:
            sprintf(message, "Gracz %s rozstaw swoje sily. Pozostalo %d", player->name, player->reinforcements);
            display_text(renderer, message, player->action_color, 480, 860);
            break;
        case MOVE:
            sprintf(message, "Gracz %s wykonaj ruch", player->name);
            display_text(renderer, message, player->action_color, 480, 860);
            break;
        default:
            break;
    }

    SDL_RenderPresent(renderer);
}

void next_turn(Game *game) {

    do {
        game->players->active_player_index++;
        if (game->players->active_player_index >= game->players->players_size) game->players->active_player_index = 0;
    } while (!game->players->list[game->players->active_player_index]->active);

    Player *player = game->players->list[game->players->active_player_index];

    if (player->fields_stack->size == 0) {
        game->state = START;
    }
    else if (player->fields_stack->size > 0) {
        player->reinforcements = max(2, player->fields_stack->size / 3);
        game->state = REINFORCEMENT;
    }

//    if (player->ai) {
//        // TODO AI turn
//        ai_action(player, game->board, game->players, &game->state);
//        next_turn(game);
//    }
}