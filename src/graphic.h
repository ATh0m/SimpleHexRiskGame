#ifndef SIMPLEHEXRISKGAME_GRAPHIC_H
#define SIMPLEHEXRISKGAME_GRAPHIC_H

#include "defs.h"
#include "utility.h"

TTF_Font *font_default;
TTF_Font *font_header;
TTF_Font *font_small;
TTF_Font *font_field;
TTF_Font *font_description;

typedef struct Graphic {
    SDL_Window *window;
    SDL_Renderer *renderer;

    int width, height;
} Graphic;

Graphic *create_graphic(int width, int height);

void delete_graphic(Graphic *graphic);

void update_graphic_size(Graphic *graphic);

SDL_Window *create_window(int width, int height);

SDL_Renderer *create_renderer(SDL_Window *window);

void draw_filled_hex(SDL_Renderer *renderer, int x, int y, int size, Color color);

void draw_hex(SDL_Renderer *renderer, int x, int y, int size, Color color);

void display_text(SDL_Renderer *renderer, char *text, Color color, int x, int y, TTF_Font *font);

void display_message(Graphic *graphic, char *text, Color color, int x, int y, TTF_Font *font);

#endif