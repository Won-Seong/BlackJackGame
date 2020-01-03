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
class Card;
typedef std::shared_ptr<Card> card_ptr;
typedef std::vector<card_ptr> Deck;


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

class Player {
protected:
	int chip;
	int current_sum_number;
	std::vector<card_ptr> player_card;
	bool die;//This become true when player die
public:
	Player() :chip(20),current_sum_number(0),die(false)
	{
		player_card.reserve(6);
	}
	~Player() {
		player_card.clear();
	}
	void add_card(card_ptr card);
	bool get_die();
	int get_chip();
	int get_current_num();
	
};//This class is for other computer, not gamer

class Gamer : public Player {
public:
	Gamer() : Player() {};
	void add_chip(int _chip);
	int bet_chip();
	int double_down(int _chip);
	friend std::ostream& operator<<(std::ostream& stream, const Gamer& gamer);
};
