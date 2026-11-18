#include<gtest/gtest.h>
#include <Battle.h>

Pokemon makePokemon(const std::string& n, int hp, int speed, int accuracy=100 ) {
    Pokemon p (n,Type::Normal,50,hp,100,100,speed);
    p.addMove(Move("Hit",Type::Normal,100,accuracy,10));
    return p;
}

TEST(BattleTest, FasterPlayerGoesFirst) {
    Pokemon player=makePokemon("Player1",1,100);
    Pokemon enemy=makePokemon("Player2",1,99);
    std::mt19937 rng(42);
    Battle battle(player,enemy,rng);

    battle.executeTurn(0,0);
    EXPECT_TRUE(enemy.isFainted());
    EXPECT_FALSE(player.isFainted());
}

TEST(BattleTest, FasterEnemyGoesFirst) {
    Pokemon player=makePokemon("Player1",1,99);
    Pokemon enemy=makePokemon("Player2",1,100);
    std::mt19937 rng(42);
    Battle battle(player,enemy,rng);

    battle.executeTurn(0,0);
    EXPECT_FALSE(enemy.isFainted());
    EXPECT_TRUE(player.isFainted());
}

TEST(BattleTest, FaintedEnemyDoesNotMakeItsMove) {
    Pokemon player=makePokemon("Player1",1,100);
    Pokemon enemy=makePokemon("Player2",1,90);
    std::mt19937 rng(42);
    Battle battle(player,enemy,rng);

    battle.executeTurn(0,0);
    EXPECT_EQ(enemy.move(0).currentPP(),10);
}

TEST(BattleTest, UsingAMoveSpendsPP) {
    Pokemon player=makePokemon("Player1",1,100);
    Pokemon enemy=makePokemon("Player2",1,90);
    std::mt19937 rng(42);
    Battle battle(player,enemy,rng);

    battle.executeTurn(0,0);
    EXPECT_EQ(player.move(0).currentPP(),9);
}

TEST(BattleTest, AMissDoesNoDamageAndSpendsPP) {
    Pokemon player=makePokemon("Player1",1,100,0);
    Pokemon enemy=makePokemon("Player2",1,90,0);
    std::mt19937 rng(42);
    Battle battle(player,enemy,rng);

    battle.executeTurn(0,0);
    EXPECT_EQ(player.currentHP(),1);
    EXPECT_EQ(enemy.currentHP(),1);
    EXPECT_EQ(player.move(0).currentPP(),9);
    EXPECT_EQ(enemy.move(0).currentPP(),9);

}

TEST (BattleTest, WinnerIsNullUntilBattleEnds) {
    Pokemon player=makePokemon("Player1",300,100);
    Pokemon enemy=makePokemon("Player2",1,90);
    std::mt19937 rng(42);
    Battle battle(player,enemy,rng);

    EXPECT_EQ(battle.winner(),nullptr);
    battle.executeTurn(0,0);
    EXPECT_TRUE(enemy.isFainted());
}