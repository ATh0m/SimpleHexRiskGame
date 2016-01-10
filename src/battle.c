//
// Created by Tomasz Nanowski on 09.01.2016.
//

#include "battle.h"

int battle_cmp (const void * a, const void * b) {
    return ( *(int*)b - *(int*)a );
}

Pair battle(int attack_power, int defense_power) {
    int attack_dices_amount, defense_dices_amount;
    int attack_dices[3], defense_dices[2];

    while (attack_power > 0 && defense_power > 0) {

        attack_dices_amount = min(attack_power, 3);
        defense_dices_amount = min(defense_power, 2);


        for (int i = 0; i < attack_dices_amount; i++) {
            attack_dices[i] = rand() % 6 + 1;
        }

        for (int i = 0; i < defense_dices_amount; i++) {
            defense_dices[i] = rand() % 6 + 1;
        }

        qsort(attack_dices, attack_dices_amount, sizeof(int), battle_cmp);
        qsort(defense_dices, defense_dices_amount, sizeof(int), battle_cmp);

//        for (int i = 0; i < attack_dices_amount; i++) {
//            printf("%d ", attack_dices[i]);
//        }
//        printf("\n");
//
//        for (int i = 0; i < defense_dices_amount; i++) {
//            printf("%d ", defense_dices[i]);
//        }
//        printf("\n");

        for (int i = 0; i < min(attack_dices_amount, defense_dices_amount); i++) {
            if (attack_dices[i] > defense_dices[i]) {
                defense_power--;
            } else {
                attack_power--;
            }
        }
    }

    return create_pair(attack_power, defense_power);
}