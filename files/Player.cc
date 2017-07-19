#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Player.h"
#include "Card.h"
#include "Minion.h"
#include "Enchantment.h"
#include "Ritual.h"
#include "Spell.h"

using std::string;
using std::cout;
using std::endl;

extern void activateTrigger(int triggerType);
// Player needs to know about this function (but cannot include sorcery.h)
extern void printError(string err);
// Error printing as defined in sorcery.cc

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

void Player::discardCard(int i){
	if(hand.size()<i){
		printError("Card " + i + " does not exist in your hand.");
	}
	else{
		graveyard.push_back(hand.at(i-1));
		hand.erase(hand.begin()+i-1);
	}
}

const string Player::getName(){
	return name;
}
const int Player::getLife(){
	return Life;
}
const int Player::getMagic(){
	return Magic;
}
const Card* Player::getMinion(int m){
	return minions.at(m-1);
}
const Card* Player::getRitual(){
	return ritual;
}
const int Player::numMinions(){
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

void Player::playCard(int i){
 // errors and shit
 if(hand.size()<i){
 	printError("Invalid card number.");
 	return;
 }

 cardType = hand.at(i-1)->getType;
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
	if(!activePlayer->decrementMagic(cost)){
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

void Player::playCard(int i, int targetCard, Player& targetPlayer){
	// errors and shit
	if(hand.size()<i){
 	printError("Invalid card number.");
 	return;
 }

 cardType = hand.at(i-1)->getType;
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
 if(!activePlayer->decrementMagic(cost)){
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
