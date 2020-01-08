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
constexpr bool LOSE = true;
constexpr bool NOT_LOSE = false;
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

class Player : public std::exception {
protected:
	int chip;
	int current_sum_number;
	Deck player_card;
	bool state;//This become true when player burst
public:
	Player() :chip(20),current_sum_number(0),state(false)
	{
		player_card.reserve(6);
	}
	~Player() {
		player_card.clear();
	}
	void add_card(card_ptr card);
	bool is_black_jack() const;
	void set_state();//if num excced 21, state is true, else it is flase
	void card_clear();
	bool get_state() const ;
	int get_chip() const ;
	int get_current_num() const ;
	
};//This class is for other computer, not gamer

class Gamer : public Player {
public:
	Gamer() : Player() {};
	~Gamer() {
		player_card.clear();
	}
	void add_chip(int _chip);
	int bet_chip();
	int double_down(int _chip);
	void check_if_gamer_lose();
	friend std::ostream& operator<<(std::ostream& stream, const Gamer& gamer);
};

class Dealer {
private:
	Deck dealer_card;
	bool state;
	int current_card_sum;
public:
	Dealer() :current_card_sum(0), state(false) {};
	~Dealer() {
		dealer_card.clear();
	}
	void add_card(card_ptr card);
	void card_clear();
	void set_state();
	int get_current_sum() const;
	bool is_black_jack() const;
	bool get_state() const ;
};
