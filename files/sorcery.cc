#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "sorcery.h"
#include "player.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::stringstream;

bool init = false;
ofstream initFile;

int turn = 0;
Player playerOne;
Player playerTwo;
Player* activePlayer = playerOne;
Player* nonActivePlayer = playerTwo;

int main(int argc, char* argv[])
{
	// take in command line args
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

