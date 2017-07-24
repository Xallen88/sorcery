#include <string>
#include "Enchantments.h"
#include "Minion.h"
#include <sstream>
#include <fstream>

using namespace std;

vector<string> enchList = {"Giant Strength", "Magic Fatigue", "Silence"};


Enchantment::Enchantment(){}
Enchantment::Enchantment(string name) {
  type = "Enchantment";
  stringstream ss;
  string line;
  string fileName = name;
  //Defaulting in the case that it is not a normalEnch
  atkVal = 0;
  hpVal = 0;
  atkOp = '+';
  hpOp = '+';

  int len = fileName.length();
  for (int i = 0; i < len; ++i) {
    if (fileName[i] == ' ') {
      fileName.erase(i);
      --i;
      --len;
    }
  }

  fileName = "minions/" + fileName + ".info";
  ifstream infoFile (fileName);
  getline(infoFile, line);
  //Adding cost, atk, hp
  ss >> cost;
  ss >> normalEnch;
  if (normalEnch == 0) {
    ss >> atkVal >> hpVal >> atkOp >> hpOp; 
  } else {//Only not normal Enchants have desc
    getline(ss, description);	
    // feed remaining line into description
  }
}
Enchantment::~Enchantment() {}
int Enchantment::getAVal() { return atkVal; }
int Enchantment::getHVal() { return hpVal; }
char Enchantment::getAOp() { return atkOp; }
char Enchantment::getHOp() { return hpOp; }
void Enchantment::Activate(Card *c) { 
  //Making sure it is a Minion to enchant  
  if (type != "Minion") {
     //Display error message for using enchantment on a non-minion
     return;
  }
  //c->addEnchant(this);//not sure if this is * or & or none
  //Doing enchantment stats in the minion class
}
                         
void Enchantment::Play(){
 //Does nothing -> needs target
}   

void Enchantment::Play(Card* c){
  if (c->getType() != "Minion") return;
  Minion *m = (Minion *) c;
  m->addEnchant(this);
}    

void Enchantment::Activate(){

}     
            
