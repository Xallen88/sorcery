#ifndef MINION_H
#define MINION_H

#include <vector>
#include "Card.h"
#include "Enchantments.h"

extern vector<string> minionList;

class Player;

class Minion : public Card {
  //Attributes
  int curAtk;
  int curHp;
  int maxHp;
  int maxAtk;
  //Enchantments;
  vector <Enchantment *> enchantments;
  int numEnch;
  //Trigger ability cost
  int tCost;
  //Actions
  int actions;
  
  void applyChange(char op, char c, int val);
  //Will be covered by triggers
  void FireElemental(Card *c); 
  void PotionSeller();
  void NovicePyromancer(Card *c);
  void ApprenticeSummoner();
  void MasterSummoner();
  
 public:
  Minion();
  Minion(std::string name);
  ~Minion() override;
  
  void Play() override;
  void Play(Card *c) override;
  void Activate() override;
  void Activate(Card *target) override;
  void Attack(Minion* m);
  void Attack(Player *p);
  void incrementAtk(int i = 1);
  void decrementAtk(int i = 1);
  void decrementLife(int i = 1);
  void incrementLife(int i = 1);
  bool isDead();
  
  int getAtk();
  int getHp();
  
  void resetActions();
  bool hasActionLeft();
  void useAction();
    
  void addEnchant(Enchantment *e);
  void removeTopEnch();
  void clearAllEnchants();
};



#endif
