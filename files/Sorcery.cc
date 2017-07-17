#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Sorcery.h"
#include "Player.h"

using std::string;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::stringstream;

bool init = false;
ofstream initFile;

int turn = 0;
Player playerOne;
Player playerTwo;
Player* activePlayer = playerOne;
Player* nonActivePlayer = playerTwo;

Card* triggerCard;
// this is the card that triggered an event (spell or minion)

int main(int argc, char* argv[])
{
	// take in command line args
	string deckFile1, deckFile2;
	deckFile1=deckFile2="";

	for(int i=1; i<argc; ++i){			// needs serious error handling
		if(argv[i]=="-deck1"){
			++i;
			deckFile1=argv[i];
		}else if(argv[i]=="-deck2"){
			++i;
			deckFile2=argv[i];
		}else if(argv[i]=="-init"){
			++i;
			init=true;
			initFile.open(argv[i]);
		}
	}

	playerOne.constructDeck(deckFile1);
	playerTwo.constructDeck(deckFile2);
	playerOne.shuffleDeck();
	playerTwo.shuffleDeck();

	// read input or initfile until EOF or quit
	string commandLine = read();	
	while(commandLine){

		stringstream ss (commandArg);
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
			if(!ss.EOF()){
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
			if(!ss.EOF()){
				int targetPlayer, targetCard;
				ss >> targetPlayer >> targetCard;
				activePlayer->playCard(card, targetPlayer, targetCard);
			}else{
				activePlayer->playCard(card);
			}
		}

		else if(commandArg=="use"){ // need error handling (FOR RITUALS????)
			int minion;
			ss >> minion;
			if(!ss.EOF()){
				int targetPlayer, targetCard;
				ss >> targetPlayer >> targetCard;
				activePlayer->useAbility(minion, targetPlayer, targetCard);
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
			printError("Not a valid command. Type help for a list of commands.")
		}
		commandLine=read();
	}

	// cleanup, delete ptrs, etc
 
 // end game

 return 0;
}

string read()
{
 string result;
 if (init){
  getline(initfile, result);
  if (!initFile.good()) {
  	getline(cin, result);
   init = false;
  }
 }
 return result;
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

void printError(string err){
	cerr << err << endl;
}

void printBoard(){
	// graphical stuff goes here (Steven)
}

void inspectMinion(){
	// code goes here (Steven)
}

void activateTrigger(int triggerType){
	// APNAP: Active minion's (l to r), active ritual, non-active minions, non-active ritual
	// Active Player
	for(int m=1; m<=5; ++m){
		minionPtr=activePlayer->getMinion(m);
		if(!minionPtr){break;}
		if(minionPtr->getTrigger()=triggerType){
			if(triggerType==1 || triggerType==4){
				minionPtr->Activate();
			}else{
				minionPtr->Activate(triggerCard);
			}
		}
	}
	ritualPtr=activePlayer->getRitual();
	if(ritualPtr){
		if(ritualPtr->getTrigger()==triggerType){
			if(triggerType==1 || triggerType==4){
				ritualPtr->Activate();
			}else{
				ritualPtr->Activate(triggerCard);
			}
		}
	}

// Non-active Player
	for(int m=1; m<=5; ++m){
		minionPtr=nonActivePlayer->getMinion(m);
		if(!minionPtr){break;}
		if(minionPtr->getTrigger()=triggerType){
			if(triggerType==1 || triggerType==4){
				minionPtr->Activate();
			}else{
				minionPtr->Activate(triggerCard);
			}
		}
	}
	ritualPtr=nonActivePlayer->getRitual();
	if(ritualPtr){
		if(ritualPtr->getTrigger()==triggerType){
			if(triggerType==1 || triggerType==4){
				ritualPtr->Activate();
			}else{
				ritualPtr->Activate(triggerCard);
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

