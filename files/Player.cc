#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Player.h"
#include "Card.h"
#include "Minion.h"
#include "Enchantments.h"
#include "Ritual.h"
#include "Spell.h"
#include "Sorcery.h"
#include <iostream>
#include "ascii_graphics.h"
using std::find;
using std::ifstream;

using namespace std;

Player::Player(){

}
Player::Player(const string name) : name(name) {

}
Player::~Player(){
	for(unsigned int i=0;i<deck.size();++i){
		delete deck.at(i);
	} deck.clear();
	for(unsigned int i=0;i<graveyard.size();++i){
		delete graveyard.at(i);
	}	graveyard.clear();
	for(unsigned int i=0;i<hand.size();++i){
		delete hand.at(i);
	} hand.clear();
	for(unsigned int i=0;i<minions.size();++i){
		delete minions.at(i);
	} minions.clear();
	delete ritual;
}

void Player::setName(string name){
	this->name=name;
}

void Player::incrementMagic(int i)
{
 magic += i;
}

bool Player::decrementMagic(int i)
{
 if (magic < i) {
  return false;}
 magic -= i;
 return true;
}

void Player::incrementLife(int i)
{
 life += i;
}

void Player::decrementLife(int i)
{
 if (life > i)
  life -= i;
 else{
 	life=0;
  endGame(activePlayer->getName());
 }
}

void Player::drawCard(){
	if(deck.size()==0){
		printError("There are no more cards in your deck.");
		return;
	}
	if(hand.size()==5){
			printError("Your hand is full.");
			return;
	}
		hand.push_back(deck.back());
		deck.pop_back();
}

void Player::discardCard(unsigned int i){
	if(hand.size()<i){
		printError("Card " + std::to_string(i) + " does not exist in your hand.");
	}
	else{
		graveyard.push_back(hand.at(i-1));
		hand.erase(hand.begin()+i-1);
	}
}

void Player::printHand(){
	int size = hand.size();
        vector <vector<string>> handString;
	int row;
        for (int k = 0; k < size; k++) {
  		vector<string> message;
                string name = hand[k]->getName();
                int cost = hand[k]->getCost();
                string desc = hand[k]->getDescription();
                if (hand[k]->getType() == "Minion") {
                        Minion *m = (Minion *) hand[k];
                        int atk = m->getAtk();
                        int hp = m->getHp();
                        if (hand[k]->getTrigger() == 0) {
                                message = display_minion_no_ability(name, cost, atk, hp);
                        } else if (hand[k]->getTrigger() == 5) {
                                message = display_minion_triggered_ability(name, cost, atk, hp, desc);
                        } else {//Case of 1-4 triggers
                                int aCost = m->getACost();
                                message = display_minion_activated_ability(name, cost, atk, hp, aCost,
                                                                            desc);
                        }
                } else if (hand[k]->getType() == "Ritual") {
                        Ritual *r = (Ritual *) hand[k];
  			int chargeCost = r->getChargeCost();
			int charges = r->getCharges();
			message = display_ritual(name, cost, chargeCost, desc, charges); 
                } else if (hand[k]->getType() == "Spell") {
			message = display_spell(name, cost, desc);
		} else {//Enchantment
			Enchantment *e = (Enchantment *) hand[k];
			int type = e->getEnchType();
  			string attack(1,e->getAOp());
			string hp(1,e->getHOp());
 			attack += to_string(e->getAVal());
			hp += to_string(e->getHVal());
			if (type == 0) {	
				message = display_enchantment_attack_defence(name, cost, desc, attack, hp);
			} else {
				message = display_enchantment(name, cost, desc);
			}
		}
		row = message.size();
  		handString.emplace_back(message);
        }
        for (int k = 0; k < row; k++) {//for every row to print
		for (int j = 0; j < size; j++) {//loop through size cards
			cout << handString[j][k];
		}
		cout << endl;
        }
}

string Player::getName() const {
	return name;
}
int Player::getLife() const {
	return life;
}
int Player::getMagic() const {
	return magic;
}
Minion* Player::getMinion(int m) const {
	return minions.at(m-1);
}
Ritual* Player::getRitual() const {
	return ritual;
}
int Player::numMinions() const {
	return minions.size();
}

void Player::constructDeck(string deckFile){
	ifstream fs(deckFile);
	string cardName;
	while(true){
		getline(fs, cardName);
		if(!fs.good()){break;}
		if(find(minionList.begin(), minionList.end(), cardName) != minionList.end()){
			Minion* minionPtr = new Minion(cardName);
			deck.emplace_back(minionPtr);
		}else if(find(enchList.begin(), enchList.end(), cardName) != enchList.end()){
			Enchantment* enchPtr = new Enchantment(cardName);
			deck.emplace_back(enchPtr);
		}else if(find(spellList.begin(), spellList.end(), cardName) != spellList.end()){
			Spell* spellPtr = new Spell(cardName);
			deck.emplace_back(spellPtr);
		}else if(find(ritualList.begin(), ritualList.end(), cardName) != ritualList.end()){
			Ritual* ritualPtr = new Ritual(cardName);
			deck.emplace_back(ritualPtr);
		}else{
			printError("Invalid card name encountered: " + cardName);
			endGame();
		}
	}
}

