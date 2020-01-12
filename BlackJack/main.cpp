#include "GameSystem.h"

void make_a_deck(Deck& _deck) {
	
	_deck.reserve(MAX_CARDS_IN_DECK);
	for (int i = 0; i < MAX_CARD_SHAPE; i++) {
		for (int j = 1; j < MAX_CARD_NUMBER + 1; j++) {
			if (j > 10) {
				card_ptr temp_card(new Card(10, i));
				_deck.push_back(temp_card);
			}
			else {
				card_ptr temp_card(new Card(j, i));
				_deck.push_back(temp_card);
			}
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

void print_deck(const Deck& _deck) {
	for (auto& itr : _deck)
		std::cout << *itr;
	std::cout << "Deck's size = " << _deck.size() << std::endl;;
}

card_ptr take_card_from_deck(Deck& _deck) {
	card_ptr temp = *(_deck.end() - 1);
	_deck.pop_back();
	return temp;
}

void print_current_status(const Gamer* gamer) {
	std::cout << "==================================================================\n"
		<< *gamer << "==================================================================" << std::endl;
}

void print_current_number_both(const Gamer* gamer, const Dealer* dealer) {
	std::cout << "==================================================================\n"
		<< "Player's number : " << gamer->get_current_num() << "\tDealer's number : " << dealer->get_current_sum()
		<< "\n==================================================================" << std::endl;
}

void dealer_algorithm(Dealer* dealer,Deck& deck) {
	
	while (dealer->get_current_sum() < 17 && !deck.empty()) {
		dealer->add_card(take_card_from_deck(deck));
		std::cout << "Dealer's sum is : " << dealer->get_current_sum() << std::endl;
	}//if the sum is less than 16, hit. but it is 16 or more than, stay.
	dealer->set_state();
}

void gamer_algorithm(Gamer* gamer, Deck& deck,int* _table_chip) {
	if (deck.size() < 2) {
		std::cout << "We don't have enough card. Replenishing the deck..." << std::endl;
		make_a_deck(deck);
	}
	gamer->add_card(take_card_from_deck(deck));
	gamer->add_card(take_card_from_deck(deck));
	print_current_status(gamer);
	if (gamer->get_current_num() == 21) {
		std::cout << "Your number is 21! Black jack!" << std::endl;
		return;
	}
	else if (gamer->get_current_num() > 21) {
		std::cout << "Your number already exceed 21..." << std::endl;
		gamer->set_state();
		return;
	}

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
		while (gamer->get_current_num() < 21 && choice == 0) {
			gamer->add_card(take_card_from_deck(deck));
			std::cout << "Your sum : " << gamer->get_current_num() << std::endl;
			while (gamer->get_current_num() < 21) {
				std::cout << "More? | Yes(0) , No(1) | ";
				std::cin >> choice;
				if (choice < 0 || choice > 1)
					std::cout << "It's wrong number! try again." << std::endl;
				break;
			}
		}
		gamer->check_if_gamer_lose();
		break;
	case 1:
		try
		{
			gamer->double_down(*_table_chip);
			gamer->add_card(take_card_from_deck(deck));
		}
		catch (const std::exception& error)
		{
			std::cout<< error.what();
			std::cout << " You're going to stay this time." << std::endl;
		}
		break;
	case 2:
		std::cout << "You stay this time." << std::endl;
		break;
	default:
		break;
	}
	print_current_status(gamer);
} //This function is for gamer's rule

int who_is_the_winner(const Gamer* gamer, const Dealer* dealer, const int* _table_chip) {
	print_current_number_both(gamer,dealer);
	if (gamer->get_state() == LOSE) {
		std::cout << "You burst..."
			<< "\nDealer takes your chip!" << std::endl;
		return 0;
	}
	else if (dealer->get_state() == LOSE) {
		std::cout << "Dealer made burst!"
			<< "\nYou can get your share." << std::endl;
		return 1;
	}

	if (!dealer->is_black_jack()) {
		if (gamer->is_black_jack()) {
			std::cout << "You made Blackjack! you're going to get 2 times chips you bet." << std::endl;
			return (*_table_chip) * 3;
		}
	}else if (dealer->is_black_jack()) {
		std::cout << "Dealer made Blackjack..." << std::endl;
		return 0;
	}

	if (gamer->get_current_num() > dealer->get_current_sum()) {
		std::cout << "You win! you can get your share." << std::endl;
		return (*_table_chip) * 2;
	}
	else if (gamer->get_current_num() < dealer->get_current_sum()) {
		std::cout << "You lose..."
			<< "\nDealer takes your chip!" << std::endl;
		return 0;
	}
	else {
		std::cout << "Well, it's draw. you can get chip you just bet." << std::endl;
		return *_table_chip;
	}

}

void game_setting(Gamer* gamer, Dealer* dealer, int* table_chip,int earned_chip) {
	gamer->add_chip(earned_chip);
	gamer->card_clear();
	dealer->card_clear();
	gamer->set_state();
	dealer->set_state();
	*table_chip = 0;
	std::cout << "\n-Next round-\n" << std::endl;
}

int main() {
	Gamer gamer;
	Deck deck;
	Dealer dealer;
	make_a_deck(deck);
	shuffle_deck(deck);
	int table_chip = 0;

	std::cout << "Dealer : Okay, game start!" << std::endl;
	
	while (gamer.get_chip() != 0) {
		try
		{
			table_chip = gamer.bet_chip();
		}
		catch (const std::exception & _error)
		{
			std::cout << _error.what() << std::endl << std::endl;
			std::cin.clear();
			std::cin.ignore(100, '\n');
			continue;
		}
		gamer_algorithm(&gamer, deck, &table_chip);
		dealer_algorithm(&dealer, deck);
		game_setting(&gamer, &dealer, &table_chip, who_is_the_winner(&gamer, &dealer, &table_chip));
	
	}
	std::cout << "You have no chips left! Game over." << std::endl;
	return 0;
	
}
