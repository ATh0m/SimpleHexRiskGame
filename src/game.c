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

    new_game->state = CREATE;

    return new_game;
}

void draw_game(SDL_Renderer *renderer, Game *game) {
    SDL_SetRenderDrawColor(renderer, game->backgroun_color.r, game->backgroun_color.g, game->backgroun_color.b, game->backgroun_color.a);
    SDL_RenderClear(renderer);

    update_field_info(renderer, game->board);
    Player *player = game->players[game->active_player_index];

    for (int x = 0; x < game->board->width; x++) {
        for (int y = 0; y < game->board->height; y++) {
            if (game->board->fields[x][y].owner >= 0) {

                Color filed_color = game->board->fields[x][y].owner == 0 ? create_color(128, 128, 128, 255) : game->players[game->board->fields[x][y].owner-1]->field_color;

                Pair point = field_to_point(x, y, game->board);
                draw_filled_hex(renderer, point.x, point.y, game->board->field_size - 2, filed_color);

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
                    display_text(renderer, force, create_color(255, 255, 255, 255), point.x, point.y);
                }
            }
        }
    }

    char message[200];

    switch (game->state) {
        case START:
            sprintf(message, "Gracz %s wybiersz swoje startowe pole", player->name);
            display_text(renderer, message, player->action_color, 320, 420);
            break;
        case REINFORCEMENT:
            sprintf(message, "Gracz %s rozstaw swoje sily. Pozostalo %d", player->name, player->reinforcements);
            display_text(renderer, message, player->action_color, 320, 420);
            break;
        case MOVE:
            sprintf(message, "Gracz %s wykonaj ruch", player->name);
            display_text(renderer, message, player->action_color, 320, 420);
            break;
        default:
            break;
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