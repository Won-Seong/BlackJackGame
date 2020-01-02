#pragma once
constexpr int MAX_BUNCH_OF_CARDS = 52;//There are 52 cards in a deck
constexpr int MAX_A_CARD = 13;//Per a shape
#include <iostream>
#include <vector>


enum { SPADE, HEART, CLOVER, DIAMOND };
enum { JACK = 10, QUEEN = 10, KING = 10 };//In blackjack, these are 10

class Card {
private:
	const int number;
	const int shape;
public:
	Card(int number, int shape) :number(number), shape(shape) {};
	~Card() {};
	int get_number() const;
	int get_shape() const;
};

class BunchOfCard {
private:
	std::vector<Card> cards;
public:
	BunchOfCard();//reserve the vector to 52 and input card to vector
	~BunchOfCard();
	void print_all_card() const;//for debugging
	void shuffle_cards();
};