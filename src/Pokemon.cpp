//
// Created by Ayush Saini on 13/11/26.
//

#include "Pokemon.h"
#include <utility>
#include <algorithm>
Pokemon::Pokemon(std::string name, Type type, int level, int maxHP, int attack, int defence, int speed):
    name_(std::move(name)),
    type_(type),
    level_(level),
    maxHP_(maxHP),
    currentHP_(maxHP),
    attack_(attack),
    defence_(defence),
    speed_(speed){}

bool Pokemon::isFainted() const {
    return currentHP_<=0;
}

void Pokemon::takeDamage(int amount) {
    if (amount<=0) return;
    currentHP_=std::max(0,currentHP_-amount);
}

void Pokemon::heal(int amount) {
    if (amount<=0) return;
    currentHP_=std::min(maxHP_,currentHP_+amount);
}

bool Pokemon::addMove(Move newMove) {
    if (moves_.size()>=kMaxMoves) return false;
    moves_.push_back(std::move(newMove));
    return true;
}

Move& Pokemon::move(std::size_t index) {
    return moves_.at(index);
}

const Move &Pokemon::move(std::size_t index) const {
    return moves_.at(index);
}

std::ostream& operator<<(std::ostream& os, const Pokemon& p) {
    os <<p.name() << " [" <<toString(p.type())<<"] Lv "<<p.level()<<" HP "<<p.currentHP()<<"/"<<p.maxHP()<<" ATK "<<p.attack()<<" DEF "<<p.defence()<<" SPD "<<p.speed()<<"\n";
    for (std::size_t i=0;i<p.moveCount();i++) {
        const Move& m=p.move(i);
        os <<"  "<<i+1<<". "<<m.name()<<" ("<<toString(m.type())<<", pow "<<m.power()<<", PP "<<m.currentPP()<<"/"<<m.maxPP()<<")\n";
    }
    return os;
}

