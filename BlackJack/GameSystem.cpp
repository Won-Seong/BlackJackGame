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