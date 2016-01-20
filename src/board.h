#ifndef SIMPLEHEXRISKGAME_BOARD_H
#define SIMPLEHEXRISKGAME_BOARD_H

#include "defs.h"
#include "utility.h"
#include "graphic.h"

int odd[6][2];
int even[6][2];

typedef struct Field {
    int owner;
    int force;
    int x, y;
} Field;

typedef struct Board {
    Field **fields;
    int width, height;

    int field_size;
    int field_width;
    int field_height;

    int offset_x;
    int offset_y;

    Field *hover_field;
} Board;

/**
 * Konwertuje współrzędne x, y z ekranu do współrzędnych w tablicy
 *
 * @return {Pair} współrzędne w tablicy
 */
Pair point_to_pair(int x, int y, Board *board);

/**
 * Konwertuje parę współrzędnych z tablicy do pola
 *
 * @return NULL, jeśli pole o danych współrzędnych nie istnieje
 * @return {Field} pole, jeśli istnieje w tablicy
 */
Field *pair_to_field(Pair pair, Board *board);

/**
 * Konwertuje współrzędne x, y z ekranu do pola
 *
 * @return NULL, jeśli pole nie istnieje
 * @return {Field} pole, jeśli istnieje
 */
Field *point_to_field(int x, int y, Board *board);

/**
 * Konwertuje pole na współrzędne na ekranie
 *
 * @return {Pair} para współrzędnych na ekranie
 */
Pair field_to_point(int x, int y, Board *board);

/**
 * Konwertuje pole na wspołrzędne w tablicy
 *
 * @return {Pair} para współrzędnych w tablicy
 */
Pair field_to_pair(Field *field);

/**
 * Losuje pole w stosie pól
 *
 * @return {Field} losowe pole
 */
Field *random_field(PairStack *pair_stack, Board *board);

/**
 * Tworzy nową strukturę {Board}, alokuje pamięć i ustawia domyślne wartości
 */
Board *create_board(int cols, int rows, int **tab);

/**
 * Czyści strukturę {Board} i zwalnia pamięć
 */
void delete_board(Board *board);

/**
 * Sprawdza czy pola o podanych współrzędnych sąsiadują ze sobą
 *
 * @return true, jeśli sąsiadują
 * @return false, jeśli nie sąsiadują
 */
bool is_neighbour(int x1, int y1, int x2, int y2);

/**
 * Sprawdza czy pole o zadanych współrzędnych ma sąsiada o danym rodzaju {enum Race}
 *
 * @return true, jeśli sąsiauje z dowolnym polem o danym rodzaju
 * @return false, jeśli nie sąsiaduje
 */
bool has_neighbour(int x, int y, enum Race race, Board *board);

/**
 * Aktualizuje rozmiar pola na podstawie rozmiarów okna
 */
void update_field_info(SDL_Renderer *renderer, Board *board);

#endif