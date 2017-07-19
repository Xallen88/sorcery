#include "Spell.h"
#include "Minion.h"
#include "Player.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using std::string;
using std::ifstream;
using std::stringstream;

printError(string err);
Player* activePlayer, nonActivePlayer;
Card* triggerCard;

Spell::Spell(){
	// nothing here, just a safety net
}
Spell::~Spell(){
	// no ptrs
}
Spell::Spell(string name) : name(name) {
	type="Spell";
	trigger=0;
	stringstream ss;
	string line;
	string fileName=name;

	for(int i=0; i<name.length();++i){
		if(fileName.at(i)==" "){
			fileName.erase(i);
		}
	}
	fileName="spells/"+fileName+".info";
 ifstream infoFile (fileName);
 getline(infoFile, line);
 
 ss >> cost;
 // take int from file

 ss >> targetable;
 // read in 0/1

 getline(ss, description);	
 // feed remaining line into description
}

bool Spell::requiresTarget(){
	return targetable;
}

void Spell::Activate(){}
void Spell::Activate(Card* c){}
// unused functions

void Spell::Play(){
	if(!acticePlayer->decrementMagic(cost)){
		printError("Insuffienct magic to cast spell.");
	}
	switch(name){
		case "Recharge": Recharge(); break;
		case "Raise Dead": RaiseDead(); break;
		case "Blizzard": Blizzard(); break;
	}
}
void Spell::Play(Card* c){
	if(!acticePlayer->decrementMagic(cost)){
		printError("Insuffienct magic to cast spell.");
	}
	switch(name){
		case "Banish": Banish(c); break;
		case "Unsummon": Unsummon(c); break;
		case "Disenchant": Disenchant(c); break;
	}
}

void Spell::Recharge(){
	Ritual* ritualPtr = activePlayer->getRitual;
	if(ritualPtr){
		ritualPtr->incrementCharges(3);
	}
	else{
		printError("You don't have a ritual.");
	}
}

void Spell::RaiseDead(){
	if(activePlayer->numMinions()==5){
		printError("There are already 5 minions on the field.");
	}

	for(auto it=graveyard.rbegin(); it!=graveyard.rend(); ++it){
		if(*it->getType=="Minion"){
			activatePlayer->summonMinion(*it);
			*it=nullptr;
			graveyard.erase(it);
			triggerCard=activePlayer->getMinion(activePlayer->numMinions);
			activateTrigger(2);
			return;
		}
	}

	printError("There are no minions in your graveyard");
}

void Spell::Blizzard(){
	Minon* currMinion;
	for(int i=1; i<activePlayer->numMinions(); ++i){
		currMinion=activePlayer->getMinion(i);
		currMinion->decrementLife(2);
		// minion will be killed if life <= 0 (handled by decrementLife)
	}
	for(int i=1; i<nonActivePlayer->numMinions(); ++i){
		currMinion=nonActivePlayer->getMinion(i);
		currMinion->decrementLife(2);
	}
}

void Spell::Banish(Card *c){
 
}

void Spell::Unsummon(Card *c){
 
}

void Spell::Disenchant(Card *c){
 
}
