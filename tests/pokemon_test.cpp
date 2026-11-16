#include<gtest/gtest.h>
#include "Pokemon.h"

TEST(PokemonTest, StartsAtHullHP) {
    Pokemon p("Charmander", Type::Fire, 5, 39, 52, 43, 65);
    EXPECT_EQ(p.currentHP(),39);
    EXPECT_EQ(p.maxHP(),39);
    EXPECT_FALSE(p.isFainted());
}

TEST(PokemonTest, HPReducesOnTakingDamageAndStopsAtZero) {
    Pokemon p("Charmander", Type::Fire, 5, 39, 52, 43, 65);
    p.takeDamage(4);
    EXPECT_EQ(p.currentHP(),35);
    p.takeDamage(36);
    EXPECT_EQ(p.currentHP(),0);
}

TEST(PokemonTest,NegativeDamageHasNoResult) {
    Pokemon p("Charmander", Type::Fire, 5, 39, 52, 43, 65);
    p.takeDamage(-1000);
    EXPECT_EQ(p.currentHP(),39);
}

TEST(PokemonTest, HealIncreasesHPAndStopsAtMaxHP) {
    Pokemon p("Charmander", Type::Fire, 5, 39, 52, 43, 65);
    p.takeDamage(10);
    p.heal(5);
    EXPECT_EQ(p.currentHP(),34);
    p.heal(1000);
    EXPECT_EQ(p.currentHP(),39);
}

TEST(PokemonTest,NegativeHealHasNoResult) {
    Pokemon p("Charmander", Type::Fire, 5, 39, 52, 43, 65);
    p.heal(-1000);
    EXPECT_EQ(p.currentHP(),39);
}

TEST(PokemonTest,FullMoveSetPreventsFurtherAdditionOfMoves) {
    Pokemon p("Charmander", Type::Fire, 5, 39, 52, 43, 65);
    for (int i =0;i<Pokemon::kMaxMoves;i++) {
        EXPECT_TRUE(p.addMove(Move("Ember",Type::Fire,40,100,10)));
    }
    EXPECT_FALSE(p.addMove(Move("Ember",Type::Fire,40,100,10)));
    EXPECT_EQ(p.moveCount(),Pokemon::kMaxMoves);
}

TEST(PokemonTest,MoveWithBadIndexThrowsError) {
    Pokemon p("Charmander", Type::Fire, 5, 39, 52, 43, 65);
    p.addMove(Move("Ember",Type::Fire,40,100,10));
    EXPECT_THROW(p.move(5),std::out_of_range);

}