void Player::shuffleDeck(){
 std::random_shuffle(deck.begin(), deck.end());
}

void Player::summonMinion(Minion* minion){
	minions.push_back(minion);
}

void Player::unsummonMinion(Minion* minion){
	// remove from hand
	for(unsigned int i=0;i<minions.size();++i){
		if(minions.at(i)==minion){
			minions.erase(minions.begin()+i);
			break;
		}
	}
}

void Player::toBottomDeck(Card *c){
	// push card to front of deck
}

void Player::setRitual(Ritual* r){
	ritual = r;
}

void Player::toGraveyard(Card* c){
	graveyard.push_back(c);
}

bool Player::summonFromGraveyard(){
	for(unsigned int i=0;i<graveyard.size();++i){
		if(graveyard.at(i)->getType()=="Minion"){
			summonMinion((Minion*) graveyard.at(i));
			graveyard.erase(graveyard.begin()+i);
			triggerCard=getMinion(numMinions());
			activateTrigger(2);
			return true;
		}
	}
		return false;
}

void Player::minionAttack(int minion, Player* otherPlayer){
	if (minion > numMinions()) {
		printError("Not a valid minion number.");
		return;
	}
	//Get minion and check if it has actions left
	Minion *m = getMinion(minion);
	if (!m->hasActionLeft()) return;
	m->useAction();
	
 int damage = m->getAtk();
	otherPlayer->decrementLife(damage);
	//Check if other player is dead after this function
}

void Player::minionAttack(int minion, int otherminion, Player* otherPlayer){
	//Checks if both minion index's exist
	if (minion > numMinions() || otherminion > numMinions()) {
		printError("Not a valid minion number.");
		return;
	}
	//Pulling minion cards
	Minion *attacker = getMinion(minion);
	Minion *victim = otherPlayer->getMinion(otherminion);
	//Checking if attacker has any actions left
	if (!attacker->hasActionLeft()) return;
	attacker->useAction();
	//pulling attack values of both minions
	int aDmg = attacker->getAtk();
	int vDmg = victim->getAtk();
	//decrement both minions (and check for death)
	attacker->decrementLife(vDmg);
	victim->decrementLife(aDmg);
}

void Player::useAbility(int minion){
	Minion *m = getMinion(minion);
	m->Activate();
}

void Player::useAbility(int minion, int targetCard, Player& targetPlayer){
	Minion *m = getMinion(minion);
	m->Activate(targetPlayer.getMinion(targetCard));
}

void Player::playCard(unsigned int i){
 // errors and shit
 if(hand.size()<i){
 	printError("Invalid card number.");
 	return;
 }

 string cardType = hand.at(i-1)->getType();
 if(cardType=="Minion"){
 	if(numMinions()==5){
 		printError("Cannot summon another minion, there is no room on the field.");
 		return;
 	}
 }
 else if(cardType=="Enchantment"){
 	printError("You must specify a target when playing an enchantment.");
 	return;
 }
 else if(cardType=="Spell"){
 	if(hand.at(i-1)->requiresTarget()){ // might not compile
 		printError("This spell requires a target.");
 		return;
 	}
 }

 // magic cost
	if(!activePlayer->decrementMagic(hand.at(i-1)->getCost())){
		printError("Insuffienct magic to cast spell.");
		return;
	}

	// triggers
	triggerCard=hand.at(i-1);	
	if(cardType=="Minion"){
		activateTrigger(2);
	}
	else if(cardType=="Spell"){
		activateTrigger(3);
	}
	triggerCard=nullptr;
	
	// play the card
	hand.at(i-1)->Play(); 
	if(cardType=="Spell"){
		discardCard(i);
	}else{ 
		hand.erase(hand.begin()+i-1);
	} 
}

void Player::playCard(unsigned int i, int targetCard, Player& targetPlayer){
	// errors and shit
	if(hand.size()<i){
 	printError("Invalid card number.");
 	return;
 }

 string cardType = hand.at(i-1)->getType();
 if(cardType=="Minion"){
 	printError("Minions do not have targets.");
 	return;
 }
 else if(cardType=="Spell"){
 	if(!hand.at(i-1)->requiresTarget()){ // might not compile
 		printError("This spell does not require a target.");
 		return;
 	}
 }
 else if(cardType=="Ritual"){
 	printError("Rituals do not have targets");
 	return;
 }

 // magic cost
 if(!activePlayer->decrementMagic(hand.at(i-1)->getCost())){
		printError("Insuffienct magic to cast spell.");
		return;
	}

	// triggers
	triggerCard=hand.at(i-1);	
	if(cardType=="Minion"){
		activateTrigger(2);
	}
	else if(cardType=="Spell"){
		activateTrigger(3);
	}
	triggerCard=nullptr;

	// play the card
	hand.at(i-1)->Play(targetPlayer.getMinion(targetCard)); // handle triggers
	if(cardType=="Spell"){
		discardCard(i);
	}else{ 
		hand.erase(hand.begin()+i-1);
	}
}
