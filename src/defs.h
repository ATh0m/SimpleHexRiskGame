#ifndef SIMPLEHEXRISKGAME_DEFS_H
#define SIMPLEHEXRISKGAME_DEFS_H

#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * Domyślny rozmiar okna
 */
#define WINDOW_WIDTH 850
#define WINDOW_HEIGHT 475

/**
 * Minimalny rozmiar okna
 */
#define WINDOW_MIN_WIDTH 655
#define WINDOW_MIN_HEIGHT 328

/**
 * Kolor tła
 */
#define BACKGROUND_COLOR create_color(0, 0, 0, 255)

/**
 * Rozmiar planszy
 */
#define BOARD_WIDTH rand() % 5 + 7
#define BOARD_HEIGHT rand() % 5 + 7

/**
 * Maksymalna ilość pustych pól
 */
#define BLANK_FIELDS_RATE 0.5

/**
 * Ustawienia graczy
 */
#define PLAYER1 "CZERWONY", 1, true, players_amount < 1, create_color(255, 204, 204, 255), create_color(255, 102, 102, 255), create_color(255, 51, 51, 255)
#define PLAYER2 "NIEBIESKI", 2, true, players_amount < 2, create_color(51, 51, 255, 255), create_color(153, 153, 255, 255), create_color(0, 0, 204, 255)
#define PLAYER3 "ZIELONY", 3, true, players_amount < 3, create_color(122, 216, 138, 255), create_color(78, 174, 95, 255), create_color(19, 86, 31, 255)
#define PLAYER4 "ŻÓŁTY", 4, true, players_amount < 4, create_color(255, 248, 144, 255), create_color(227, 220, 102, 255), create_color(113, 107, 24, 255)

#endif