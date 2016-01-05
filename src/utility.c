#include "utility.h"

Color create_color(int r, int g, int b, int a) {
    Color new_color = {r, g, b, a};
    return new_color;
}

Pair create_pair(int x, int y) {
    Pair new_pair = {x, y};
    return new_pair;
}
