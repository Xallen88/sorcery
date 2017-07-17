#ifndef _ENCHANTMENTS_H_
#define _ENCHANTMENTS_H_
#include "Card.h"
#include <string>

using namespace std;



class Enchantment : public Card {
  int atkVal;
  int hpVal;
  char op;
 public:
  Enchantment(string name, int atkVal, int hpVal, char op);
  ~Enchantment();
  void Activate(Card *c) override;
  int getAVal();
  int getHVal();
  char getOp();



#endif
