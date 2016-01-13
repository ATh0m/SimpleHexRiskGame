#include "game.h"

Game *create_game(Graphic *graphic) {

    Game *new_game = malloc(sizeof(Game));
    new_game->graphic = graphic;

    int width = rand() % 5 + 7;
    int height = rand() % 5 + 7;

    int **tab = generate_fields_tab(width, height);

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

    int width = rand() % 5 + 7;
    int height = rand() % 5 + 7;

    int **tab = generate_fields_tab(width, height);

    game->board = create_board(width, height, tab);

    delete_generated_fields_tab(tab, width, height);
}

void draw_game(SDL_Renderer *renderer, Game *game) {
    SDL_SetRenderDrawColor(renderer, game->backgroun_color.r, game->backgroun_color.g, game->backgroun_color.b,
                           game->backgroun_color.a);
    SDL_RenderClear(renderer);

    update_graphic_size(game->graphic);

    if (game->state == CREATE) {
        display_splash_screen(game, renderer);
    }
    else {

        update_field_info(renderer, game->board);
        Player *player = game->players->list[game->players->active_player_index];

        display_game_board(game, renderer);

        display_player_instructions(game, renderer);

        if (game->state == WIN) {
            char message[200];
            sprintf(message, "Gracz %s wygrał. Kliknij, aby zacząć od nowa", player->name);
            display_message(game->graphic, message, player->action_color, game->graphic->width / 2,
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

void display_player_instructions(Game *game, SDL_Renderer *renderer) {

    char message[200];
    Player *player = game->players->list[game->players->active_player_index];

    switch (game->state) {
        case START:
            sprintf(message, "Gracz %s wybierz swoje startowe pole", player->name);
            display_text(renderer, message, player->action_color, game->graphic->width / 2,
                         game->graphic->height - 45, font_default);
            if (!player->ai) {
                display_text(renderer, "Wybierz dowolne, wolne pole jako twój startowy teren",
                             create_color(128, 128, 128, 255), game->graphic->width / 2, game->graphic->height - 20,
                             font_small);
            }
            break;
        case REINFORCEMENT:
            sprintf(message, "Gracz %s rozstaw swoje siły. Pozostało %d", player->name, player->reinforcements);
            display_text(renderer, message, player->action_color, game->graphic->width / 2,
                         game->graphic->height - 45, font_default);
            if (!player->ai) {
                display_text(renderer,
                             "Wybierz swoje pole, które chcesz wzmocnić. Kliknięcie prawym przyciskiem dodaje całą, pozostałą siłę",
                             create_color(128, 128, 128, 255), game->graphic->width / 2, game->graphic->height - 20,
                             font_small);
            }
            break;
        case MOVE:
            sprintf(message, "Gracz %s wykonaj ruch", player->name);
            display_text(renderer, message, player->action_color, game->graphic->width / 2,
                         game->graphic->height - 45, font_default);
            if (!player->ai) {
                display_text(renderer, "Dołącz neutralne pole, zaatakuj wroga lub wzmocnij swój teren",
                             create_color(128, 128, 128, 255), game->graphic->width / 2, game->graphic->height - 20,
                             font_small);
            }
            break;
        default:
            break;
    }
}

void display_game_board(Game *game, SDL_Renderer *renderer) {
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

                if (!player->ai) {
                    if (is_actionable(game->board, x, y, player, game->state)) {
                        if (!player->ai && game->board->hover_field != NULL) {
                            if (x == game->board->hover_field->x && y == game->board->hover_field->y) {
                                draw_filled_hex(renderer, point.x, point.y, game->board->field_size - 2,
                                                hover_color);
                            }
                        }
                        draw_hex(renderer, point.x, point.y, game->board->field_size - 1, action_color);
                    }
                }

                if (game->board->fields[x][y].owner > 0) {
                    char force[10];
                    sprintf(force, "%d", game->board->fields[x][y].force);
                    display_text(renderer, force, create_color(0, 0, 0, 255), point.x, point.y, font_default);
                }
            }
        }
    }
}

void display_splash_screen(Game *game, SDL_Renderer *renderer) {
    display_text(renderer, "SIMPLEHEXRISKGAME", create_color(128, 128, 128, 255), game->graphic->width / 2,
                 game->graphic->height / 2 - 130, font_header);
    display_text(renderer,
                 "Jest to prosta gra strategiczna podobna do Ryzyko. Twoim celem jest wyeliminowanie pozostałych wrogów.",
                 create_color(128, 128, 128, 255), game->graphic->width / 2, game->graphic->height / 2 - 70,
                 font_small);
    display_text(renderer, "Przejmuj neutralne i wrogie tereny, aby zwiększac swoją siłę",
                 create_color(128, 128, 128, 255), game->graphic->width / 2, game->graphic->height / 2 - 50,
                 font_small);
    display_text(renderer,
                 "Kiedy przejmiesz pusty teren jego siła będzie wynosiła połowę siły sąsiednich, przyjaznych terenów.",
                 create_color(128, 128, 128, 255), game->graphic->width / 2, game->graphic->height / 2 - 30,
                 font_small);
    display_text(renderer, "Kiedy atakujesz, wykorzystujesz w bitwie połowę siły sąsiednich, przyjaznych pól.",
                 create_color(128, 128, 128, 255), game->graphic->width / 2, game->graphic->height / 2 - 10,
                 font_small);
    display_text(renderer, "Mapa jest generowana losowo.",
                 create_color(128, 128, 128, 255), game->graphic->width / 2, game->graphic->height / 2 + 10,
                 font_small);

    display_text(renderer, "Wybierz liczbę graczy, którzy wezmą udział w potyczce.", create_color(128, 128, 128, 255),
                 game->graphic->width / 2, game->graphic->height / 2 + 50, font_small);
    display_text(renderer, "Nad resztą kontrolę przejmie komputer.", create_color(128, 128, 128, 255),
                 game->graphic->width / 2, game->graphic->height / 2 + 70, font_small);

    display_text(renderer, "0", create_color(128, 128, 128, 255), game->graphic->width / 2 - 150,
                 game->graphic->height / 2 + 130, font_header);
    display_text(renderer, "1", create_color(128, 128, 128, 255), game->graphic->width / 2 - 75,
                 game->graphic->height / 2 + 130, font_header);
    display_text(renderer, "2", create_color(128, 128, 128, 255), game->graphic->width / 2,
                 game->graphic->height / 2 + 130, font_header);
    display_text(renderer, "3", create_color(128, 128, 128, 255), game->graphic->width / 2 + 75,
                 game->graphic->height / 2 + 130, font_header);
    display_text(renderer, "4", create_color(128, 128, 128, 255), game->graphic->width / 2 + 150,
                 game->graphic->height / 2 + 130, font_header);
}