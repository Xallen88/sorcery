#ifndef “SORCERY.H”
#define “SORCERY.H”
#include <string>
#include <vector>

using std::string;
using std::vector;

extern bool testing = false;

string read();
// Reads from initFile if an initFile was specified and has not
// been exhausted. Otherwise reads from stdin

void takeTurn(Player player);
// Called for each turn and does the following:
// 	Increment magic (not turn 1)
// 	Draw a card (not turn 1)
// 	Activate beginning of phase triggers
// 	Accept input from player until end commend
// 	Activate end of phase triggers

static void activateTrigger(int triggerType);
//	Calls triggers for:
// 	1: beggining of turn
//  2: monster summon
//  3: spell use
//  4: end of turn

static vector<Card> shuffleDeck(vector<Card>);

#endif
