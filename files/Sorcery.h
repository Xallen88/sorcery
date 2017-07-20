#ifndef _SORCERY_H_
#define _SORCERY_H_
#include <string>
#include "Player.h"

using std::string;

extern bool testing = false;

string read();
// reads from initFile if an initFile was specified and has not
// been exhausted. Otherwise reads from stdin

extern void printError(string err);
// prints an error message and handles any other error related issues

void printBoard();
// prints the entire board

void printHelp();
// displays all commands available when help command is invoked

void inspectMinon(int m, Player* p);
// inspect minion #m of player p

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


#endif
