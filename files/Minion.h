#ifndef MINION_H
#define MINION_H

#include <vector>
#include "Card.h"
#include "Enchantments.h"

class Player;

class Minion : public Card {
  //Attributes
  int curAtk;
  int curHp;
  int maxHp;
  int maxAtk;
  int base_atk;
  int base_hp;
  //Enchantments;
  vector <Enchantment *> enchantments;
  int numEnch;
  
  void applyChange(char op, char c, int val);
  
 public:
  Minion();
  Minion(std::string name);
  ~Minion() override;
  
  void Play() override;
  void Activate() override;
  void Activate(Card *target) override;
  void Attack(Minion* m);
  void Attack(Player *p);
  void decrementLife(int i = 1);
  void incrementLife(int i = 1);
  bool isDead();
  
  int getAtk();
  int getHp();
  
  void addEnchant(Enchantment *e);
  void clearAllEnchants();
};



#endif
