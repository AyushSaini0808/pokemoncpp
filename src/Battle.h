#ifndef POKEMON_BATTLE_H
#define POKEMON_BATTLE_H
#include <random>
#include "Pokemon.h"


class Battle {
public:
    Battle(Pokemon& player, Pokemon& enemy, std::mt19937& rng);
    bool isOver() const;
    void executeTurn(std::size_t playerMove, std::size_t enemyMove); // Both sides would pick their moves. The faster pokemon would execute first
    const Pokemon* winner() const; // nullptr when the battle is going on

private:
    void performMove( Pokemon& attacker,  Pokemon& defender, std::size_t moveIndex);
    Pokemon& player_;
    Pokemon& enemy_;
    std::mt19937& rng_;

};
#endif //POKEMON_BATTLE_H
