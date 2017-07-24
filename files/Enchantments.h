#ifndef _ENCHANTMENTS_H_
#define _ENCHANTMENTS_H_
#include "Card.h"
#include <string>
#include <vector>

using std::vector;

extern vector<string> enchList;

class Enchantment : public Card {
  int atkVal;  
  int hpVal;
  int costVal;
  char atkOp;
  char hpOp;
  char costOp;
  int enchType;
 public:
  Enchantment();
  Enchantment(string name);
  ~Enchantment();
  void Play() override;
  void Play(Card *c) override;
  void Activate() override;
  void Activate(Card *c) override;
  int getAVal();
  int getHVal();
  int getCVal();
  char getAOp();
  char getHOp();
  char getCOp();
};

#endif
