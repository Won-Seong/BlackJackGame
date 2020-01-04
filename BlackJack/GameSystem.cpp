#include "GameSystem.h"

Card::Card(const Card& card):number(card.number),shape(card.shape)
{

}

int Card::get_number() const
{
	return number;
}

int Card::get_shape() const
{
	return shape;
}

std::ostream& operator<<(std::ostream& stream, const Card& card) {
	stream << "Num : " << std::setw(10)<<std::left<<card.number 
		<< std::setw(8) << "Shape : " << card.shape
		<< std::endl;
	return stream;
}

void Player::add_card(card_ptr card)
{
	player_card.push_back(card);
	current_sum_number += card->get_number();
	if (current_sum_number > 21) {
		die = true;
		std::cout << "*Your cards exceed 21!" << std::endl;
	}
}

bool Player::get_die() const
{
	return die;
}

int Player::get_chip() const 
{
	return chip;
}

int Player::get_current_num() const 
{
	return current_sum_number;
}



void Gamer::add_chip(int _chip)
{
	chip += _chip;
}

int Gamer::bet_chip()
{
	int chip_to_bet;
	std::cout << "How many chips do you bet? (Your chip count : " << chip << " ) ";
	std::cin >> chip_to_bet;
	if (chip_to_bet > chip)
		throw std::out_of_range("You don't have that much chips!");
	else if (chip_to_bet < 0)
		throw std::out_of_range("You can't input minus!");
	else if (std::cin.fail())
		throw std::out_of_range("Do not input non-integer!");
	chip -= chip_to_bet;
	return chip_to_bet;

}

int Gamer::double_down(int _chip)
{
	if (chip < _chip)
		throw std::out_of_range("You don't have enough chips!");
	chip -= _chip;
	return _chip;
}

std::ostream& operator<<(std::ostream& stream, const Gamer& gamer) {
	stream << "Current chip : " << gamer.chip
		<< std::setw(20) << "Current number : " << gamer.current_sum_number
		<< std::endl;
	return stream;
}

void Dealer::add_card(card_ptr card)
{
	
	dealer_card.push_back(card);
	for (auto& itr : dealer_card)
		current_card_sum += itr->get_number();
	
}

int Dealer::get_current_sum() const
{
	return current_card_sum;
}
