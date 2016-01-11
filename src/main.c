#include "main.h"

int main(int argc, char **argv) {

    srand(time(NULL));

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    Graphic *graphic = create_graphic(850, 475);

    Game *game = create_game(graphic);

//    game->state = START;

    int quit = false;

    while (!quit) {

        quit = read_events(game);

        draw_game(graphic->renderer, game);

        SDL_Delay(16);
    }

    SDL_DestroyWindow(graphic->window);
    SDL_Quit();

    return EXIT_SUCCESS;
}