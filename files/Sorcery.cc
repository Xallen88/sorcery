#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Sorcery.h"
#include "Player.h"
#include "Card.h"
#include "Minion.h"
#include "Spell.h"
#include "Ritual.h"
#include "Enchantments.h"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::stringstream;
using std::vector;
using std::ifstream;

bool init = false;
ifstream initFile;

bool testing = false;
bool gameover = false;

int turn = 0;
Player playerOne;
Player playerTwo;
Player *activePlayer = &playerOne;
Player *nonActivePlayer = &playerTwo;
Card* triggerCard=nullptr;
// this is the card that triggered an event (spell or minion)

int main(int argc, char* argv[]){
	// command line args
	string deckFile1, deckFile2, name, initFileName;
	deckFile1=deckFile2="default.deck";

	for(int i=1; i<argc; ++i){			// needs serious error handling
		string strArg = argv[i];
		if(strArg=="-deck1"){
			++i;
			deckFile1=strArg;
		}else if(strArg=="-deck2"){
			++i;
			deckFile2=strArg;
		}else if(strArg=="-init"){
			++i;
			init=true;
			initFileName=strArg;
		}else if(strArg=="-testing"){
			testing=true;
		}
	}

	// player names
	getline(cin, name);
	playerOne.setName(name);
	getline(cin, name);
	playerTwo.setName(name);
	// deck construction
	playerOne.constructDeck(deckFile1);
	playerTwo.constructDeck(deckFile2);	
	if(!testing){
		playerOne.shuffleDeck();
		playerTwo.shuffleDeck();
	}

	// read input or initfile until EOF or quit
	if(init){initFile.open(initFileName);}
	string commandLine;	
	while(!gameover){

	 if (init){
	  getline(initFile, commandLine);
	  if (!initFile.good()) {
	   init = false;
	  }
	 }
	 else {
	 	getline(cin, commandLine);
	 	if(!cin.good()){
	 		break;
	 	}
	 }

		stringstream ss (commandLine);
		string commandArg;
		ss >> commandArg;

		if(commandArg=="help"){
			printHelp();
		}

		else if(commandArg=="end"){
			endTurn(activePlayer, nonActivePlayer);
		}

		else if(commandArg=="quit"){
			break;
		}

		else if(commandArg=="attack"){ // need error handling
			int minion;
			ss >> minion;
			if(ss.good()){
				int otherminion;
				ss >> otherminion;
				activePlayer->minionAttack(minion, otherminion, nonActivePlayer);
			}else{
				activePlayer->minionAttack(minion, nonActivePlayer);
			}
		}

		else if(commandArg=="play"){ // need error handling
			int card;
			ss >> card;
			if(ss.good()){
				int targetPlayer, targetCard;
				ss >> targetPlayer >> targetCard;
				if(targetPlayer==1){
					activePlayer->playCard(card, targetCard, playerOne);
				}
				else if(targetPlayer==2){
					activePlayer->playCard(card, targetCard, playerTwo);
				}
				else{
					printError("Not a valid target player.");
				}
			}else{
				activePlayer->playCard(card);
			}
		}

		else if(commandArg=="use"){ // need error handling (FOR RITUALS????)
			int minion;
			ss >> minion;
			if(ss.good()){
				int targetPlayer, targetCard;
				ss >> targetPlayer >> targetCard;
				if(targetPlayer==1){
					activePlayer->useAbility(minion, targetCard, playerOne);
				}
				else if(targetPlayer==2){
					activePlayer->useAbility(minion, targetCard, playerTwo);
				}
				else{
					printError("Not a valid target player.");
				}
			}else{
				activePlayer->useAbility(minion);
			}
		}

		else if(commandArg=="inspect"){ // need error handling
			int minion;
			ss >> minion;
			inspectMinion(minion, nonActivePlayer);
		}

		else if(commandArg=="hand"){
			activePlayer->printHand();
		}

		else if(commandArg=="board"){
			printBoard();
		}
		
		else if(commandArg=="draw"){
			if(testing){
				activePlayer->drawCard();
			}
			else{
				printError("This command can only be used in testing mode");
			}
		}else if(commandArg=="discard"){
			if(testing){
				int card;
				ss >> card;
				activePlayer->discardCard(card);
			}
			else{
				printError("This command can only be used in testing mode");
			}
		}else{
			printError("Not a valid command. Type help for a list of commands.");
		}
	}

	// cleanup, delete ptrs, etc
 
 // end game - print winner, etc

 return 0;
}

