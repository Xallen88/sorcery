#include <string>
#include "Enchantments.h"

vector<string> enchList = {"Giant Strength", "Magic Fatigue", "Silence"};

Enchantment::Enchantment(){}
Enchantment::Enchantment(string name) {

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

}   

void Enchantment::Play(Card* c){

}    

void Enchantment::Activate(){

}     
            
