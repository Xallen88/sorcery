#ifndef _SORCERY_H_
#define _SORCERY_H_
#include <string>
#include <vector>
using std::string;

class Player;
class Card;

extern Player playerOne;
extern Player playerTwo;
extern Player* activePlayer;
extern Player* nonActivePlayer;
extern Card* triggerCard;

extern void printError(string err);
// prints an error message and handles any other error related issues

void printBoard();
// prints the entire board

void printHelp();
// displays all commands available when help command is invoked

void inspectMinion(int m, Player* p);
// inspect minion #m of player p


extern void printSeries(std::vector<std::vector<string>> &v, int howmany);
//prints the graphical interface

extern void activateTrigger(int triggerType);
//	calls triggers for:
// 	1: beggining of turn
//  2: monster summon
//  3: spell use
//  4: end of turn

void endTurn(Player *activePlayer, Player *nonActivePlayer);
// performs the following:
//  activates end of turn trigger
//  switches active and non-active player
//  increments active player magic
//  active player draws a card
//  activates start of turn trigger

extern void endGame(string name);
extern void endGame();


#endif
