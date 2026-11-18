#include <gtest/gtest.h>
#include "damage_test.h"

Pokemon make(Type type, int level, int attack, int defence, int speed, int maxHP,std::string name) {
    return Pokemon(std::move(name),type,level,maxHP,attack,defence,speed);
}

TEST(DamageTest, StatMoveDoesNoDamage) {
    Pokemon a= make(Type::Normal,5,40,50,90,100,"Evee");
    Pokemon b= make(Type::Normal,5,40,50,90,100,"Pancham");
    Move growl("Growl",Type::Normal,0,95,20);
    std::mt19937 rng(1);
    EXPECT_EQ(calculateDamage(a,b,growl,rng),0);
}

TEST(DamageTest, AHitAlwaysDoesOneDamage) {
    Pokemon weak= make(Type::Normal,5,40,50,90,100,"Evee");
    Pokemon tank= make(Type::Normal,80,100,100,100,300,"Mewtwo");
    Move growl("Growl",Type::Normal,1,95,20);
    for (unsigned seed=0;seed<50;seed++) {
        std::mt19937 rng(seed);
        EXPECT_GE(calculateDamage(weak,tank,growl,rng),1);
    }
}

TEST(DamageTest, SameSeedAlwaysDoesSameDamage) {
    Pokemon a= make(Type::Normal,5,40,50,100,100,"Evee");
    Pokemon b= make(Type::Normal,5,60,40,100,100,"Pancham");
    Move growl("Scratch",Type::Normal,40,95,20);
    std::mt19937 rng1(42),rng2(42);

    EXPECT_EQ(calculateDamage(a,b,growl,rng1),calculateDamage(a,b,growl,rng2));
}

TEST(DamageTest, RandomRollAlwaysDoesExpectedDamage) {
    // levelfactor=22;move.power=100;ratio=1; base= ((22*100)/50)+2=46 ; expected range =[39,46]
    Pokemon a = make(Type::Normal,50,100,100,80,200,"Farfetch'd");
    Pokemon b = make(Type::Normal,50,100,100,80,200,"Aggron");

    Move flamethrower("Flamethrower",Type::Fire,100,100,10);
    for (unsigned int seed =0;seed<=50;seed++) {
        std::mt19937 rng(seed);
        EXPECT_GE(calculateDamage(a,b,flamethrower,rng),39);
        EXPECT_LE(calculateDamage(a,b,flamethrower,rng),46);
    }
}

TEST(DamageTest, SameTypeAttackDoesMoreDamage) {
    Pokemon a = make(Type::Fire,50,100,100,80,200,"Charizard");
    Pokemon b = make(Type::Normal,50,100,100,80,200,"Aggron");

    Move thrash("Thrash",Type::Normal,100,100,10);
    Move flamethrower("Flamethrower",Type::Fire,100,100,10);
    std::mt19937 rng(42);
    EXPECT_GT(calculateDamage(a,b,flamethrower,rng),calculateDamage(a,b,thrash,rng));
}
