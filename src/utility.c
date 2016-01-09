#include "utility.h"

Color create_color(int r, int g, int b, int a) {
    Color new_color = {r, g, b, a};
    return new_color;
}

Pair create_pair(int x, int y) {
    Pair new_pair = {x, y};
    return new_pair;
}

int max (int a, int b) {
    return a > b ? a : b;
}

int min (int a, int b) {
    return a < b ? a : b;
}

PairItem *create_pair_item(Pair pair, PairItem *prev) {
    PairItem *new_pair_item = malloc(sizeof(PairItem));

    new_pair_item->pair = pair;
    new_pair_item->prev = prev;

    return new_pair_item;
}

PairStack *create_pair_stack() {
    PairStack *new_pair_stack = malloc(sizeof(PairStack));

    new_pair_stack->size = 0;
    new_pair_stack->top = NULL;

    return new_pair_stack;
}

void push(PairStack *pair_stack, Pair pair) {
    PairItem *pair_item = create_pair_item(pair, pair_stack->top);

    pair_stack->top = pair_item;
    pair_stack->size++;
}

void erase(PairStack *pair_stack, Pair pair) {
    PairItem *last = NULL;
    PairItem *pair_item = pair_stack->top;

    while (pair_item != NULL) {

        if(pair_item->pair.x == pair.x && pair_item->pair.y == pair.y) {
            if (last == NULL) pair_stack->top = pair_item->prev;
            else last->prev = pair_item->prev;

            pair_stack->size--;
            free(pair_item);
            return;
        }

        last = pair_item;
        pair_item = pair_item->prev;
    }
}