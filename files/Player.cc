#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Player.h"

using std::string;
using std::cout;
using std::endl;

void activateTrigger(int triggerType);
// Player needs to know about this function (but cannot include sorcery.h)
void printError(string err);
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
		deck.back=nullptr;
		deck.pop_back();
}

void Player::discardCard(int i){
	if(hand.size()<i){
		printError("Card " + i + " does not exist in your hand.");
	}
	else{
		graveyard.push_back(hand.at(i-1));
		hand.at(i-1)=nullptr;
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

void Player::summonMinion(Card* minion){
	minions.push_back(minion);
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
 if(hand.size()<i){
 	printError("Invalid card number.");
 	return;
 }

 cardType = hand.at(i-1)->getType;

 if(cardType=="Minion"){
 	if(minion.size()<5){
 		summonMinion(hand.at(i-1));
 		hand.at(i-1)=nullptr;
 		hand.erase(hand.begin()+i-1);
 	}
 	else{
 		printError("Cannot summon another minion, there is no room on the field.");
 	}
 }
 else if(cardType=="Enchantment"){
 	printError("You must specify a target when playing an enchantment.");
 }
 else if(cardType=="Spell"){
 	if(hand.at(i-1)->requiresTarget()){ // might not compile
 		printError("This spell requires a target.");
 	}
 	else{
 		hand.at(i-1)->Play();
 		discardCard(i);
 	}
 }
 else{
 	if(ritual){
 		graveyard.push_back(ritual);
 	}
 	ritual = hand.at(i-1);
 	hand.at(i-1)=nullptr;
 	hand.erase(hand.begin()+i-1);
 }
}

void Player::playCard(int i, int targetCard, Player& targetPlayer){
	if(hand.size()<i){
 	printError("Invalid card number.");
 	return;
 }

 cardType = hand.at(i-1)->getType;

 if(cardType=="Minion"){
 	printError("Minions do not have targets.");
 }
 else if(cardType=="Enchantment"){
 	hand.at(i-1)->Play(targetPlayer.getMinion(targetCard))
 }
 else if(cardType=="Spell"){
 	if(!hand.at(i-1)->requiresTarget()){ // might not compile
 		printError("This spell does not require a target.");
 	}
 	else{
 		hand.at(i-1)->Play(targetPlayer.getMinion(targetCard));
 		discardCard(i);
 	}
 }
 else{
 	printError("Rituals do not have targets");
 }
}
