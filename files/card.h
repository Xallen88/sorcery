#ifndef CARD_H
#define CARD_H

#include <string>

using std::string;

class Card{
protected:
	string name;
	string description;
	string type; 			//One of "Enchantment", "Minion", "Spell", "Ritual"
	int owner;			//owner of the card
	int cost;
	int trigger;			//0 = no trigger. [1,2,3,4] = [start, end, on summon, on spell]

	virtual Play();
	// play the card	
	//  minion: summon
	//  ritual: place on field
	//  enchantment: attach to minion
	//  spell: activate effect
	virtual Activate();
	// use the card's ability
	virtual Activate(Card* target);
public:
	Card();
	virtual Card(string name);
	virtual ~Card()=0;
};

#endif
