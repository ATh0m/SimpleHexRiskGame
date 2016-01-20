//
// Created by Tomasz Nanowski on 11.01.2016.
//

#ifndef SIMPLEHEXRISKGAME_GENERATOR_H
#define SIMPLEHEXRISKGAME_GENERATOR_H

#include "defs.h"
#include "utility.h"
#include "board.h"

/**
 * Generuje losowa tablicę, na podstawie której tworzona będzie plansza.
 * Wszystkie komórki wypełnione jedynkami muszą tworzyć wspólny obszar
 *
 * @param width szerokość tablicy
 * @param height wysokość tablicy
 *
 * @return tablica wypełniona zerami i jedynkami
 */
int **generate_fields_tab(int width, int height);

/**
 * Poprawia tablicę, jeśli komórki z jedynkami nie są spójne
 */
void fix_fields_tab(int **fields_tab, int width, int height);

/**
 * Usuwa wszystkie pola o innym, niz zadany kolor
 */
void erase_another_colors(int **fields_tab, int width, int height, int color);

/**
 * Liczy ilość pól posiadających dany kolor
 */
int count_fields_color(int **fields_tab, int width, int height, int color);

/**
 * Zamienia pola z 0 na 1, jeśli sąsiadują z polami o różnych kolorach
 */
int normalize_fields_tab(int **fields_tab, int width, int height);

/**
 * Sprawdza z iloma różnymi kolorami sąsiaduje dane pole
 */
int count_different_fields(int **fields_tab, int width, int height, int x, int y);

/**
 * Koloruje spójne obszary jedynek
 */
int color_fields_tab(int **fields_tab, int width, int height);

/**
 * Koloruje spójny obszar na dany kolor
 */
void color_fields(int **fields_tab, int width, int height, int x, int y, int color);

/**
 * Zamienia wszystkie kolory na 0 lub 1
 */
void format_fields_tab(int **fields_tab, int width, int height);

/**
 * Wypisuje tablicę na standardowe wyjście
 */
void print_fields_tab(int **fields_tab, int width, int height);

/**
 * Zwalnia pamięć tablicy
 */
void delete_generated_fields_tab(int **fields_tab, int width, int height);

#endif //SIMPLEHEXRISKGAME_GENERATOR_H
