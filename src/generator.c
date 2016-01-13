//
// Created by Tomasz Nanowski on 11.01.2016.
//

#include "generator.h"

int **generate_fields_tab(int width, int height) {

    int **fields_tab = malloc(width * sizeof(int *));

    int blank_fields = (int) (width * height * BLANK_FIELDS_RATE);
    blank_fields = rand() % blank_fields;

    for (int x = 0; x < width; x++) {
        fields_tab[x] = malloc(height * sizeof(int));
        for (int y = 0; y < height; y++) {
            fields_tab[x][y] = 0;
        }
    }

    int x, y;

    while (blank_fields > 0) {
        x = rand() % width;
        y = rand() % height;
        if (fields_tab[x][y] != -1) {
            fields_tab[x][y] = -1;
            blank_fields--;
        }
    }

    int different = 0;

    different = color_fields_tab(fields_tab, width, height) - 1;

    if (different > 1) {
        fix_fields_tab(fields_tab, width, height);
    }

    format_fields_tab(fields_tab, width, height);

    return fields_tab;
}

void fix_fields_tab(int **fields_tab, int width, int height) {

    while (normalize_fields_tab(fields_tab, width, height)) {
        color_fields_tab(fields_tab, width, height);
    };

    int different = color_fields_tab(fields_tab, width, height) - 1;

    if (different > 1) {

        int max_amount = 0, max_color = 1, amount;

        for (int i = 1; i <= different; i++) {
            amount = count_fields_color(fields_tab, width, height, i);
            if (amount > max_amount) {
                max_color = i;
                max_amount = amount;
            }
        }

        erase_another_colors(fields_tab, width, height, max_color);

    }

}

void erase_another_colors(int **fields_tab, int width, int height, int color) {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (fields_tab[x][y] != -1 && fields_tab[x][y] != color) {
                fields_tab[x][y] = -1;
            }
        }
    }
}

int count_fields_color(int **fields_tab, int width, int height, int color) {
    int counter = 0;

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (fields_tab[x][y] == color) {
                counter++;
            }
        }
    }

    return counter;
}

int normalize_fields_tab(int **fields_tab, int width, int height) {

    int counter = 0;

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (fields_tab[x][y] == -1) {
                if (count_different_fields(fields_tab, width, height, x, y) > 1) {
                    fields_tab[x][y] = 0;
                    counter++;
                }
            }
        }
    }

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            fields_tab[x][y] = fields_tab[x][y] >= 0 ? 0 : -1;
        }
    }

    return counter;
}

int count_different_fields(int **fields_tab, int width, int height, int x, int y) {
    int X, Y;

    int counter = 0;
    int color = 0;

    for (int i = 0; i < 6; i++) {
        if (y % 2 == 0) {
            X = x + even[i][0];
            Y = y + even[i][1];
        }
        else {
            X = x + odd[i][0];
            Y = y + odd[i][1];
        }

        if ( X >= 0 && Y >= 0 && X < width && Y < height) {
            if (fields_tab[X][Y] != 0 && fields_tab[X][Y] != -1 && fields_tab[X][Y] != color) {
                color = fields_tab[X][Y];
                counter++;
            }
        }
    }
    return counter;
}

int color_fields_tab(int **fields_tab, int width, int height) {
    int color = 1;

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (fields_tab[x][y] == 0) {
                color_fields(fields_tab, width, height, x, y, color);
                color++;
            }
        }
    }

    return color;
}

void color_fields(int **fields_tab, int width, int height, int x, int y, int color) {
    if (x >= 0 && y >= 0 && x < width && y < height) {
        if (fields_tab[x][y] == 0) {
            fields_tab[x][y] = color;

            int X, Y;

            for (int i = 0; i < 6; i++) {
                if (y % 2 == 0) {
                    X = x + even[i][0];
                    Y = y + even[i][1];
                }
                else {
                    X = x + odd[i][0];
                    Y = y + odd[i][1];
                }

                color_fields(fields_tab, width, height, X, Y, color);
            }
        }
    }
}

void format_fields_tab(int **fields_tab, int width, int height) {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            fields_tab[x][y] = fields_tab[x][y] < 0 ? 0 : 1;
        }
    }
}

void print_fields_tab(int **fields_tab, int width, int height) {
    printf("\n");
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            printf("%2d ", fields_tab[x][y]);
        }
        printf("\n");
    }
}

void delete_generated_fields_tab(int **fields_tab, int width, int height) {

    for (int x = 0; x < width; x++) {
        free(fields_tab[x]);
    }

    free(fields_tab);
}
