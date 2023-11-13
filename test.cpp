#include "pokerHand.h"
//#include <googletest-main/gtest/gtest.h>
#include <gtest/gtest.h>
#include <vector>


TEST(ParseHandTest, CorrectlyParsesHand) {
    std::string hand = "2H 3D 5S 9C KD";
    auto parsedHand = parseHand(hand);
    ASSERT_EQ(parsedHand.size(), 5);
    EXPECT_EQ(parsedHand[0].value, 2);
    EXPECT_EQ(parsedHand[0].suit, 'H');

}

TEST(HandTypeTest, IdentifiesStraight) {
    std::string straightHand = "2H 3D 4S 5C 6D";
    auto parsedHand = parseHand(straightHand);
    EXPECT_TRUE(isStraight(parsedHand));
}

TEST(HandTypeTest, IdentifiesFlush) {
    std::string flushHand = "2H 3H 5H 9H KH";
    auto parsedHand = parseHand(flushHand);
    EXPECT_TRUE(isFlush(parsedHand));
}

TEST(BestPokerHandTest, IdentifiesWinningHand) {
    std::string hand1 = "2H 3D 5S 9C KD";
    std::string hand2 = "2C 3H 4S 8C AH";
    EXPECT_EQ(bestPokerHand(hand1, hand2), "Player Two Wins");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
