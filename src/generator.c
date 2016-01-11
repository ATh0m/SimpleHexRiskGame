//
// Created by Tomasz Nanowski on 11.01.2016.
//

#include "generator.h"

int **generate_fileds_tab(int width, int height) {

    int **fields_tab = malloc(width * sizeof(int *));

    int blank_fields = width * height * 0.4;
    blank_fields = rand() % blank_fields;

    printf("%d\n", blank_fields);

    for (int x = 0; x < width; x++) {
        fields_tab[x] = malloc(height * sizeof(int));
        for (int y = 0; y < height; y++) {
            if (blank_fields <= 0 || (rand() / (double)RAND_MAX) < 0.5) {
                fields_tab[x][y] = 1;
            }
            else {
                fields_tab[x][y] = 0;
                blank_fields--;
            }
        }
    }

    return fields_tab;
}

void delete_generated_fields_tab(int **fields_tab, int width, int height) {

    for (int x = 0; x < width; x++) {
        free(fields_tab[x]);
    }

    free (fields_tab);
}
