#ifndef “SORCERY.H”
#define “SORCERY.H”
#include <string>

using std::string;

extern bool testing = false;

string read();
// Reads from initFile if an initFile was specified and has not
// been exhausted. Otherwise reads from stdin

void takeTurn(Player player);

static void activateTrigger(TriggerType triggerType);
//Calls all

static vector<Card> shuffleDeck(vector<Card>);

#endif
