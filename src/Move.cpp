//
// Created by Ayush Saini on 13/11/26.
//

#include "Move.h"

Move::Move(std::string name, Type type, int power, int accuracy,int maxPP)
    :name_(std::move(name)),
    type_(type),
    power_(power),
    accuracy_(accuracy),
    maxPP_(maxPP),
    currentPP_(maxPP){}

bool Move::hasPP() const {
    return currentPP_>0;
}

bool Move::usePP() {
    if (!this->hasPP()) return false;
    --currentPP_;
    return true;
}
