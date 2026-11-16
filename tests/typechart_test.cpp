#include<gtest/gtest.h>
#include<TypeChart.h>

TEST(TypeChartTest,SuperEffectiveTypePairs) {
    EXPECT_DOUBLE_EQ(effectiveness(Type::Fire,Type::Grass),2.0);
    EXPECT_DOUBLE_EQ(effectiveness(Type::Water,Type::Fire),2.0);
    EXPECT_DOUBLE_EQ(effectiveness(Type::Grass,Type::Water),2.0);
    EXPECT_DOUBLE_EQ(effectiveness(Type::Electric,Type::Water),2.0);
}

TEST(TypeChartTest,NotSoEffectiveTypePairs) {
    EXPECT_DOUBLE_EQ(effectiveness(Type::Fire,Type::Water),0.5);
    EXPECT_DOUBLE_EQ(effectiveness(Type::Water,Type::Grass),0.5);
    EXPECT_DOUBLE_EQ(effectiveness(Type::Grass,Type::Fire),0.5);
    EXPECT_DOUBLE_EQ(effectiveness(Type::Fire,Type::Fire),0.5);
    EXPECT_DOUBLE_EQ(effectiveness(Type::Water,Type::Water),0.5);
    EXPECT_DOUBLE_EQ(effectiveness(Type::Electric,Type::Electric),0.5);
    EXPECT_DOUBLE_EQ(effectiveness(Type::Grass,Type::Grass),0.5);
    EXPECT_DOUBLE_EQ(effectiveness(Type::Electric,Type::Grass),0.5);

}

TEST(TypeChartTest,NormalEffectTypePairs) {
    for (int i=0;i<static_cast<int>(Type::Count);i++) {
        EXPECT_DOUBLE_EQ(effectiveness(Type::Normal,static_cast<Type>(i)),1.0);
    }
    EXPECT_DOUBLE_EQ(effectiveness(Type::Electric,Type::Fire),1.0);
    EXPECT_DOUBLE_EQ(effectiveness(Type::Water,Type::Electric),1.0);
    EXPECT_DOUBLE_EQ(effectiveness(Type::Grass,Type::Electric),1.0);

}

TEST(TypeChartTest,ChartIsNotSymmetric) {
    EXPECT_NE(effectiveness(Type::Fire,Type::Water),effectiveness(Type::Water,Type::Fire));
    EXPECT_NE(effectiveness(Type::Water,Type::Grass),effectiveness(Type::Grass,Type::Water));
    EXPECT_NE(effectiveness(Type::Grass,Type::Fire),effectiveness(Type::Fire,Type::Grass));
}