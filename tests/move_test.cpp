#include <gtest/gtest.h>
#include "Move.h"

TEST(MoveTest, StartsWithFullPP) {
    Move m("Ember", Type::Fire, 40, 100, 3);
    EXPECT_EQ(m.currentPP(), 3);
    EXPECT_TRUE(m.hasPP());
}

TEST(MoveTest, UsePPCountsDownAndStopsAtZero) {
    Move m("Ember", Type::Fire, 40, 100, 2);
    EXPECT_TRUE(m.usePP());
    EXPECT_TRUE(m.usePP());
    EXPECT_FALSE(m.usePP());      // out of PP
    EXPECT_EQ(m.currentPP(), 0);  // never goes negative
    EXPECT_FALSE(m.hasPP());
}