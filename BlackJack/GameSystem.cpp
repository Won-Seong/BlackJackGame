#include "GameSystem.h"
#include <cstdlib>
#include <chrono>




int Card::get_number() const
{
	return number;
}

int Card::get_shape() const
{
	return shape;
}

BunchOfCard::BunchOfCard()
{
	cards.reserve(52);
}

BunchOfCard::~BunchOfCard()
{
	cards.clear();
}

void BunchOfCard::print_all_card() const
{
	for (auto& _card : cards)
		std::cout << _card.get_number() << "\t" << _card.get_shape() << std::endl;
}

void BunchOfCard::shuffle_cards()
{
	srand(unsigned int(time));

	for (int i = 0; i < 200; i++) {
		int idx = rand() % 52;

		int number = cards[idx].get_number();
		int shape = cards[idx].get_shape();

		Card temp(number, shape);
		cards.erase(cards.begin() + idx);
		cards.push_back(temp);
	}//repeat 100 times

}

