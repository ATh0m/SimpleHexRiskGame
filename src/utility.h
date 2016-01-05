#ifndef UTILITY_H
#define UTILITY_H

#include "defs.h"

typedef struct Color {
    int r, g, b, a;
} Color;

typedef struct Pair {
    int x, y;
} Pair;

Color create_color(int r, int g, int b, int a);

#endif