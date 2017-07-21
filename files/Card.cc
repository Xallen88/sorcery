#include <string>
#include "Card.h"
#include "Sorcery.h"

Card::Card(){}
Card::Card(string name):name(name){}
Card::~Card(){}

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

bool Card::requiresTarget() const {
	return targetable;
}
