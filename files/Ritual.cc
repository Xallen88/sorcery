#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <cctype>
#include <algorithm>
#include "Card.h"
#include "Ritual.h"
#include "Player.h"
#include "Minion.h"
#include "Sorcery.h"

using std::stringstream;
using std::ifstream;

class Player;

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

	int len=fileName.length();
	for(int i=0;i<len;++i){
		if(fileName[i]==' '){
			fileName.erase(i);
			--i;
			--len;
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
	Minion* m = (Minion*) c;
	m->decrementLife(m->getHp());
}

void Ritual::AuraOfPower(Card* c){
	// +1/+1 enchantment
	// attach to minion
}

void Ritual::AuraOfSilence(Card* c){
	// destroy spell
}

void Ritual::incrementCharges(int i){
	charges+=i;
}