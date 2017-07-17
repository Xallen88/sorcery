#ifndef _ENCHANTMENTS_H_
#define _ENCHANTMENTS_H_
#include "Card.h"
#include <string>

using namespace std;



class Enchantment : public Card {
  int atkVal;
  char atkOp;
  int hpVal;
  char HpOp;
 public:
  Enchantment(string name, int atkVal, int hpVal, char AtkOp, char HpOp);
  ~Enchantment();
  void Activate(Card *c) override;
  int getAVal();
  int getHVal();
  char getOp();



#endif
