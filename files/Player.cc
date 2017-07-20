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

void activateTrigger(int triggerType);
// Player needs to know about this function (but cannot include sorcery.h)
void printError(string err);
// Error printing as defined in sorcery.cc
Player* activePlayer;
Player* nonActivePlayer;
Card* triggerCard;
// Forward declaration for global vars

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
  //end game
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

}

void Player::shuffleDeck(){
 std::random_shuffle(deck.begin(), deck.end());
}

void Player::summonMinion(Minion* minion){
	minions.push_back(minion);
}

void Player::setRitual(Ritual* r){
	ritual = r;
}

void Player::minionAttack(int minion, Player* otherPlayer){
 // Steven code 
}

void Player::minionAttack(int minion, int otherminion, Player* otherPlayer){
	// Steven code
}

void Player::useAbility(int minion){
	// Steven code
}

void Player::useAbility(int minion, int targetCard, Player& targetPlayer){
	// Steven code
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
