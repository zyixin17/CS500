#ifndef POKER_HAND_H
#define POKER_HAND_H

#include <string>
#include <vector>

struct Card {
    int value;
    char suit;
};

std::vector<Card> parseHand(const std::string& hand);
bool isHighCard(const std::vector<Card>& hand);
bool isPair(const std::vector<Card>& hand);
bool isTwoPairs(const std::vector<Card>& hand);
bool isThreeOfAKind(const std::vector<Card>& hand);
bool isStraight(const std::vector<Card>& hand);
bool isFlush(const std::vector<Card>& hand);
bool isFullHouse(const std::vector<Card>& hand);
bool isFourOfAKind(const std::vector<Card>& hand);
bool isStraightFlush(const std::vector<Card>& hand);
int handType(const std::vector<Card>& hand);
int compareHands(const std::vector<Card>& hand1, const std::vector<Card>& hand2);
std::string bestPokerHand(const std::string& p1, const std::string& p2);

#endif
