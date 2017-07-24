#include <string>
#include "Enchantments.h"
#include "Minion.h"
#include <sstream>
#include <fstream>

using namespace std;

vector<string> enchList = {"Giant Strength", "Magic Fatigue", "Silence"};


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
    }
    getline(ss, description);
    // feed remaining line into description
  }
}
Enchantment::~Enchantment() {}
int Enchantment::getAVal() { return atkVal; }
int Enchantment::getHVal() { return hpVal; }
int Enchantment::getCVal() { return costVal; }
char Enchantment::getAOp() { return atkOp; }
char Enchantment::getHOp() { return hpOp; }
char Enchantment::getCOp() { return costOp; }
int Enchantment::getEnchType() { return enchType; }
void Enchantment::Activate(Card *c) { 
  if (name == "Silence") SilenceEnchantment(c);
  Minion *m = (Minion *) c;
  m->addEnchant(this);
}
void Enchantment::SilenceEnchantment(Card *c) {
  Minion *m = (Minion *) c;
  m->Silence();
}                        
void Enchantment::Play(){
 //Does nothing -> needs target
}   

void Enchantment::Play(Card* c){
  if (c->getType() != "Minion") return;//Checking if minion
  Activate(c);
}    

void Enchantment::Activate(){

}     
            
