#include "Card.h"
#include <string>
using std::string;

Card::Card(){}
Card::Card(string name):name(name){}

int Card::getOwner() const {
	return owner;
}
int Card::getTrigger() const {
	return trigger;
}
int Card::getCost() const {
	return cost;
}
string Card::getName() const {
	return name;
}
string Card::getDescription() const {
	return description;
}
string Card::getType() const {
	return type;
}
