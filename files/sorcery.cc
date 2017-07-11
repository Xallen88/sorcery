#include <string>
#include <iostream>
#include "sorcery.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

bool init = false;
ofstream initFile;

int turn = 0;
Player playerOne;
Player playerTwo;
Player* activePlayer;
Player* nonActivePlayer;

int main()
{

 return 0;
}

string read()
{
 string result;
 if (init){
  initFile >> result;
  if (initFile.good()) {
   cout << "Read '" << result << "' automatically from init file." << endl;
   return result;
  } else {
   init = false;
  }
 }
 cin >> result // change to read until good input
 return result;
}

takeTurn(Player player)
{
 ++turn;
 if (turn > 1){
  player.incrementHealth();
  player.drawCard();
 }
 activateTriggers(TriggerType::TURN_START);
 //unfinished
}
