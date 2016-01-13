#include "main.h"

int main(int argc, char **argv) {

    srand((unsigned int) time(NULL));

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    Graphic *graphic = create_graphic(WINDOW_WIDTH, WINDOW_HEIGHT);
    Game *game = create_game(graphic);

    int quit = false;

    while (!quit) {

        quit = read_events(game);

        draw_game(graphic->renderer, game);

        SDL_Delay(16);
    }

    delete_game(game);
    delete_graphic(graphic);

    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}