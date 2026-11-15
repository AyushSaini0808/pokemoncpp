#ifndef POKEMON_BATTLEUI_H
#define POKEMON_BATTLEUI_H
#include <optional>
#include <random>

#include "Pokemon.h"

std::optional<std::size_t> promptPlayerMove(const Pokemon &player, const Pokemon& enemy);
std::size_t chooseEnemyMove(const Pokemon& enemy, std::mt19937& rng);

#endif //POKEMON_BATTLEUI_H
