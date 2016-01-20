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

/**
 * Tworzy nową strukturę {Graphic}, alokuje pamięć i ustawia domyślne wartości
 */
Graphic *create_graphic(int width, int height);

/**
 * Czyści strukturę {Graphic} i zwalnia pamięć
 */
void delete_graphic(Graphic *graphic);

/**
 * Aktualizuje rozmiar okna w strukturze {Graphic}
 */
void update_graphic_size(Graphic *graphic);

/**
 * Tworzy nowe okno {SDL_Window} o zadanym rozmiarze
 */
SDL_Window *create_window(int width, int height);

/**
 * Tworzy nowy renderer {SDL_Renderer} na podstawie podanego okna
 */
SDL_Renderer *create_renderer(SDL_Window *window);

/**
 * Rysuje wypełniony hexagon o podanym kolorze i środku w zadanym punkcie
 */
void draw_filled_hex(SDL_Renderer *renderer, int x, int y, int size, Color color);

/**
 * Rysuje pusty hexagon o podanym kolorze i środku w zadanym punkcie
 */
void draw_hex(SDL_Renderer *renderer, int x, int y, int size, Color color);

/**
 * Rysuje tekst o podanym kolorze, czcionce i środku w zadanym punkcie
 */
void display_text(SDL_Renderer *renderer, char *text, Color color, int x, int y, TTF_Font *font);

/**
 * Rysuje prostokąt na całej szerokosi ekranu i środku w zadanym punkcie, a w nim
 * rysuje tekst o podanym kolorze, czcionce i środku w zadanym punkcie
 */
void display_message(Graphic *graphic, char *text, Color color, int x, int y, TTF_Font *font);

#endif