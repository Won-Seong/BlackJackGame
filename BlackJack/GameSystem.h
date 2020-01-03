#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <iomanip>
constexpr int MAX_CARDS_IN_DECK = 52;//There are 52 cards in a deck
constexpr int MAX_CARD_NUMBER = 13;//How many numbers is a card able to have
constexpr int MAX_CARD_SHAPE = 4;//How many Shapes is a card able to have
constexpr int MAX_NUMBER = 10;//In blackjack, number can't exceed 10
enum { SPADE, HEART, CLOVER, DIAMOND };
enum { JACK = 10, QUEEN = 10, KING = 10 };//In blackjack, these are 10

class Card {
private:
	const int number;
	const int shape;
public:
	Card(int number, int shape) :number(number), shape(shape) {};
	Card(const Card& card);		
	~Card() {};
	int get_number() const;
	int get_shape() const;
	friend std::ostream& operator<<(std::ostream& stream, const Card& card) ;
};


