#ifndef MINION_H
#define MINION_H


Class Minion : public Card {
  //Attributes
  int curAtk;
  int curHp;
  int maxHp;
  int maxAtk;
  //Enchantments;
  vector <Enchantment *> enchantments;
  int numEnch;
  
 public:
  Minion(std::string name, int a, int d);
  ~Minion() override;
  
  void Play() override;
  void Activate() override;
  void Activate(Card *target) override;
  void Attack(Card *c);
  void Attack(Player *p);
  void decrementLife(int i = 1);
  void incrementLife(int i = 1);
  bool isDead();
  
  
  void addEnchant(Enchantment *e);
  void clearAllEnchants();
};



#endif