void printHelp(){
	cout <<
	"help -- Display this message." << endl <<
	"end -- End the current player's turn." << endl <<
	"quit -- End the game." << endl <<
	"attack minion other-minion -- Orders minion to attack other-minion." << endl <<
	"attack minion -- Orders minion to attack opponent." << endl <<
	"play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player." << endl <<
	"use minion [target-player target-card] -- Use minion's special ability, optionally targeting target-card owned by target-player." << endl <<
	"inspect minion -- View a minion's card and all enchantments on that minion." << endl <<
	"hand -- Describe all cards in your hand." << endl <<
	"board -- Describe all cards on the board." << endl;
}

extern void printError(string err){
	cout << err << endl;
}

void printBoard(){
	// graphical stuff goes here (Steven)
}

void inspectMinion(int m, Player* p){
	// code goes here (Steven)
}

extern void activateTrigger(int triggerType){
	// APNAP: Active minion's (l to r), active ritual, non-active minions, non-active ritual
	// Active Player
	Minion *minionPtr, *minionPtrTwo;
	Ritual* ritualPtr;
	Spell* spellPtr;
	if(triggerType==2){
		minionPtrTwo = (Minion*) triggerCard;
	}else if(triggerType==3){
		spellPtr = (Spell*) triggerCard;
	}

	for(int m=1; m<=5; ++m){
		minionPtr=activePlayer->getMinion(m);
		if(!minionPtr){break;}
		if(minionPtr->getTrigger()==triggerType){
			if(triggerType==1 || triggerType==4){
				minionPtr->Activate();
			}else if (triggerType==2){
				minionPtr->Activate(triggerCard);
				if(minionPtrTwo->isDead()){
					return;
				}
			}else{
				minionPtr->Activate(triggerCard);
				if(spellPtr->isDestroyed()){
					return;
				}
			}
		}
	}
	ritualPtr=activePlayer->getRitual();
	if(ritualPtr){
		if(ritualPtr->getTrigger()==triggerType){
			if(triggerType==1 || triggerType==4){
				ritualPtr->Activate();
			}else if (triggerType==2){
				ritualPtr->Activate(triggerCard);
				if(minionPtrTwo->isDead()){
					return;
				}
			}else{
				ritualPtr->Activate(triggerCard);
				if(spellPtr->isDestroyed()){
					return;
				}
			}
		}
	}

// Non-active Player
	for(int m=1; m<=5; ++m){
		minionPtr=nonActivePlayer->getMinion(m);
		if(!minionPtr){break;}
		if(minionPtr->getTrigger()==triggerType){
			if(triggerType==1 || triggerType==4){
				minionPtr->Activate();
			}else if (triggerType==2){
				minionPtr->Activate(triggerCard);
				if(minionPtrTwo->isDead()){
					return;
				}
			}else{
				minionPtr->Activate(triggerCard);
				if(spellPtr->isDestroyed()){
					return;
				}
			}
		}
	}
	ritualPtr=nonActivePlayer->getRitual();
	if(ritualPtr){
		if(ritualPtr->getTrigger()==triggerType){
			if(triggerType==1 || triggerType==4){
				ritualPtr->Activate();
			}else if (triggerType==2){
				ritualPtr->Activate(triggerCard);
				if(minionPtrTwo->isDead()){
					return;
				}
			}else{
				ritualPtr->Activate(triggerCard);
				if(spellPtr->isDestroyed()){
					return;
				}
			}
		}
	}
}

void endTurn(Player* active, Player* nonactive){
	// end of turn trigger
	activateTrigger(4);

 // swap active and non-active player pointers
 Player* temp = active;
 active = nonactive;
 nonactive = temp;

 // active player's turn begins
 activePlayer->incrementMagic();
 activePlayer->drawCard();

 // start of turn trigger
 activateTrigger(1);
}

extern void endGame(string name){
	cout << name << " is the winner!" << endl;
	gameover=true;
}

extern void endGame(){
	cout << "A game-breaking error has occured." << endl;
	gameover=true;
}
