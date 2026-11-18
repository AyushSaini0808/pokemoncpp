#include "Battle.h"

#include "damage_test.h"
#include "TypeChart.h"

Battle::Battle(Pokemon &player, Pokemon &enemy, std::mt19937 &rng)
    :player_(player),
    enemy_(enemy),
    rng_(rng){};

bool Battle::isOver() const {
    return player_.isFainted() || enemy_.isFainted();
}

void Battle::executeTurn(std::size_t playerMove, std::size_t enemyMove) {
    bool playerFirst{};
    // Determining which pokemon will execute its move first through speed property
    if (player_.speed()!=enemy_.speed()) {
        playerFirst=player_.speed()>enemy_.speed();
    }else {
        // If speeds are same, we can randomly choose between the two pokemons
        playerFirst=std::uniform_int_distribution<int>(0,1)(rng_)==0;
    }

    Pokemon& first = playerFirst?player_:enemy_;
    Pokemon& second = playerFirst?enemy_:player_;

    std::size_t firstMove=playerFirst? playerMove:enemyMove;
    std::size_t secondMove=playerFirst? enemyMove:playerMove;

    performMove(first,second,firstMove);
    if (!second.isFainted()) {
        performMove(second,first,secondMove);
    }
}

const Pokemon *Battle::winner() const {
    if (!isOver())return nullptr; // If match is going on and it hasn't been decided, we will keep it as a nullptr
    return player_.isFainted()?&enemy_:&player_;
}

void Battle::performMove(Pokemon &attacker,  Pokemon &defender, std::size_t moveIndex) {
    Move& move = attacker.move(moveIndex);
    if (!move.hasPP()) {
        std::cout<<attacker.name()<<" has no PP left for "<<move.name()<<'\n';
        return;
    }
    move.usePP();
    std::cout<<attacker.name()<<" used "<< move.name()<<"!\n";
    // To introduce some randomness in the match, we are checking whether the move should actually hit
    int accuracyRoll = std::uniform_int_distribution<int>(1, 100)(rng_);
    if (accuracyRoll>move.accuracy()) {
        std::cout<<"Missed!\n";
        return;
    }
    int damage=calculateDamage(attacker,defender,move,rng_);
    defender.takeDamage(damage);

    double multiplier=effectiveness(move.type(),defender.type());
    if (multiplier>1.0) {
        std::cout<<"It's super effective!\n";
    }
    else if (multiplier<1.0) {
        std::cout<<"It's not very effective\n";
    }

    std::cout<<defender.name()<<" took "<<damage<<" damage\n"<<"HP: "<<defender.currentHP()<<"/ "<<defender.maxHP()<<'\n';

    if (defender.isFainted()) {
        std::cout<<defender.name()<<" fainted!\n";
    }
}
