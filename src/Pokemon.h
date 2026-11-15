//
// Created by Ayush Saini on 13/11/26.
//

#ifndef POKEMON_POKEMON_H
#define POKEMON_POKEMON_H
#include <ostream>
#include <string>
#include <vector>
#include "Move.h"
#include "Type.h"


class Pokemon {
public:
    static constexpr std::size_t kMaxMoves=4; // we don't want to provide this max move to every pokemon we are just telling the compiler to declare this variable before any pokemon is created coz it will be universal
    // No default constructor so that we ensure that we don't create an empty object as it would be meaningless
    Pokemon(std::string name,Type type,int level, int maxHP,int attack,int defence, int speed);

    const std::string& name() const{return name_;}
    Type type() const{return type_;};
    int level() const{return level_;}
    int maxHP() const{return maxHP_;}
    int currentHP() const{return currentHP_;}
    int attack() const{return attack_;}
    int defence() const {return defence_;}
    int speed() const {return speed_;}

    // HP will only be manipulated by these functions here
    bool isFainted() const;
    void takeDamage(int amount);
    void heal(int amount);

    bool addMove(Move move);
    std::size_t moveCount() const {return moves_.size();} // This will tell outside use how many moves the current pokemon has (0-4)
    Move& move(std::size_t index); // Non const version because the battle loop would need it to reduce PP
    const Move &move(std::size_t index) const; // for overloaded "<<" operator since it takes const Pokemon& p, it would need read-only access

private:
    std::string name_;
    Type type_;
    int level_;
    int maxHP_;
    int currentHP_;
    int attack_;
    int defence_;
    int speed_;
    std::vector<Move> moves_;
};

std::ostream& operator<<(std::ostream& os, const Pokemon& p);

#endif //POKEMON_POKEMON_H
