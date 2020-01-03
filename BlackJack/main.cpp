#include "GameSystem.h"

void make_a_deck(std::vector<Card*>& _deck) {
	
	_deck.reserve(MAX_CARDS_IN_DECK);
	for (int i = 0; i < MAX_CARD_SHAPE; i++) {
		for (int j = 0; j < MAX_CARD_NUMBER; j++) {
			Card* temp_card = new Card(j, i);
			_deck.push_back(temp_card);
		}
	}
}

void delete_a_deck(std::vector<Card*>& _deck) {
	for (auto& itr : _deck) {
		delete itr;
	}
	_deck.clear();
}

void shuffle_deck(std::vector<Card*>& _deck) {
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 200; i++) {
		int zero_to_fiftyone = rand() % 51;
		Card* temp_card_ptr = _deck.at(zero_to_fiftyone);
		_deck.erase(_deck.begin() + zero_to_fiftyone);
		_deck.push_back(temp_card_ptr);
	}//repeat two hundred times

}

void print_deck(std::vector<Card*>& _deck) {
	for (auto& itr : _deck)
		std::cout << *itr;
}


int main() {
	std::vector<Card*> deck;
	make_a_deck(deck);
	shuffle_deck(deck);
	print_deck(deck);


}
