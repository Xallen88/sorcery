#include <string>
#include "Enchantments.h"

using std::string;

Enchantment::Enchantment(string name, int atkVal, int hpVal, char atkOp, char hpOp): 
                                                                            Card(name), 
                                                                            atkVal(atkVal),
                                                                            hpVal(hpVal),
                                                                            atkOp(atkOp),
                                                                            hpOp(hpOp) {}
                                           

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
                         
                        
