#ifndef SIMPLEHEXRISKGAME_UTILITY_H
#define SIMPLEHEXRISKGAME_UTILITY_H

#include "defs.h"

enum State {
    CREATE,
    START,
    REINFORCEMENT,
    MOVE,
    WIN
};

enum Race {
    NEUTRAL,
    ENEMY,
    ALLY
};

typedef struct Color {
    Uint8 r, g, b, a;
} Color;

/**
 * Tworzenie struktury {Color}
 */
Color create_color(int r, int g, int b, int a);

typedef struct Pair {
    int x, y;
} Pair;

/**
 * Tworzenie struktury {Pair}
 */
Pair create_pair(int x, int y);

typedef struct Triple {
    int x, y, z;
} Triple;

/**
 * Tworzenie struktury {Triple}
 */
Triple create_triple(int x, int y, int z);

/**
 * Zwraca max z dwóch liczb
 */
int max(int a, int b);

/**
 * Zwraca min z dwóch liczb
 */
int min(int a, int b);

/**
 * Zwraca wartość bezwzględną liczby
 */
int abs(int a);

typedef struct PairItem {
    Pair pair;
    struct PairItem *prev;
} PairItem;

/**
 * Tworzy nową strukturę {PairItem}, alokuje pamięć i ustawia domyślne wartości
 */
PairItem *create_pair_item(Pair pair, PairItem *prev);

typedef struct PairStack {
    int size;
    PairItem *top;
} PairStack;

/**
 * Tworzy nową strukturę {PairStack}, alokuje pamięć i ustawia domyślne wartości
 */
PairStack *create_pair_stack();

/**
 * Wkładanie nowej wartości na koniec do stosu {PairStack}
 */
void push(PairStack *pair_stack, Pair pair);

/**
 * Usuwanie pierwszego wystąpienia w stosie {PairStack}
 */
void erase(PairStack *pair_stack, Pair pair);

/**
 * Czyści strukturę {PairStack} i zwalnia pamięć
 */
void delete_pair_stack(PairStack *pair_stack);

/**
 * Wypisuje strukturę {PairStack} na standardowe wyjście
 */
void print_stack(PairStack *pair_stack);

#endif