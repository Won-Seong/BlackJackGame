#include "GameSystem.h"

void make_a_deck(Deck& _deck) {
	
	_deck.reserve(MAX_CARDS_IN_DECK);
	for (int i = 0; i < MAX_CARD_SHAPE; i++) {
		for (int j = 0; j < MAX_CARD_NUMBER; j++) {
			card_ptr temp_card(new Card(j, i));
			_deck.push_back(temp_card);
		}
	}
}

void delete_a_deck(Deck& _deck) {
	_deck.clear();
}

void shuffle_deck(Deck& _deck) {
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 200; i++) {
		int zero_to_fiftyone = rand() % 51;
		card_ptr temp_card_ptr = _deck.at(zero_to_fiftyone);
		_deck.erase(_deck.begin() + zero_to_fiftyone);
		_deck.push_back(temp_card_ptr);
	}//repeat two hundred times

}

void print_deck(Deck& _deck) {
	for (auto& itr : _deck)
		std::cout << *itr;
}

card_ptr take_card_from_deck(Deck& _deck) {
	card_ptr temp = *_deck.begin();
	_deck.pop_back();
	return temp;
}

void print_current_status(Gamer& gamer) {
	std::cout << "==================================================================\n"
		<< gamer << "==================================================================" << std::endl;
}

int main() {
	Gamer gamer;
	Deck deck;
	make_a_deck(deck);
	shuffle_deck(deck);
	
	while (!deck.empty()) {
		try
		{
			gamer.bet_chip();
		}
		catch (const std::exception& _error)
		{
			std::cout << _error.what() << std::endl;
			std::cin.clear();
			std::cin.ignore(100, '\n');
			continue;
		}
		gamer.add_card(take_card_from_deck(deck));
		gamer.add_card(take_card_from_deck(deck));
		print_current_status(gamer);
		






	}

	



}
