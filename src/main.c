#include "main.h"

int main(int argc, char **argv) {

    srand(time(NULL));

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    Graphic *graphic = create_graphic(960, 900);

    Game *game = create_game(graphic);

    game->state = START;

    next_turn(game);

    int quit = false;

    while (!quit) {

        quit = read_events(game);

        if (game->players->list[game->players->active_player_index]->ai) {
            if (ai_action(game->players->list[game->players->active_player_index], game->board, game->players, &game->state)) next_turn(game);
        }

        draw_game(graphic->renderer, game);

        SDL_Delay(16);
    }

    SDL_DestroyWindow(graphic->window);
    SDL_Quit();

    return EXIT_SUCCESS;
}