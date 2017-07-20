#ifndef _ENCHANTMENTS_H_
#define _ENCHANTMENTS_H_
#include "Card.h"
#include <string>

using namespace std;



class Enchantment : public Card {
  int atkVal;
  char atkOp;
  int hpVal;
  char hpOp;
 public:
  Enchantment(string name, int atkVal, int hpVal, char atkOp, char hpOp);
  ~Enchantment();
  void Activate(Card *c) override;
  int getAVal();
  int getHVal();
  char getAOp();
  char getHOp();
};

#endif
