#ifndef _CARD_H_
#define _CARD_H_

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
	bool targetable;

public:
	Card();
	virtual ~Card()=0;

	int getTrigger() const;
	int getCost() const;
	int getOwner() const;
	string getName() const;
	string getDescription() const;
	string getType() const;
	bool requiresTarget() const;

	virtual void Play();
	virtual void Play(Card* target);
	// play the card	
	//  minion: summon
	//  ritual: place on field
	//  enchantment: attach to minion
	//  spell: activate effect
	virtual void Activate();
	// use the card's ability
	virtual void Activate(Card* target);
};

#endif
