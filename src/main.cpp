#include <iostream>
#include <random>

#include "Battle.h"
#include "BattleUI.h"
#include "Move.h"
#include "Pokemon.h"
#include "Type.h"

int main() {
    std::cout<<"==== Welcome to Pokemon : Inflamed Red ====="<<'\n';
    // std::cout << "Creating a pokemon game !!!" << std::endl;
    // std::cout<<"\nThe types available: "<<std::endl;
    // for (int i=0;i<static_cast<int>(Type::Count);i++) { // static_cast is needed because an enum doesn't implicitly convert to or from int .
    //     std::cout<<toString(static_cast<Type>(i))<<'\t';
    // }
    // std::cout<<std::endl;
    // // Checking out moves working
    // Move ember("Ember",Type::Fire,40,100,3);
    // for (int i=0;i<4;i++) {
    //     bool ok=ember.usePP();
    //     std::cout<<ember.name()<<" ("<<toString(ember.type())<<") "
    //     << (ok?"used":"no PP left")<<", PP: "<<ember.currentPP() <<"/"<<ember.maxPP()<<'\n';
    // }
    // std::cout<<std::endl;
    //
    // Pokemon charmander("Charmander",Type::Fire,5,39,52,43,65);
    // charmander.addMove(Move("Scratch",Type::Normal,40,100,30));
    // charmander.addMove(Move("Ember",Type::Fire,40,100,25));
    // std::cout<< charmander;
    // charmander.takeDamage(30);
    // std::cout<<"After taking 30 HP of damage\nCurrent HP: "<<charmander.currentHP()<<"\nIs fainted: "<<charmander.isFainted()<<std::endl;
    //
    // charmander.takeDamage(500);
    // std::cout<<"After taking 500 HP of damage\nCurrent HP: "<<charmander.currentHP()<<"\nIs fainted: "<<charmander.isFainted()<<std::endl;
    // charmander.heal(1000);
    // std::cout<<"After providing 1000 HP of heal\nCurrent HP: "<<charmander.currentHP()<<"\n";
    //
    // for (std::size_t i =0;i<Pokemon::kMaxMoves;i++) {
    //     bool added=charmander.addMove(Move("Flamethrower",Type::Fire,45,95,10));
    //     std::cout<<"Added flamethrower"<<i+1<<": "<<added<<'\n';
    // }
    //
    // std::cout<<effectiveness(Type::Electric,Type::Electric);


    // Pokemon charmander("Charmander", Type::Fire, 5, 39, 52, 43, 65);
    // Move ember("Ember", Type::Fire, 40, 100, 25);
    //
    // // Same stats, different types, so the type multiplier is the only difference.
    // Pokemon grassDummy("GrassDummy", Type::Grass, 5, 45, 49, 49, 45);
    // Pokemon waterDummy("WaterDummy", Type::Water, 5, 45, 49, 49, 45);
    //
    // std::mt19937 rngA(42), rngB(42);   // same seed, so the random roll is identical
    // std::cout << "Ember vs Grass: " << calculateDamage(charmander, grassDummy, ember, rngA) << '\n';
    // std::cout << "Ember vs Water: " << calculateDamage(charmander, waterDummy, ember, rngB) << '\n';
    // return 0;

    Pokemon charmander("Charmander", Type::Fire, 5, 39, 52, 43, 65);
    charmander.addMove(Move("Scratch", Type::Normal, 40, 100, 35));
    charmander.addMove(Move("Ember", Type::Fire, 40, 100, 25));

    Pokemon bulbasaur("Bulbasaur", Type::Grass, 5, 45, 49, 49, 45);
    bulbasaur.addMove(Move("Tackle", Type::Normal, 40, 100, 35));
    bulbasaur.addMove(Move("Vine Whip", Type::Grass, 45, 100, 25));

    std::mt19937 rng(std::random_device{}());   // different battle every run
    Battle battle(charmander, bulbasaur, rng);

    int turn = 1;
    while (!battle.isOver()) {
        std::cout << "\n--- Turn " << turn++ << " ---\n";

        auto playerMove = promptPlayerMove(charmander, bulbasaur);
        if (!playerMove) {
            std::cout << "\nInput closed. Exiting.\n";
            return 0;
        }

        battle.executeTurn(*playerMove, chooseEnemyMove(bulbasaur, rng));
    }

    std::cout << "\n" << battle.winner()->name() << " wins!\n";
}
