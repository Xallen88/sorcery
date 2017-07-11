#ifndef CARD_H
#define CARD_H

#include <string>

using std::string;

class Card{
protected:
	string name;
	string description;
	string type;
	string owner;			//owner of the card
	int cost;
	int trigger;			//0 = no trigger. [1,2,3,4] = [start, end, on summon, on spell]

	virtual Activate();				//use the card's ability
	virtual Activate(Card* target);	//use the card's with a target
public:
	Card();
	virtual ~Card()=0;
};

#endif
