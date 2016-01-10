#ifndef SIMPLEHEXRISKGAME_UTILITY_H
#define SIMPLEHEXRISKGAME_UTILITY_H

#include "defs.h"

typedef struct Color {
    int r, g, b, a;
} Color;

Color create_color(int r, int g, int b, int a);

typedef struct Pair {
    int x, y;
} Pair;

Pair create_pair(int x, int y);

typedef struct Triple {
    int x, y, z;
} Triple;

Triple create_triple(int x, int y, int z);

int max (int a, int b);
int min (int a, int b);

typedef struct PairItem {
    Pair pair;
    struct PairItem *prev;
} PairItem;

PairItem *create_pair_item(Pair pair, PairItem *prev);

typedef struct PairStack {
    int size;
    PairItem *top;
} PairStack;

PairStack *create_pair_stack();
void push(PairStack *pair_stack, Pair pair);
void erase(PairStack *pair_stack, Pair pair);
void clear(PairStack *pair_stack);
void print_stack(PairStack *pair_stack);

#endif