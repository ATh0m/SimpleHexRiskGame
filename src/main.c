#include "main.h"

int main(int argc, char **argv) {

    srand(time(NULL));

    SDL_Window *window = create_window(640, 480);
    SDL_Renderer *renderer = crete_renderer(window);

    int quit = false;

    Game *game = create_game();

    game->state = START;

    while (!quit) {

        quit = read_events(game);

        draw_game(renderer, game);

        SDL_Delay(16);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}