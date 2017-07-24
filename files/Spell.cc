#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Card.h"
#include "Spell.h"
#include "Ritual.h"
#include "Minion.h"
#include "Player.h"
#include "Sorcery.h"

using std::string;
using std::ifstream;
using std::stringstream;

vector<string> spellList = {"Recharge", "Raise Dead", "Blizzard", "Banish", "Unsummon", "Disenchant"};

Spell::Spell(){
	// nothing here, just a safety net
}
Spell::~Spell(){
	// no ptrs
}
Spell::Spell(string name) : Card(name){
	type="Spell";
	trigger=0;
	destroyed=false;
	stringstream ss;
	string line;
	string fileName=name;

	int len=fileName.length();
	for(int i=0;i<len;++i){
		if(fileName[i]==' '){
			fileName.erase(fileName.begin()+i);
			--i;
			--len;
		}
	}

	fileName="spells/"+fileName+".info";
 ifstream infoFile (fileName);
 getline(infoFile, line);
 ss.str(line);
 
 ss >> cost;
 // take int from file

 ss >> targetable;
 // read in 0/1

 getline(ss, description);	
 // feed remaining line into description
}

bool Spell::isDestroyed(){
	return destroyed;
}

void Spell::Destroy(){
	destroyed=true;
}

void Spell::Activate(){}
void Spell::Activate(Card* c){}
// unused functions

void Spell::Play(){
	if(!isDestroyed()){
		if(name=="Recharge"){
			Recharge();
		}else if(name=="Raise Dead"){
			RaiseDead();
		}else	if(name=="Blizzard"){
			Blizzard();
		}
	}
}
void Spell::Play(Card* c){
	if(!isDestroyed()){
		if(name=="Banish"){
			Banish(c); 
		}else if(name=="Unsummon"){
			Unsummon(c);
		}else if(name=="Disenchant"){
			Disenchant(c);
		}
	}
}

void Spell::Recharge(){
	Ritual* ritualPtr = activePlayer->getRitual();
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

	if(!activePlayer->summonFromGraveyard()){
		printError("There are no minions in your graveyard");
	}
}

void Spell::Blizzard(){
	Minion* currMinion;
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
 if(c->getType()=="ritual"){
 	Player* playerPtr;
		if(c->getOwner()==1){
	 	playerPtr=&playerOne;
	 }else{
	 	playerPtr=&playerTwo;
	 }
		playerPtr->toGraveyard(c);
	 playerPtr->setRitual(nullptr);
 }else{ //minions
 	Minion* minionPtr = (Minion*) c;
 	minionPtr->decrementLife(minionPtr->getHp());
 }
}

void Spell::Unsummon(Card *c){ 
	Player* playerPtr;
	if(c->getOwner()==1){
 	playerPtr=&playerOne;
 }else{
 	playerPtr=&playerTwo;
 }
 playerPtr->unsummonMinion((Minion*) c);
 playerPtr->toBottomDeck(c);
}

void Spell::Disenchant(Card *c){
 Minion* minionPtr = (Minion*) c;
 minionPtr->removeTopEnch();
}
