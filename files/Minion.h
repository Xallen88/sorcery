#ifndef MINION_H
#define MINION_H


Class Minion {
  int baseAtk;
  int baseHp;
  int curAtk;
  int curHp;
  int maxHp;
 public:
  Minion(int a, int d);
  ~Minion() override;
  void Play() override;
  void Activate() override;
  void Activate(Card *target) override;
  void Attack(Card *c);
  void Attack(Player *p);
  void decrementLife(int i = 1);
  void incrementLife(int i = 1);
};



#endif
