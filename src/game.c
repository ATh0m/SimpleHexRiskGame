#include "game.h"

Game *create_game() {

    Game *new_game = malloc(sizeof(Game));

    int tab[5][4] = {{1, 1, 0, 1},
                     {1, 0, 0, 1},
                     {1, 1, 1, 1},
                     {1, 0, 1, 0},
                     {1, 0, 1, 0}};

    new_game->board = create_board(5, 4, tab);

    new_game->players = malloc(4 * sizeof(Player*));

    new_game->players[0] = create_player("Red", 1, true, false, create_color(255, 204, 204, 255), create_color(255, 102, 102, 255), create_color(255, 51, 51, 255));
    new_game->players[1] = create_player("Blue", 2, true, false, create_color(51, 51, 255, 255), create_color(153, 153, 255, 255), create_color(0, 0, 204, 255));

    new_game->backgroun_color = create_color(0, 0, 0, 255);

    new_game->activ_player_index = 1;

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

                Player *player = game->players[game->activ_player_index];

                Color hover_color = player->hover_color;
                Color action_color = player->action_color;

                if (is_actionable(game->board, x, y, player, game->state)) {
                    if (x == game->board->hover_field.x && y == game->board->hover_field.y) {
                        draw_filled_hex(renderer, point.x, point.y, game->board->field_size - 2, hover_color);
                    }
                    draw_hex(renderer, point.x, point.y, game->board->field_size, action_color);
                }

                if (game->board->fields[x][y].force > 0) {
                    char force[10];
                    sprintf(force, "%d", game->board->fields[x][y].force);
                    stringRGBA(renderer, point.x, point.y, force, 0, 0, 0, 255);
                }
            }
        }
    }

    SDL_RenderPresent(renderer);
}