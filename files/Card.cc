#include "Card.h"
#include <string>
using std::string;

const int Card::getOwner(){
	return owner;
}
const int Card::getTrigger(){
	return trigger;
}
const int Card::getCost(){
	return cost;
}
const string Card::getName(){
	return name;
}
const string Card::getDescription(){
	return description;
}
const string Card::getType(){
	return type;
}
