#include "graphic.h"

SDL_Window *create_window(int width, int height) {
    SDL_Window *window = NULL;

    font = TTF_OpenFont("../src/font/Ubuntu-M.ttf", 20);

    window = SDL_CreateWindow(
            "SimpleHexRiskGame",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width,
            height,
            SDL_WINDOW_SHOWN);

    return window;
}

SDL_Renderer *crete_renderer(SDL_Window *window) {
    SDL_Renderer *renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    return renderer;
}

void draw_filled_hex(SDL_Renderer *renderer, int x, int y, int size, Color color) {

    const short vx[6] = {x - size, x - size, x, x + size, x + size, x};
    const short vy[6] = {y + size * 0.5, y - size * 0.5, y - size, y - size * 0.5, y + size * 0.5, y + size};

    filledPolygonRGBA(renderer, vx, vy, 6, color.r, color.g, color.b, color.a);
}

void draw_hex(SDL_Renderer *renderer, int x, int y, int size, Color color) {
    const short vx[6] = {x - size, x - size, x, x + size, x + size, x};
    const short vy[6] = {y + size * 0.5, y - size * 0.5, y - size, y - size * 0.5, y + size * 0.5, y + size};

    short last_x = vx[5];
    short last_y = vy[5];

    for (int i = 0; i < 6; i++) {
        thickLineRGBA(renderer, last_x, last_y, vx[i], vy[i], 5, color.r, color.g, color.b, color.a);

        last_x = vx[i];
        last_y = vy[i];
    }
}

void display_text(SDL_Renderer *renderer, char *text, Color color, int x, int y) {

    SDL_Color sdl_color = {color.r, color.g, color.b};

    if (font == NULL) {
        fprintf(stderr,
                "\nTTF_OpenFont Error:  %s\n",
                SDL_GetError());
        exit(1);
    }

    SDL_Surface* surface_message = TTF_RenderText_Solid(font, text, sdl_color);

    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surface_message);

    SDL_Rect Message_rect;
    Message_rect.x = x - surface_message->w / 2.0;
    Message_rect.y = y - surface_message->h / 2.0;
    Message_rect.w = surface_message->w;
    Message_rect.h = surface_message->h;

    SDL_RenderCopy(renderer, message, NULL, &Message_rect);

    SDL_FreeSurface(surface_message);
    SDL_DestroyTexture(message);

}

