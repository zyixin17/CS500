#include "pokerHand.h"
#include <vector>
#include <algorithm>
#include <map>
#include <iostream>

// convert char to value
int charToValue(char c) {
    if (c >= '2' && c <= '9') return c - '0';
    if (c == 'T') return 10;
    if (c == 'J') return 11;
    if (c == 'Q') return 12;
    if (c == 'K') return 13;
    if (c == 'A') return 14;
    return -1;
}

// parse hand
std::vector<Card> parseHand(const std::string& hand) {
    std::vector<Card> cards;
    for (int i = 0; i < hand.length(); i += 3) {
        Card card;
        card.value = charToValue(hand[i]);
        card.suit = hand[i + 1];
        cards.push_back(card);
    }
    return cards;
}

// check if high card
bool isHighCard(const std::vector<Card>& hand) {
    return true;
}

// check if pair
bool isPair(const std::vector<Card>& hand) {
    std::map<int, int> cnt;
    for (const auto& card : hand) {
        cnt[card.value]++;
    }
    for (const auto& p : cnt) {
        if (p.second == 2) return true;
    }
    return false;
}

//check if two pairs
bool isTwoPairs(const std::vector<Card>& hand) {
    std::map<int, int> cnt;
    for (const auto& card : hand) {
        cnt[card.value]++;
    }
    int cnt2 = 0;
    for (const auto& p : cnt) {
        if (p.second == 2) cnt2++;
    }
    return cnt2 == 2;
}

//check if three of a kind
bool isThreeOfAKind(const std::vector<Card>& hand) {
    std::map<int, int> cnt;
    for (const auto& card : hand) {
        cnt[card.value]++;
    }
    for (const auto& p : cnt) {
        if (p.second == 3) return true;
    }
    return false;
}

// check if straight
bool isStraight(const std::vector<Card>& hand) {
    std::vector<int> values;
    for (const auto& card : hand) {
        values.push_back(card.value);
    }
    std::sort(values.begin(), values.end());
    for (int i = 1; i < values.size(); ++i) {
        if (values[i] != values[i - 1] + 1) return false;
    }
    return true;
}

// check if flush
bool isFlush(const std::vector<Card>& hand) {
    char suit = hand[0].suit;
    for (const auto& card : hand) {
        if (card.suit != suit) return false;
    }
    return true;
}

// check if full house
bool isFullHouse(const std::vector<Card>& hand) {
    std::map<int, int> cnt;
    for (const auto& card : hand) {
        cnt[card.value]++;
    }
    bool hasTwo = false, hasThree = false;
    for (const auto& p : cnt) {
        if (p.second == 2) hasTwo = true;
        if (p.second == 3) hasThree = true;
    }
    return hasTwo && hasThree;
}

//check if four of a kind
bool isFourOfAKind(const std::vector<Card>& hand) {
    std::map<int, int> cnt;
    for (const auto& card : hand) {
        cnt[card.value]++;
    }
    for (const auto& p : cnt) {
        if (p.second == 4) return true;
    }
    return false;
}

// check if straight flush
bool isStraightFlush(const std::vector<Card>& hand) {
    return isStraight(hand) && isFlush(hand);
}

// check hand type
int handType(const std::vector<Card>& hand) {
    if (isStraightFlush(hand)) return 8; // Straight flush
    if (isFourOfAKind(hand)) return 7; // Four of a kind
    if (isFullHouse(hand)) return 6; // Full house
    if (isFlush(hand)) return 5; // Flush
    if (isStraight(hand)) return 4; // Straight
    if (isThreeOfAKind(hand)) return 3; // Three of a kind
    if (isTwoPairs(hand)) return 2; // Two pairs
    if (isPair(hand)) return 1; // Pair
    return 0; // High card
}

int compareHands(const std::vector<Card>& hand1, const std::vector<Card>& hand2) {
    std::vector<int> values1, values2;
    for (const auto& card : hand1) values1.push_back(card.value);
    for (const auto& card : hand2) values2.push_back(card.value);

    std::sort(values1.begin(), values1.end(), std::greater<int>());
    std::sort(values2.begin(), values2.end(), std::greater<int>());

    for (size_t i = 0; i < values1.size(); ++i) {
        if (values1[i] > values2[i]) return 1; 
        if (values2[i] > values1[i]) return -1;
    }
    return 0;   // Tie
}

// compare two hands
std::string bestPokerHand(const std::string& p1, const std::string& p2) {
    std::vector<Card> hand1 = parseHand(p1);
    std::vector<Card> hand2 = parseHand(p2);

    int handType1 = handType(hand1);
    int handType2 = handType(hand2);

    if (handType1 > handType2) return "Player One Wins";
    if (handType2 > handType1) return "Player Two Wins";

    // Same hand type
    int result = compareHands(hand1, hand2);
    if (result == 1) return "Player One Wins";
    if (result == -1) return "Player Two Wins";

    return "Tie";
}


int main() {
    // Sample input
    std::string hand1 = "2H 3D 5S 9C KD";
    std::string hand2 = "2C 3H 4S 8C AH";

    // Call the function and output the result
    std::string result = bestPokerHand(hand1, hand2);
    std::cout << "Result: " << result << std::endl;

    return 0;
}