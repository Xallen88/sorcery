#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "Ritual.h"

extern printError(string err);
extern Player* activePlayer;
extern Player* nonActivePlayer;
extern Card* triggerCard;

Ritual::Ritual(){
	// catchall
}
Ritual::~Ritual(){
	// no ptrs
}

Ritual::Ritual(string name) : name(name) {
 type="Ritual";
 stringstream ss;
	string line;
	string fileName=name;

	for(int i=0; i<name.length();++i){
		if(fileName.at(i)==" "){
			fileName.erase(i);
		}
	}
	fileName="rituals/"+fileName+".info";
 ifstream infoFile (fileName);
 getline(infoFile, line);
 
 ss >> cost;
 ss >> charges;
 ss >> chargeCost;
 ss >> trigger;
 // take ints from file

 getline(ss, description);	
 // feed remaining line into description
}

void Ritual::Play(){
	Card* ritualPtr = activePlayer->getRitual();
	if(ritualPtr){
 	graveyard.push_back(ritualPtr);
 }
 activePlayer->setRitual(this);
}

void Ritual::Play(Card* c){
	// not a valid function call
}

void Ritual::Activate(){
	if(charges >= chargesCost){
		switch(name){
			case "Dark Ritual": DarkRitual(); break;
		}
	}
}

void Ritual::Activate(Card* c){
	if(charges >= chargeCost){
		switch(name){
			case "Aura of Power": AuraOfPower(c); break;
			case "Standstill": Standstill(c); break;
			case "Aura of Silence": AuraOfSilence(c); break;
		}
	}
}

void Ritual::DarkRitual(){
	activePlayer->incrementMagic();
}

void Ritual::Standstill(Card* c){
	c->decrementLife(c->getHp());
}

void Ritual::AuraOfPower(Card* c){
	// +1/+1 enchantment
	// attach to minion
}

void Ritual::AuraOfSilence(Card* c){
	// destroy spell
}
