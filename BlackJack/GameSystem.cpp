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
		state = true;
		std::cout << "*Your cards exceed 21!" << std::endl;
	}
}

bool Player::is_black_jack() const
{
	if (current_sum_number == 21)
		return true;
	else
		return false;
}

void Player::set_state()
{
	if (current_sum_number > 21)
		state = true;
	else
		state = false;
}



void Player::card_clear()
{
	player_card.clear();
	current_sum_number = 0;
}

bool Player::get_state() const
{
	return state;
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
	else if (chip_to_bet <= 0)
		throw std::out_of_range("You can't input below zero!");
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

void Gamer::check_if_gamer_lose()
{
	if (current_sum_number > 21)
		state = true;
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
	current_card_sum += card->get_number();
	
}

void Dealer::card_clear()
{
	dealer_card.clear();
	current_card_sum = 0;
}

void Dealer::set_state()
{
	if (current_card_sum > 21)
		state = true;
	else
		state = false;
}

int Dealer::get_current_sum() const
{
	return current_card_sum;
}

bool Dealer::is_black_jack() const
{
	if (current_card_sum == 21)
		return true;
	else
		return false;
}

bool Dealer::get_state() const
{
	return state;
}
