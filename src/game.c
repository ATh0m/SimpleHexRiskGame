#include "game.h"

Game *create_game() {

    Game *new_game = malloc(sizeof(Game));

    int tab[5][4] = {{1, 1, 0, 1},
                     {1, 0, 0, 1},
                     {1, 1, 1, 1},
                     {1, 0, 1, 0},
                     {1, 0, 1, 0}};

    new_game->board = create_board(5, 4, tab);

    new_game->players = malloc(2 * sizeof(Player*));
    new_game->players_size = 2;

    new_game->players[0] = create_player("Red", 1, true, false, create_color(255, 204, 204, 255), create_color(255, 102, 102, 255), create_color(255, 51, 51, 255));
    new_game->players[1] = create_player("Blue", 2, true, false, create_color(51, 51, 255, 255), create_color(153, 153, 255, 255), create_color(0, 0, 204, 255));

    new_game->backgroun_color = create_color(0, 0, 0, 255);

    new_game->active_player_index = rand() % new_game->players_size;
    new_game->active_players_amount = new_game->players_size;

    return new_game;
}

void draw_game(SDL_Renderer *renderer, Game *game) {
    SDL_SetRenderDrawColor(renderer, game->backgroun_color.r, game->backgroun_color.g, game->backgroun_color.b, game->backgroun_color.a);
    SDL_RenderClear(renderer);

    update_field_info(renderer, game->board);

    for (int x = 0; x < game->board->width; x++) {
        for (int y = 0; y < game->board->height; y++) {
            if (game->board->fields[x][y].owner >= 0) {

                Color filed_color = game->board->fields[x][y].owner == 0 ? create_color(128, 128, 128, 255) : game->players[game->board->fields[x][y].owner-1]->field_color;

                Pair point = field_to_point(x, y, game->board);
                draw_filled_hex(renderer, point.x, point.y, game->board->field_size - 2, filed_color);

                Player *player = game->players[game->active_player_index];

                Color hover_color = player->hover_color;
                Color action_color = player->action_color;

                if (is_actionable(game->board, x, y, player, game->state)) {
                    if (x == game->board->hover_field.x && y == game->board->hover_field.y) {
                        draw_filled_hex(renderer, point.x, point.y, game->board->field_size - 2, hover_color);
                    }
                    draw_hex(renderer, point.x, point.y, game->board->field_size, action_color);
                }

                if (game->board->fields[x][y].owner > 0) {
                    char force[10];
                    sprintf(force, "%d", game->board->fields[x][y].force);
                    stringRGBA(renderer, point.x, point.y, force, 0, 0, 0, 255);
                }
            }
        }
    }

    SDL_RenderPresent(renderer);
}

void next_turn(Game *game) {

    do {
        game->active_player_index++;
        if (game->active_player_index >= game->players_size) game->active_player_index = 0;
    } while (!game->players[game->active_player_index]->active);

    Player *player = game->players[game->active_player_index];

    if (player->fields_stack->size == 0) {
        game->state = START;
    }
    else if (player->fields_stack->size > 0) {
        player->reinforcements = max(2, player->fields_stack->size / 3);
        game->state = REINFORCEMENT;
    }

    if (player->ai) {
        // TODO AI turn
        ;
    }
}