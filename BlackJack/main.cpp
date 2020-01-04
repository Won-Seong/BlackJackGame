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

int dealer_algorithm(Dealer& dealer,Deck& deck) {
	
	while (dealer.get_current_sum < 17 || !deck.empty()) {
		dealer.add_card(take_card_from_deck(deck));
		std::cout << "Dealer's sum is : " << dealer.get_current_sum() << std::endl;
	}//if the sum is less than 16, hit. but it is 16 or more than, stay.
	return dealer.get_current_sum();
}

void gamer_algorithm(Gamer& gamer, Deck& deck,int& _table_chip) {
	if (deck.size < 2) {
		std::cout << "We don't have enough card. Replenishing the deck..." << std::endl;
		make_a_deck(deck);
	}
	gamer.add_card(take_card_from_deck(deck));
	gamer.add_card(take_card_from_deck(deck));
	print_current_status(gamer);
	int choice;
	while (1) {
		std::cout << "What do you want to do? | Hit(0) , Double down(1) , Stay(2) | ";
		std::cin >> choice;
		if (choice < 0 || choice > 2)
			std::cout << "It's wrong number! try again." << std::endl;
		break;
	}
	switch (choice)
	{
	case 0:
		while (gamer.get_current_num < 21 || choice ==0) {
			gamer.add_card(take_card_from_deck(deck));
			std::cout << "Your sum : " << gamer.get_current_num() << std::endl;
			while (1) {
				std::cout << "More? | Yes(0) , No(1) | ";
				std::cin >> choice;
				if (choice < 0 || choice > 1)
					std::cout << "It's wrong number! try again." << std::endl;
				break;
			}
		}

	case 1:
		try
		{
			gamer.double_down(_table_chip);
		}
		catch (const std::exception& error)
		{
			std::cout<< error.what();
			std::cout << "You're going to stay this time." << std::endl;
		}
		break;
	case 2:
		break;
	default:
		break;
	}
	print_current_status(gamer);
}



int main() {
	Gamer gamer;
	Deck deck;
	Dealer dealer;
	make_a_deck(deck);
	shuffle_deck(deck);
	int table_chip = 0;
	while (gamer.get_chip != 0) {
		try
		{
			table_chip = gamer.bet_chip();
		}
		catch (const std::exception & _error)
		{
			std::cout << _error.what() << std::endl;
			std::cin.clear();
			std::cin.ignore(100, '\n');
			continue;
		}
		gamer_algorithm(gamer, deck, table_chip);
		
		






	}

	



}
