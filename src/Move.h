//
// Created by Ayush Saini on 13/11/26.
//

#ifndef POKEMON_MOVE_H
#define POKEMON_MOVE_H
#include <string>

#include "Type.h"


class Move {
public:
    Move(std::string name,Type type,int power,int accuracy,int maxPP);

    const std::string& name() const{ return name_ ;} // We would simply move the string rather than creating a copy
    Type type() const {return type_ ;}
    int power() const{return power_ ; }
    int accuracy() const{return accuracy_ ;}
    int maxPP() const{ return maxPP_; }
    int currentPP() const{ return currentPP_;}

    bool hasPP() const;
    bool usePP();
private:
    std::string name_;
    Type type_;
    int power_;
    int accuracy_;
    int maxPP_;
    int currentPP_;
};


#endif //POKEMON_MOVE_H
