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
#include "ascii_graphics.h"
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::stringstream;
using std::vector;
using std::ifstream;

using namespace std;

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
	deckFile1=deckFile2="decks/default.deck";

	for(int i=1; i<argc; ++i){			// needs serious error handling
		string strArg = argv[i];
		if(strArg=="-deck1"){
			++i;
			strArg=argv[i];
			deckFile1=strArg;
		}else if(strArg=="-deck2"){
			++i;
			strArg=argv[i];
			deckFile2=strArg;
		}else if(strArg=="-init"){
			++i;
			init=true;
			strArg=argv[i];
			initFileName=strArg;
		}else if(strArg=="-testing"){
			testing=true;
		}
	}

	if(init){initFile.open(initFileName);}

	// player names
	if(init){
		getline(initFile, name);
		playerOne.setName(name);
		getline(initFile, name);
		playerTwo.setName(name);
	}else{
		getline(cin, name);
		playerOne.setName(name);
		getline(cin, name);
		playerTwo.setName(name);
	}
	// deck construction
	playerOne.constructDeck(deckFile1);
	activePlayer=&playerTwo;
	playerTwo.constructDeck(deckFile2);	
	activePlayer=&playerOne;
	if(!testing){
		playerOne.shuffleDeck();
		playerTwo.shuffleDeck();
	}
	for(int i=0;i<4;++i){
		playerOne.drawCard();
		playerTwo.drawCard();
	}

	// read input or initfile until EOF or quit
	string commandLine;	
	while(!gameover){

	 if (init){
	  getline(initFile, commandLine);
	  if (!initFile.good()) {
	   init = false;
	   getline(cin, commandLine);
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
			endTurn();
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
	vector <string> text = display_minion_no_ability("Spongebob", 3, 5, 5);
  	vector <string> text2 = display_minion_activated_ability("Patrick Star", 5, 3, 3, 5, "Burns Spongebob");
 	 vector <string> text3 = CENTRE_GRAPHIC;// prints sorcery in middle 
	  //variable for first line of player
	  vector <vector<string>> field;
  	//Check if it has a ritual otherwise use the empty one
 	 vector <string> ritual = CARD_TEMPLATE_BORDER;
 	 field.emplace_back(ritual);
 	 field.emplace_back(CARD_TEMPLATE_EMPTY);
 	 field.emplace_back(display_player_card(1, "Sean", 20, 0));
	  field.emplace_back(CARD_TEMPLATE_EMPTY);
	  field.emplace_back(text);
 	 //prints out minion field
 	 vector<vector<string>> minions;
	  minions.emplace_back(text);
	  minions.emplace_back(text);
 	 //if there isnt enough minions on the field, make an empty template
 	 minions.emplace_back(CARD_TEMPLATE_EMPTY);
 	 minions.emplace_back(CARD_TEMPLATE_EMPTY);
 	 minions.emplace_back(CARD_TEMPLATE_EMPTY);
  	//Prints out top of Sorcery
  	cout << EXTERNAL_BORDER_CHAR_TOP_LEFT;
 	for (int k = 0; k < 165; k++)  cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
 	cout << EXTERNAL_BORDER_CHAR_TOP_RIGHT << endl;
 	//printing first ine 
 	for (unsigned int k = 0; k < field[0].size(); k++) {
 	 	cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
 	 	for (int j = 0; j < 5; j++) {
 	     		cout  << field[j][k];
    		}
		cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
 		cout << endl;
  	}
  	//printing minion line 
  	for (unsigned int k = 0; k < minions[0].size(); k++) {
    		cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
    		for (int j = 0; j < 5; j++) {
    	  		cout  << minions[j][k];
    		}
    		cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
    		cout << endl;
  	}
  	//printing sorcery
  	vector<string> sorceryLogo = CENTRE_GRAPHIC;
  	for (unsigned int k = 0; k < sorceryLogo.size(); k++) {
   		cout << sorceryLogo[k] << endl;
  	}
	//printing minion line 
  	for (unsigned int k = 0; k < minions[0].size(); k++) {
   		cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
    		for (int j = 0; j < 5; j++) {
      			cout  << minions[j][k];
   		 }
		cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
   		 cout << endl;
  	}
  	//printing first ine 
  	for (unsigned int k = 0; k < field[0].size(); k++) {
   		 cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
  		  for (int j = 0; j < 5; j++) {
  		  	cout  << field[j][k];
    		  }

   		 cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
  		 cout << endl;
 	 }
	//prints bottom border
 	 cout << EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;
  	for (int k = 0; k < 165; k++)  cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
 	 cout << EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT << endl;
}

void inspectMinion(int m, Player* p){
	//pulling variables out
	cout << p->numMinions() << endl;
	if(m > p->numMinions()){
		printError("Invalid minion number.");
		return;
	}
	Minion *min = p->getMinion(m);
	 Card *c = (Card *) min;
	 string name = c->getName();
	int cost = c->getCost();
	string desc = c->getDescription();
	 int atk = min->getAtk();
	int hp = min->getHp();
	//variables to use
	vector<vector<string>> print;
	vector<string> message;
	//Printing  minion
	 if (c->getTrigger() == 0)  message = display_minion_no_ability(name, cost, atk, hp);
	else if (c->getTrigger() == 5) message = display_minion_activated_ability(name,cost,atk,hp,min->getACost(), desc);
	else message = display_minion_triggered_ability(name, cost, atk, hp, desc);
	print.emplace_back(message);
	printSeries(print, 1);
	print.pop_back();
	//Printing Enchantments
	int num = min->getEnchNum();	
	for (int k = 0; k < num; k++) {
		vector<string> enchLines;
		Enchantment *e = min->getEnch(k);
		c = (Card *) e;
		name = c->getName();
		cost = c->getCost();
		desc = c->getDescription();
		int type = e->getEnchType();
		if (type == 0) {
			string atk(1,e->getAOp());
			string hp(1,e->getHOp());
			atk += to_string(e->getAVal());
			hp += to_string(e->getHVal());
			enchLines = display_enchantment_attack_defence(name, cost, desc, atk, hp);
		} else {
			enchLines = display_enchantment(name, cost, desc);
		}
		print.emplace_back(enchLines);
	}	
	printSeries(print, num);
}

extern void printSeries(vector<vector<string>> &v, int howmany) {
	int count = 0;     
	int rows = v[0].size();
	while (count < howmany) {
		int count = 0;
		for (int k = 0; k < rows; k++) {
			for (int j = count; j < count+5 && j < howmany; j++) {
				cout << v[j][k];
			}
			cout << endl;
		}
		count += 5;
	}
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

	for(int m=1; m<=activePlayer->numMinions(); ++m){
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
	for(int m=1; m<=nonActivePlayer->numMinions(); ++m){
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

void endTurn(){
	// end of turn trigger
	activateTrigger(4);

 // swap active and non-active player pointers
 if(activePlayer==&playerOne){
 	activePlayer=&playerTwo;
 	nonActivePlayer=&playerOne;
 }else{
 	activePlayer=&playerOne;
 	nonActivePlayer=&playerTwo;
 }

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
