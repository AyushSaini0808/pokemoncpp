#include <gtest/gtest.h>
#include <stdexcept>
#include "Pokemon.h"

namespace {

    Pokemon makePokemon() {
        return Pokemon("Charmander", Type::Fire, 5, 39, 52, 43, 65);
    }

}  // namespace

TEST(PokemonTest, StartsAtFullHP) {
    Pokemon p = makePokemon();
    EXPECT_EQ(p.currentHP(), 39);
    EXPECT_EQ(p.maxHP(), 39);
    EXPECT_FALSE(p.isFainted());
}

TEST(PokemonTest, TakeDamageReducesHP) {
    Pokemon p = makePokemon();
    p.takeDamage(10);
    EXPECT_EQ(p.currentHP(), 29);
}

TEST(PokemonTest, HPNeverGoesBelowZero) {
    Pokemon p = makePokemon();
    p.takeDamage(500);
    EXPECT_EQ(p.currentHP(), 0);
    EXPECT_TRUE(p.isFainted());
}

TEST(PokemonTest, NegativeDamageIsIgnored) {
    Pokemon p = makePokemon();
    p.takeDamage(-10);
    EXPECT_EQ(p.currentHP(), 39);   // must not heal
}

TEST(PokemonTest, HealRestoresHPButNotPastMax) {
    Pokemon p = makePokemon();
    p.takeDamage(30);
    p.heal(10);
    EXPECT_EQ(p.currentHP(), 19);
    p.heal(1000);
    EXPECT_EQ(p.currentHP(), 39);
}

TEST(PokemonTest, NegativeHealIsIgnored) {
    Pokemon p = makePokemon();
    p.takeDamage(10);
    p.heal(-5);
    EXPECT_EQ(p.currentHP(), 29);   // must not hurt
}

TEST(PokemonTest, CannotAddMoreThanMaxMoves) {
    Pokemon p = makePokemon();
    for (std::size_t i = 0; i < Pokemon::kMaxMoves; ++i) {
        EXPECT_TRUE(p.addMove(Move("Move", Type::Normal, 40, 100, 10)));
    }
    EXPECT_FALSE(p.addMove(Move("Extra", Type::Normal, 40, 100, 10)));
    EXPECT_EQ(p.moveCount(), Pokemon::kMaxMoves);
}

TEST(PokemonTest, MoveWithBadIndexThrows) {
    Pokemon p = makePokemon();
    p.addMove(Move("Scratch", Type::Normal, 40, 100, 35));
    EXPECT_THROW(p.move(5), std::out_of_range);
}

TEST(PokemonTest, MoveReturnsTheRealMoveNotACopy) {
    Pokemon p = makePokemon();
    p.addMove(Move("Scratch", Type::Normal, 40, 100, 2));
    p.move(0).usePP();
    EXPECT_EQ(p.move(0).currentPP(), 1);   // PP spent through the reference sticks
}