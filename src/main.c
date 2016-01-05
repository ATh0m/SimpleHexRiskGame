#include "main.h"

int main(int argc, char **argv) {

    SDL_Window *window = create_window(640, 480);
    SDL_Renderer *renderer = crete_renderer(window);
    enum Status status;

    int quit = false;
    SDL_Event e;

    int tab[5][4] = {{1, 1, 0, 1},
                     {1, 0, 0, 1},
                     {1, 1, 1, 1},
                     {1, 0, 1, 0},
                     {1, 0, 1, 0}};
    Board *board = create_board(5, 4, tab);

    Player *players[3];

    players[0] = malloc(sizeof(Player));
    players[0]->name = strdup("Red");
    players[0]->id = 0;
    players[0]->active = false;
    players[0]->ai = false;
    players[0]->field_color = create_color(255, 255, 255, 255);
    players[0]->hover_color = create_color(0, 0, 0, 0);
    players[0]->action_color = create_color(0, 0, 0, 0);

    board->status = START;

    while (!quit) {

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_MOUSEMOTION) {
                int x, y;
                SDL_GetMouseState(&x, &y);

                board->hover_field = point_to_field(x, y, board);
            }
        }

        draw(renderer, board);

        SDL_Delay(10);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}

void draw(SDL_Renderer *renderer, Board *board) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    draw_board(renderer, board);

    SDL_RenderPresent(renderer);
}