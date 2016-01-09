#ifndef SIMPLEHEXRISKGAME_UTILITY_H
#define SIMPLEHEXRISKGAME_UTILITY_H

#include "defs.h"

typedef struct Color {
    int r, g, b, a;
} Color;

typedef struct Pair {
    int x, y;
} Pair;

Color create_color(int r, int g, int b, int a);

Pair create_pair(int x, int y);

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

#endif