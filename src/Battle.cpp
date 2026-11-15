#include "Battle.h"

#include "Damage.h"
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
    if (player_.speed()!=enemy_.speed()) {
        playerFirst=player_.speed()>enemy_.speed();
    }else {
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
    if (!isOver())return nullptr;
    return player_.isFainted()?&enemy_:&player_;
}

void Battle::performMove(Pokemon &attacker,  Pokemon &defender, std::size_t moveIndex) {
    Move& move = attacker.move(moveIndex);
    if (!move.usePP()) {
        std::cout<<attacker.name()<<" has no PP left for "<<move.name()<<'\n';
        return;
    }
    std::cout<<attacker.name()<<" used "<< move.name()<<"!\n";
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
        std::cout<<"It's not ver effective\n";
    }

    std::cout<<defender.name()<<" took "<<damage<<" damage\n"<<"HP: "<<defender.currentHP()<<"/ "<<defender.maxHP()<<'\n';

    if (defender.isFainted()) {
        std::cout<<defender.name()<<" fainted!\n";
    }
}
