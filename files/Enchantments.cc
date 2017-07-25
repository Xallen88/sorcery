#include <string>
#include "Enchantments.h"
#include "Minion.h"
#include "Sorcery.h"
#include "Player.h"
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

vector<string> enchList = {"Giant Strength", "Magic Fatigue", "Silence", "Mad Bomber"};


Enchantment::Enchantment(){}
Enchantment::Enchantment(string name) : Card(name){
  type = "Enchantment";
  stringstream ss;
  string line;
  string fileName = name;
  //Defaulting in the case that it is not a normal enchant
  atkVal = 0;
  hpVal = 0;
  costVal = 0;
  atkOp = '+';
  hpOp = '+';
  costOp = '+';

  if(activePlayer==&playerOne){
    owner=1;
  }else{
    owner=2;
  }

  int len = fileName.length();
  for (int i = 0; i < len; ++i) {
    if (fileName[i] == ' ') {
      fileName.erase(fileName.begin()+i);
      --i;
      --len;
    }
  }

  fileName = "enchantments/" + fileName + ".info";
  ifstream infoFile (fileName);
  getline(infoFile, line);
  ss.str(line);
  //Adding cost, atk, hp
  ss >> cost;
  ss >> enchType;
  if (enchType == 0) {
    ss >> atkVal >> hpVal >> atkOp >> hpOp;
  } else {//Only not normal Enchants have desc
    if (enchType == 1) {//Changing ability cost
      ss >> costVal >> costOp;
    }else if(enchType==3){
      ss >> targetable;
    }
    getline(ss, description);
    // feed remaining line into description
  }
  infoFile.close();
}
Enchantment::~Enchantment() {}
int Enchantment::getAVal() { return atkVal; }
int Enchantment::getHVal() { return hpVal; }
int Enchantment::getCVal() { return costVal; }
char Enchantment::getAOp() { return atkOp; }
char Enchantment::getHOp() { return hpOp; }
char Enchantment::getCOp() { return costOp; }
int Enchantment::getEnchType() { return enchType; }

void Enchantment::Activate(){
  if (name == "Mad Bomber") MadBomber();
}  
void Enchantment::Activate(Card *c) { 

}
void Enchantment::SilenceEnchantment(Card *c) {
  Minion *m = (Minion *) c;
  m->Silence();
}  
void Enchantment::MadBomber(){
  srand(time(0));
  int d=2;
  int activeMin = activePlayer->numMinions();
  int nonActMin = nonActivePlayer->numMinions();
  int range = 2 + activeMin + nonActMin;
  int target = rand() % range + 1;
  if(target==1){
    playerOne.decrementLife(d);
  }else if(target==2){
    playerTwo.decrementLife(d);
  }else if(target > 2 && target <= 2 + activeMin){
    activePlayer->getMinion(target-2)->decrementLife(d);
  }else{
    nonActivePlayer->getMinion(target-2-activeMin)->decrementLife(d);
  }
}

void Enchantment::Play(){
 //Does nothing -> needs target
}   

void Enchantment::Play(Card* c){
  if (c->getType() != "Minion"){
    printError("You cannot attach an enchatment to a ritual.");
    activePlayer->incrementMagic(getCost());
    return;//Checking if minion
  } 
  Minion *m = (Minion *) c;
  m->addEnchant(this);
}    
   
            
