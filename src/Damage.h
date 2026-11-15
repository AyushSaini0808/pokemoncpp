//
// Created by Ayush Saini on 14/11/26.
//

#ifndef POKEMON_DAMAGE_H
#define POKEMON_DAMAGE_H
#include <random>

#include "Move.h"
#include "Pokemon.h"

int calculateDamage(const Pokemon& attacker, const Pokemon& defender, const Move& move, std::mt19937& rng);
#endif //POKEMON_DAMAGE_H
