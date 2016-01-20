//
// Created by Tomasz Nanowski on 09.01.2016.
//

#ifndef SIMPLEHEXRISKGAME_BATTLE_H
#define SIMPLEHEXRISKGAME_BATTLE_H

#include "defs.h"
#include "utility.h"

/**
 * Symulacja bitwy na podstawie losowania
 *
 * @param attack_power ilość atakujących
 * @param defende_power ilość broniących
 *
 * @return {Pair} para pozostałych atakujących i broniących
 */
Pair battle(int attack_power, int defense_power);

#endif //SIMPLEHEXRISKGAME_BATTLE_H
