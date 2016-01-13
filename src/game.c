#include "game.h"

Game *create_game(Graphic *graphic) {

    Game *new_game = malloc(sizeof(Game));
    new_game->graphic = graphic;

    int width = rand() % 5 + 7;
    int height = rand() % 5 + 7;

    int **tab = generate_fileds_tab(width, height);

    new_game->board = create_board(width, height, tab);

    delete_generated_fields_tab(tab, width, height);

    new_game->players = NULL;

    update_field_info(new_game->graphic->renderer, new_game->board);

    new_game->backgroun_color = create_color(0, 0, 0, 255);

    new_game->state = CREATE;

    return new_game;
}

void delete_game(Game *game) {

    delete_board(game->board);
    delete_players(game->players);
    free(game);
}

void reset_game(Game *game) {
    game->state = CREATE;

    delete_players(game->players);
    game->players = NULL;

    delete_board(game->board);
    game->board = NULL;

//    int tab[10][11] = { {0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0},
//                        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//                        {0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0},
//                        {0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1},
//                        {1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1},
//                        {1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0},
//                        {1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1},
//                        {0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0},
//                        {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0},
//                        {0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1} };

    int width = rand() % 5 + 7;
    int height = rand() % 5 + 7;

    int **tab = generate_fileds_tab(width, height);

    game->board = create_board(width, height, tab);

    delete_generated_fields_tab(tab, width, height);
}

void draw_game(SDL_Renderer *renderer, Game *game) {
    SDL_SetRenderDrawColor(renderer, game->backgroun_color.r, game->backgroun_color.g, game->backgroun_color.b, game->backgroun_color.a);
    SDL_RenderClear(renderer);

    update_graphic_size(game->graphic);

    if (game->state == CREATE) {
        display_text(renderer, "SIMPLEHEXRISKGAME", create_color(128, 128, 128, 255), game->graphic->width/2, game->graphic->height/2-130, font_header);
        display_text(renderer, "Jest to prosta gra strategiczna podobna do Ryzyko. Twoim celem jest wyeliminowanie pozostalych wrogow.", create_color(128, 128, 128, 255), game->graphic->width/2, game->graphic->height/2-70, font_small);
        display_text(renderer, "Przejmuj neutralne i wrogie tereny, aby zwiekszac swoja sile", create_color(128, 128, 128, 255), game->graphic->width/2, game->graphic->height/2-50, font_small);
        display_text(renderer, "Kiedy przejmiesz pusty teren jego sila bedzie wynosila polowe sily sasiednich, przyjaznych terenow.", create_color(128, 128, 128, 255), game->graphic->width/2, game->graphic->height/2-30, font_small);
        display_text(renderer, "Kiedy atakujesz, wykorzystujesz w bitwie polowe sily sasiednich, przyjaznych pol.", create_color(128, 128, 128, 255), game->graphic->width/2, game->graphic->height/2-10, font_small);

        display_text(renderer, "Wybierz liczbe graczy, ktorzy wezma udzial w potyczce.", create_color(128, 128, 128, 255), game->graphic->width/2, game->graphic->height/2+50, font_small);
        display_text(renderer, "Nad reszta kontrole przejmie komputer.", create_color(128, 128, 128, 255), game->graphic->width/2, game->graphic->height/2+70, font_small);

        display_text(renderer, "0", create_color(128, 128, 128, 255), game->graphic->width/2 - 150, game->graphic->height/2+130, font_header);
        display_text(renderer, "1", create_color(128, 128, 128, 255), game->graphic->width/2 - 75, game->graphic->height/2+130, font_header);
        display_text(renderer, "2", create_color(128, 128, 128, 255), game->graphic->width/2, game->graphic->height/2+130, font_header);
        display_text(renderer, "3", create_color(128, 128, 128, 255), game->graphic->width/2 + 75, game->graphic->height/2+130, font_header);
        display_text(renderer, "4", create_color(128, 128, 128, 255), game->graphic->width/2 + 150, game->graphic->height/2+130, font_header);
    }
    else {

        update_field_info(renderer, game->board);
        Player *player = game->players->list[game->players->active_player_index];

        for (int x = 0; x < game->board->width; x++) {
            for (int y = 0; y < game->board->height; y++) {
                if (game->board->fields[x][y].owner >= 0) {

                    Color filed_color = game->board->fields[x][y].owner == 0 ? create_color(128, 128, 128, 255)
                                                                             : game->players->list[
                                                game->board->fields[x][y].owner - 1]->field_color;

                    Pair point = field_to_point(x, y, game->board);
                    draw_filled_hex(renderer, point.x, point.y, game->board->field_size - 2, filed_color);

                    Color hover_color = player->hover_color;
                    Color action_color = player->action_color;

                    if (is_actionable(game->board, x, y, player, game->state)) {
                        if (!player->ai && game->board->hover_field != NULL) {
                            if (x == game->board->hover_field->x && y == game->board->hover_field->y) {
                                draw_filled_hex(renderer, point.x, point.y, game->board->field_size - 2, hover_color);
                            }
                        }
                        draw_hex(renderer, point.x, point.y, game->board->field_size, action_color);
                    }

                    if (game->board->fields[x][y].owner > 0) {
                        char force[10];
                        sprintf(force, "%d", game->board->fields[x][y].force);
                        display_text(renderer, force, create_color(0, 0, 0, 255), point.x, point.y, font_default);
                    }
                }
            }
        }

        char message[200];

        switch (game->state) {
            case START:
                sprintf(message, "Gracz %s wybiersz swoje startowe pole", player->name);
                display_text(renderer, message, player->action_color, game->graphic->width / 2,
                             game->graphic->height - 30, font_default);
                break;
            case REINFORCEMENT:
                sprintf(message, "Gracz %s rozstaw swoje sily. Pozostalo %d", player->name, player->reinforcements);
                display_text(renderer, message, player->action_color, game->graphic->width / 2,
                             game->graphic->height - 30, font_default);
                break;
            case MOVE:
                sprintf(message, "Gracz %s wykonaj ruch", player->name);
                display_text(renderer, message, player->action_color, game->graphic->width / 2,
                             game->graphic->height - 30, font_default);
                break;
            default:
                break;
        }

        if (game->state == WIN) {
            boxRGBA (renderer, 0, game->graphic->height / 2 - 40, game->graphic->width, game->graphic->height / 2 + 40, 0, 0, 0, 170);

            sprintf(message, "Gracz %s wygral. Kliknij, aby zaczac od nowa", player->name);
            display_text(renderer, message, player->action_color, game->graphic->width / 2,
                         game->graphic->height / 2, font_default);
        }

    }

    SDL_RenderPresent(renderer);
}

void next_turn(Game *game) {

    if (game->state != CREATE && game->state != WIN) {
        do {
            game->players->active_player_index++;
            if (game->players->active_player_index >= game->players->players_size)
                game->players->active_player_index = 0;
        } while (!game->players->list[game->players->active_player_index]->active);

        Player *player = game->players->list[game->players->active_player_index];

        if (player->fields_stack->size == 0) {
            game->state = START;
        }
        else if (player->fields_stack->size > 0) {
            player->reinforcements = max(2, player->fields_stack->size / 3);
            game->state = REINFORCEMENT;
        }
    }

}