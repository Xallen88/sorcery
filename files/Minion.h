#ifndef MINION_H
#define MINION_H


Class Minion {
  int atk;
  int hp;
  int maxHp;
 public:
  Minion(int a, int d);
  ~Minion() override;
  void Play() override;
  void Activate() override;
  void Activate(Card *target) override;
  void Attack(Card *c);
  void Attack(Player *p);
};



#endif
