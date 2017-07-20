#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "Card.h"
#include "Ritual.h"
#include "Player.h"

using std::stringstream;
using std::ifstream;

class Player;

void printError(string err);
Player* activePlayer;
Player* nonActivePlayer;
Card* triggerCard;

Ritual::Ritual(){
	// catchall
}
Ritual::~Ritual(){
	// no ptrs
}

Ritual::Ritual(string name) : Card(name) {
 type="Ritual";
 stringstream ss;
	string line;
	string fileName=name;

	for(auto it=fileName.begin();it!=fileName.end();++it){
		if(*it==" "){
			it = fileName.erase(it);
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
 	//graveyard.push_back(ritualPtr);
 }
 activePlayer->setRitual(this);
}

void Ritual::Play(Card* c){
	// not a valid function call
}

void Ritual::Activate(){
	if(charges >= chargeCost){
		if(name=="Dark Ritual"){
			DarkRitual();
		}
	}
}

void Ritual::Activate(Card* c){
	if(charges >= chargeCost){
		if(name=="Aura of Power"){
			AuraOfPower(c);
		}else if(name=="Standstill"){
			Standstill(c);
		}else if(name=="Aura of Silence"){
			AuraOfSilence(c);
		}
	}
}

void Ritual::DarkRitual(){
	activePlayer->incrementMagic();
}

void Ritual::Standstill(Card* c){
	Minion* m = c;
	m->decrementLife(m->getHp());
}

void Ritual::AuraOfPower(Card* c){
	// +1/+1 enchantment
	// attach to minion
}

void Ritual::AuraOfSilence(Card* c){
	// destroy spell
}
