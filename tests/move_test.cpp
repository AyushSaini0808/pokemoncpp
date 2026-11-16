#include <gtest/gtest.h>
#include "Move.h"

TEST(MoveTest,StartsWithFullPP) {
    Move m=Move("Ember",Type::Fire,40,80,20);
    EXPECT_EQ(m.currentPP(),20);
    EXPECT_TRUE(m.hasPP());
}

TEST(MoveTest, UsingMoveReducesPP) {
    Move m=Move("Ember",Type::Fire,40,80,20);
    m.usePP();
    EXPECT_EQ(m.currentPP(),19);
}

TEST(MoveTest, FullUseReducesPPToZeroAndStops) {
    Move m=Move("Ember",Type::Fire,40,80,20);
    for (int i =1;i<m.maxPP();++i) {
        m.usePP();
        EXPECT_TRUE(m.hasPP());
    }
    m.usePP();
    EXPECT_FALSE(m.hasPP());
}